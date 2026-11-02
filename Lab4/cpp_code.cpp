#include <iostream>
#include <cmath>

/*
This definition would go in a header file normally, but since I am going with a
single file, it does not matter.
*/
class Vector {
    public:
        // These are kept public to mimic C
        int m_x;
        int m_y;
        int m_z;
        Vector(int x, int y, int z);
        /*
        Don't need unless we need to clean up something before destruction.
        Like if a member has allocated memory that needs to be freed.
        */
        // ~Vector();
        // No required this
        int dot(Vector *other);
        double magnitude();
        void to_str();
};

int main() {
    // On stack
    Vector a(1,2,3);
    // On the heap, equivalent to (Vector *)malloc(sizeof(Vector));
    Vector *b = new Vector(6,7,8);

    /*
    This std:: is a namespace, and is used to differentiate functions with the
    same name. In C, you cannot, to my knowledge, have two functions with the
    same name.
    */
    std::cout << "a: ";
    a.to_str();
    std::cout << "b: ";
    b->to_str();

    int output = a.dot(b);

    std::cout << "a dot b: " << output << "\n";

    double a_mag = a.magnitude();
    double b_mag = b->magnitude();

    std::cout << "a magnitude: " << a_mag << "\n";
    std::cout << "b magnitude: " << b_mag << "\n";

    // Equivalent to free(b)
    delete b;
    b = nullptr;
    return 0;
}

// Initializer list for the class.
Vector::Vector(int x, int y, int z) :
    m_x(x),
    m_y(y),
    m_z(z) 
{}

int Vector::dot(Vector *other) {
    int total = 0;

    /*
    Because classes are just structs, you can actually perform the same 
    equivalent statements shown in c_code.c (the dot function).

    Also, because you can do that, you can actually access private variables
    outside of the class, and it does not stop you.

    Yet again, in C (and C++) types are a myth, and data is data;
    */

    total += m_x * other->m_x;
    total += m_y * other->m_y;
    total += m_z * other->m_z;

    return total;
}

/*
Magnitude is defined as the length of a vector, calculated by performing
the Pythagorean Theorem, which actually works for any n dimensional space.
For this, sqrt(x^2 + y^2 + z^2)
*/
double Vector::magnitude() {
    double total = 0.0;
    total += m_x * m_x;
    total += m_y * m_y;
    total += m_z * m_z;

    return std::sqrt(total);
}

void Vector::to_str() {
    std::cout << "[" << m_x << ", " << m_y << ", " << m_z << "]\n";
}