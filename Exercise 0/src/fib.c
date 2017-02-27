/* gcc -Wall -O2 fib.c */

#include <stdio.h>
#include <stdint.h>

int fib(int a) {
    if (a == 0 || a == 1)
        return a;

    return fib(a - 1) + fib(a - 2);
}

int main(void) {

    printf("fib(10) = %u\n", fib(10));

    return 0;
}
