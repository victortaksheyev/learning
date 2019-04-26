#include <iostream>
#include <string>

using namespace std;


int main()
{
    string toLookFor[4] = {"81", "229", "222", "230"};
    bool swap = true;
    int j = 0;
    while (swap) {
        j++;
        swap = false;
        string temp;
        for (int i = 0; i<4-j; i++) {
            if (toLookFor[i+1].compare(toLookFor[i]) < 0) {
                temp = toLookFor[i+1];
                toLookFor[i+1] = toLookFor[i];
                toLookFor[i] = temp;
                swap = true;
            }
        }
    }
    
    for (int j = 0; j<4; j++) {
        cout << toLookFor[j] << " ";
        
    }

    
//    int num = toLookFor[1].compare(toLookFor[2]);
//    cout << num << endl;
    cout << endl;
//
//    int num = 1;
//    char cNum = '0' +num;
//    cout << cNum << endl;
    
    // convert double float and int to a string and then bubble sort them
    
    
    // if p, array toLookFor becomes the array of prices; if t, it becomes titles...
    // toLookFor is what is used by the bubble sort
    // it is all a string at that point
    
    return 0;
}
