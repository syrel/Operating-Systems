#include <stdio.h>
#include <stdlib.h>

int *f(int a) {
    int *b;
    // instead of returning an address of a local variable located on the stack
    // we must allocate a dynamic memory on the heap
    b = (int*) malloc(sizeof(int));
    *b = 2 * a;
    return b;
}

int main(void) {
    int *p4, *p8;

    p4 = f(4);
    p8 = f(8);
    printf("p4: %i / p8: %i\n", *p4, *p8);
}
