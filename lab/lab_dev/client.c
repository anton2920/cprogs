#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <poll.h>

#include <zconf.h>

#include <string.h>

#define handle_error(msg)   \
    do {                    \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

#define sizeof_buffer (4096)

#define DEFAULT_FTP_PORT (21)

static char *usage_string = "usage: %s hostname:[port] [port]\n";

int log_in(char *domain, int socket);
void read_and_write_possible_answer(int socket);
void active_mode(int *ns, int port);

struct data {
    int socket;
    uint32_t ip;
};

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

        putc('\r', stdout);
        fputs(buffer, stdout);
        fflush(stdout);

        if (!strcmp(buffer, "221 Goodbye.\r\n")) {
            break;
        }
    }

    /* Exitting */
    pthread_exit(0);
}

void *send_messages(void *arg) {

    /* Initializing variables */
    auto char buffer[sizeof_buffer] = {};

    auto struct data *d = (struct data *) arg;
    auto int sockfd = d->socket;
    d->ip = 0x1f849c07; /* 31.132.156.7 */

    auto char *prompt = "\rtftp$> ";

    auto int port, ns;

    /* Main part */
    for ( ;; ) {
        fputs(prompt, stdout);
        fflush(stdout);
        fgets(buffer, sizeof_buffer, stdin);

        if (!strcmp(buffer, "bye\n") || !strcmp(buffer, "quit\n")) {
            write(sockfd, "quit\n", sizeof("quit\n"));
            break;
        }

        if (!strcmp(buffer, "ls\n") || !strcmp(buffer, "dir\n")) {
            port = (rand() % (1 << 16) - 1025 + 1) + 1025;
            sprintf(buffer, "PORT %u,%u,%u,%u,%d,%d\n", d->ip >> 24 & 0xFF,
                    d->ip >> 16 & 0x00FF, d->ip >> 8 & 0x0000FF,
                    d->ip & 0x000000FF, port / (1 << 8), port % (1 << 8));
            write(sockfd, buffer, strlen(buffer));
            active_mode(&ns, port);
            fputs("200 PORT command successful\n", stdout);
            write(sockfd, "TYPE A\n", sizeof("TYPE A\n"));
            write(sockfd, "LIST\n", sizeof("LIST\n"));
            read_and_write_possible_answer(ns);
            fputs("226 Transfer complete", stdout);
            close(ns);
        }

        if (write(sockfd, buffer, strlen(buffer)) < 0) {
            handle_error("write");
        }
    }

    /* Exitting */
    pthread_exit(0);
}

int main(int argc, char *argv[]) {

    /* Initializing variables */
    auto int sockfd, portno;

    auto struct sockaddr_in serv_addr = {};
    auto struct hostent *server;

    auto char ip_string[0x14], *colon, *err_ptr = NULL, hostname[sizeof_buffer];

    /* VarCheck */
    if (argc < 2) {
        fprintf(stderr, usage_string, argv[0]);
        exit(0);
    }

    /* Main part */
    srand(time(NULL));

    /* Getting hostname and port */
    if ((colon = strchr(*(argv + 1), ':')) != NULL) {
        portno = (int) strtol(colon + 1, &err_ptr, 10);
        if (*(err_ptr) != '\0' || (err_ptr == colon + 1)) {
            fprintf(stderr, usage_string, argv[0]);
            exit(0);
        }
        *(colon) = '\0';
    } else {
        if (argc == 2) {
            portno = DEFAULT_FTP_PORT;
        } else if (argc == 3) {
            portno = (int) strtol(*(argv + 2), &err_ptr, 10);
            if (*(err_ptr) != '\0' || (err_ptr == colon + 1)) {
                fprintf(stderr, usage_string, argv[0]);
                exit(0);
            }
        }
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        handle_error("socket");
    }

    server = gethostbyname(argv[1]);
    if (server == NULL) {
        handle_error("gethostbyname");
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);

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

    /* Log in */
    if (log_in(*(argv + 1), sockfd) < 0) {
        handle_error("login");
    }

    /* Let's go with threads */
    auto pthread_t recv_t, send_t;
    auto struct data d = {sockfd, human_readable_ip};

    if (pthread_create(&recv_t, NULL, get_messages, &sockfd)) {
        handle_error("pthread");
    }
    if (pthread_create(&send_t, NULL, send_messages, &d)) {
        handle_error("pthread");
    }

    pthread_join(recv_t, 0);
    pthread_join(send_t, 0);

    /*send_messages(&sockfd);*/

    /* Returning value */
    return 0;
}

void read_and_write_possible_answer(int socket) {

    /* Initializing variables */
    auto ssize_t n = 0, total = 0;
    auto struct pollfd pfd = {socket, POLLIN, 0};
    auto char read_buffer[sizeof_buffer];

    /* Main part */
    for ( ;; ) {
        if (poll(&pfd, 1, 100) < 0) {
            handle_error("poll");
        }

        if (pfd.revents == POLLIN) {
            n = read(socket, read_buffer + total, sizeof_buffer);
            if (n < 0) {
                handle_error("read");
            }
            total += n;
        } else {
            break;
        }
    }

    *(read_buffer + total) = '\0';

    if (write(1, read_buffer, total) < 0) {
        handle_error("write");
    }
}

int log_in(char *domain, int socket) {

    /* Initializing variables */
    auto char write_buffer[sizeof_buffer];
    auto char read_buffer[sizeof_buffer];
    auto char *user_env = strdup(getenv("USER"));

    /* Main part */

    /* First time read without threads */
    read_and_write_possible_answer(socket);

    /* Perform log in sequence (USER, PASS) */
    sprintf(write_buffer, "Name (%s:%s): ", domain, user_env);
    if (write(1, write_buffer, strlen(write_buffer)) < 0) {
        handle_error("write");
    }

    fgets(read_buffer, sizeof_buffer, stdin);

    if (*(read_buffer) == '\n') {
        sprintf(write_buffer, "USER %s\n", user_env);
    } else {
        sprintf(write_buffer, "USER %s", read_buffer);
    }
    write(socket, write_buffer, strlen(write_buffer));
    free(user_env);

    /* Read answer */
    read_and_write_possible_answer(socket);

    fputs("Password: ", stdout);
    fgets(read_buffer, sizeof_buffer, stdin);
    sprintf(write_buffer, "PASS %s", read_buffer);
    write(socket, write_buffer, strlen(write_buffer));

    /* Read answer */
    read_and_write_possible_answer(socket);

    /* Returning value */
    return EXIT_SUCCESS;
}

void active_mode(int *ns, int port) {

    /* Initializing variables */
    auto int s;
    auto unsigned int clilen;
    auto struct sockaddr_in serv_addr = {}, cli_addr;

    /* Main part */
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        handle_error("socket");
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    if (bind(s, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        handle_error("bind");
    }

    listen(s, 1);
    clilen = sizeof(cli_addr);

    if ((*ns = accept(s, (struct sockaddr *) &cli_addr, &clilen)) < 0) {
        handle_error("accept");
    }

    close(s);
}