#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
You are more than welcome to debug this.
Just some basic questions:
Does the key listed below (correct key) ever get exposed in a way where you 
could read it from memory?
Is the "encryption" reversible? Does it only use reversible functions?
*/
// The correct key: ThiS1saR3AllyL0ngKey

const uint RAND = 281084207; // First key
const uint RAND2 = 946543959; // Second key
const char key[] = ",t\xc3{fn\nj\xe0\xcaP\xe8\x1f\":\x04x~\xcan";
#define MAX 49 // 2 * keylen + 1

typedef struct node {
    int value;
    struct node* next;
} node_t;

/*
In 64 bit, it should look like this:

+-------+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
| Byte  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F |
+-------+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
| Value | value         | padding       | next                          |
+-------+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+

We will be hiding stuff in the padding, though this is not as obvious in the 
stripped but I had the thought to hide stuff there so :shrug:. Plus I find it
more funny to just use different methods to reference it. Also, something that
you could consider doing is making a really big struct, then cast it to a char*
and write to weird indices.

Something I thought about doing was instead of using static random numbers, call
random with these and use those instead, but I am lazy, and didn't want to.
*/


typedef union input { // Used soley for the odd output/easier reference
    char buf[MAX];
    int hid[MAX / 4];
} input_t;

int pop_head(node_t* head);
void clean_ll(node_t* head);
int main(int argc, char ** argv);
void idek(node_t* head, int len);

int main(int argc, char ** argv) {
    int amt = MAX - 1;
    int i = 0;
    input_t inp = {};
    if( argc < 2) { // Ensure that an argument was provided.
        return 0;
    }
    int len = strlen(argv[1]); // Get length of argument.
    if(amt > len) { // Sets a max limit for the string
        amt = len;
    }

    strncpy(inp.buf, argv[1], amt); // Copy the first argument, to the max length, into the union
    int temp = amt;
    while(temp % 4 != 0) { // Pad out so we don't deal with bad data (I didn't want the code exiting early because the length is incorrect)
        strcat(inp.buf, "\1");
        temp++;
    } 
    inp.buf[temp] = '\0';

    const int it = temp / 4; // Quarter the length, since we put 4 bytes into each node
    int value;

ll: // Initializes the Linked List
    node_t* head = (node_t*)malloc(sizeof(node_t));
    *((long *)head) = (long)RAND << 32; // Put RAND in the padding
    *((int *)head) = RAND2; // Set head->value to RAND2 without using value
    head->next = NULL;
    goto LOOP;

append: // The append function
    node_t* nn = (node_t *)malloc(sizeof(node_t)); 

    node_t* cur = head;

    while(cur->next != NULL) {
        cur = cur->next;
    }

    nn->value = value;
    nn->next = NULL;
    cur->next = nn;
    goto FOR;

FOR: // A "for" loop created using gotos only
    i++;
    goto LOOP;

LOOP: // The conditional for the loop
    if(i < it) {
        value = inp.hid[i]; // Put every 4 bytes into a linked list node, hence the union.
        goto append;
    }
    // Exit the loop
    idek(head, temp); // 1st key

    // The below is just so that the two function calls aren't directly one after the other.
    int j = 0;
    input_t s = {0};
    cur = head->next;
    idek(head, temp + 1); // 2nd key

    while(cur != NULL) { // Extract the "encrypted" input from the linkedlist
        int val = (int)(*(long *)cur >> 32);
        s.hid[j] = val; // Put the exctracted value into a new union
        j++;
        cur = cur->next;
    }
    if(!strcmp(key,s.buf)) { // Compare to the "encrypted key"
        printf("Correct\n");
    } else {
        printf("Incorrect\n");
    }

exit_fun: // The exit
    clean_ll(head);
    return 0;
}

// Only used for the exit
int pop_head(node_t* head) {
    if(head->next == NULL) {
        return -1;
    }
    node_t* temp = head->next;
    head->next = temp->next;

    int value = temp->value;
    free(temp);
    temp = NULL;

    return value;
}

// Only used for the exit
void clean_ll(node_t* head) {
    while(head->next != NULL) {
        pop_head(head);
    }
    free(head);
    head = NULL;
}

// I don't even know what to name this. This is the "encryption", that was a 
// terrible idea and fun to implement.
void idek(node_t* head, int len) {
    int i;
    int temp;
    int initval;
    node_t* cur = head->next;
    if(len % 2) { // 2nd call, len % 2 != 0. RAND2
        initval = *(int *)head;
    } else { // 1st call. Grabs RAND. Could be done a lot easier, but no
        initval = (int)(((*(long *)head) & ((long)0xFFFFFFFF << 32)) >> 32);
    }
    i = 0;
    while(cur != NULL) { // Go over the created list
        if(len % 2) { 
            // 2nd call, we need to grab the already "encrypted" data from the list
            // It sits in the padding :), so is referenced this way. 
            temp = *((int *)cur + 1);
        } else { // 1st call, grab the original string.
            temp = cur->value;
        }
        // XOR = (~A | B) & (A & ~B)
        // XNOR = ~XOR
        int na = ~initval;
        int nb = ~temp;
        int x = ~(na & temp);
        int y = ~(nb & initval); // Technically this is XNOR, but idk why I did it like this
        initval = ~(x & y); // XOR
        if(i % 2) {     
            initval = ~(initval); // XNOR
        }

        *((int *)cur + 1) = initval; // Set the padding to the "encrypted" 4 bytes
        i++;
        cur = cur->next;
    }
}


