

#include <iostream>
#include <string>

using namespace std;

class date_t {
public:
    // constructor with default params
    date_t(int d = 0, int m = 0, int y = 0);
    
    void printDate() const {
        cout << mm << "/" << dd << "/" << yyyy << endl;
    }
    void getD(int &day) const {
        day = dd;
    }
    void setD(int day) {
        dd = day;
    }
public:
    int dd;
    int mm;
    int yyyy;
};

date_t::date_t(int d, int m, int y) {
    dd = d;
    mm = m;
    yyyy = y;
}

class event_t {
public:

    date_t myDate;
    event_t(string) : myDate(5, 10, 11) {};
    void printEvent() const {
        cout << "Event: " << eventName << endl <<  "Date: ";
        myDate.printDate();
        cout << endl;
    }
private:
    string eventName;
    static int eventNum;
};

//event_t::event_t(string name, int d, int m, int yr) : date_t(d, m, yr) {
//    eventName = name;
//    dd = d;
//    mm = m;
//    yyyy = yr;
//}

int main() {
    event_t newEvent("tv");
    newEvent.printEvent();
//    date_t myDate(10, 10, 20);
//    myDate.printDate(); // prints 10, 10, 20
//    event_t tv("travis scott concert", 10, 10, 10); // will print 0/0/0 because derived constructor only applies to vars that derived class inherits
                                                        // since im using composition, i cant actually change them
//    tv.printEvent();
    // insert code here...
    
}
