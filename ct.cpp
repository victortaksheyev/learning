#include <iostream>
#include <string>

using namespace std;

class employee {
	public:
        employee(int, string);
        void getVals(string&, int&, int&);
        void changeId(int);
        void printInfo();
        
    private:
        string name;
        int salary;
        int id;
        static int empNum;
};

// initializing static var
int employee::empNum = 0;

employee::employee(int empSal, string empName) {
    salary = empSal;
    name = empName;
    id = empNum++; // give the first object defined 0, the next 1, etc...
}

// getter func
void employee::getVals(string& empName, int& empSal, int& empId) {
    empSal = salary;
    empName = name;
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
    cout << "Name: " << name << endl;
    cout << "Salary: " << salary << endl;
    cout << "----------------------------------------------" << endl;
}

int main() {
    string empName;
    int empSal;
    int empId;
    
    employee emp1(10, "Mikian");
    employee emp2(20, "Victor");
    emp1.printInfo();
    emp2.printInfo();
    
    return 0;

}
