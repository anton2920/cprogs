#ifndef LAB_DEV_LIBS_H
#define LAB_DEV_LIBS_H

/* New data types */
enum thread_consts {
    RUN_SIZE = 50,
    MAX_SIZE = 17
};

struct thread_status {
    int *buffer; /* General storage */
    int *prod_percentage;
    int *cons_percentage;
    int *overall_percentage;
};

/* Functions' declarations */
void *draw_system(void *);

#endif
