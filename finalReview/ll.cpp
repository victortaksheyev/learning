#include <iostream>
using namespace std;

struct Nodetype {
  Nodetype() {
    data = -1;
    next = 0;
  }
  int data;
  Nodetype* next;
};

class LinkedList {
  public:
    LinkedList();
    void insert(const int& data);
    void printList();
    void printListRec(Nodetype* inputNode);
    void deleteElementAtIndex(int index);
    int getNumElements();
  // private:
    Nodetype* firstNode;
    Nodetype* lastNode;
};

LinkedList::LinkedList() {
  firstNode = 0;
  lastNode = 0;
}

void LinkedList::insert(const int& data){
  // step 1: create new Nodetype
  Nodetype* newNode = new Nodetype;
  newNode->data = data; // using the arrow because accessing member of a pointer

  // step 2: conditions for inserting
    // case 1: the linked list is empty
    if (firstNode == 0) {
      firstNode = newNode;
      lastNode = newNode;
    }
    // case 2: not empty 
    else {
      lastNode->next = newNode;
      lastNode = newNode;
    }
}

void LinkedList::deleteElementAtIndex(int index){
  // Case 1: if list is empty
  if (firstNode == 0) {
    return;
  }
  // Case 2: not empty
    Nodetype* temp;
    // subcase 1. first element is being deleted
    if (index == 0) {
      temp = firstNode;
      cout << "last node: " << lastNode << endl;
      // if (getNumElements() == 0) { // if it's the only element in the list
      //   firstNode = 0;
      //   lastNode = 0;
      // } else {
      //   firstNode = firstNode->next;
      // }
      firstNode = firstNode->next;

      delete temp;
    }
    // subcase 2. last element is being deleted
    if (index == getNumElements()-1) {
      temp = firstNode;
      Nodetype* temp2;
      int count = 0;
      while (count < getNumElements()-2) {  // get to the element before the last
        temp = temp->next;
        count += 1;
      }
      temp2 = temp;
      temp = lastNode;
      lastNode = temp2;
      lastNode->next = 0;
      delete temp;
    }

    // subcase 3. middle element is being deleted
    if (index < getNumElements() && index >=0) {
      Nodetype* del;
      temp = firstNode;
      int counter = 0;
      while (counter < index-1) {
        temp = temp->next;
        counter++;
      }
      del = temp->next;
      temp->next = del->next;
      delete del;
    }
    // subcase 4. element that is being deleted is the last element
}

void LinkedList::printList(){
  Nodetype* temp = firstNode;
  while (temp != lastNode) {
    cout << temp->data << " > ";
    temp = temp->next;
  }
  // printing the last Nodetype
  cout << temp->data << endl;
}

void LinkedList::printListRec(Nodetype* inputNode){
  // base case
  if (inputNode == lastNode){
    cout << inputNode->data << endl;
    return;
  }
  else {
    cout << inputNode->data << " > ";
    printListRec(inputNode->next);
  }
}

int LinkedList::getNumElements() {
  Nodetype* temp = firstNode;
  int num = 0;
  while (temp != 0) {
    num++;
    temp = temp->next;
  }
  return num;
}

void inputData(LinkedList& list, int A[], int n) {
  for (int i = 0; i < n; i++) {
    list.insert(A[i]);
  }
}

// building a linked list
int main() {
  LinkedList myList;
  int A[5] = {3, 5, 7, 10, 15};
  
  inputData(myList, A, 5);
  myList.printList();

  myList.deleteElementAtIndex(3);
  myList.printList();
  // myList.deleteElementAtIndex(0);

  myList.printList();





}