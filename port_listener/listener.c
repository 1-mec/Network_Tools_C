#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/select.h>
#include <sys/time.h>

int scanning(const char * ip,int port,int timeout) {

    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0) return -1;

    int flag = fcntl(sd,F_GETFL,0);
    if (flag < 0 || fcntl(sd,F_SETFL, flag | O_NONBLOCK) < 0) {
        close(sd);
        return -1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (inet_pton(AF_INET,ip,&addr.sin_addr) != 1) {
        close(sd);
        return -1;
    }

    int connexion = connect(sd, (struct sockaddr *)&addr, sizeof(addr)) ;
    if (connexion == 0) {
        close(sd);
        return 1;
    }

    if (errno != EINPROGRESS) {
        close(sd);
        return 0;
    }

    fd_set test;
    FD_ZERO(&test);
    FD_SET(sd,&test);

    struct timeval tv ={  timeout / 1000 , (timeout % 100) * 1000};
    connexion = select(sd+1,NULL,&test,NULL,&tv);
    if (connexion <= 0) {
        close(sd);
        return 0;
    }

    int so_error = 0;
    socklen_t len = sizeof(so_error);
    if (getsockopt(sd,SOL_SOCKET,SO_ERROR,&so_error, &len) < 0) {
        close(sd);
        return -1;
    }

    close(sd);
    return so_error == 0 ? 1 : 0;
}

int main(int argc , char ** argv) {
    if (argc != 4) {
        printf("input are ip(char),start port(int),end port(int)\n");
        return 1;
    }

    const char * ip = argv[1];
    int start = atoi(argv[2]);
    int end = atoi(argv[3]);


    if (start < 1 || end > 65535 || start > end) {
        fprintf(stderr,"smt wrong with ports\n");
        return 1;
    }

    struct in_addr target;
    if (inet_pton(AF_INET,ip,&target) != 1) {
        fprintf(stderr,"smt wrong with ips\n");
        return 1;
    }

    printf("We're scanning\n");
    for (int i = start ; i <= end ; i++) {
        if (scanning(ip,i,500) == 1 )
            printf("port %d is opened\n",i);
    }

    return 0;
}