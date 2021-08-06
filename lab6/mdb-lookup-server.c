//mdb-lookup-server.c

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "mylist.h"
#include "mdb.h"

#define KeyMax 5

static void die(const char *s){
        perror(s);
        exit(1);
}

void lookup(int clientsock, char *filename){

        char output[1000];
        FILE *fp = fopen(filename, "rb");
        if (fp == NULL)
                die(filename);

        FILE *client = fdopen(clientsock, "r");
        if (client == NULL)
                die("fdopen failed");

        struct List list;
        initList(&list);

        //code from my lab4 submission bc can't use loadmdb
        struct MdbRec x;
        struct Node *node = NULL;

        while (fread(&x, sizeof(x), 1, fp) != 0){
                struct MdbRec *new = (struct MdbRec *)malloc(sizeof(x));
                if (new == NULL){
                        die("malloc error");
                        exit(1);
                }
                memcpy(new, &x, sizeof(x));
                node = addAfter(&list, node, new);
                if (node == NULL){
                        die("addAfter error");
                }
        }
       if (ferror(fp))
                die(filename);

        fclose(fp);


        char line[1000];
        char key[KeyMax + 1];
        int out;
        int sender;
        unsigned int n;

        while (fgets(line, sizeof(line), client) != NULL){
                strncpy(key, line, sizeof(key) -1);
                key[sizeof(key) -1] = '\0';

                size_t last = strlen(key) -1;
                if (key[last] == '\n')
                        key[last] = '\0';

                struct Node *node = list.head;
                int recNo = 1;
                while (node) {
                        struct MdbRec *rec = (struct MdbRec *)node->data;
                        if (strstr(rec->name, key) || strstr(rec->msg, key)) {
                                sender = sprintf(output, "%4d: {%s} said {%s}\n", recNo, rec->name, rec->msg);
                                if ((n = send(clientsock, output, sender, 0)) != sender){
                                        die("send failed");
                                        break;
                        }
                        }

                        node = node->next;
                        recNo++;
                }

                //check if send failed
                out  = sprintf(output, "\n");
                if ((n = send(clientsock, output, out, 0)) != out)
                        die("send failed");
        }
        if (ferror(client))
                die("fgets failed");

        traverseList(&list, &free);
        removeAllNodes(&list);
        fclose(client);
}

int main(int argc, char **argv){
        //ignore SIGPIPE so that we don't terminate when we call
        //send() on a disconnected socket.
        if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
                die("signal() failed");

        if (argc != 3) {
                fprintf(stderr, "%s usage: mdb-lookup-server <database_file> <port_number>\n", argv[0]);
                exit(1);
        }

        unsigned short port = atoi(argv[2]);

        char *filename = argv[1];
        FILE *fp = fopen(filename, "rb");
        if (fp == NULL)
                die(filename);

        int servsock;
        if ((servsock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
                die("socket failed");

        struct sockaddr_in servaddr;
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port = htons(port);

        //bind
        if (bind(servsock, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
                die("bind failed");

        if (listen(servsock, 5) < 0)
                die("listen failed");


        int clientsock;
        socklen_t clientlen;
        struct sockaddr_in clientaddr;

        while(1) {

                clientlen = sizeof(servaddr);

                if ((clientsock = accept(servsock, (struct sockaddr *) &clientaddr, &clientlen)) < 0)
                        die("accept() failed");
                fprintf(stderr, "client started: %s\n", inet_ntoa(clientaddr.sin_addr));

                lookup(clientsock, filename);

                fprintf(stderr, "client terminated: %s\n", inet_ntoa(clientaddr.sin_addr));
        }
        return 0;
  
}
                                                                       
