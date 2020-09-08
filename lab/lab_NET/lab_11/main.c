#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <time.h>
#include <signal.h>

#include <sys/socket.h>
#include <netinet/in.h>

#include <sys/mman.h>

#include <zconf.h>
#include <sys/fcntl.h>
#include <sys/stat.h>

#define handle_error(msg)   \
    do {                    \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

#define sizeof_buffer (4096)

static char buffer[sizeof_buffer];

void handle_connections(int);
int prepare_answer(char *rd, size_t nbytes, char *wr);
void sigpipe_handler(int);
char *get_filename_ext(const char *filename);

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
    signal(SIGPIPE, sigpipe_handler);
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

    for (;;) {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) {
            handle_error("accept");
        }

        pid = fork();

        if (!pid) {
            close(sockfd);
            handle_connections(newsockfd);
            exit(EXIT_SUCCESS);
        } else {
            close(newsockfd);
        }
    }

    /* Returning value */
    return 0;
}

enum sizes {
    sizeof_command = 0x10,
    sizeof_ver = 0xA
};

struct http {
    char command[sizeof_command];
    char uri[sizeof_buffer];
    char ver[sizeof_ver];
};

struct http message = {};

void to_lower_case(char *str) {

    /* Main part */
    while (*str) {
        if (isupper(*str)) {
            *str = tolower(*str);
        }
        ++str;
    }
}

void decompose() {

    /* Initializing variables */
    auto char *s = buffer;

    /* Main part */
    strcat(message.uri, "./");
    sscanf(s, "%s %s %s", message.command, message.uri + 2, message.ver);
    to_lower_case(message.command);

    if (*(message.uri + strlen(message.uri) - 1) == '/' && !strcmp(get_filename_ext(message.uri), "")) {
        strcat(message.uri, "/index.html");
    }
}

static char ok[sizeof_buffer];

int write_answer(char *response, char *content_type, size_t nbytes, int socket) {

    /* Initializing variables */
    auto time_t t = time(NULL);
    auto struct tm *date;

    /* Main part */
    date = localtime(&t);
    sprintf(ok, "\n%s %s\n"
                "Date: %s"
                "Server: Tushino Advanced HTTP Server\n"
                "Content-Type: %s\n"
                "Content-Length: %lu\n"
                "Connection: close\n"
                "\n",
            message.ver, response, asctime(date), content_type, nbytes);
    return write(socket, ok, strlen(ok));
}

char *get_filename_ext(const char *filename) {

    /* Initializing variables */
    char *dot = strrchr(filename, '.');

    /* Main part */
    if (!dot || dot == filename) {
        return "";
    }

    /* Returning value */
    return dot + 1;
}

void get_type_by_ext(char *buf) {

    /* Initializing variables */
    auto char *s = get_filename_ext(message.uri);

    /* Main part */
    if (!strcmp(s, "htm") || !strcmp(s, "html")) {
        strcpy(buf, "text/html");
    } else if (!strcmp(s, "txt")) {
        strcpy(buf, "text/plain");
    } else if (!strcmp(s, "css")) {
        strcpy(buf, "text/css");
    } else if (!strcmp(s, "js")) {
        strcpy(buf, "text/javascript");
    } else if (!strcmp(s, "jpg") || !strcmp(s, "jpeg")) {
        strcpy(buf, "image/jpeg");
    } else if (!strcmp(s, "png")) {
        strcpy(buf, "image/png");
    } else if (!strcmp(s, "gif")) {
        strcpy(buf, "image/gif");
    } else if (!strcmp(s, "wav")) {
        strcpy(buf, "audio/wav");
    } else if (!strcmp(s, "avi")) {
        strcpy(buf, "video/x-msvideo");
    } else {
        if (strlen(s) > 1) {
            strcat(buf, "application/");
            strcat(buf, s);
        } else {
            strcpy(buf, "application/unknown");
        }
    }
}

int write_file(int fd, char *response, int socket) {

    /* Initializing variables */
    auto char *file;
    auto struct stat st;
    auto int ans;
    auto char content_type[sizeof_buffer] = {};

    /* Main part */
    fstat(fd, &st);

    file = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (file == MAP_FAILED) {
        return MAP_FAILED;
    }
    get_type_by_ext(content_type);
    write_answer(response, content_type, st.st_size, socket);
    ans = write(socket, file, st.st_size);
    if (munmap(file, st.st_size) == -1) {
        ans = -1;
    }

    /* Returning value */
    return ans;
}

static int was_pipe = 0;

void handle_connections(int socket) {

    /* Initialzing variables */
    auto size_t n;
    auto int fd;

    /* Main part */
    was_pipe = 0;
    if ((n = read(socket, buffer, sizeof_buffer)) < 0) {
        handle_error("read");
    }

    if (was_pipe) {
        return;
    }

    *(buffer + n) = '\0';

    decompose();

    if (strlen(message.uri) > 50) {
        fd = open("responses/414.html", O_RDONLY, 0666);
        strcpy(message.uri, "responses/414.html");
        write_file(fd, "414 Request-URI Too Large", socket);
        close(fd);
    } else if (!strcmp(message.command, "get")) {
        fd = open(message.uri, O_RDONLY, 0666);
        if (strstr(message.uri, "responses")) {
            goto err_403;
        }
        if (fd < 0) {
            if (errno == ENOENT) {
                fd = open("responses/404.html", O_RDONLY, 0666);
                strcpy(message.uri, "responses/404.html");
                write_file(fd, "404 Not Found", socket);
                close(fd);
                return;
            } else if (errno == EACCES) {
                err_403:
                fd = open("responses/403.html", O_RDONLY, 0666);
                strcpy(message.uri, "responses/403.html");
                write_file(fd, "403 Forbidden", socket);
                close(fd);
                return;
            } else {
                fd = open("responses/418.html", O_RDONLY, 0666);
                strcpy(message.uri, "responses/418.html");
                write_file(fd, "418 I'm a teapot", socket);
                close(fd);
            }
        }
        if (write_file(fd, "200 OK", socket) == MAP_FAILED) {
            close(fd);
            fd = open("responses/400.html", O_RDONLY, 0666);
            strcpy(message.uri, "responses/400.html");
            write_file(fd, "400 Bad Request", socket);
        }
        close(fd);
    } else if (!strcmp(message.command, "disconnect")) {
        write(socket, "Bye!\n", sizeof("Bye!\n"));
        return;
    } else {
        fd = open("responses/501.html", O_RDONLY, 0666);
        strcpy(message.uri, "responses/501.html");
        write_file(fd, "501 Not Implemented", socket);
        close(fd);
    }
}

void sigpipe_handler(int arg) {

    /* Main part */
    was_pipe = 1;
}
