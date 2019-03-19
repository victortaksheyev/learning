#include <iostream>
using namespace std;

class a {
public:
    a () {
        *xPtr = 10;
        x = 20;
    }
    int *xPtr = new int(10);
protected:
    int x;
    
};

int main () {
    a A;
    A.*xPtr;
    
    return 0;
}
