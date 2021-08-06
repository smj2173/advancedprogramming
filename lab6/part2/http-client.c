//http-client

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

static void die(const char *message){
        perror(message);
        exit(1);
}

int main(int argc, char **argv){

        if (argc != 4){
                fprintf(stderr, "usage: %s <host> <port-number> <file-path>\n", argv[0]);
                exit(1);
        }
        char *serverName = argv[1];
        unsigned short port = atoi(argv[2]);
        char *path = argv[3];

        struct hostent *he;

        //get server ip from server name
        if ((he = gethostbyname(serverName)) == NULL)
                die("gethostbyname failed");

        char *serverIP = inet_ntoa(*(struct in_addr *)he->h_addr);

        int sock;
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
                die("socket failed");

        struct sockaddr_in servaddr;
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = inet_addr(serverIP);
        servaddr.sin_port = htons(port);

        //Establish a TCP connection to the server
        if (connect(sock, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
                die("connect failed");

        char buf[4096];

        char *mypath = strrchr(path, '/');
        mypath = mypath + 1;
        snprintf(buf, sizeof(buf), "GET %s HTTP/1.0\r\n""Host: %s:%d\r\n""\r\n", path, serverName, port);
        int len = strlen(buf);
        if (send(sock, buf, len, 0) != len)
                die("send failed");

        FILE *file = fdopen(sock, "r");
        if (file == NULL)
                die("fdopen failed");
        //first line!! :)
        if (fgets(buf, sizeof(buf), file) == NULL){
                die("server terminated");
        }
        if (strncmp("HTTP/1.0", &buf[0], 8) != 0 && strncmp("HTTP/1.1", &buf[0], 8) != 0){
                printf("%s", buf);
                exit(1);
                }
        if (strncmp("200", &buf[9], 3) != 0){
                printf("%s", buf);
                exit(1);
        } //exit program :))

        //skip file headers
        while(1){
                if (fgets(buf, sizeof(buf), file) == NULL){
                        die("fgets failed");
                }
                if(strcmp("\r\n", buf) == 0){
                        break;
                }
        }

        //read file contents
        //create file
        FILE *output = fopen(mypath, "w");
        if (output == NULL)
                die("couldn't open file");

        unsigned int n;

        while ((n = fread(buf, 1, sizeof(buf), file)) > 0) {
                if (fwrite(buf, 1, n, output) != n){
                        die("fwrite failed");
                }
        }
        if (ferror(file))
                die("fread failed");

        fclose(output);
        fclose(file);

        return 0;
                                                                                                                                                                             106,1-8       94%

  }
