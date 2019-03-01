#include <iostream>

using namespace std;

class smallSet {
public:
    smallSet();
    smallSet(int lx, int ly, int lz) {x = lx; y = ly; z = lz;}
    void printSmall() {cout << x << y << z << endl;}
private:
    int x, y, z;
};

smallSet::smallSet() {
    x = 1;
    y = 1;
    z = 1;
}

class largerSet : public smallSet {
public:
    largerSet(int, int);
    largerSet(int ux, int uy, int uz, int uk, int uq);
    void printLarge() {printSmall(); cout << k << q ;  cout << endl;}
private:
    int k, q;
};
largerSet::largerSet(int uk, int uq) {
    k = uk;
    q = uq;
}
largerSet::largerSet(int ux, int uy, int uz, int uk, int uq) : smallSet(ux, uy, uz){
    k = uk;
    q = uq;
}

int main()
{
    smallSet s;
    s.printSmall();
    smallSet s1(3, 4, 2);
    s1.printSmall();
    
    largerSet l(5, 5, 5, 3, 2);
    l.printSmall();
    l.printLarge();
    
    cout << endl << endl << endl;
    largerSet ls(1, 2);
    ls.printSmall();//111
    ls.printLarge();
    
}




// 25
// 3242?
