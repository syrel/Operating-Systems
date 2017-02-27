/* gcc -Wall -O2 fib.c */

#include <stdio.h>
#include <stdint.h>

/**
 * Return a result of fibonacci function applied on a given number
 * @param a
 * @return
 */
int fib(int a) {
    // if argument is 0 or 1 fibonacci returns 0 or 1 respectively
    if (a == 0 || a == 1)
        return a;

    // recursion approach; not the best, since we can find ourselves in a stack overflow
    return fib(a - 1) + fib(a - 2);
}

int main(void) {

    printf("fib(10) = %u\n", fib(10));

    return 0;
}
