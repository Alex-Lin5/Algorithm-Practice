//CSE674 HW2
//Due: 11:59PM, Sunday, September 25
//Do not modify main function.
//Do not introduce new functions.
//In-place implementation is required.  External structures are not allowed.
//For example, you are not allowed to copy linked list values to outside, and then process the data and copy them
//back to linked list.
//Need to use the same parameters of functions as stated.
//For all three functions, using call by reference to pass pointers is also acceptable.

#include <iostream>
using namespace std;

class Node {
public:
	int value;
	Node* next;
	Node* previous;
	Node(int i) { value = i; next = previous = nullptr; }
	Node() { next = previous = nullptr; }
};

class DoublyLinkedList {
public:
	Node* head;
	Node* tail;
	DoublyLinkedList() { head = tail = nullptr; }
	DoublyLinkedList(int n, int m);//constructor for an n-node DoublyLinkedList with random values in 0 ... m-1  
	void printForward();
	void printBackward();
	//implement the following member function:
	void MergeSortIte(Node* p1, Node* p2);//Implement MergeSort iteratively. Sort a portion of a DoublyLinkedList, from the node pointed by p1 to the node pointed by p2.
	void MergeSortRec(Node* p1, Node* p2); //Implement MergeSort recursively. Sort a portion of DoublyLinkedList, from the node pointed by p1 to the node pointed by p2.
	void Merge(Node* p1, Node* p2, Node* p3, Node* p4); //Merge two portions of a DoublyLinkedList, one from the node pointed by p1 to the node pointed by p2 and
	//the other from the node pointed by p3 to the node pointed by p4.
	//The function Merge can be called by functions MergeSortIte and MergeSortRec;
};

void DoublyLinkedList::MergeSortIte(Node* p1, Node* p2) {
	//Your code
}

void DoublyLinkedList::MergeSortRec(Node* p1, Node* p2) {
	//Your code
}

void DoublyLinkedList::Merge(Node* p1, Node* p2, Node* p3, Node* p4) {
	//Your code
}



DoublyLinkedList::DoublyLinkedList(int n, int m) {
	head = tail = nullptr;
	for (int i = 0; i < n; ++i) {
		Node* p1 = new Node{ rand() % m };
		if (!head) {
			head = tail = p1;
		}
		else {
			tail->next = p1;
			p1->previous = tail;
			tail = p1;
		}
	}
}


void DoublyLinkedList::printForward() {
	cout << endl;
	Node* p1 = head;
	while (p1) {
		cout << p1->value << " ";
		p1 = p1->next;
	}
}

void DoublyLinkedList::printBackward() {
	cout << endl;
	Node* p1 = tail;
	while (p1) {
		cout << p1->value << " ";
		p1 = p1->previous;
	}
}

int main() {
	int a{ 50 }, b{ 30 };
	DoublyLinkedList d1{a,b}, d2{a,b};

	d1.printForward();
	d1.printBackward();

	d1.MergeSortIte(d1.head, d1.tail);
	d1.printForward();
	d1.printBackward();


	d2.MergeSortRec(d2.head, d2.tail);
	d2.printForward();
	d2.printBackward();

	return 0;
}