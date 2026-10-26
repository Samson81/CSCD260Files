#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
NOTE: If it crashes for any reason (most likely a segmentation fault), just run it again. 
NOTE: If the issue persists, ask me.
Just one answer per line of questions.

Variables on the heap
set a break point on the while(1) and run to it (stack.c:37)
To find the location of a variable:
p <var>
To see what value is stored, run:
x/<size>x <var>

What is different about the value stored in each variable (compared to stack.c)? What is stored (look at the type)? 
Where is the assigned value stored?
What is different about how they are stored compared to stack.c? Are they stored sequentially? 
What does the previous answer tell you about the heap?
In the works:
Is there a minimum allocation size?
*/


int main() {
    char *x = (char *)malloc(sizeof(char));
    *x = 'a';

    int *y = (int *)malloc(sizeof(int));
    *y = 0x12345678;
    
    unsigned short *z = (unsigned short *)malloc(sizeof(unsigned short));
    *z = 65535;

    long int *w = (long int *)malloc(sizeof(long int));
    *w = 0x1010101001010101l;

    long long int *a = (long long int *)malloc(sizeof(long long int));
    *a = 0x0101010110101010l;
    double *b = (double *)malloc(sizeof(double));
    *b = 12345.54321;
    char *c = (char *)malloc(64 * sizeof(char));
    strcpy(c, "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+");
    while(1) {
        x += 1;
    }
    free(x);
    free(y);
    free(z);
    free(w);
    free(a);
    free(b);
    free(c);
}
