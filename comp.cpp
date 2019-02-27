#include <time.h>
#include <iostream>
#include <math.h>

using namespace std;

class personType {
public:
    void print() {cout << "fname: "<< fname << endl << "lname: " << lname << endl;}
    personType(string f = " ", string l = " ") {fname = f; lname = l;}
private:
    string fname;
    string lname;
};

class billType {
public:
    billType(int uid = 0) {billId = uid;}
    void setid(int uid) {billId =uid;}
    int getid() const {return billId;}
    void print() {cout << "bill id: " << billId;}
private:
    int billId;
};

class doctorType : public personType {
public:
    void print() {personType::print();cout << "doc spec: " << spec << endl;}
    doctorType(string f = " ", string l = " ", string uspec = " ");
private:
    string spec;
};

doctorType::doctorType(string f, string l, string uspec) : personType(f, l) {
    spec = uspec;
}

class patientType {
public:
    patientType(string dfname = "", string dlname = "", string dspec = "", int pid = 0);
    doctorType patientDoc;
    billType patientBill;
    void setid(int pid);
    void print() {
        cout << "patient id: " << id << endl;
        patientDoc.print();
        patientBill.print();
    }
private:
    int id;
};

patientType::patientType(string dfname, string dlname, string dspec, int pid) : patientDoc(dfname, dlname, dspec),  patientBill(pid) {
    id = pid;
}

void patientType::setid(int pid) {
    id = pid;
    patientBill.setid(pid); // change must reflect to the patientbill
}

int main() {
    
    patientType p("dr jones", "millard", "dentist", 100);
    p.print();
    p.setid(1);
    cout << endl << endl << endl;
    p.print();
    cout << endl;
    return 0;
}

// look at how and why you passed objects as params in a5
