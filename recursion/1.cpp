#include <iostream>
#include <math.h>

using namespace std;

int fibb(int n) {
    if (n == 1 || n == 2) {
        return 1;
    } else {
        return fibb(n-1) + fibb(n-2);
    }
}

// formula for calculating fibbonacci numbers
long BinetForm(int n) {
    double theta = (1 + sqrt(5))/2;
    double p = (1 - sqrt(5))/2;
    return (pow(theta, n) - pow(p, n))/(theta - p);

}

int main () {
    // f1 = 1
    // f2 = 1
    // f3 = 2
    // fn = fn-1 + fn-2
    int input; 
    // cout << "Input the index of the Fibonacci sequence you'd like me to ouput: ";
    cin >> input;
    for (int i = 1; i <= input; i++) {
    cout << "---------- index: " << i << "----------" << endl;
    cout << "Recursive formula result: " << fibb(i) << endl;
    // cout << "Binet formula result: " << BinetForm(i) << endl;
    cout << endl;
    }
    return 0;
}