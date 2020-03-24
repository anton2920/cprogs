#include <string.h>
#include "control.h"
#include <stdlib.h>

void microcode(cu_t *cu) {

    /* Initializing varaibles */
    bool val = false;

    /* Main part */
    /* Writing zeros everywhere */
    memset(cu->data, false, (1 << 7) * CONTROL_UNIT_SIZE);

    /* Fetch cycle */
    for (uint8_t i = 0; i < 0x0F; ++i) {
        cu->data[(i << 3) & 0x78][MI] = true;
        cu->data[(i << 3) & 0x78][CO] = true;

        cu->data[((i << 3) + 0x01) & 0x79][RO] = true;
        cu->data[((i << 3) + 0x01) & 0x79][II] = true;
        cu->data[((i << 3) + 0x01) & 0x79][CE] = true;
    }

    /* LDA */
    cu->data[((LDA << 3) + 0b010) & 0x7F][IO] = true;
    cu->data[((LDA << 3) + 0b010) & 0x7F][MI] = true;

    cu->data[((LDA << 3) + 0b011) & 0x7F][RO] = true;
    cu->data[((LDA << 3) + 0b011) & 0x7F][AI] = true;

    /* OUT */
    cu->data[((OUT << 3) + 0b010) & 0x7F][AO] = true;
    cu->data[((OUT << 3) + 0b010) & 0x7F][OI] = true;
}