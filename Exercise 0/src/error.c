#include <stdio.h>

void f(int a, int *b) {
    *b = 2 * a;
}


int main(void) {
    int p4, p8;

    f(4, &p4);
    f(8, &p8);
    printf("p4: %i / p8: %i\n", p4, p8);
}
