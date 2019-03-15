#include <iostream>
#include <string>

using namespace std;

class id_type {
protected:
    id_type() {id = idcnt++;}
    int id;
private:
    static int idcnt;
};

int id_type::idcnt = 0;

class ent_t {
public:
    virtual void whatamI() const = 0;
    virtual void print() const = 0;
};

class location_t {
public:
    location_t() {x = 0; y = 0;}
    location_t(int ux, int uy) {x = ux; y = uy;}
    void setX(int ux) {x = ux;}
    void setY(int uy) {y = uy;}
    void whereAmI() const {cout << "(" << x << "," << y << ")" << endl;}
private:
    int x;
    int y;
};

class human_t : public ent_t {
public:
    human_t(string s = "Default") {name = s;}
    void whatamI() const {cout << "I am a human" << endl;}
    void print() const {
        whatamI();
        cout <<"Located at "; l.whereAmI();
        cout << "My name is "; whoAmI();
    }
    void whoAmI() const {cout << name << endl;}
    void setname (string uname) {name = uname;}
    string getName() {return name;}
    location_t l;
private:
    string name;
};

class vehicle_t : public ent_t, public id_type {
public:
    vehicle_t() {driver.setname("Default");}
    vehicle_t(human_t h) {driver = h.getName();}
    void whatamI() const {cout << "I am a vehicle" << endl;}
    void print() const {
        whatamI();
        cout << "Located at "; l.whereAmI();
        cout << "Driven by: "; driver.whoAmI();
        cout << "Car ID: " << id << endl;
    }
    void setDriver(human_t h) {
        driver = h.getName();
        cout << "\nChanging driver of Car ID: " << id << endl;
    }
    location_t l;
private:
    human_t driver;
};


int main () {
    human_t human;
    human.print();
    human.setname("Jorge");
    human_t human2("Random");
    vehicle_t car(human2);
    cout << endl;
    car.print();
    
    vehicle_t vehicle;
    cout << endl;
    vehicle.print();
    
    vehicle.setDriver(human);
    vehicle.l.setX(5);
    vehicle.l.setY(10);
    cout << endl;
    vehicle.print();
    return 0;
}
