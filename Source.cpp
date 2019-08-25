#include <iostream>

using namespace std;

struct Stack {
	int size;
	int top;
	int* s;

	bool isFull() {
		return top == size - 1 ? true : false;
	}

	bool isEmpty() {
		return top == -1 ? true : false;
	}

	bool push(int data) {
		if (!isFull()) {
			top += 1;
			s[top] = data;
			return true;
		}
		return false;
	}

	bool pop(int& output) {
		if (!isEmpty()) {
			output = s[top];
			top -= 1;
			return	true;
		}
		return false;
	}
};

int main() {
	Stack st;
	cout << "Enter size of stack: " << endl;
	cin >> st.size;

	st.s = new int[st.size];
	st.top = -1;
	
	
	cout << "full? " << st.isFull() << endl;
	for (int i = 0; i < st.size; i++) {
		st.s[i] = 0;
	}





	return 0;
}