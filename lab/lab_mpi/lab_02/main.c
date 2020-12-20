#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define NITER   300
#define MiB     (1024.0 * 1024.0)

#define BToKiB(_x)      ((_x) / 1024.)
#define SecToMcsec(_x)  ((_x) * 1000 * 1000)

void blocking_bandwidth(int rank, int nbytes);
void nonblocking_bandwidth(int rank, int msg_size);
void latency(int rank);
int error(const char *msg);

int main(int argc, char *argv[])
{
    /* Initializing variables */
    int world_size;
    int rank;
    char *remainder;
    size_t msg_size;

    /* MPI */
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /* VarCheck */
    if (argc < 2) {
        return error("message size is not provided!");
    }
    if (world_size != 2) {
        return error("at least 2 processes required");
    }

    msg_size = strtoul(*(argv + 1), &remainder, 10);
    if (msg_size <= 0)
        return error("incorrect message size!");

    if (!rank) {
        printf("Number of iterations:\t%d\n", NITER);
        printf("Message size:\t\t%.1lf KB\n\n", BToKiB(msg_size));
    }

    /* Main part */
    blocking_bandwidth(rank, msg_size);
    nonblocking_bandwidth(rank, msg_size);
    latency(rank);

    /* Finalizing */
    MPI_Finalize();
}

void blocking_bandwidth(int rank, int nbytes)
{
    /* Initializing variables */
    register int i;
    double startwtime, endwtime, totaltime, bandw;
    size_t arr_size;
    int *sendbuf, *recvbuf;

    arr_size = nbytes / sizeof(int);
    sendbuf = calloc(arr_size, sizeof(int));
    recvbuf = calloc(arr_size, sizeof(int));

    /* Main part */
    if (!rank) {
        startwtime = MPI_Wtime();
    }

    for (i = 0; i < NITER; ++i) {
        switch (rank) {
            case 0:
                MPI_Send(sendbuf, arr_size, MPI_INT, 1, 1, MPI_COMM_WORLD);
                MPI_Recv(recvbuf, arr_size, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                break;
            case 1:
                MPI_Recv(recvbuf, arr_size, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Send(sendbuf, arr_size, MPI_INT, 0, 1, MPI_COMM_WORLD);
                break;
            default:
                break;
        }
    }

    if (!rank) {
        endwtime = MPI_Wtime();
        totaltime = endwtime - startwtime;
        bandw = 2.0 * NITER * nbytes / (totaltime * MiB);
        printf("Blocking bandwidth:\t%.6f MB/s\n", bandw);
        printf("Total time:\t\t%.6lf seconds\n\n", totaltime);
    }

    free(sendbuf);
    free(recvbuf);
}

void nonblocking_bandwidth(int rank, int msg_size)
{
    /* Initializing variables */
    register int i;
    int otherproc = (rank + 1) % 2;
    int *sendbuf, *recvbuf;
    size_t arr_size;
    double startwtime, endwtime, totaltime, bandw;
    MPI_Request requests[2];

    arr_size = msg_size / sizeof(int);
    sendbuf = malloc(arr_size * sizeof(int));
    recvbuf = malloc(arr_size * sizeof(int));

    /* Main part */
    startwtime = MPI_Wtime();

    for (i = 0; i < NITER; ++i) {
        MPI_Isend(sendbuf, arr_size, MPI_INT, otherproc, 1, MPI_COMM_WORLD, requests);
        MPI_Irecv(recvbuf, arr_size, MPI_INT, otherproc, 1, MPI_COMM_WORLD, requests + 1);
        MPI_Waitall(2, requests, MPI_STATUSES_IGNORE);
    }

    if (!rank) {
        endwtime = MPI_Wtime();
        totaltime = endwtime - startwtime;
        bandw = 2.0 * NITER * msg_size / (totaltime * MiB);
        printf("Nonblocking bandwidth:\t%.3lf MiB/s\n", bandw);
        printf("Total time:\t\t%.6lf seconds\n\n", totaltime);
    }

    free(sendbuf);
    free(recvbuf);
}

void latency(int rank)
{
    /* Initializing variables */
    register int i;
    double startwtime, endwtime, totaltime;
    char sendmsg = 'k', recvmsg;

    /* Main part */
    startwtime = MPI_Wtime();

    for (i = 0; i < NITER; ++i) {
        switch (rank) {
            case 0:
                MPI_Send(&sendmsg, 1, MPI_CHAR, 1, 1, MPI_COMM_WORLD);
                MPI_Recv(&recvmsg, 1, MPI_CHAR, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                break;
            case 1:
                MPI_Recv(&recvmsg, 1, MPI_CHAR, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Send(&sendmsg, 1, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
                break;
            default:
                break;
        }
    }

    if (!rank) {
        endwtime = MPI_Wtime();
        totaltime = endwtime - startwtime;
        printf("Latency:\t\t%.6lf mcs\n", SecToMcsec(totaltime / (2.0 * NITER)));
    }
}

int error(const char *msg)
{
    fprintf(stderr, "MPI error: %s\n", msg);
    MPI_Finalize();
    return -1;
}
