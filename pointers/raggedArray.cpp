#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const string NEW = "-NEW";

int main (int argc, char * argv[]) {
    bool c_allocation = true;
    if (argv[2] == NEW.c_str()) c_allocation = false; // if user specifies to use new
    
    int rows;
    ifstream input(argv[1]);                    // ifstream 
    input >> rows;                              // storing first number of file (which determines # rows) into rows
    if (c_allocation) {
        int *cols = (int*)malloc(sizeof(int) * rows);
        int ** twoDArr = (int**)malloc(sizeof(int *) * rows);
        for (int i = 0; i < rows; i++) {
            input >> cols[i];                       // storing first number of each row (which determines # cols) into cols
            twoDArr[i] = (int *)malloc(sizeof(int) * cols[i]);
            for (int j = 0; j < cols[i]; j++) {     // storing data into the columns
                input >> twoDArr[i][j];
            }    
        }

    } else { 
        int *cols = new int[rows];
        int ** twoDArr = new int*[rows];

        for (int i = 0; i < rows; i++) {
            input >> cols[i];                       // storing first number of each row (which determines # cols) into cols
            twoDArr[i] = new int[cols[i]];
            for (int j = 0; j < cols[i]; j++) {     // storing data into the columns
                input >> twoDArr[i][j];
            }    
        }
    }

    // printing out info
    cout << rows << endl;                       // printing first element
    // loop to print out array in reverse
    for (int i = rows-1; i >= 0; i--) {         // beginning at rows-1 because rows is size of array [0, row-1]
        cout << cols[i] << " ";                 // printing out first (metadata) columns 
        for (int j = 0; j < cols[i]; j++) {     // loop to print out columns
            cout << twoDArr[i][j] << " ";
        }
        cout << endl;
    }

    // de-allocating memory
    if (malloc) {
        for (int i = 0; i < rows; i++) {
            free(twoDArr[i]);
        }
        free (twoDArry);
        free (cols)
    } else {
        for (int i = 0; i < rows; i++) {
            delete [] twoDArr[i];
        }
        delete [] twoDArr;                      // deallocating 1d array
        delete [] cols;
    }

    input.close();                              // closing input file


    return 0;
}