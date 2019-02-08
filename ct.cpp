#include <iostream>
#include <string>

using namespace std;

class human {
    public:
        human();
        human(string);
        void printInfo();
    private:
        string name;
};

void human::printInfo() {
    cout << "Name: " << name << endl;
}

human::human(string humName) {
    name = humName;
}

human::human() {        //default constructor
    name = "defaultName";
}

class employee : public human {
	public:
        employee(int, string);
        void getVals(string&, int&, int&);
        void changeId(int);
        void printInfo();
        
    private:
        int salary;
        int id;
        static int empNum;
};

// initializing static var
int employee::empNum = 0;

// creating constructor for derived class requires to initialize constructor for base class
// empName initializes both
employee::employee(int empSal, string empName) : human(empName) {
    salary = empSal;
    id = empNum++; // give the first object defined 0, the next 1, etc...
}

// getter func
void employee::getVals(string& empName, int& empSal, int& empId) {
    empSal = salary;
    empId = id;
}

// mutator func
void employee::changeId(int newSal){
    salary = newSal;
}

void employee::printInfo() {
    cout << endl;
    cout << "----------------------------------------------" << endl;    
    cout << "Information about employee id " << id << endl;
    human::printInfo();
    cout << "Salary: " << salary << endl;
    cout << "----------------------------------------------" << endl;
}

int main() {
    string empName;
    int empSal;
    int empId;
    
    human hum1("Ilya");
    hum1.printInfo();
    
    employee emp1(10, "Mikian"); // name is only applied to instance of name var
                                 // that derived class inherits from base
                                 // not applied to base class itself
    employee emp2(20, "Victor");
    emp1.printInfo();
    hum1.printInfo();
    emp2.printInfo();
    
    return 0;

}
