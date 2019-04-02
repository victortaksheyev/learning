#include <iostream>

using namespace std;

int main () {
    int mainsize = 6;
    int subsize = 1;
    char main[mainsize]; 
    main[0] = 'b';
    main[1] = 'a';
    main[2] = 'n';
    main[3] = 'a';
    main[4] = 'n';
    main[5] = 'a';

    char sub[subsize];
    sub[0] = 'a';
    // b a n a n a
    //   a

    
    for (int i = 0; i < mainsize; i++) {
        bool substring = true;
        for (int j = 0; j < subsize; j++) {
            if (sub[j] != main[i+j]) {
                substring = false;
            }
        }
        if (substring == true) {
            for (int j = i; j < mainsize-subsize; j++) {
                main[j] = main[j+subsize];
            }
            mainsize -= subsize;
            break;
        }
    }

    for (int i = 0; i < mainsize; i++) {
        cout << main[i] << endl;
    }


    return 0;
}