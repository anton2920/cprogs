#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/ioctl.h>

/* Essential include */
#include <libssh/libssh.h>

#include "libs/libs.h"

enum sizes {
    sizeof_buffer = 0xFFFF
};

/* If flag is set, than sh**t happened */
static int shit_flag = 0;

int interactive_shell_session(ssh_session session, ssh_channel channel) {

    /* Initializing variables */
    auto char buffer[sizeof_buffer];
    auto ssize_t nbytes, nwritten, nwritten_2 = 0, offset;
    auto int rc;

    rc = ssh_channel_request_pty(channel);
    if (rc != SSH_OK) return rc;

    rc = ssh_channel_request_shell(channel);
    if (rc != SSH_OK) return rc;

    while (ssh_channel_is_open(channel) && !ssh_channel_is_eof(channel)) {
        auto struct timeval timeout;
        auto ssh_channel in_channels[2], out_channels[2];
        auto fd_set fds;
        auto int maxfd;
        auto struct winsize size;

        ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

        rc = ssh_channel_change_pty_size(channel, size.ws_col, size.ws_row);
        if (rc != SSH_OK) return rc;

        timeout.tv_sec = 30;
        timeout.tv_usec = 0;
        in_channels[0] = channel;
        in_channels[1] = NULL;
        FD_ZERO(&fds);
        FD_SET(0, &fds);
        FD_SET(ssh_get_fd(session), &fds);
        maxfd = ssh_get_fd(session) + 1;

        ssh_select(in_channels, out_channels, maxfd, &fds, &timeout);

        if (out_channels[0] != NULL) {
            nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
            if (nbytes < 0) return SSH_ERROR;
            if (nbytes > 0) {
                offset = (nwritten_2) ? nwritten_2 + 1 : 0;
                nwritten = write(1, buffer + offset, nbytes - offset);
                if (nwritten != nbytes - offset) return SSH_ERROR;
                nwritten_2 = 0;
            }
        }

        if (FD_ISSET(0, &fds)) {
            nbytes = read(0, buffer, sizeof(buffer));
            if (nbytes < 0) return SSH_ERROR;
            if (nbytes > 0) {
                nwritten_2 = ssh_channel_write(channel, buffer, nbytes);
                if (nbytes != nwritten_2) return SSH_ERROR;
            }
        }
    }

    return rc;
}

int main(int argc, char *argv[]) {

    /* Initializing variables */
    auto ssh_session my_ssh_session = ssh_new();

    auto char *host = (argc >= 2) ? *(argv + 1) : "localhost";

    auto int verbosity = SSH_LOG_PROTOCOL;
    auto int port = 22;

    auto char *password;
    auto int rc;

    /* VarCheck */
    if (my_ssh_session == NULL) {
        handle_error("ssh_session");
    }

    /* Main part */
    ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, host);
    /* ssh_options_set(my_ssh_session, SSH_OPTIONS_LOG_VERBOSITY, &verbosity); */
    ssh_options_set(my_ssh_session, SSH_OPTIONS_PORT, &port);

    /* Connecting to server */
    rc = ssh_connect(my_ssh_session);
    if (rc != SSH_OK) {
        fprintf(stderr, "Error connecting to %s: %s\n", host,
                ssh_get_error(my_ssh_session));
        ssh_free(my_ssh_session);
        exit(-1);
    }

    /* Verify the server's identity */
    if (verify_knownhost(my_ssh_session) < 0) {
        ssh_disconnect(my_ssh_session);
        ssh_free(my_ssh_session);
        exit(-1);
    }

    /* Authenticate ourselves */
    password = getpass("Password: ");
    rc = ssh_userauth_password(my_ssh_session, NULL, password);
    if (rc != SSH_AUTH_SUCCESS) {
        fprintf(stderr, "Error authenticating with password: %s\n",
                ssh_get_error(my_ssh_session));
        ssh_disconnect(my_ssh_session);
        ssh_free(my_ssh_session);
        exit(-1);
    }
    printf("Tushuno SSH is connected to %s\n", host);

    if (argc <= 2) {
        auto ssh_channel channel = ssh_channel_new(my_ssh_session);
        if (channel == NULL) {
            fprintf(stderr, "Error with creating channel: %s\n",
                    ssh_get_error(my_ssh_session));
            ssh_disconnect(my_ssh_session);
            ssh_free(my_ssh_session);
            exit(EXIT_FAILURE);
        }

        if (ssh_channel_open_session(channel) != SSH_OK) {
            fprintf(stderr, "Error with opening session: %s\n",
                    ssh_get_error(my_ssh_session));
            ssh_channel_free(channel);
            ssh_disconnect(my_ssh_session);
            ssh_free(my_ssh_session);
            exit(EXIT_FAILURE);
        }

        rc = interactive_shell_session(my_ssh_session, channel);
        if (rc == SSH_OK) {
            printf("Connection to %s closed\n", host);
        }

        ssh_channel_send_eof(channel);
        ssh_channel_close(channel);
        ssh_channel_free(channel);
    } else if (!strcmp(*(argv + 2), "-f")) {
        rc = direct_forwarding(my_ssh_session, *(argv + 3),
                atoi(*(argv + 4)), atoi(*(argv + 5)));
    }

    ssh_disconnect(my_ssh_session);
    ssh_free(my_ssh_session);

    /* Returning value */
    return 0;
}