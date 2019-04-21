#include <iostream>

using namespace std;


// 5 2 10

// 1st - largest(list, 0, 2)
// 2nd - 

int largest(int *list, int lowerI, int upperI) {
    int max;
    if(lowerI == upperI) {
        return list[lowerI];        // this is the max
                                    // essentially loop through all the elements by doing this
        
    }  else {
        max = largest(list, lowerI+1, upperI);

        if (list[lowerI] >= max)     // affects what becomes returned to previous function call
            return list[lowerI];
        else
            return max;
    }
}


int smallest(int *list, int lowerI, int upperI) {
    int min;
    if (lowerI == upperI) {
        return lowerI;
    } else {
        min = smallest(list, lowerI + 1, upperI);

        if (list[lowerI] <= min)
            return list[lowerI];
        else
            return min;
    }

}

void reverse(int a[], int left, int right) {
    if (left >= right-1) return;   // covers case for odd and even length array
    else {
            int temp;
        temp = a[left];
        a[left] = a[right-1];
        a[right-1] = temp;
        reverse(a, left+1, right-1);
    }
}

bool elementPresent(int a[], int n, int x) {
    cout << a[n-1] << endl;
    if (a[n-1] == x) return true;
    else if (n == 1) return (a[n-1]==x);
    else {
        return elementPresent(a, n-1, x);
    }
}

int main (){

    int arr[3] = {5, 4, 2};
    cout << "---MAX---" << endl;
    cout << largest(arr, 0, 2) << endl;
    cout << "---MIN---" << endl;
    cout << smallest(arr, 0, 2) << endl;
    return 0;
}
