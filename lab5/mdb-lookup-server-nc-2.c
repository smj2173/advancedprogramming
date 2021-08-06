//mdb-lookup-server-nc-2.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

static void die(const char *s)
{
        perror(s);
        exit(1);
}

int main(int argc, char **argv){
        if (argc != 1){
                die("incorrect number of arguments");
                exit(1);
        }
        pid_t pid;

        while(1){
                while((pid = waitpid( (pid_t) -1, NULL, WNOHANG)) > 0){
                        fprintf(stderr, "[pid=%d] ", (int)pid);
                        fprintf(stderr, "mdb-lookup-server terminated\n");
                }
                printf("port number: ");
                char input[1000];
                input[0] = '\0';
                fgets(input, sizeof(input), stdin);
                if (input[0] == '\n' || input[0] == '\0'){
                        continue;
                }
                pid = fork();
                if (pid < 0)
                        die("fork failed");
                else if (pid == 0){
                        fprintf(stderr, "[pid=%d] ", (int)getpid());
                        fprintf(stderr, "mdb-lookup-server started on port %s", input);
                        execl("./mdb-lookup-server-nc.sh", "mdb-lookup-server-nc.sh", input, (char *)0);
                        die("execl failed");
                }
        }
        return 0;
}
