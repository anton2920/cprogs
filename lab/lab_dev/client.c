#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <pthread.h>
#include <errno.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <poll.h>

#include <zconf.h>
#include <fcntl.h>
#include <signal.h>

#define handle_error(msg)   \
    do {                    \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

#define sizeof_buffer (4096)

#define DEFAULT_SMTP_PORT (25)
#define DEFAULT_POP3_PORT (110)

static char *usage_string = "usage: %s hostname:[port] [port]\n";

void read_and_write_possible_answer(int sin, int sout);

static char read_buffer[sizeof_buffer];
static int stash = 0;


void *get_messages(void *arg) {

    /* Initializing variables */
    auto char buffer[sizeof_buffer] = {};
    auto int sockfd = *((int *) arg);
    auto size_t n;

    /* Main part */
    for ( ;; ) {
        if ((n = read(sockfd, buffer, sizeof_buffer)) < 0) {
            handle_error("read");
        }

        *(buffer + n) = '\0';

        if (!stash) {
            putc('\r', stdout);
            fputs(buffer, stdout);
        }
        break;
    }

    /* Exitting */
    pthread_exit(0);
}

void *send_messages(void *arg) {

    /* Initializing variables */
    auto char buffer[sizeof_buffer] = {};

    /* Main part */
    for ( ;; ) {
        break;
    }

    /* Exiting */
    pthread_exit(0);
}

int main(int argc, char *argv[]) {

    /* Initializing variables */
    auto int sockfd;

    auto struct sockaddr_in serv_addr = {};
    auto struct hostent *server;

    auto char ip_string[0x14];

    /* VarCheck */
    if (argc < 2) {
        fprintf(stderr, usage_string, argv[0]);
        exit(0);
    }

    /* Main part */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        handle_error("socket");
    }

    server = gethostbyname(argv[1]);
    if (server == NULL) {
        handle_error("gethostbyname");
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(DEFAULT_SMTP_PORT);
    bcopy((char *) server->h_addr_list[0], (char *) &serv_addr.sin_addr.s_addr, server->h_length);

    /* Printing introductory strings */
    auto uint32_t human_readable_ip = ntohl(serv_addr.sin_addr.s_addr);
    sprintf(ip_string, "%u.%u.%u.%u", (human_readable_ip >> 24 & 0xFF), human_readable_ip >> 16 & 0x00FF,
            human_readable_ip >> 8 & 0x0000FF, human_readable_ip & 0x000000FF);
    printf("Trying %s...\n", ip_string);

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        handle_error("connect");
    }

    printf("Connected to %s (%s)\n", *(argv + 1), ip_string);
    fflush(stdout);


    /* Let's go with threads */
    auto pthread_t recv_t, send_t;

    if (pthread_create(&recv_t, NULL, get_messages, &sockfd)) {
        handle_error("pthread");
    }
    if (pthread_create(&send_t, NULL, send_messages, &sockfd)) {
        handle_error("pthread");
    }

    pthread_join(recv_t, 0);
    pthread_join(send_t, 0);

    /* Returning value */
    return 0;
}

void read_and_write_possible_answer(int sin, int sout) {

    /* Initializing variables */
    auto ssize_t n, total = 0;
    auto struct pollfd pfd = {sin, POLLIN, 0};

    /* Main part */
    for ( ;; ) {
        if (poll(&pfd, 1, 100) < 0) {
            handle_error("poll");
        }

        if (pfd.revents == POLLIN) {
            n = read(sin, read_buffer + total, sizeof_buffer);
            if (n < 0) {
                handle_error("read");
            } else if (n == 0) {
                break;
            }
            total += n;
        } else {
            break;
        }
    }

    *(read_buffer + total - 1) = '\0';

    if (total) {
        if (sout == 1) {
            putc('\r', stdout);
            puts(read_buffer);
            fflush(stdout);
        } else if (sout > 0) {
            if (write(sout, read_buffer, total) < 0) {
                handle_error("write");
            }
        }
    }
}