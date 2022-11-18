//CSE674 HW2
//Due: 11:59PM, Thursday, September 22
//Do not modify main function.
//Do not introduce new functions.
//In-place implementation is required.  External structures are not allowed.
//For example, you are not allowed to copy linked list values to outside, and then process the data and copy them
//back to linked list.
//Need to use the same parameters of functions as stated.


#include <iostream>
#include <cmath>
#include <ctime>
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
	// Merge in ascending order
};

void DoublyLinkedList::MergeSortIte(Node* p1, Node* p2) {
	if(!p1 || !p2) return; // Invalid input
	else if(p1 == p2) return; // Do not sort only 1 element
	// Initialization
	int size = 1;
	int batch = 1;
	Node *pt2, *pt1, *med;
	pt1 = pt2 = p1;
	while(pt2!=p2){
		pt2 = pt2->next;
		size++;
	}
	if(!pt2){
		pt2 = p2;
		size = 1;
		while(pt2!=p1){
			pt2 = pt2->next;
			size++;
		}
		swap(p1, p2);
	}
	// Sorting
	// pt2 is next to pt1
	pt1 = med = pt2 = p1;
	while(2*batch <= size){
		if(pt2 == p2 || !pt1){
			// cout << endl << "batch=" << batch;
			// cout << endl << "MergeITR: ";
			// printForward();
			pt1 = med = pt2 = head;
			batch*=2;
		} 
		pt2 = med = pt1;
		for(int i=1; i<=2*batch; i++){
			if(med && i<batch) med = med->next;
			if(pt2 && i<size && i<2*batch) pt2 = pt2->next;
			if(!med || med == tail){
				med = p2->previous;
				pt2 = p2;
				break;
			}
			if(!pt2){
				pt2 = p2;
				break;
			} 
		}
		Node *tp = pt2->next;
		Merge(pt1, med, med->next, pt2);
		pt1 = tp;
	}
}

void DoublyLinkedList::MergeSortRec(Node* p1, Node* p2) {
	if(!p1 || !p2) return; // Invalid input
	else if(p1 == p2) return; // Do not sort only 1 element
	// Initialization
	int size = 1;
	Node *med;
	med = p1;
	while(med && med!=p2){
		med = med->next;
		size++;
	}
	if(!med){
		med = p2;
		size = 1;
		while(med && med!=p1){
			med = med->next;
			size++;
		}
		cout << endl << "swapping p1 and p2 so that p2 is next to p1.";
		swap(p1, p2);
	}
	med = p1;
	for(int i=0; i<size/2; i++){
		if(size == 2) break;
		med = med->next;
	}
	// cout << endl << "MergeRec Pass: " << p1->value << ", " << med->value << ", " << p2->value;
	// cout << endl << "Pass size=" << size;
	Node *pt1, *pt2, *pt3;
	bool flg1, flg2;
	flg1 = flg2 = false;
	pt1 = pt2 = pt3 = nullptr;
	if(p1 == head) flg1 = true;
	else pt1 = p1->previous;
	if(p2 == tail) flg2 = true;
	else pt2 = p2->next;
	pt3 = med->next;
	MergeSortRec(p1, med);
	med = pt3->previous;
	MergeSortRec(med->next, p2);
	
	if(flg1) p1 = head;
	else p1 = pt1->next;
	if(flg2) p2 = tail;
	else p2 = pt2->previous;
	med = p1;
	for(int i=0; i<size/2; i++){
		if(size == 2) break;
		med = med->next;
	}
	// cout << endl << "Sort size=" << size;
	// cout << endl << "MergeRec Sort: " << p1->value << ", " << med->value << ", " << p2->value;
	Merge(p1, med, med->next, p2);
}

void DoublyLinkedList::Merge(Node* p1, Node* p2, Node* p3, Node* p4) {
	// Initialize the list, p2 is in the direction to p1 of next, so does p4 to p3.
	// p1->next ... = p2, p3->next ... = p4
	int size1, size2;
	Node *pt1, *pt2;
	pt1 = p1; pt2 = p3;
	if(p1 == p3) return; // only 1 element
	if(!p1 || !p2){
		size1 = 0;
		cout << endl << "invalid list 1: " << "p1=" << p1 << ", p2=" << p2;
		return;
	}
	else{
		size1 = 1;
		while(pt1!=p2 && pt1){
			pt1 = pt1->next;
			size1++;
		}
		if(!pt1){
			size1 = 1;
			pt1 = p2;
			while(pt1!=p1 && pt1){
				pt1 = pt1->next;
				size1++;
			}
			cout << endl << "swapping p1 and p2.";
			p1 = p2;
			p2 = pt1;
		} 
	}
	if(!p3 || !p4){
		size2 = 0;
		cout << endl << "invalid list 2: " << "p3=" << p3 << ", p4=" << p4;
		return;
	}
	else{
		size2 = 1;
		while(pt2!=p4 && pt2){
			pt2 = pt2->next;
			size2++;
		}
		if(!pt2){
			size2 = 1;
			pt2 = p4;
			while(pt2!=p3 && pt2){
				pt2 = pt2->next;
				size2++;
			}
			cout << endl << "swapping p3 and p4.";
			p3 = p4;
			p4 = pt2;
		}
	}
	if(size1 < size2){
		// cout << endl << "swapping p1 with p3, and p2 with p4 considering the size.";
		swap(p1, p3);
		swap(p2, p4);
	}
	// cout << endl << "Merge: ";
	// cout << endl << p1 << ", " << p2 << ", " << p3 << ", " << p4;
	// cout << endl << "p1=" << p1->value << ", p2=" << p2->value;
	// cout << ", p3=" << p3->value << ", p4=" << p4->value;
	// printForward();

	// Sorting
	// Sort 2 sublist in different length
	// p3 adopt as intermediate pointers
	pt1 = p1; pt2 = p3;
	for(int i=0; i<size1+size2; i++){
		if(i != 0 && pt2 && pt2->previous && p3 == p2){ // end of sublist 1
			p2->next = pt2;
			pt2->previous = p2;
			break; // connect last element of sublist 1 to one of sublist 2
		} else if(!pt2 || (p4 && pt2->previous && pt2->previous == p4)){ // end of sublist 2
			if(!pt2){ // tail operation, end of overall list
				p2->next = nullptr;
				tail = p2;
			} else if(p3 && p4->next){
				p3 = p4->next;
				p2->next = p3;
				p3->previous = p2;
			}
			// if(!pt1 || !p4 || !pt2) return;
			p4->next = pt1;
			pt1->previous = p4;
			break; // connect last element of sublist 2, and connect tail of sublist
		}
		// pt1 indicates the most recent unsorted element in sublist 1
		// pt2 indicates the most recent unsorted element in sublist 2
		if(pt1->value > pt2->value){
			if(i==0){
				if(pt1 == head){ // head of overall list
					pt2->previous = nullptr;
					head = pt2;
				} else{
					p3 = pt1->previous;
					p3->next = pt2;
					pt2->previous = p3;
				}
			}
			if(i != 0 && (!pt2->previous || pt2->previous != p3)){
				p3->next = pt2;
				pt2->previous = p3;
			}
			p3 = pt2;
			pt2 = pt2->next;
		}
		else{ // pt1->value <= pt2->value
			if(i != 0 && (!pt1->previous || pt1->previous != p3)){
				p3->next = pt1;
				pt1->previous = p3;
			}
			p3 = pt1;
			pt1 = pt1->next;
		}
	}
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
	// srand(time(NULL));
	// int a{ 130 }, b{ 310 };
	// // int a{ 11 }, b{ 20 };
	// // int a{ 64 }, b{ 30 };
	// // int a{ 48 }, b{ 30 };
	// DoublyLinkedList d1{a,b}, d2{a,b};
	
	// cout << endl << "Original Dlist d1: ";
	// d1.printForward();
	// d1.printBackward();
	// cout << endl << "Original Dlist d2: ";
	// d2.printForward();
	// d2.printBackward();

	// // cout << endl << "After MergeItr: ";
	// // d1.MergeSortIte(d1.head, d1.tail);
	// // d1.printForward();
	// // d1.printBackward();

	// cout << endl << "After MetgeRec: ";
	// d2.MergeSortRec(d2.head, d2.tail);
	// d2.printForward();
	// d2.printBackward();
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