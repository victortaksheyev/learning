#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const string NEW = "-NEW";

void printArray (int **arr) {
    // will end at index 1, because index 0 will not need to be printed again
    for (int i = arr[0][0]; i >= 1; i--) {
        // prints out initial number 
        if (i == arr[0][0]) {
            cout << arr[0][0] << endl;
        }
        // printing all elements of next array
        for (int j = 0; j < arr[i][0] + 1; j++) {       // loops until arr[i][0] + 1 because it includes the first element (metadata)
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

int main (int argc, char * argv[]) {
    bool c_allocation = true;
    if (argv[2] == NEW.c_str()) c_allocation = false; // if user specifies to use new
    
    int rows;
    int cols;
    ifstream input(argv[1]);
    input >> rows;    

    if (c_allocation) {
        int ** twoDArr = (int**)malloc(sizeof(int*)*(rows + 1));
        for (int i = 0; i < rows + 1; i++) {
            if (i == 0) {
                cols = 1;
                twoDArr[i] = (int*)malloc(sizeof(int)*cols);
                twoDArr[i][0] = rows;
                continue;
            }
            input >> cols;
            twoDArr[i] = (int*)malloc(sizeof(int)*(cols+1));
            twoDArr[i][0] = cols;
            for (int j = 1; j < cols + 1; j++) {
                input >> twoDArr[i][j];
            }
        }
        printArray(twoDArr);
        // deallocating
        for (int i = 0; i < rows + 1; i++) {
            free(twoDArr[i]);
        }
        free(twoDArr);
    } else {
        int ** twoDArr = new int*[rows + 1];
        for (int i = 0; i < rows + 1; i++) {
            if (i == 0) {
                cols = 1;
                twoDArr[i] = new int[cols];
                twoDArr[i][0] = rows;
                continue;
            }
            input >> cols;
            twoDArr[i] = new int[cols+1];
            twoDArr[i][0] = cols;
            for (int j = 1; j < cols + 1; j++) {
                input >> twoDArr[i][j];
            }
        }
        printArray(twoDArr);
        // deallocating
        for (int i = 0; i < rows + 1; i++) {
            delete [] twoDArr[i];
        }
        delete [] twoDArr;
    }    
}
