// HackerRank challenge: print name of numbers < 10 and parity of number >= 10

#include <iostream>
#include <cstdio>
using namespace std;

void numToName(int num);

int main() {
    int in1, in2;
    cin >> in1 >> in2;
    // in1 = 8
    // in2 = 12
    for (int i = in1; i <= in2; ++i) {
        if (i <= 9) {
            cout << i<< "this is called" << endl;
            numToName(i);
            
        } else {
            if (i % 2 == 0) {
                cout << "even" << endl;
            } else {
                cout << "odd" << endl;
            }
        }
    }
    
    return 0;
}

void numToName(int num) {
    switch (num) {
        case 1:
            cout << "one" << endl;
            break;
        case 2:
            cout << "two" << endl;
            break;
        case 3:
            cout << "three" << endl;
            break;
        case 4:
            cout << "four" << endl;
            break;
        case 5:
            cout << "five" << endl;
            break;
        case 6:
            cout << "six" << endl;
            break;
        case 7:
            cout << "seven" << endl;
            break;
        case 8:
            cout << "eight" << endl;
            break;
        case 9:
            cout << "nine" << endl;
            break;
        default:
            cout << "error" << endl;
    }
}
