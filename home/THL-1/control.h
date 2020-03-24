#ifndef THL_1_CONTROL_H
#define THL_1_CONTROL_H

/* Header inclusion */
#include <stdint.h>
#include <stdbool.h>

/* New data types */
enum CU_CONSTS {
    CONTROL_UNIT_SIZE = 0x11,
    HLT = 0,
    MI,
    RI,
    RO,
    II,
    IO,
    OI,
    EO,
    EC2,
    EC1,
    EC0,
    BI,
    AI,
    AO,
    CE,
    CO,
    JUMP
};

enum ISA {
    LDA = 0b0001,
    ADD = 0b0010,
    OUT = 0b1110
};

typedef struct cu {
    bool data[1 << 7][CONTROL_UNIT_SIZE];
    uint8_t counter;
} cu_t;

void microcode(cu_t *);

#endif
