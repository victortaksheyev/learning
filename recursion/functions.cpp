void printArray(int a[], int n) {
  if(n>0) {                             // continue until at the first index
    printArray(a, n-1);                 // head (call function)
    cout << a[n-1] << " ";              // tail (print)
  }
}

/*
    * function_identifier: reverses the content of a n integer array a[]
    * parameters: array, left element, right element
    * return value: none
*/

void reverse(int a[], int left, int right) {
    if (left >= right-1) return;        // covers case for odd and even length array
    else {  
        int temp;                       // create a temp var
        temp = a[left];                 // store left data in temp
        a[left] = a[right-1];           // swap left with right
        a[right-1] = temp;              // swap right with left
        reverse(a, left+1, right-1);    // perform operation again, recursively
    }
}

/*
    * function_identifier: returns true if integer x is found in integer array a of size n
    * parameters: array, size, element to look for
    * return value: true if found, false otherwise
*/

bool elementPresent(int a[], int n, int x) {
    if (a[n-1] == x) return true;           // returns true id finds one match
    else if (n == 1) return (a[n-1]==x);    // checks and returns last element
    else {
        return elementPresent(a, n-1, x);   // performs same operation again
    }
}

/*
    * function_identifier: checks if a given array is a palindrom
    * parameters: array, left element, right element
    * return value: true if palindrome, false otherwise
*/

bool isPalindrome(int a[], int left, int right) {
    if (left > right-1) return true;                    // checks if entire array has been traversed
    else if (a[left]!= a[right - 1]) return false;      // returns false if one element doesnt match
    else {
        return isPalindrome(a, left+1, right-1);        // performs check again, recursively
    }
}

/*
    * function_identifier: outputs to stdout the reverse of the given integer
    * parameters: number to reverse
    * return value: none
*/

void reverseDisplay(int num) {
    if (num/10 == 0) {cout << num; return;}             // if its the last digit, output it
    else {
        cout << num%10;                                 // output right digit
        num /= 10;                                      // remove right digit
        reverseDisplay(num);                            // continue recursively
    }
}
