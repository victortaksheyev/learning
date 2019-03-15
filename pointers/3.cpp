#include <iostream>
#include<stdio.h>  //printf
using namespace std;

int main() {
    int list[5]; // merely doing list++ here would not work because arrays are constant poitners
    list[0] = 0;
    list[1] = 1;
    list[2] = 2;
    list[3] = 3;
    list[4] = 4;
    
    int *listPtr;
    
    listPtr = list;
    listPtr+= 2;
    
    cout << *listPtr << endl;
    
//    int input;
//    cin >> input;
//    int *ptr;
//    ptr = new int[input];
//    for (int i = 0; i < input; i++) {
//        ptr[i] = 100;
//        cout << ptr[i] << endl;
//    }
//
//
//    delete [] ptr;
//    ptr = NULL;
    
    
    
    //  for 2d array, B[][]
    //  B[i][j] = *(B[i]+j)
    //          = *(*(B+1)+j)
    return 0;
}
