#include <stddef.h>
#include "register.h"
#include "ram.h"
#include "control.h"
#include "alu.h"
#include "pc.h"

int main() {

    /* Initializing variables */
    uint8_t bus = 0;

    reg_t a = {}, b = {}, out = {}, ma = {}, ir = {};
    ram_t ram = {};
    cu_t cu = {};
    alu_t alu = {};
    pc_t pc = {};

    alu.a = &a;
    alu.b = &b;

    b.OE = false;

    ma.OE = true;
    ma.RWB = false;

    out.OE = true;

    bool clock = false;
    cu.counter = 0x0;

    bool opt_flag = false;

    uint8_t cu_index;

    bool *ctrl_map[CONTROL_UNIT_SIZE] = {NULL, &ma.RWB, &ram.RWB, &ram.OE, &ir.RWB, &ir.OE, &out.RWB,
                                         &alu.OE, alu.ctrl + 2, alu.ctrl + 1, alu.ctrl, &b.RWB, &a.RWB, &a.OE, &pc.CE, &pc.CO, &pc.J};

    /* Main part */
    microcode(&cu);
    ram.data[0x00] = (LDA << 4) + 0b1010;
    ram.data[0x01] = OUT << 4;
    ram.data[0x0A] = 0xAA;

    for ( ; pc.data != 0x0F ; clock = !clock, bus = 0) {
        cu_index = ((ir.data & 0xF0) >> 1) + cu.counter;

        /* Set up control pins */
        if (!clock) {
            opt_flag = false;
            for (int i = 0; i < CONTROL_UNIT_SIZE; ++i) {
                if (ctrl_map[i] != NULL) {
                    *ctrl_map[i] = cu.data[cu_index][i];
                    opt_flag |= cu.data[cu_index][i];
                }
            }
        } else {
            if (!opt_flag) {
                cu.counter = (cu.counter + 1) % 5;
                continue;
            }
            /* Write to BUS */
            if (ram.OE && !ram.RWB) {
                bus = ram.data[ma.data & 0x0F];
                goto bus_read;
            }
            if (ir.OE && !ir.RWB) {
                bus = ir.data & 0x0F;
                goto bus_read;
            }
            if (alu.OE) {
                switch ((alu.ctrl[2] << 2) | (alu.ctrl[1] << 1) | alu.ctrl[0]) {
                    case ALU_AND:
                        bus = alu.a->data & alu.b->data;
                        break;
                    case ALU_OR :
                        bus = alu.a->data | alu.b->data;
                        break;
                    case ALU_ADD:
                        bus = alu.a->data + alu.b->data;
                        break;
                    case ALU_AND_NOT:
                        bus = alu.a->data & ~alu.b->data;
                        break;
                    case ALU_OR_NOT:
                        bus = alu.a->data | ~alu.b->data;
                        break;
                    case ALU_SUB:
                        bus = alu.a->data - alu.b->data;
                        break;
                    case ALU_LESS:
                        bus = alu.a->data < alu.b->data ? 1 : 0;
                        break;
                    default:
                        break;
                }
                goto bus_read;
            }
            if (a.OE && !a.RWB) {
                bus = a.data;
                goto bus_read;
            }
            if (pc.CO && !pc.J) {
                bus = pc.data & 0x0F;
            }

bus_read:
            /* Read from BUS */
            if (ma.RWB) {
                ma.data = bus & 0x0F;
            }
            if (ram.RWB && !ram.OE) {
                ram.data[ma.data & 0x0F] = bus;
            }
            if (ir.RWB && !ir.OE) {
                ir.data = bus;
            }
            if (out.RWB) {
                out.data = bus;
            }
            if (b.RWB) {
                b.data = bus;
            }
            if (a.RWB && !a.OE) {
                a.data = bus;
            }
            if (pc.J && !pc.CO) {
                pc.data = bus & 0x0F;
            }

            if (cu.data[((ir.data & 0xF0) >> 1) + cu.counter][CE]) {
                pc.data = (pc.data + 1) % 0x10;
            }

            cu.counter = (cu.counter + 1) % 5;
        }
    }

    /* Returning value */
    return 0;
}
