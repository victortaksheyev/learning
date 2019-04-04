#include <iostream>

using namespace std;

// gonna overload + to subtract
class a {
    public:
    a () {
        x = 0;
    }
    int x;
};
class b {
    public:
    b() {
        x = 1;
    }
    int x;
};

class clockType {
    public:
    void print () const {
        cout << "Hr: " << this->hr << endl;
        cout << "Min: " << this->min << endl;
        cout << "Sec: " << this->sec << endl;
    }

    clockType(int hr = 0, int min = 0, int sec = 0) {
        this->hr = hr;
        this->min = min;
        this->sec = sec;
    }

    // passing by constant reference which is the same as passing by value (functionally) but more efficient
    bool operator == (const clockType& otherClock) {
        return (this->hr == otherClock.hr &&
                this->min == otherClock.min &&
                this->sec == otherClock.sec);
    }
    // subtract hr, min, and sec by other clock's hr, min, sec
    friend void operator-(clockType&, clockType&);
    private:
    int hr;
    int min; 
    int sec;

};

// implementation of friend function
void operator-(clockType& clock1, clockType& clock2) {
    clock1.hr -= clock2.hr;
    clock1.min -= clock2.min;
    clock1.sec -= clock2.sec;
}


int main () {
    a myA;
    b myB;
    // myA = myB;

    clockType clock1(1, 2, 3);
    clockType clock2 (5,10,15);
    cout << "Clock 1" << endl;
    clock1.print();
    cout << endl;
    cout << "Clock 2" << endl;
    clock2.print();

    if (clock1 == clock2) {
        cout << "The two objects are equal" << endl;
    } else {
        cout << "Not equal" << endl;
    }

    cout << endl << endl << endl;

    clock2 - clock1;
    clock2.print();

    
    return 0;
}