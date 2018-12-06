#include <zconf.h>

#define SIZE 1024

main() {

    int n, buf[SIZE];
    int *bufp = buf;

    n = (int) read(0, buf, SIZE);
    while (--n) {
        write(1, bufp++, 1);
    }
}