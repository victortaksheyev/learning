// program that will create dynamic 2 d array from any data type
#include <iostream>
#include <string>

using namespace std;

// overload >>, =. +
// >> outside bc leftmost is not member of A
// = inside
// + either

class A {
public:
    A(int x = 0, int y = 0){
        this->x = x;
        this->y = y;
    }
    void print() const {
        cout << "x: " << this->x << endl;
        cout << "y: " << this->y << endl;
    }
    friend istream& operator>>(istream& outS, A&);
    const A& operator=(const A&);
    A operator+(const A&);

private:
    int x;
    int y;

};

// +
A A::operator+(const A& other) {
    A result;
    result.x = this->x + other.x;
    result.y = this->y + other.y;
    return result;
}

// = 
const A& A::operator=(const A& other){
    if (this != &other) {
        this->x = other.x;
        this->y = other.y;
    }
    return *this;
}

// >>
istream& operator>> (istream& outS, A& otherA) {
    outS >> otherA.x;
    outS >> otherA.y;
    return outS;
}

int main () {
    A first;
    cout << "Before: " << endl;
    first.print();
    cout << endl;

    cout << "After: " << endl;
    cin >> first;
    first.print();
    cout << endl;

    A second(100, 100);
    cout << "First: " << endl;
    first.print();
    cout << endl;
    cout << "Second: " << endl;
    second.print();
    cout << endl;

    cout << "After = first: " << endl;
    first = second;
    first.print();
    

    cout << endl << "PLUS OPERATOR" << endl;
    first = first+second;
    first.print();



}