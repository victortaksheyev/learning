#include <iostream>

using namespace std;

template <class myT>
struct Nodetype {
    Nodetype() {next = prev = nullptr;}

    myT data;
    Nodetype* next;
    Nodetype* prev;
};

template <class myT>
class doubleLL {
public:
    doubleLL() { firstNode = lastNode = nullptr;}
    void insert(myT);
    void print(Nodetype<myT>*);
    Nodetype<myT>* getFirstNode() {return firstNode;};

private:
    Nodetype<myT>* firstNode;
    Nodetype<myT>* lastNode;
};

template <class myT>
void doubleLL<myT>::insert(myT data) {
    Nodetype<myT>* newNode = new Nodetype<myT>;
    newNode->data = data;

    // 1. empty
    if (firstNode == nullptr) {
        firstNode = newNode;
        lastNode = newNode;
    } 
    // 2. not empty
    else {
        lastNode->next = newNode;
        newNode->prev = lastNode;
        lastNode = newNode;
    }
}

template <class myT>
void doubleLL<myT>::print(Nodetype<myT>* head) {
    if (head == nullptr) {
        cout << endl;
        return;
    }
    cout << head->data << " ";
    print(head->next);
}

int main () {
    
    doubleLL<int> myList;
    myList.insert(3);
    myList.insert(3);
    myList.insert(3);

    myList.print(myList.getFirstNode());

    return 0;
}