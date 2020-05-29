#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define handle_error(msg)   \
    do {                    \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

main() {

    /* Initializing variables */
    auto key_t key;
    auto int shmid;
    auto char *buf;
    auto const int SIZE = 26;

    /* Main part */

    /* Generate unique identifier */
    if ((key = ftok("./lab_dev",01)) == -1) {
        handle_error("ftok");
    }

    /* Acquire System V shared memory segment */
    if ((shmid = shmget(key, SIZE, 0666)) == -1) {
        handle_error("shmget");
    }

    /* Attach created segment to our process' address space */
    if ((buf = shmat(shmid, NULL, 0)) == -1) {
        handle_error("shmat");
    }

    /* Final output */
    printf("%s\n", buf);

    /* Detach from memory */
    if (shmdt(buf) == -1) {
        handle_error("shmdt");
    }
}