#include <iostream>
#include <string>
/*
Classes in C++
needs to be compiled with g++, not gcc
What does the class look like on the stack?
What does it look like on the heap?
Compare it to the struct program? What is different between a class and a struct?
*/

class Test {
    private:
        int m_x;
        int m_y;
        int m_z;
        char n[30] = "Making the data more obvious\n";
    public:
        Test(int x, int y, int z);
        float dot(Test other);
        int x();
        int y();
        int z();
        void p_n();
};

int main() {
    Test a(1,2,3); // On Stack
    Test *b = new Test(6,7,8); // On heap
    
    float dotprod = b->dot(a);
    std::cout << "Dot Product: " << dotprod << "\n";
    delete b; // Freeing b
    b = nullptr;
    return 0;
}

Test::Test(int x, int y, int z) {
    m_x = x;
    m_y = y;
    m_z = z;
}

float Test::dot(Test other) {
    float total = 0.0f;

    total += other.x() * m_x;
    total += other.y() * m_y;
    total += other.z() * m_z;
    
    return total;
}

/* 
These are just to make x,y,z "immutable". There are ways to still modify them
by taking advantage of pointer shenanigans :)
*/

int Test::x() {
    return m_x;
}

int Test::y() {
    return m_y;
}

int Test::z() {
    return m_z;
}

void Test::p_n() {
    std::cout << n;
}
