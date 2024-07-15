#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg){
    perror(msg);
    exit(1);
}

void receive_file(int socket, const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        error("File open error");
    }
    char buffer[1024];
    int n;
    while ((n = recv(socket, buffer, sizeof(buffer), 0)) > 0) {
        fwrite(buffer, 1, n, fp);
        if (n < sizeof(buffer)) {
            break;
        }
    }
    fclose(fp);
}

int main(int argc, char *argv[]){
    if (argc < 3) {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(1);
    }

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(1);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("Connection Failed");
    }

    printf("Enter the file name to download: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
    char request[256];
    sprintf(request, "GET %s", buffer);

    n = write(sockfd, request, strlen(request));
    if (n < 0) {
        error("Error on writing");
    }

    receive_file(sockfd, buffer);

    close(sockfd);
    return 0;
}
