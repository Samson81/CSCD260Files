#include <stdio.h>
/*
Originally prog1.c
Just a small program to practice basic debugging on.

GDB Cheatsheet, more than you will ever need to know.
https://www.cs.utexas.edu/~dahlin/Classes/UGOS/reading/gdb-ref.pdf

target remote <ip>:<port> -> connects to a GDB server running on ip on port port. You can leave IP blank if local
b main -> break on main
r -> run (start/restart the program) (does not work for remote, use c)
c -> continue (run to next breakpoint)
n -> next line (step over)
ni -> next instruction (step over)
s -> next line (step into)
ni -> next instruction (step into)
finish -> runs to end of current function

p <var> -> prints the value stored in var
x/<val>x <var> -> prints val bytes in hex starting at the address of var. There are way to many ways to modify this command
*/

int square(int x) {
    return x * x; 
}

int main(void) {
    int x = 2;
    int y = square(x);
    printf("%d, %d\n", x, y);
    puts("Hello World"); // The "correct" way to print non format strings. Optimizations will switch to this, includes \n
    return 0;
}
