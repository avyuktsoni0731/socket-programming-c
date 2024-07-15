#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg){
    perror(msg);
    exit(1);
}

void send_file(int socket, const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        error("File open error");
    }
    char buffer[1024] = {0};
    int n;
    while ((n = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        if (send(socket, buffer, n, 0) < 0) {
            error("Error sending file");
        }
        memset(buffer, 0, sizeof(buffer));
    }
    fclose(fp);
}

int main(int argc, char *argv[]){
    if (argc < 2) {
        fprintf(stderr, "Port Number not provided. Program terminated\n");
        exit(1);
    }

    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("Error opening socket");
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("Binding Failed");
    }

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) {
        error("Error on accept");
    }

    while (1) {
        bzero(buffer, 256);
        int n = read(newsockfd, buffer, 255);
        if (n < 0) {
            error("Error on reading");
        }
        printf("Client: %s\n", buffer);
        if (strncmp(buffer, "GET ", 4) == 0) {
            char filename[256];
            sscanf(buffer + 4, "%s", filename);
            send_file(newsockfd, filename);
        } else if (strncmp(buffer, "Bye", 3) == 0) {
            break;
        }
    }

    close(newsockfd);
    close(sockfd);
    return 0;
}
