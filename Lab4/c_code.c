#include <stdio.h>
#include <stdlib.h>
// Rip not requiring a flag. -lm
#include <math.h>

/*
Mimicking a class in C
*/

/*
When doing this in a "real" program, this struct and the function 
definitions would go in a header file (.h). These are effectively what happens
when you run `gcc -E file.c -o test.i`, where the headers get appended at the
start of the file.

Sorry for the Vector enthusiasm. I am currently in Offensive Applications of AI
and have been dealing with them for weeks. It's better than other ideas, and 
simple to implement.
*/

// m_* is just mimicking the style I learned for member variables in C++
typedef struct {
    int m_x;
    int m_y;
    int m_z;
} Vector;

// Mimic Constructor. Note we don't have namespaces so we cannot do Vector::
Vector *InitVector(int x, int y, int z);
// Mimic destructor Vector::~Vector()
void DeleteVector(Vector *obj);
/*
Internally, Vector::dot becomes a __thiscall (in C++), where the first input 
parameter is a reference to the object, so a.dot(b) becomes Vector::dot(&a, &b)
with the objects:
Vector a(1,2,3);
Vector b(1,2,3);
*/
int dot(Vector *this, Vector *other);
double magnitude(Vector *this);
void to_str(Vector *this);

int main() {
    // On the stack
    Vector a = {
        .m_x = 1,
        .m_y = 2,
        .m_z = 3
    };
    // On the heap
    Vector *b = InitVector(6, 7, 8);

    printf("a: ");
    to_str(&a);
    printf("b: ");
    to_str(b);

    // Need to do &a to get a pointer to a, since dot takes a Vector*
    int output = dot(&a, b);
    
    printf("a dot b: %d\n", output);
    
    double a_mag = magnitude(&a);
    double b_mag = magnitude(b);

    printf("a magnitude: %lf\n", a_mag);
    printf("b magnitude: %lf\n", b_mag);

    DeleteVector(b);
    return 0;
}

Vector *InitVector(int x, int y, int z) {
    // malloc returns a void *, which we cast to Vector *
    // sizeof is replaced at compile time with the actual size of a Vector (12)
    Vector *temp = (Vector *)malloc(sizeof(Vector));
    
    temp->m_x = x;
    temp->m_y = y;
    temp->m_z = z;

    return temp;
}

void DeleteVector(Vector *obj) {
    free(obj);
    obj = NULL;
}

int dot(Vector *this, Vector *other) {
    int total = 0;
    /*
    Equivalent statements, assume a Vector
    a->m_z
    (*a).m_z
    *(((int *)a) + 2)
    ((int *)a)[2]
    (int)((char *)a)[8]
    (int)((long *)a)[1])

    In C, types are a myth, data is data. You can cast anything to anything 
    assuming correct syntax.
    */ 
    total += this->m_x * other->m_x;
    total += this->m_y * other->m_y;
    total += this->m_z * other->m_z;

    return total;
}

// Because of sqrt, it requires the math library
double magnitude(Vector *this) {
    double total = 0.0f;
    total += this->m_x * this->m_x;
    total += this->m_y * this->m_y;
    total += this->m_z * this->m_z;

    return sqrt(total);
}

void to_str(Vector *this) {
    printf("[%d, %d, %d]\n", this->m_x, this->m_y, this->m_z);
}