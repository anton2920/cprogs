#ifndef THL_1_ALU_H
#define THL_1_ALU_H

/* Header inclusion */
#include <stdint.h>
#include "register.h"

/* New data types */
enum ALU_CTRL {
    ALU_AND = 0x00,
    ALU_OR = 0x01,
    ALU_ADD = 0x02,
    ALU_Not_Used = 0x03,
    ALU_AND_NOT = 0x04,
    ALU_OR_NOT = 0x05,
    ALU_SUB = 0x06,
    ALU_LESS = 0x07,
    ALU_CONTROL_SIZE = 0x03
};

typedef struct ALU {
    bool ctrl[ALU_CONTROL_SIZE];
    reg_t *a, *b;
    bool OE;
} alu_t;

#endif
