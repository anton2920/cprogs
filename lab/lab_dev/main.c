/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>

#include <zconf.h>

#define handle_error(msg)   \
    do {                    \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

#define sizeof_buffer (4096)

static char read_buffer[sizeof_buffer];
static char write_buffer[sizeof_buffer];

void handle_connections(int);
int prepare_answer(char *rd, size_t nbytes, char *wr);

int main(int argc, char *argv[]) {

    /* Initializing variables */
    auto int sockfd, newsockfd, portno;
    auto unsigned int clilen;
    auto struct sockaddr_in serv_addr = {}, cli_addr;
    auto pid_t pid;

    /* VarCheck */
    if (argc < 2) {
        fprintf(stderr, "tserver: no port provided\n");
        exit(1);
    }

    /* Main part */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        handle_error("socket");
    }

    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        handle_error("bind");
    }

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    for ( ;; ) {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) {
            handle_error("accept");
        }

        pid = fork();

        if (!pid) {
            close(sockfd);
            handle_connections(newsockfd);
            exit(0);
        } else {
            close(newsockfd);
        }
    }

    /* Returning value */
    return 0;
}

void handle_connections(int socket) {

    /* Initialzing variables */
    auto size_t n;
    auto pthread_t get, send, compose;

    /* Main part */
    for ( ;; ) {
        if ((n = read(socket, read_buffer, sizeof_buffer)) < 0) {
            handle_error("read");
        }

        n = prepare_answer(read_buffer, n, write_buffer);

        if (!memcmp(write_buffer, "disconnect\n", sizeof("disconnect\n"))) {
            if ((n = write(socket, "Bye!\n", sizeof("Bye!\n"))) < 0) {
                handle_error("write");
            }
            break;
        }

        if ((n = write(socket, write_buffer, n)) < 0) {
            handle_error("write");
        }
    }
}

int prepare_answer(char *rd, size_t nbytes, char *wr) {

    /* Initializing variables */
    auto size_t msg_size = nbytes;

    /* Main part */
    memcpy(wr, rd, nbytes);

    /* Returning value */
    return msg_size;
}