#include <iostream>
#include <stddef.h>
using namespace std;




int main() {
    //2d array
    int rows;
    int cols;
    
    cout << "rows and cols pls: ";
    cin >> rows >> cols;
    
    int **array = new int*[ rows ];
    
    for( int i = 0; i < rows; ++i )
    {
        array[ i ]  = new int[ cols ];
    }
    
    for( int i = 0; i < rows; ++i )
    {
        for( int j = 0; j < cols; ++j )
        {
            array[ i ][ j ] = 9;
        }
    }
    
    
    for (int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
    
    
    
}


