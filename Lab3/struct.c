#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/*
Author: Isaiah Bessire
Date: March 31, 2026
Class: CYBR 470

Where I got the bolding text from:
https://stackoverflow.com/questions/71274207/how-to-bold-text-in-c-program

Struct in memory
Run to the first seperator (printf("\n---------------------------------------\n");)
You will have to scroll to the bottom (find main) to see what I mean
Find the head in memory.
Find a node of the linked list in memory.

Is there any visual difference between the head and a node in memory?
What does the data in the node look like in gdb compared to the struct below (struct node)?
*/

const char VALID[] = "valid";
const char INVALID[] = "invalid";

// The node struct
struct node {
    int value;
    struct node* next;
};

// The linked list struct
typedef struct {
    int length;
    struct node* head;
} intll_t;

// Initializes a linked list
intll_t* linkedlist(void) {
    intll_t* temp = (intll_t *)malloc(sizeof(intll_t));

    // If the malloc failed, we don't want to continue
    assert(temp != NULL);

    temp->head = NULL;
    temp->length = 0;
    return temp;
}

// Appends a new node with the provided value to the end of the Linked List
void append(intll_t* ll, int value) {
    struct node* nn;

    if(ll->length == 0) {
        nn = (struct node *)malloc(sizeof(struct node)); 

        // If the malloc failed, we don't want to continue
        assert(nn != NULL);

        nn->next = NULL;
        nn->value = value;
        ll->head = nn;

    } else {
        struct node* cur = ll->head;

        while(cur->next != NULL) {
            cur = cur->next;
        }

        nn = (struct node *)malloc(sizeof(struct node));

        // If the malloc failed, we don't want to continue
        assert(nn != NULL);

        nn->value = value;
        nn->next = NULL;
    
        cur->next = nn;
    }
    ll->length++;
}

// Deletes the node at the given index if the index is valid.
void del(intll_t* ll, int index) {
    if(index > ll->length || index < 0) {
        printf("Index Out of Bounds\n");
        return;
    }

    struct node* cur = ll->head;
    struct node* prev = cur;
    
    int i;
    for(i = 0; i < index; i++) {
        prev = cur;
        cur = cur->next;
    }

    prev->next = cur->next;
    ll->length--;

    free(cur);
    cur = NULL;
}

// Inserts the given value at the given index if the index is valid.
void insert(intll_t* ll, int index, int value) {
    if(index > ll->length || index < 0) {
        printf("Index Out of Bounds\n");
        return;
    }

    struct node* cur = ll->head;
    struct node* prev = cur;
    int i;

    for(i = 0; i < index; i++) {
        prev = cur;
        cur = cur->next;
    }

    struct node* nn = (struct node *)malloc(sizeof(struct node));

    // If the malloc failed, we don't want to continue
    assert(nn != NULL);

    nn->value = value;

    prev->next = nn;
    nn->next = cur;

    ll->length++;
}

// Removes the head node, and returns the value that it contained.
int pop_head(intll_t* ll) {
    if(ll->head == NULL) {
        return -1;
    }
    struct node* temp = ll->head;
    ll->head = temp->next;
    ll->length--;

    int value = temp->value;
    free(temp);
    temp = NULL;

    return value;
}

// Removes the last node, and returns the value it contained.
int pop_tail(intll_t* ll) {
    if(ll->head == NULL) {
        return -1;
    }
    struct node* cur = ll->head;
    struct node* prev = cur;

    while(cur->next != NULL) {
        prev = cur;
        cur = cur->next;
    }

    int value = cur->value;
    prev->next = NULL;
    ll->length--;

    free(cur);
    cur = NULL;

    return value;
}

// Displays the Linked List
// Ex. [1 -> 2 -> 3]
void print_ll(intll_t* ll) {
    if(ll->head == NULL) {
        printf("Empty\n");
        return;
    }
    struct node* cur = ll->head;

    printf("[");
    while(cur->next != NULL) {
        printf("%d -> ", cur->value);
        cur = cur->next;
    }
    printf("%d]\n", cur->value);
}

// Appends the given value to the front of the list. 
void prepend(intll_t* ll, int value) {
    struct node* nn = (struct node *)malloc(sizeof(struct node));

    // If the malloc failed, we don't want to continue
    assert(nn != NULL);
    
    nn->next = ll->head;
    nn->value = value;

    ll->head = nn;
    ll->length++;
}

// Cleans the list. Frees all left over memory used by the list, including the
// list object, and sets it to NULL.
void clean_ll(intll_t* ll) {
    while(ll->head != NULL) {
        pop_head(ll);
    }
    free(ll);
    ll = NULL;
}

// The main function. Contains all the "tests"
int main(void) {
    intll_t* intl = linkedlist();
    int ret;
    int i;
    // Indices to test deletion on. 2 valid, 2 invalid
    int delind[4] = {1, 2, -1, 5}; 

    // Indices to test insertion on. 2 valid, 2 invalid
    int insind[4] = {1, 4, -1, 10};

    // The values to attempt to insert.
    int insval[4] = {6, 21, 4, 3};
    int ind, val;

    printf("\e[1mAppending 1-5\n\e[m");
    printf("Initial Linked List: ");
    print_ll(intl); 
    printf("\n");

    for(i = 1; i < 6; i++) {
        append(intl, i);
        printf("After Adding %d: ", i);
        print_ll(intl);
    }

    printf("\n---------------------------------------\n");
    
    printf("\e[1m\nDeleting Values\n\e[m");
    printf("Initial Linked List: ");
    print_ll(intl); 
    
    for(i = 0; i < 4; i++) {
        ind = delind[i];

        if(0 < ind && ind <= intl->length) {
            printf("\nDeleting Index %d (%s)\n", ind, VALID);
        } else {
            printf("\nDeleting Index %d (%s)\n", ind, INVALID);
        }
        del(intl, ind);
        print_ll(intl);
    }

    printf("\n---------------------------------------\n");
    
    printf("\e[1m\nInserting Values\n\e[m");
    printf("Initial Linked List: ");
    print_ll(intl); 

    for(i = 0; i < 4; i++) {
        ind = insind[i];
        val = insval[i];
        
        printf("\nInsert at index %d the value %d\n", ind, val);
        insert(intl, ind, val);
        print_ll(intl);
    }
 
    printf("\n---------------------------------------\n");

    printf("\e[1m\nPopping the Head\n\e[m");
    printf("Initial Linked List: ");
    print_ll(intl); 
    printf("\n");

    for(i = 0; i < 2; i++) {
        ret = pop_head(intl);
        printf("Value Returned: %d\n", ret);
        print_ll(intl);
    }

    printf("\n---------------------------------------\n");

    printf("\e[1m\nPopping the Tail\n\e[m");
    printf("Initial Linked List: ");
    print_ll(intl); 
    printf("\n");

    for(i = 0; i < 2; i++) {
        ret = pop_tail(intl);
        printf("Value Returned: %d\n", ret);
        print_ll(intl);
    }

    printf("\n---------------------------------------\n");

    printf("\e[1m\nPrepend 6-10 (reverse order)\n\e[m");
    printf("Initial Linked List: ");
    print_ll(intl);    
    printf("\n");
    
    for(i = 6; i < 11; i++) {
        prepend(intl, i);
        printf("After Adding %2d: ", i);
        print_ll(intl);
    }

    clean_ll(intl);
    return 0;
}

