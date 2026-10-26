#include <stdio.h>
/*
Originally prog2.c
Intro to looking at functions. In GDB, test:
```
info functions
````
versus
```
b main
r (c if remote)
info functions
```

What changes for a couple functions?
*/

void win() {
    puts("Much Win\n");
}

void lose() {
    puts("You lose :(\n");
}

void hw() {
    puts("Hello World\n");
}

int readinp() {
    char buffer[64];
    // Turns out scanf may be deprecated for the reason I used it
    scanf("%[^\n]%*c", buffer);
    return 0;
}

/* This code is written to contain an exploit, you can try it if you want :)
*/
int main(void) { 
    printf("%p\n", win);
    int pass = readinp();
    if(pass) {
        hw();
    } else {
        lose();
    }
    return 0;
}
