/* pointer - a variable whose content is an address
 * dataType of var youre pointing to *identifier;
 * for each variable, you must have a * to make it a pointer variable
 *  this means that in the statement int* p, q; only p is a pointer, q is a var of type int
 * the 2 operators that work with pointers are & and * (address operator and dereferencing operator)
 *  & address of operator that return the address of its operand
 *
 *  Dereferencing operator: *
        &p is the address of the pointer
        p means the content of p (usually the address to which it is pointing to)
        *p means the content within the memory location to which p points
 
 this means:
        p = 10 changes the content of p to 10
        *p = 20 changes the content of memory space p is pointing to to 20
 
 suppose we have the follwing:
 int *p;
 int x;
 
 &p = 1400 (for example);
 p = unknown (unknown);
 *p = does not exist (undefined);
 
 &x = 1800 (for example);
 x = unknown (unknown);
 
 
 after x = 50 executed:
 &x = 1800 (for example);
 x = 50;
 
 after p = &x:
 &p = 1400;
 p = 1800;
 *p = 50;
 
 after *p = 38:
 &x = 1800;
 x = 38;
 
 &p = 1400;
 p = 1800;
 *p = 38
 *
 *
 *
 *
 *
 *
 *
 */

#include <iostream>

using namespace std;

int main() {
//    int x, y;   // variable
//    x = 100;
//    int *p;     // pointer variable that will point to x
//                // (since x is an int, the pointer is of type int)
//    p = &x;     // assings the address of x to p
//
//    // if we want to copy the value at memory location named x to another mem location..
//    y = x;      // now memory location named y contains the value of the value in memory location x;
//    p = &x;     // copy the address of x into the pointer p
//                // p is a reference to x (it holds the name num1)
    
    int x = 25;
    int *p;             // pointer of int data type
    p = &x;             // reference to x (is storing the address of x/ location x)
    cout << p << endl;  // should print the number in memory of p
    cout << *p << endl; // prints what's stored at that location
    cout << &x << endl; // prints
    
    
}
