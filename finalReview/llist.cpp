#include <iostream>

using namespace std;

struct nodeType {
    int data;
    nodeType* link;
};

class linkedList {
    public:
    void insert(int data){
        // create a new node
        nodeType* newNode = new nodeType;
        newNode->data = data;
        newNode->link = nullptr;
            // case 1: the linked list is empty
            if (head == nullptr) {
                head = newNode;
                last = newNode;
            }else { // case 2: the linked list is not empty
                last->link = newNode;
                last = newNode;
            }
            
    }

    void deleteItem(int data) {
        nodeType* curr = head;
        nodeType* prev;

        // if first element is the one that needs to be deleted
        if (head->data == data) {
            curr = head;
            // if that item is the only item in the list
            if (curr->link == nullptr) {
                
                delete curr;
                head = nullptr;
                last = nullptr;
            }
            // otherwise there is some item coming after it
            else {
                
                head = curr->link;
                delete curr;
            }
            
        } else {
            while (curr->data != data){
                prev = curr;
                curr = curr->link;
            }
            if (curr->link == nullptr){       // if we're trying to del the last element
                delete curr;
                prev->link = nullptr;
                last = nullptr;
            } else {
            prev->link = curr->link;
            delete curr;
            }
        }

    }

    void print() {
        nodeType* curr = head;
        while (curr != nullptr) {
            cout << curr->data << "->";
            curr = curr->link;
        }
    }
    linkedList();    
        nodeType* head;
        nodeType* last;
};

linkedList::linkedList() {
    head = nullptr;
    last = nullptr;
}

int main () {
    linkedList myList;

    myList.insert(10);
    myList.insert(11);
    myList.insert(12);
    myList.deleteItem(12);

    myList.print();

    return 0;
}