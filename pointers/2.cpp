#include <iostream>

using namespace std;

int main() {
    int *numP;      // creating a pointer variable of type int
                    // status: print(numP): undefined
                    // status: print(&numP): some address
                    // status: print(*numP): undefined
    
    numP = new int; // creates a dynamic variable of type int and stores its address in numP
                    // status: print(numP): undefined
                    // status: print(&numP): some address
                    // status: print(*numP): undefined
    
    *numP = 12;     // stores 12 in the dynamically created var
    
    cout << "address of the dynamic var: " << numP << endl;
    cout << "value of the dynamic var: " << *numP << endl;
    cout << "address of numP: " << &numP << endl;
    
    
    cout << endl << endl << endl;
    
    // we can initialize memory straight from the new keyword
    char *chP;      // creating a char type pointer
    
    chP = new char('t');    // will create a dynamic variable of type char,
                            // initialize it with 't'
                            // and store its address into the pointer var chP
    
    delete chP;
    chP = 0;
    
    chP = new char;
    *chP = 'r';
    
    cout << "value of char var: " << *chP << endl;
    
    
    
}
