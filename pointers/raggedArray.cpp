/*
* Description: creates a dynamically allocated 2-d ragged array from input, prints the array in reverse
* Input: input file name passed by parameter
* Output: reversed array
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const string NEW = "-NEW";

/*
* function_identifier: prints array in reverse order
* parameters: pointer to 2d array
* return value: none
*/

void printArray (int **arr) {
    cout << arr[0][0] << endl;                          // prints out initial number (always first)
    for (int i = arr[0][0]; i >= 1; i--) {              // ends at index 1, because index 0 will not need to be printed again
                                                        // printing all elements of next array
        for (int j = 0; j < arr[i][0] + 1; j++) {       // loops until arr[i][0] + 1 because first num in row must be printed too
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

int main (int argc, char * argv[]) {
    bool c_allocation = true;                           // defaults to C allocation
    if (argv[2] == NEW.c_str()) c_allocation = false;   // becomes C++ allocation if user specifies "-NEW"
    
    int rows;
    int cols;
    ifstream input(argv[1]);                            // opening input file from command-line arg
    input >> rows;                                      // storing first value as rows to determine rows of 2d arr

    // ----------------------------------------- C Allocation -------------------------------------------------------------
    if (c_allocation) {
        int ** twoDArr = (int**)malloc(sizeof(int*)*(rows + 1));    // allocates rows + 1 to fit first (metadata) row
        for (int i = 0; i < rows + 1; i++) {
            if (i == 0) {                                           // handles case of 1st (metadata) row
                cols = 1;
                twoDArr[i] = (int*)malloc(sizeof(int) * cols);         // allocates 1 int space for first row (which always contains a number)
                twoDArr[i][0] = rows;                               // stores value of that number into that 2d arr index
                continue;                                           // continue to then begin main portion on index 1
            }
            input >> cols;
            twoDArr[i] = (int*)malloc(sizeof(int)*(cols+1));        // allocates cols + 1 to include space for first number of row
            twoDArr[i][0] = cols;                                   // assigns value of first item to first index
            for (int j = 1; j < cols + 1; j++) {                    // assigns values for all remaining items of the row
                input >> twoDArr[i][j];
            }
        }

        printArray(twoDArr);                                        // printing array

        // deallocating
        for (int i = 0; i < rows + 1; i++) {                        // deallocating all 1d arrays within 2d array
            free(twoDArr[i]);
        }
        free(twoDArr);                                              // deallocate 2d array
    } else {
        // ----------------------------------------- C++ Allocation ----------------------------------------------------------
        int ** twoDArr = new int*[rows + 1];                        // allocates rows + 1 to fit first (metadata) row
        for (int i = 0; i < rows + 1; i++) {
            if (i == 0) {                                           // handles case of 1st (metadata) row
                cols = 1;
                twoDArr[i] = new int[cols];                            // allocates 1 int space for first row (which always contains a number)
                twoDArr[i][0] = rows;                               // stores value of that number into that 2d arr index
                continue;                                           // continue to then begin main portion on index 1
            }
            input >> cols;
            twoDArr[i] = new int[cols+1];                           // allocates cols + 1 to include space for first number of row
            twoDArr[i][0] = cols;                                   // assigns value of first item to first index
            for (int j = 1; j < cols + 1; j++) {                    // assigns values for all remaining items of the row
                input >> twoDArr[i][j];
            }
        }

        printArray(twoDArr);                                        // printing array

        // deallocating
        for (int i = 0; i < rows + 1; i++) {                        // deallocating all 1d arrays within 2d array
            delete [] twoDArr[i];
        }
        delete [] twoDArr;                                          // deallocate 2d array
    }    
    input.close();                                                  // close input file
}
