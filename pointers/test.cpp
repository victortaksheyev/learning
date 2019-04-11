#include <iostream>

using namespace std;

class String {
    public:
        String(int size = 1);
        friend istream & operator >> (istream &in, String &);
        friend ostream & operator << (ostream & out, String &);
        void operator = (const String & otherString);
       
    private:
        char*strArr;
        int size;
};

void String::operator = (const String & otherString) {
    for (int i = 0; i < otherString.size; i++) {                // performing deep copy
        this->strArr[i] = otherString.strArr[i];
    }
}

istream & operator>>(istream &in, String & s) {
    int letters = 0;
    while (!(in.peek() == ' ' || in.peek() == '\n' ||in.peek() == EOF)) {
        in >> s.strArr[letters];
        ++letters;
        if (letters >= s.size) {
            String temp(s.size);            // creating a temporary object
            temp = s;                       // deep copying s into temp
            cout << endl;
            delete [] s.strArr;             // deleting old (small) string
            s.strArr = new char [letters];  // creating new (larger) string
            s.size = temp.size+1;

            s = temp;
        }
    }
    return in;
}

ostream & operator << (ostream & out, String & s) {
    for (int i = 0; i < s.size; i++) {
        out << s.strArr[i];
    }
    out << '\n';
    return out;
}

String::String(int size) {
    this->size = size;
    strArr = new char [size];
}


int main () {

    String myString;
    cin >> myString;
    cout << "Your string is:" << endl;
    cout << myString;


    return 0;
}