// program that will create dynamic 2 d array from any data type
#include <iostream>
#include <string>

using namespace std;

template <typename myT>
myT** createArr(int cols, int rows) {
    myT** arr = new myT*[rows];
    for (int i = 0; i < rows; i++) {
        arr[i] = new myT[cols];
    }
    return arr;
}

template <typename myT>
void populateArr(int cols, int rows, myT** & arr, myT content) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = content;
        }
    }
}

template <typename myT>
void printArr(int cols, int rows, myT** arr) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

int main () {
    string** arr = createArr<string>(5, 10);
    populateArr<string>(5, 10, arr, "aylmao");
    printArr<string>(5, 10, arr);

}
