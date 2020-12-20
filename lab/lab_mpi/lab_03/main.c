#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <assert.h>

int error(const char *msg);
size_t count_rows(int rank, size_t size, size_t w_size);
void data_distribution(double *matrix, double *pProcRows, double *pVector, size_t size, int procNum, int rank);
void read_data(double *matrix, double *vector, size_t size);
void write_data(const double *res, size_t size);
void parallelResultCalculation(const double *pProcRows, const double *pVector, double *pProcResult, size_t size, size_t rowNum);
void resultReplication(double *pProcResult, double *pResult, size_t size, int procNum, int rank);
void print_data(const double *matrix, const double *vector, size_t size);
void print_result(const double *result, size_t size);

int main(int argc, char **argv)
{
    /* Initializing variables */
    int world_size;
    int rank;
    char *remainder;
    size_t size, nrows;
    double starttime, totaltime, endtime;
    double *matrix, *vector;
    double *pProcRows, *pProcResult, *pResult;

    /* MPI */
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /* VarCheck */
    if (argc < 2) {
        return error("message size is not provided");
    }

    if ((size = strtoul(*(argv + 1), &remainder, 10)) <= 0) {
        return error("incorrect data size");
    }

    /* Main part */
    matrix = calloc(size * size, sizeof(double)),
    vector = calloc(size, sizeof(double));

    if (!rank) {
        read_data(matrix, vector, size);
        printf("Data read successful!\n");
    }

    nrows = count_rows(rank, size, world_size);
    /*printf("rows to process %lu = %d \n", nrows, rank);*/
    pProcRows = malloc(nrows * size * sizeof(double));
    pProcResult = malloc(nrows * sizeof(double));
    pResult = malloc(size * sizeof(double));

    starttime = MPI_Wtime();

    data_distribution(matrix, pProcRows, vector, size, world_size, rank);
    parallelResultCalculation(pProcRows, vector, pProcResult, size, nrows);
    resultReplication(pProcResult, pResult, size, world_size, rank);

    endtime = MPI_Wtime();
    totaltime = endtime - starttime;

    if (!rank) {
        write_data(pResult, size);
        printf("Time taken (parallel calc): %.3lf sec\n", totaltime);
    }

    free(matrix);
    free(vector);
    free(pResult);
    free(pProcRows);
    free(pProcResult);

    MPI_Finalize();
}

int error(const char *msg)
{
    fprintf(stderr, "MPI error: %s\n", msg);
    MPI_Finalize();
    return -1;
}

size_t count_rows(int rank, size_t size, size_t w_size)
{
    /* Initializing variables */
    register size_t i;
    size_t nrows = size;

    /* Main part */
    for (i = 0; i < rank; ++i)
        nrows -= nrows / (w_size - i);
    return nrows / (w_size - rank);
}

void data_distribution(double *matrix, double *pProcRows, double *pVector, size_t size, int procNum, int rank)
{
    /* Initializing variables */
    register size_t i;
    int *pSendNum, *pSendInd;
    size_t restRows, rowNum;

    /* MPI */
    MPI_Bcast(pVector, size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    /* Main part */
    pSendNum = malloc(procNum * sizeof(int));
    pSendInd = malloc(procNum * sizeof(int));

    restRows = size;
    rowNum = (size / procNum);
    *pSendNum = (int) (rowNum * size);
    *pSendInd = 0;
    for (i = 1; i < procNum; ++i) {
        restRows -= rowNum;
        rowNum = restRows / (procNum - i);

        *(pSendNum + i) = (int) (rowNum * size);
        *(pSendInd + i) = *(pSendInd + i - 1) + *(pSendNum + i - 1);
    }

    MPI_Scatterv(matrix, pSendNum, pSendInd, MPI_DOUBLE, pProcRows, *(pSendNum + rank), MPI_DOUBLE, 0, MPI_COMM_WORLD);

    free(pSendNum);
    free(pSendInd);
}

void read_data(double *matrix, double *vector, size_t size)
{
    /* Initializing variables */
    register size_t i, j;
    FILE *file;

    file = fopen("/home/anton/C/lab/lab_dev/cmake-build-debug-mpi/matrix", "r");
    assert(file != NULL);

    for (i = 0; i < size && !feof(file); ++i) {
        for (j = 0; j < size && !feof(file); ++j) {
            fscanf(file, "%lf", matrix + (i * size + j));
        }
    }
    fclose(file);

    file = fopen("/home/anton/C/lab/lab_dev/cmake-build-debug-mpi/vector", "r");
    assert(file != NULL);

    for (j = 0; j < size && !feof(file); ++j) {
        fscanf(file, "%lf", vector + j);
    }
    fclose(file);
}

void write_data(const double *res, size_t size)
{
    /* Initializing variables */
    register size_t i;
    FILE *file = fopen("/home/anton/C/lab/lab_dev/cmake-build-debug-mpi/parallel.out", "w+");
    assert(file != NULL);

    /* Main part */
    for (i = 0; i < size; ++i) {
        fprintf(file, "%5.5lf ", *(res + i));
    }
    fclose(file);
}

void parallelResultCalculation(const double *pProcRows, const double *pVector, double *pProcResult, size_t size, size_t rowNum)
{
    /* Initializing variables */
    register size_t i, j;

    /* Main part */
    for (i = 0; i < rowNum; ++i) {
        *(pProcResult + i) = 0;
        for (j = 0; j < size; ++j) {
            *(pProcResult + i) += *(pProcRows + (i * size + j)) * *(pVector + j);
        }
    }
}

void resultReplication(double *pProcResult, double *pResult, size_t size, int procNum, int rank)
{
    /* Initializing variables */
    register size_t i;
    int pReceiveNum[procNum];
    int pReceiveInd[procNum];
    int restRows = size;

    *pReceiveInd = 0;
    *pReceiveNum = (int) (size / procNum);

    /* Main part */
    for (i = 1; i < procNum; i++) {
        restRows -= *(pReceiveNum + i - 1);
        *(pReceiveNum + i) = (int) (restRows / (procNum - i));
        *(pReceiveInd + i) = *(pReceiveInd + i - 1) + *(pReceiveNum + i - 1);
    }

    MPI_Allgatherv(pProcResult, *(pReceiveNum + rank), MPI_DOUBLE, pResult, pReceiveNum, pReceiveInd, MPI_DOUBLE, MPI_COMM_WORLD);
}

void print_data(const double *matrix, const double *vector, size_t size)
{
    /* Initializing variables */
    register size_t i, j;

    /* I/O flow */
    printf("Matrix: \n");

    /* Main part */
    for (i = 0; i < size; ++i) {
        for (j = 0; j < size; ++j) {
            printf("%3.3lf ", *(matrix + (i * size + j)));
        }
        printf("\n");
    }

    printf("Vector: \n");
    for (i = 0; i < size; ++i) {
        printf("%3.3lf ", *(vector + i));
    }

    /* Final output */
    printf("\n");
}

void print_result(const double *result, size_t size)
{
    /* Initializing variables */
    register size_t i;

    /* I/O flow */
    printf("Result: \n");

    /* Main part */
    for (i = 0; i < size; i++) {
        printf("%3.3lf ", result[i]);
    }

    /* Final output */
    printf("\n");
}
