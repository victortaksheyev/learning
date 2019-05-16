#include <iostream>
#include <cmath>
#include <string>

using namespace std;


// recursive function to return the max element of array
int max (int* arr, int size){
    if (size == 1) return arr[size-1] > arr[size] ? arr[size-1] : arr[size];
    else {
        return max(arr, size-1) > arr[size-1] ? max(arr, size-1) : arr[size-1];
    }
}


int betterMax (int* arr, int s) {
    int maxNum;
    if (s == 0) return -1;
    if (s == 1) return arr[s-1];    // return that only element
    else {                          // recurse
       return betterMax(arr, s-1) > arr[s-1] ? betterMax(arr, s-1) : arr[s-1];
    }
}

// converts binary number to decimal number
void binaryToDec(int binaryNum, int& decimal, int& weight) {        // make sure these are reference parameters!!!
    // specify base case
    if (binaryNum > 0) {
        // get a bit
        int bit = binaryNum%10;     // this can be %2
        // bit*base^(weight)
        decimal += bit * pow(2, weight);       // we have successfully performed it on right bit, now let's move on
        weight +=1;
        // recurse
        binaryToDec(binaryNum/10, decimal, weight);
    }   
}



void hexToDec(string hexNum, int& hexSize, int& decimal, int& weight){
    if (hexSize>0) {
        char character = hexNum[hexSize-1];         // stores rightmost character (like the right-most bit)
        int coef;                                   // the numerical value of the character
        switch(character) {
            case 'A':
                coef = 10;
                break;
            case 'B':
                coef = 11;
                break;
            case 'C':
                coef = 12;
                break;
            case 'D':
                coef = 13;
                break;
            case 'E':
                coef = 14;
                break;
            case 'F':
                coef = 15;
                break;
            defualt:
                cout << "we are in defualt" << endl;
                coef = character - 48;
                break;
        }
        cout << coef << endl;
        decimal += coef* pow(16, weight);
        // recurse
        hexToDec(hexNum, --hexSize, decimal, ++weight);
    }
}

void decToBin(int num, int base) {
    if (num>0) {
        decToBin(num/base, base);
        cout << num%base;
    }
}

/*



*/

int main (){

    int arr[5] = {1, 2, 5, 9, 0};
    int arr1[5] = {9, 2, 5, 5, 0};
    int arr2[5] = {1, 2, 5, 2, 9};

    // printf ("Max - %i",betterMax(arr, 5));
    // printf ("Max - %i",max(arr, 5));

    // printf("%i", 1011%10);
    int bitWeight = 0;      // initial condition
    int decimalNum = 0;     // initial condition
    // binaryToDec(11010110, decimalNum, bitWeight);
    int size = 2;
    hexToDec("AD", size, decimalNum, bitWeight); // should be 15
    printf("The hex num is %i", decimalNum);
    
    int dec = 10;
    int bNum = 0;
    int iter = 1;
    cout << "The binary number is: " << endl;
    decToBin(100, 2);



    return 0;
}