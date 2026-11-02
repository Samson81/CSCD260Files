#include <stdio.h>
#include <stdlib.h>
// Rip not requiring a flag. -lm

typedef struct {
    int m_x;
    int m_y;
    int m_z;
} Vector;

int main() {
    Vector *a = (Vector *)malloc(sizeof(Vector));
    a->m_x = 1;
    a->m_y = 2;
    a->m_z = 3;

    printf("%d\n", a->m_z);
    printf("%d\n", (*a).m_z);
    printf("%d\n", *(((int *)a) + 2));
    printf("%d\n", ((int *)a)[2]);
    printf("%d\n", (int)((char *)a)[8]);
    printf("%d\n", (int)((long *)a)[1]);

    return 0;
}