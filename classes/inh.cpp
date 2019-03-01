#include <time.h>
#include <iostream>
#include <math.h>

using namespace std;

class a {
public:
    a();
    int publicx;
    int getprivatex() const {return privatex;}
    int getprotectedx() const {return protectedx;}
protected:
    int protectedx;
private:
    int privatex;
};

a::a(){
    publicx = 10;
    protectedx = 5;
    privatex = 1;
}

class b : private a {
public:
    void print() {cout << publicx << endl;}
};

int main() {
    b myB;
//    cout << "public x of a: " << myB.publicx << endl;
//    cout << "protected x of a: " << myB.getprotectedx() << endl;
//    cout << "private x of a: " << myB.getprivatex() << endl;
    myB.print(); // print still has access to public and protected of a which is why this works
                 // however, to an object of b, they will be private (cannot access directly)
    
    return 0;
}
