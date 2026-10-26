#include <stdio.h>
/*
Variables on the stack
set a break point on the while(1) and run to it (stack.c:23)
x/64x $rbp-96
What do you see? Why 96?
Can you make out any of the values below? (0x33 == '3')
Where are the values stored?
How are the values stored? What does that tell you about the stack?
*/

int main() {
    char x = 'a';
    unsigned short y = 65535;
    int z = 1;
    long int w = 0x1010101001010101l; // Why the l?
    long long int a = 0x0101010110101010l; 
    // Difference between long int and long long int? (both take up 8 bytes in 64 bit) 
    double b = 12345.54321;
    // Why a[64] for a length 63 string (0-9 + a-z + A-Z + \+)
    char c[64] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+";
    while(1) {
        x += 1;
    }
}
