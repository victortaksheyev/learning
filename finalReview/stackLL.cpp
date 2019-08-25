#include <iostream>

using namespace std;

struct Nodetype {
	int data;
	Nodetype* next;
};


class Stack {
public:
	Stack() {
		firstNode = nullptr;
	}

	bool isEmpty() {
		if (firstNode == nullptr) {
			return true;
		}
		return false;
	}

	void push(int data) {
		Nodetype* newNode = new Nodetype;
		Nodetype* prevNode = new Nodetype;

		newNode->data = data;
		
		if (isEmpty()) {
			firstNode = newNode;
			firstNode->next = nullptr;
		}
		else {
			prevNode = firstNode;
			firstNode = newNode;
			firstNode->next = prevNode;
		}
	}

	int pop() {
		int value = -1;
		if (!isEmpty()) {
			value = firstNode->data;
			Nodetype* temp = firstNode;

			// check if it's the last node
			if (temp->next == nullptr) {
				firstNode = nullptr;
			}
			else {
				firstNode = firstNode->next;
			}

			delete temp;
		}
		return value;
	}

	void print() {
		Nodetype* temp = firstNode;
		if (isEmpty()) {
			cout << "empty" << endl;
		}
		else {
			while (temp->next != nullptr) {
				cout << temp->data << " ";
				temp = temp->next;
			}
			cout << temp->data;
			cout << endl;
		}
	}
private:
	Nodetype* firstNode;
};


int main()
{
	Stack myStack;
	for (int i = 0; i < 10; i++) {
		myStack.push(i);
	}
	myStack.print();
	for (int i = 0; i < 10; i++) {
		myStack.pop();
		myStack.print();
	}
	


}	
