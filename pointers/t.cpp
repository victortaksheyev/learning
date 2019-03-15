#include <iostream>

using namespace std;

class house {
public:
    int *nums;                      // creating a pointer of type int;
};


void printcArr(int size, char c[]) {
    for (int i = 0; i < size; i++)
        cout << c[i] << " ";
    cout << endl;
}

int main() {
//    house *myhouse;
//    myhouse = new house;            // allocating house amount of memory to the pointer
//
//    int *nums = new int[10];        // creating a dynamic array of 10 elements
//    nums[2] = 9;
//    myhouse->nums = nums;
//
//
//    cout << myhouse->nums << endl;  // memory location of 1st element
//    cout << *((myhouse->nums)+2) << endl;  // memory location of 1st element
    
    char c[10];
    c[0] = 'H';
    c[1] = 'e';
    c[2] = 'y';
    c[3] = '\0';
    
    printcArr(10, c);
    
    
    
    
}


