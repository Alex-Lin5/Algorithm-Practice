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
    int length = 1;
    int flag;
    Node* var1 = p1->previous;
    Node* var2 = p2->next;
    Node* leftfirst = p1; // first block
    Node* leftlast = nullptr;
    Node* rightfirst = nullptr; // second block
    Node* rightlast = nullptr;
    Node* lastnum = nullptr;


    if (p1 == p2 || !p1 || !p2)
        return;

    if (var1) {
        var1->next = nullptr;
    }
    if (var2) {
        var2->previous = nullptr;
    }
    p1->previous = nullptr;
    p2->next = nullptr;

    while (p1 != p2) {
        length++;
        if (p2->previous) {
            p2 = p2->previous;
        }
    }

    for (int size = 1; size < length; size *= 2) {
        leftfirst = p1;
        while (leftfirst) {

            if (leftfirst == p1) {
                flag = 1;
            }
            else {
                flag = 0;
            }

            leftlast = leftfirst;
            int end = size;
            while (--end && leftlast->next) {
                leftlast = leftlast->next;
            }

            rightfirst = leftlast->next;
            if (!rightfirst)
                break;

            rightfirst->previous = nullptr;
            leftlast->next = nullptr;
            rightlast = rightfirst;
            end = size;

            while (--end && rightlast->next) {
                rightlast = rightlast->next;
            }

            Node* newfirst = rightlast->next;

            if (newfirst) {
                newfirst->previous = nullptr;
            }
            rightlast->next = nullptr;

            Merge(leftfirst, leftlast, rightfirst, rightlast);

            while (leftfirst->previous) {
                leftfirst = leftfirst->previous;
            }
            while (rightlast->next) {
                rightlast = rightlast->next;
            }

            if (flag) {
                p1 = leftfirst;
            }
            else {
                lastnum->next = leftfirst;
                leftfirst->previous = lastnum;
            }

            lastnum = rightlast;
            leftfirst = newfirst;
        }

        if (lastnum) {
            lastnum->next = leftfirst;
        }
        if (leftfirst) {
            leftfirst->previous = lastnum;
        }
    }

    while (p1->previous) {
        p1 = p1->previous;
    }
    p2 = p1;
    while (p2->next) {
        p2 = p2->next;
    }

    if (var1) {
        var1->next = p1;
        p1->previous = var1;
    }
    if (var2) {
        p2->next = var2;
        var2->previous = p2;
    }

}

void DoublyLinkedList::MergeSortRec(Node* p1, Node* p2) {
    Node* var1 = p1->previous;
    Node* var2 = p2->next;
    Node* slowpointer = p1;
    Node* fastpointer = p1;
    Node* p3 = slowpointer;
    Node* p4 = slowpointer->next;

    if (p1 == p2 || !p1 || !p2)
        return;
    if (var1) {
        var1->next = nullptr;
    }
    if (var2) {
        var2->previous = nullptr;
    }
    p1->previous = nullptr;
    p2->next = nullptr;

    while (fastpointer && fastpointer->next) {
        slowpointer = slowpointer->next;
        fastpointer = fastpointer->next->next;
    }
    slowpointer = slowpointer->previous;

    p3->next = nullptr;
    p4->previous = nullptr;

    MergeSortRec(p1, p3);
    MergeSortRec(p4, p2);

    while (p1->previous) {
        p1 = p1->previous;
    }
    while (p4->previous) {
        p4 = p4->previous;
    }
    while (p3->next) {
        p3 = p3->next;
    }
    while (p2->next) {
        p2 = p2->next;
    }

    Merge(p1, p3, p4, p2);

    while (p1->previous) {
        p1 = p1->previous;
    }
    while (p2->next) {
        p2 = p2->next;
    }

    if (var1) {
        var1->next = p1;
        p1->previous = var1;
    }
    if (var2) {
        p2->next = var2;
        var2->previous = p2;
    }

}

void DoublyLinkedList::Merge(Node* p1, Node* p2, Node* p3, Node* p4) {

    if (!p1 || !p2 || !p3 || !p4)
        return;
    while (p1 && p3) {
        if (p1->value <= p3->value) {
            p1 = p1->next;
        }
        else {
            Node* temp = p3->next;

            if (p3->previous) {
                p3->previous->next = p3->next;
            }
            if (p3->next) {
                p3->next->previous = p3->previous;
            }
            if (p1->previous) {
                p1->previous->next = p3;
            }
            p3->previous = p1->previous;
            p3->next = p1;
            p1->previous = p3;

            if (p1 == head) {
                head = p3;
            }
            if (p3 == tail) {
                tail = p2;
            }
            p3 = temp;
        }
    }
    if (p3) {
        if (p2) p2->next = p3;
        p3->previous = p2;
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
    int a{ 50 }, b{ 30 };
    DoublyLinkedList d1{ a,b }, d2{ a,b };

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

