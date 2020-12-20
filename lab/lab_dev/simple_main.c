#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int error(const char *msg)
{
    perror(msg);
    MPI_Finalize();
    return -1;
}

size_t count_rows(int rank, size_t size, size_t w_size)
{
    int rest_rows = size;
    for (int i = 0; i < rank; i++)
        rest_rows -= rest_rows / (w_size - i);
    return rest_rows / (w_size - rank);
}

void print_proc_rows(double* rows, size_t nrows, int rank)
{
    printf("Rows for process %d :\n", rank);
    for (int i = 0; i < nrows; i++) {
        printf ("%3.3lf ", rows[i]);
    }
    printf ("\n");
}

void data_distribution(
        double *matrix, double *pProcRows,
        double *pVector, size_t size,
        int procNum, int rank)
{
    MPI_Bcast(pVector, size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    int *pSendNum = malloc(procNum * sizeof(int));
    int *pSendInd = malloc(procNum * sizeof(int));

    int restRows = size;
    int rowNum = (size / procNum);
    pSendNum[0] = rowNum * size;
    pSendInd[0] = 0;
    for (int i = 1; i < procNum; i++)
    {
        restRows -= rowNum;
        rowNum = restRows / (procNum - i);
        pSendNum[i] = rowNum * size;
        pSendInd[i] = pSendInd[i - 1] + pSendNum[i - 1];
    }

    MPI_Scatterv(
            matrix, pSendNum, pSendInd,
            MPI_DOUBLE, pProcRows, pSendNum[rank],
            MPI_DOUBLE, 0, MPI_COMM_WORLD);

    free(pSendNum);
    free(pSendInd);
}

void read_data(double* matrix, double* vector, size_t size)
{
    // read matrix
    FILE *file;
    int count = 0;
    file = fopen("/mirror/matrix.dat", "r");

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (!fscanf(file, "%lf", &matrix[i * size + j]))
                break;
            count++;
        }
    }
    // printf("Matrix element count: %d\n", count);
    fclose(file);

    // read vector
    file = fopen("/mirror/vector.dat", "r");
    count = 0;

    for (int j = 0; j < size; j++) {
        if (!fscanf(file, "%lf", &vector[j]))
            break;
        count++;
    }
    // printf("Vector element count: %d\n", count);
    fclose(file);
}

void print_data(double* matrix, double* vector, size_t size)
{
    printf("Matrix: \n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            printf ("%3.3lf ", matrix[i * size + j]);
        printf ("\n");
    }
    printf("Vector: \n");
    for (int i = 0; i < size; i++) {
        printf ("%3.3lf ", vector[i]);
    }
    printf ("\n");
}

void write_data(double *res, int size) {
    FILE *file = fopen("parallel.out", "w+");
    for (int j = 0; j < size; j++)
        fprintf(file, "%5.5lf ", res[j]);
    fclose(file);
}

void print_result(double* result, int size)
{
    printf("Result: \n");
    for (int i = 0; i < size; i++)
        printf ("%3.3lf ", result[i]);
    printf ("\n");
}

void parallelResultCalculation(
        double *pProcRows,
        double *pVector,
        double *pProcResult,
        size_t size,
        size_t rowNum)
{
    for (int i = 0; i < rowNum; i++)
    {
        pProcResult[i] = 0;
        for (int j = 0; j < size; j++)
            pProcResult[i] += pProcRows[i * size + j] * pVector[j];
    }
}

void resultReplication(
        double *pProcResult,
        double *pResult,
        size_t size,
        int procNum,
        int rank)
{
    int pReceiveNum[procNum];
    int pReceiveInd[procNum];
    int restRows = size;

    pReceiveInd[0] = 0;
    pReceiveNum[0] = size / procNum;

    for (int i = 1; i < procNum; i++) {
        restRows -= pReceiveNum[i - 1];
        pReceiveNum[i] = restRows / (procNum - i);
        pReceiveInd[i] = pReceiveInd[i - 1] + pReceiveNum[i - 1];
    }

    MPI_Allgatherv(
            pProcResult, pReceiveNum[rank],
            MPI_DOUBLE, pResult, pReceiveNum,
            pReceiveInd, MPI_DOUBLE,
            MPI_COMM_WORLD
    );
}


int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int world_size, rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double starttime, endtime, totaltime;
    if (argc < 2)
        return error ("[Error]: Data size is not provided!");
    if ((size = atoi(argv[1])) <= 0)
        return error ("[Error]: Incorrect data size!");

    double *matrix = malloc(size * size * sizeof(double)),
            *vector = malloc(size * sizeof(double));

    if (rank == 0)
    {
        read_data(matrix, vector, size);
        printf("Data read successful!\n");
    }

    int rows_n = count_rows(rank, size, world_size);
    printf("rows for process %d = %d \n", rows_n, rank);
    double *pProcRows = malloc(rows_n * size * sizeof(double));
    double *pProcResult = malloc(rows_n * sizeof(double));
    double *pResult = malloc(size * sizeof(double));

    starttime = MPI_Wtime();

    data_distribution(matrix, pProcRows, vector, size, world_size, rank);
    parallelResultCalculation(pProcRows, vector, pProcResult, size, rows_n);
    resultReplication(pProcResult, pResult, size, world_size, rank);

    endtime = MPI_Wtime();
    totaltime = endtime - starttime;

    if (rank == 0) {
        write_data(pResult, size);
        printf("Time taken (parallel calc): %.3lf sec\n", totaltime);
    }

    free(matrix); free(vector); free(pResult);
    free(pProcRows); free(pProcResult);
    MPI_Finalize();
}
