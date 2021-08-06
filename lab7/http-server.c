//http-server

#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <netdb.h>
#include <stdio.h>

static void die(const char *s){
        perror(s);
        exit(1);
}

char *getReason(int status){
        if (status == 400)
                return "Bad Request";
        else if (status == 403)
                return "Forbidden";
        else if (status == 501)
                return "Not Implemented";
        else if (status == 404)
                return "Not Found";
        else
                return "OK";
}

static int myMdb(const char *host, unsigned short port){
        //code right from lab 6 solutions
        int sock;
        struct sockaddr_in serverAddr;
        struct hostent *he;
        if ((he = gethostbyname(host)) == NULL)
                die("gethostbyname failed");

        char *serverIP = inet_ntoa(*(struct in_addr *)he->h_addr);

        if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
                die("mdb socket failed");

        memset(&serverAddr, 0, sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = inet_addr(serverIP); //modify to IP
        serverAddr.sin_port = htons(port);

        if (connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0){
                die("connect failed");
        }
        return sock;
}

static void statusCode(int clientsock, int status, char *reason){
        char buf[1000];
        sprintf(buf, "HTTP/1.0 %d", status);
        strcat(buf, reason);
        strcat(buf, "\r\n");
        strcat(buf, "\r\n"); //again for blank line :)))

        if (status != 200){
                char new_buf[1000];
                sprintf(new_buf, "<html><body><h1>%d %s</h1><body></html>", status, reason);
                strcat(buf, new_buf);
        }

        if (send(clientsock, buf, strlen(buf), 0) < 0){
                die("send failed");
        }
}

static int processFile(char *requestURI, const char *webRoot, int clientsock){

        char buf[4096];
        size_t n;
        int status = 200;
        int len = strlen(requestURI);
        if (requestURI[len-1] == '/')
                strcat(requestURI, "index.html");
        char *output = malloc(strlen(requestURI) + strlen(webRoot) + 50); //extra memory to avoid memory errors
        if (output == NULL)
                die("malloc failed");
        strcat(output, webRoot);
        strcat(output, requestURI);

        struct stat stats;
        if (stat(output, &stats) == 0){
                if (S_ISDIR(stats.st_mode)){
                        statusCode(clientsock, 403, "Forbidden");
                        free(output);
                        return 403;
                }
        }
        FILE *fp = NULL;
        fp = fopen(output, "rb");
        if (fp == NULL){
                statusCode(clientsock, 404, "Not Found");
                free(output);
                return 404;
        }
        //assuming everything works here
        statusCode(clientsock, 200, "OK");

        while ((n = fread(buf, 1, sizeof(buf), fp)) > 0){
                if (send(clientsock, buf, n, 0) != n){
                        break;
               }
        }
        if (ferror(fp)){
                perror("fread failed");
        }
        free(output);
        if (fp){
                fclose(fp);
        }
        return status;
}

static int myLookup(char *requestURI, FILE *mdb, int clientsock, int sock){

        int code = 200;
        statusCode(clientsock, code, "OK");
        //send form regarless of whether requestURI is with key or not
        const char *form =
        "<h1>mdb-lookup</h1>\n"
        "<p>\n"
        "<form method=GET action=/mdb-lookup>\n"
        "lookup: <input type=text name=key>\n"
        "<input type=submit>\n"
        "</form>\n"
        "<p>\n";

        if (send(clientsock, form, strlen(form), 0) < 0){
                return 400; //bad request
        }
        char *table = NULL;
        char buf[1000];
        if (strncmp(requestURI, "/mdb-lookup?", strlen("/mdb-lookup?")) == 0){
                //build table
                table = "<p><table border>";
                char *newURI = requestURI + strlen("mdb-lookup?key=");
                if (send(sock, newURI, strlen(newURI), 0) < 0)
                        return 400; //bad request
                if (send(sock, "\n", strlen("\n"), 0) < 0)
                        return 400; //bad request
                if (send(clientsock, table, strlen(table), 0) < 0)
                        return 400;

                int row_number = 1;
                while(1){
                        if (fgets(buf, sizeof(buf), mdb) == NULL){
                                return 400; //bad request       
                        }
                        if (!(row_number % 2)){
                                if (send(clientsock, "\n<tr><td>", strlen("\n<tr><td>"), 0) < 0){
                                        perror("send failed");
                                        return code;
                                }
                        }
                      else{
                                char *row_2 = "\n<tr><td bgcolor=yellow>";
                                if (send(clientsock, row_2, strlen(row_2), 0) < 0){
                                        perror("send failed");
                                        return 400;
                                }
                        }
                        if (send(clientsock, buf, strlen(buf), 0) < 0){
                                perror("send failed");
                                return 400;
                        }
                        row_number++;
                }
                if (send(clientsock, "\n</table>", strlen("\n</table>"), 0) < 0){
                        perror("send failed");
                        return 400;
                        }
                char *end = "\n</body></html>\n";
                if (send(clientsock, end, strlen(end), 0) < 0){
                        perror("send failed");
                        return 400;
                }
        }
        return code;
}
int main(int argc, char *argv[]){
        if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
                die("signal failure");

        if (argc != 5){
                fprintf(stderr, "usage: %s <server_port> <web_root> <mdb-lookup-host> <mdb-lookup-port>", argv[0]);
                exit(1);
        }


        unsigned short server_port = atoi(argv[1]);
        const char *web_root = argv[2];
        const char *host = argv[3];
        unsigned short port = atoi(argv[4]);

        int sock = myMdb(host, port);

        //create listening sock for server
        int servsock;
        if ((servsock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
                die("socket failed");

        //construct local address structure
        struct sockaddr_in servaddr;
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port = htons(server_port);

        //bind to local address structure
        if (bind(servsock, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
                die("bind failed");

        if (listen(servsock, 5) < 0)
                die("listen failed");


        FILE *mdb;
        if ((mdb = fdopen(sock, "r")) == NULL){
                die("fdopen failed");
        }

        //back to server
        int clientsock;
        struct sockaddr_in clntaddr;
        char buf[1000];
        char new_buf[1000];
        int status = 199;
        status++; //need to "use" status otherwise error is produced

        //now: clientsock for server, not mdb
        while (1) {
                unsigned int clntlen = sizeof(clntaddr);
                if ((clientsock = accept(servsock, (struct sockaddr *) &clntaddr, &clntlen)) < 0){
                        die("accept failed");
                }
                FILE *fp;
                if ((fp = fdopen(clientsock, "r")) == NULL)
                        die("fdopen failed");


                if (fgets(buf, sizeof(buf), fp) == NULL){
                        status = 400;
                        fclose(fp);
                }
                char *token_separators = "\t \r\n"; //tab, space, new line
                char *method = strtok(buf, token_separators);
                char *requestURI = strtok(NULL, token_separators);
                char *httpVersion = strtok(NULL, token_separators);
                char *extras = strtok(NULL, token_separators);
                if (extras){
                        statusCode(clientsock, 501, "Not Implemented");
                        fprintf(stderr, "%s \"%s %s %s\" %d %s\n", inet_ntoa(clntaddr.sin_addr), method, requestURI, httpVersion, 501, "Not Implemented");
                        fclose(fp);
                }

                if (method == NULL || httpVersion == NULL || requestURI == NULL){
                        statusCode(clientsock, 501, "Not Implemented");
                        fprintf(stderr, "%s \"%s %s %s\" %d %s\n", inet_ntoa(clntaddr.sin_addr), method, requestURI, httpVersion, 501, "Not Implemented");
                        fclose(fp);
                }
                if (strcmp("GET", method) != 0){
                        statusCode(clientsock, 501, "Not Implemented");
                        fprintf(stderr, "%s \"%s %s %s\" %d %s\n", inet_ntoa(clntaddr.sin_addr), method, requestURI, httpVersion, 501, "Not Implemented");
                        fclose(fp);
                }
                if (strcmp("HTTP/1.0", httpVersion) != 0 && strcmp("HTTP/1.1", httpVersion) != 0){
                        statusCode(clientsock, 501, "Not Implemented");
                        fprintf(stderr, "%s \"%s %s %s\" %d %s\n", inet_ntoa(clntaddr.sin_addr), method, requestURI, httpVersion, 501, "Not Implemented");
                        fclose(fp);
                }

                if (requestURI[0] != '/' || requestURI == NULL){
                        statusCode(clientsock, 400, "Bad Request");
                        fprintf(stderr, "%s \"%s %s %s\" %d %s\n", inet_ntoa(clntaddr.sin_addr), method, requestURI, httpVersion, 400, "Bad Request");
                        fclose(fp);

                }
                if (strstr(requestURI, "/../") != NULL){
                        statusCode(clientsock, 400, "Bad Request");
                        fprintf(stderr, "%s \"%s %s %s\" %d %s\n", inet_ntoa(clntaddr.sin_addr), method, requestURI, httpVersion, 400, "Bad Request");
                        fclose(fp);
                }

                int len = strlen(requestURI);
                if (strstr(requestURI, "/..") && (requestURI[len-1] == '.') &&
                        (requestURI[len-2] == '.') && (requestURI[len-3] == '/')){
                        statusCode(clientsock, 400, "Bad Request");
                        fprintf(stderr, "%s \"%s %s %s\" %d %s\n", inet_ntoa(clntaddr.sin_addr), method, requestURI, httpVersion, 400, "Bad Request");
                        fclose(fp);
                }
                //skip headers (code from lab 6 solutions)
                while(1){
                        if (fgets(new_buf, sizeof(new_buf), fp) == NULL){
                                status = 400;
                                fclose(fp);
                        }
                        if (strcmp("\r\n", new_buf) == 0)
                                break;
             }
                if (strcmp(requestURI, "/mdb-lookup") == 0 || strncmp(requestURI, "/mdb-lookup?", strlen("/mdb-lookup?")) == 0){
                        status = myLookup(requestURI, mdb, clientsock, sock);
                        fprintf(stderr, "%s \"%s %s %s\" %d %s\n", inet_ntoa(clntaddr.sin_addr), method, requestURI, httpVersion, status, getReason(status));
                }
                else{
                        status = processFile(requestURI, web_root, clientsock);
                        fprintf(stderr, "%s \"%s %s %s\" %d %s\n", inet_ntoa(clntaddr.sin_addr), method, requestURI, httpVersion, status, getReason(status));

                }

                if (fp)
                        fclose(fp);
        }

        return 0;
        }

                                                                                                                                               
