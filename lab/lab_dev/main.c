#include <stdio.h>
#include <omp.h>

main() {

#pragma omp parallel
{

    auto int id = omp_get_thread_num();
    printf("Hello (%d), ", id);
    printf("world (%d)!\n", id);
}
}