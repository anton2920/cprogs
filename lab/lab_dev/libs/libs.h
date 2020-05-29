#ifndef LAB_DEV_LIBS_H
#define LAB_DEV_LIBS_H

/* Header inclusion */
#include <STL/STL_Queue.h>
#include "../process/process.h"

/* New data types */
enum QUEUE_CONSTS {
    NUM_OF_QS = 4,
    QUEUE_QUANT = 2
};

/* Functions' declarations */
void prt_ln(void);

void multiple_queues(void);
void round_robin(STL_Queue *process_q, process *average);

#endif