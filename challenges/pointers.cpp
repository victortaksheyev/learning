// HackerRank challenge: You have to complete the function void update(int *a,int *b), which reads two integers as argument, and sets a with the sum of them, and b with the absolute difference of them.
#include <stdio.h>

void update(int *a,int *b) {
    // Complete this function
    int temp;
    temp = *a;          // storing the value that a points to in temp
    // store a+b in a
    *a = *a + *b;
    // store abs(a-b) in b
    if (temp-*b < 0) {
        *b = -1*(temp - *b);
    } else if (temp-*b >= 0) {
        *b = temp - *b;
    }
    
}

int main() {
    int a, b;
    int *pa = &a, *pb = &b;
    
    scanf("%d %d", &a, &b);
    update(pa, pb);
    printf("%d\n%d", a, b);
    printf("\n");
    
    return 0;
}

