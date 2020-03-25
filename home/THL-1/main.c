#include <stdio.h>
#include "register.h"
#include "ram.h"
#include "control.h"
#include "alu.h"
#include "pc.h"

#define INSTR(x, op) ((x << 4) + op)

void output(reg_t out);

int main() {

    /* Initializing variables */
    auto uint8_t bus = 0;
    auto bool halt_flag = false;

    auto reg_t a = {}, b = {}, out = {}, ma = {}, ir = {}, flags = {};
    auto ram_t ram = {};
    auto cu_t cu = {};
    auto alu_t alu = {};
    auto pc_t pc = {};

    alu.a = &a;
    alu.b = &b;

    b.OE = false;

    ma.OE = true;
    ma.RWB = false;

    out.OE = true;

    auto bool clock = false;
    cu.counter = 0x0;

    auto bool opt_flag = false;

    auto uint8_t cu_index;

    auto bool *ctrl_map[] = {&halt_flag, &ma.RWB, &ram.RWB, &ram.OE, &ir.RWB, &ir.OE, &out.RWB,
                                         &alu.OE, alu.ctrl + 1, alu.ctrl, &b.RWB, &a.RWB, &a.OE, &pc.CE, &pc.CO, &pc.J, &flags.RWB};

    /* Main part */
    microcode(&cu);
    ram.data[0x0] = INSTR(LDA,  0xE);
    ram.data[0x1] = INSTR(OUT,  0x0);
    ram.data[0x2] = INSTR(ADD,  0xD);
    ram.data[0x3] = INSTR(JC,   0xA);
    ram.data[0x4] = INSTR(STA,  0xF);
    ram.data[0x5] = INSTR(LDA,  0xE);
    ram.data[0x6] = INSTR(STA,  0xD);
    ram.data[0x7] = INSTR(LDA,  0xF);
    ram.data[0x8] = INSTR(STA,  0xE);
    ram.data[0x9] = INSTR(JMP,  0x0);
    ram.data[0xA] = INSTR(HALT, 0x0);
    ram.data[0xB] = 0x0;
    ram.data[0xC] = 0x0;
    ram.data[0xD] = 0x0; // z - pre-prev
    ram.data[0xE] = 0x1; // y - prev
    ram.data[0xF] = 0x0; // x - current

    for ( ; !halt_flag; clock = !clock, bus = 0) {

        /* Set up control pins */
        if (!clock) {
            opt_flag = false;
            for (int i = 0; i < NSIGNALS; ++i) {
                if (ctrl_map[i] != NULL) {
                    *ctrl_map[i] = (cu.data[flags.data & 0x7][(ir.data & 0xF0) >> 4][cu.counter] >> (NSIGNALS - i - 1)) & 0x1;
                    opt_flag |= *ctrl_map[i];
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
                bus = perform_alu(&alu, &flags);
                goto bus_read;
            }
            if (a.OE && !a.RWB) {
                bus = a.data;
                goto bus_read;
            }
            if (pc.CO && !pc.CE && !pc.J) {
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
                output(out);
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

            if (pc.CE && !pc.CO && !pc.J) {
                pc.data = (pc.data + 1) % 0x10;
            }

            cu.counter = (cu.counter + 1) % 5;
        }
    }

    /* Returning value */
    return 0;
}

void output(reg_t out) {

    /* I/O flow */
    printf("Octal: %o\tSigned: %d\tUnsigned: %u \tHex: %x\n", out.data, out.data, out.data, out.data);
}