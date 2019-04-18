#include <iostream>

using namespace std;

int main () {

    // int ** arr = new int*[10];
    // for (int i = 0; i < 10; i++){
    //     arr[i] = new int[5];
    // }

    // for (int i = 0; i < 10; i++)
    //     for(int j = 0; j < 5; j++){
    //         arr[i][j] = 9;
    //     }

    // for (int i = 0; i < 10; i++) {
    //     for(int j = 0; j < 5; j++){
    //         cout << arr[i][j];
    //     }
    //     cout << endl;
    // }

    // for (int i = 0; i < 10; i++){
    //     delete[] arr[i];
    // }
    // delete[]arr;

    int *ptr = new int[10];
    for (int i = 0; i < 10; i++){
        ptr[i] = i+1;
        cout << ptr[i] << " ";
    }
    cout << endl;
    
    cout << "------------- DOING POINTER ARITHMETIC -------------" << endl;
    int i =0;
    cout << ptr[i++] << endl;   // 1
    i =0;
    cout << ptr[++i] << endl;   // 2
    i =0;
    cout << *(ptr+1) << endl;   // 2

    i =0;
    cout << *(ptr++) << endl;   // 4
    i =0;
    cout << *(++ptr) << endl;   // 4
    
    return 0;
}
