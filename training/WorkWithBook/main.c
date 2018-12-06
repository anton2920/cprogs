#include <zconf.h>

#define SIZE 1024

main() {

    int n, buf[SIZE];

    write(1, "Type string: ", 13);
    n = (int) read(0, buf, SIZE);
    write(1, "Your string: ", 13);
    write(1, buf, n);
}