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

static pthread_mutex_t read_m, write_m;
static pthread_cond_t read_cs, write_cs, comp_cs;

static char read_buffer[sizeof_buffer];
static char write_buffer[sizeof_buffer];

static int read_is_ready = 1;
static int write_is_ready = 0;
static size_t nbytes = 0;

void handle_connections(int);
void init_pthread(void);
void prepare_answer(char *, char *);

void *get_messages(void *arg) {

    /* Initializing variables */
    auto int sockfd = *((int *) arg);

    /* Main part */
    for ( ;; ) {
        pthread_mutex_lock(&read_m);
            if (!read_is_ready) {
                pthread_cond_wait(&read_cs, &read_m);
            }
            if ((nbytes = read(sockfd, read_buffer, sizeof_buffer)) < 0) {
                handle_error("read");
            }
            read_is_ready = 0;
            pthread_cond_signal(&comp_cs);
        pthread_mutex_unlock(&read_m);
    }

    /* Exitting */
    pthread_exit(0);
}

void *compose_messages(void *arg) {

    /* Main part */
    for ( ;; ) {
        pthread_mutex_lock(&read_m);
        pthread_mutex_lock(&write_m);

        if (read_is_ready) {
            pthread_cond_wait(&comp_cs, &read_m);
        }

        prepare_answer(read_buffer, write_buffer);

        read_is_ready = 1;
        pthread_mutex_unlock(&read_m);
        pthread_cond_signal(&read_cs);

        write_is_ready = 1;
        pthread_mutex_unlock(&write_m);
        pthread_cond_signal(&write_cs);
    }

    /* Exitting */
    pthread_exit(0);
}

void *send_messages(void *arg) {

    /* Initializing variables */
    auto int sockfd = *((int *) arg);
    auto size_t n;

    /* Main part */
    for ( ;; ) {
        pthread_mutex_lock(&write_m);
            if (!write_is_ready) {
                pthread_cond_wait(&write_cs, &write_m);
            }
            if (write(sockfd, write_buffer, nbytes) < 0) {
                handle_error("write");
            }
            write_is_ready = 0;
        pthread_mutex_unlock(&write_m);
    }

    /* Exitting */
    pthread_exit(0);
}

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

    init_pthread();

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

void init_pthread(void) {

    /* Main part */
    pthread_mutex_init(&read_m, NULL);
    pthread_mutex_init(&write_m, NULL);

    pthread_cond_init(&read_cs, NULL);
    pthread_cond_init(&write_cs, NULL);
    pthread_cond_init(&comp_cs, NULL);
}

void handle_connections(int socket) {

    /* Initialzing variables */
    auto size_t n;
    auto pthread_t get, send, compose;

    /* Main part */
    pthread_create(&get, NULL, get_messages, &socket);
    pthread_create(&compose, NULL, compose_messages, NULL);
    pthread_create(&send, NULL, send_messages, &socket);

    pthread_join(get, 0);
    pthread_join(compose, 0);
    pthread_join(send, 0);
}

void prepare_answer(char *rd, char *wr) {

    /* Initializing variables */

    /* Main part */
    memcpy(wr, rd, nbytes);
}