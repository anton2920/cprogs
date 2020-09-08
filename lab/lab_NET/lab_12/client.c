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

#define DEFAULT_FTP_PORT (21)

static char *usage_string = "usage: %s hostname:[port] [port]\n";
static char *help_string = "Commands are: \n"
                           "Directories:\tcd\tdir\tlcd\tls\tlpwd\tpwd\n"
                           "Files:\t\tget [-a|--all]\n"
                           "Help:\t\t?\thelp\n"
                           "Others:\t\tbye\tquit\traw\tuser\n";

enum modes {
    ascii,
    binary
};

int log_in(char *domain, int socket);
void read_and_write_possible_answer(int sin, int sout);
void active_mode(int *s, int sockfd, uint32_t ip, enum modes mode);
char *get_filename_ext(const char *filename);
enum modes get_mode_by_ext(const char *fn);

void send_command(int sockfd, uint32_t ip, char *cmd, enum modes mode, int sout);
void get_file(int sockfd, uint32_t ip, char *fn);
void list_dirs(int sockfd, uint32_t ip, char *arg, int sout);

static char read_buffer[sizeof_buffer];
static int stash = 0;

struct data {
    int socket;
    uint32_t ip;
};

void *get_messages(void *arg) {

    /* Initializing variables */
    auto char buffer[sizeof_buffer] = {};
    auto int sockfd = *((int *) arg);
    auto size_t n;
    auto char *prompt = "\rtftp$> ";

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

        if (!strcmp(buffer, "221 Goodbye.\r\n")) {
            break;
        }

        if (!stash) {
            fputs(prompt, stdout);
            fflush(stdout);
        }
    }

    /* Exitting */
    pthread_exit(0);
}

struct command {
    char cmd[0xA];
    char arg[sizeof_buffer];
};

void *send_messages(void *arg) {

    /* Initializing variables */
    auto char buffer[sizeof_buffer] = {};
    auto char path[sizeof_buffer] = {};
    auto char dir_name[sizeof_buffer] = {};
    auto struct command cmd;

    auto struct data *d = (struct data *) arg;
    auto int sockfd = d->socket;

    auto char *prompt = "\rtftp$> ";

    auto struct sockaddr_in cli_addr;
    auto unsigned int clilen = sizeof(cli_addr);

    /* Main part */
    signal(SIGCONT, exit);
    if (!d->ip) {
        if (getsockname(sockfd, (struct sockaddr *) &cli_addr, &clilen) < 0) {
            handle_error("getsockname");
        }

        d->ip = ntohl(cli_addr.sin_addr.s_addr);
    }

    for ( ;; ) {
        stash = 0;
        fputs(prompt, stdout);
        fflush(stdout);
        fgets(buffer, sizeof_buffer, stdin);

        memset(&cmd, 0, sizeof(cmd));
        sscanf(buffer, "%s %[^\n]", cmd.cmd, cmd.arg);

        if (!strcmp(cmd.cmd, "bye") || !strcmp(cmd.cmd, "quit") || *cmd.cmd == EOF) {
            write(sockfd, "quit\n", sizeof("quit\n"));
            break;
        }

        if (!strcmp(cmd.cmd, "ls") || !strcmp(cmd.cmd, "dir")) {\
            list_dirs(sockfd, d->ip, cmd.arg, 1);
        } else if (!strcmp(cmd.cmd, "?") || !strcmp(cmd.cmd, "help")) {
            fputs(help_string, stdout);
        } else if (!strcmp(cmd.cmd, "raw")) {
            sprintf(buffer, "%s\r\n", cmd.arg);
            if (write(sockfd, buffer, strlen(buffer)) < 0) {
                handle_error("write");
            }
        } else if (!strcmp(cmd.cmd, "cd")) {
            sprintf(buffer, "CWD %s\r\n", cmd.arg);
            if (write(sockfd, buffer, strlen(buffer)) < 0) {
                handle_error("write");
            }
        } else if (!strcmp(cmd.cmd, "lcd")) {
            if (chdir(cmd.arg) < 0) {
                sprintf(buffer, "Failed: %s\n", strerror(errno));
            } else {
                sprintf(buffer, "Successfully changed to %s\r\n", getcwd(path, sizeof(path)));
            }
            fputs(buffer, stdout);
        } else if (!strcmp(cmd.cmd, "pwd")) {
            if (write(sockfd, "PWD\r\n", strlen("PWD\r\n")) < 0) {
                handle_error("write");
            }
        } else if (!strcmp(cmd.cmd, "lpwd")) {
            sprintf(buffer, "%s\r\n", getcwd(path, sizeof(path)));
            fputs(buffer, stdout);
        } else if (!strcmp(cmd.cmd, "get")) {
            if (!strncmp(cmd.arg, "-a", strlen("-a")) || !strncmp(cmd.arg, "--all", strlen("--all"))) {
                auto char *line, *line_end;
                register int i;

                sscanf(cmd.arg, "%*s %s", dir_name);

                stash = 1;
                list_dirs(sockfd, d->ip, dir_name, -1);

                for (line = read_buffer, i = 0; line != (char *) 0x1; line = line_end + 1, ++i) {
                    line_end = strchr(line, '\n');
                    if (*line == 'd' || *line == 'l') {
                        --i;
                        continue;
                    }

                    sscanf(line, "%*s %*s %*s %*s %*s %*s %*s %*s %s", path);
                    if (strlen(dir_name)) {
                        sprintf(buffer, "%s/%s", dir_name, path);
                    } else {
                        sprintf(buffer, "%s", path);
                    }
                    get_file(sockfd, d->ip, buffer);
                }
                if (i) {
                    sprintf(buffer, "%d file%s %s successfully downloaded\r\n",
                            i, (i == 1) ? "" : "s", (i == 1) ? "was" : "were");
                    fputs(buffer, stdout);
                }
            } else {
                get_file(sockfd, d->ip, cmd.arg);
            }
        } else if (!strcmp(cmd.cmd, "user")) {
            stash = 1;
            fputs("(username) ", stdout);
            fflush(stdout);
            fgets(read_buffer, sizeof_buffer, stdin);

            *(read_buffer + strlen(read_buffer) - 1) = '\0';

            sprintf(buffer, "USER %s\r\n", read_buffer);
            if (write(sockfd, buffer, strlen(buffer)) < 0) {
                handle_error("write");
            }

            fputs("Password: ", stdout);
            fflush(stdout);
            fgets(read_buffer, sizeof_buffer, stdin);

            *(read_buffer + strlen(read_buffer) - 1) = '\0';

            sprintf(buffer, "PASS %s\r\n", read_buffer);
            if (write(sockfd, buffer, strlen(buffer)) < 0) {
                handle_error("write");
            }
        } else if (!*cmd.cmd) {
            continue;
        } else {
            fputs("Command not found!\r\n", stdout);
        }
    }

    /* Exiting */
    pthread_exit(0);
}

int main(int argc, char *argv[]) {

    /* Initializing variables */
    auto int sockfd, portno;

    auto struct sockaddr_in serv_addr = {};
    auto struct hostent *server;

    auto char ip_string[0x14], *colon, *err_ptr = NULL;

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

    /* Log in */
    if (log_in(*(argv + 1), sockfd) < 0) {
        handle_error("login");
    }

    /* Let's go with threads */
    auto struct data d = {sockfd, 0x0};
    auto pthread_t recv_t, send_t;

    if (pthread_create(&recv_t, NULL, get_messages, &sockfd)) {
        handle_error("pthread");
    }
    if (pthread_create(&send_t, NULL, send_messages, &d)) {
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

int log_in(char *domain, int socket) {

    /* Initializing variables */
    auto char write_buffer[sizeof_buffer];
    auto char *user_env = strdup(getenv("USER"));

    /* Main part */

    /* First time read without threads */
    read_and_write_possible_answer(socket, 1);

    /* Perform log in sequence (USER, PASS) */
    sprintf(write_buffer, "Name (%s:%s): ", domain, user_env);
    if (write(1, write_buffer, strlen(write_buffer)) < 0) {
        handle_error("write");
    }

    fgets(read_buffer, sizeof_buffer, stdin);

    if (*(read_buffer) == '\n') {
        sprintf(write_buffer, "USER %s\r\n", user_env);
    } else {
        sprintf(write_buffer, "USER %s", read_buffer);
    }
    write(socket, write_buffer, strlen(write_buffer));
    free(user_env);

    /* Read answer */
    read_and_write_possible_answer(socket, 1);

    fputs("Password: ", stdout);
    fgets(read_buffer, sizeof_buffer, stdin);
    sprintf(write_buffer, "PASS %s", read_buffer);
    write(socket, write_buffer, strlen(write_buffer));

    /* Read answer */
    read_and_write_possible_answer(socket, 1);

    /* Returning value */
    return EXIT_SUCCESS;
}

void active_mode(int *s, int sockfd, uint32_t ip, enum modes mode) {

    /* Initializing variables */
    auto char buffer[sizeof_buffer] = {};
    auto struct sockaddr_in serv_addr = {};
    auto unsigned short port;

    /* Main part */
    port = (rand() % (1 << 16) - 1025 + 1) + 1025;
    if (port <= 1024) {
        port = 1800;
    }
    sprintf(buffer, "PORT %u,%u,%u,%u,%d,%d\r\n", ip >> 24 & 0xFF,
            ip >> 16 & 0x00FF, ip >> 8 & 0x0000FF,
            ip & 0x000000FF, port / (1 << 8), port % (1 << 8));
    if (write(sockfd, buffer, strlen(buffer)) < 0) {
        handle_error("write");
    }

    if (mode == ascii) {
        if (write(sockfd, "TYPE A\r\n", strlen("TYPE A\r\n")) < 0) {
            handle_error("write");
        }
    } else if (mode == binary) {
        if (write(sockfd, "TYPE I\r\n", strlen("TYPE I\r\n")) < 0) {
            handle_error("write");
        }
    }

    *s = socket(AF_INET, SOCK_STREAM, 0);
    if (*s < 0) {
        handle_error("socket");
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    if (bind(*s, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        handle_error("bind");
    }

    if (listen(*s, 1) < 0) {
        handle_error("listen");
    }
}

char *get_filename_ext(const char *filename) {

    /* Initializing variables */
    auto char *dot = strrchr(filename, '.');

    /* Main part */
    if (!dot || dot == filename) {
        return "";
    }

    /* Returning value */
    return dot + 1;
}

enum modes get_mode_by_ext(const char *fn) {

    /* Initializing variables */
    auto char *ext = get_filename_ext(fn);

    /* Main part */
    if (!strcmp(ext, "txt") || !strcmp(ext, "html")) {
        return ascii;
    } else {
        return binary;
    }
}

void send_command(int sockfd, uint32_t ip, char *cmd, enum modes mode, int sout) {

    /* Initializing variables */
    auto int s, ns;
    auto char buffer[sizeof_buffer];

    auto struct sockaddr_in cli_addr;
    auto unsigned int clilen = sizeof(cli_addr);

    /* Main part */
    active_mode(&s, sockfd, ip, mode);

    sprintf(buffer, "%s\r\n", cmd);
    if (write(sockfd, buffer, strlen(buffer)) < 0) {
        handle_error("write");
    }

    if ((ns = accept(s, (struct sockaddr *) &cli_addr, &clilen)) < 0) {
        handle_error("accept");
    }

    close(s);
    read_and_write_possible_answer(ns, sout);
    close(ns);
}

void get_file(int sockfd, uint32_t ip, char *fn) {

    /* Initializing varaibles */
    auto int file;
    auto char *file_name;
    auto char buffer[sizeof_buffer];

    /* Main part */
    if ((file_name = strrchr(fn, '/')) == NULL) {
        file_name = fn;
    } else {
        ++file_name;
    }

    if ((file = creat(file_name, 0644)) < 0) {
        handle_error("creat");
    }

    sprintf(buffer, "RETR %s\r\n", fn);
    send_command(sockfd, ip, buffer, get_mode_by_ext(fn), file);
    close(file);
}

void list_dirs(int sockfd, uint32_t ip, char *arg, int sout) {

    /* Initializing variables */
    auto char buffer[sizeof_buffer];

    /* Main part */
    sprintf(buffer, "LIST %s", arg);
    send_command(sockfd, ip, buffer, ascii, sout);
}