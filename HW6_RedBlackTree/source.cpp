//CSE674 HW6  Due: 11:59PM, Dec. 1 Thursday
#include <iostream>
using namespace std;

class node {
public:
	node* p_parent;
	node* p_Lchild;
	node* p_Rchild;
	int value;
	bool color; //true: red, false: black
	node() { p_parent = p_Lchild = p_Rchild = nullptr; is_left_child = is_right_child = false; }
	node(int i) { value = i; p_parent = p_Lchild = p_Rchild = nullptr; is_left_child = is_right_child = false; color = true;}
};

class tree {
public:
	node* root;
	tree() { root = nullptr; }
	void R_rotate(node* p);//R-rotate at node pointed by p
	void L_rotate(node* p);//L-rotate at node pointed by p
	//R_rotate and L_rotate will be called by insert_node, delete_node, delete_1, delete_2A, delete_2B, and delete_3.

	void add_node(int i);//same policy as HW5 for avl trees.
	
	void delete_node(int i);//same policy as HW5 for avl trees.
	

	
	void delete_1(node* p, bool b);
	//Case 1 of delete_node; p points to the parent of double black node; b is true if double black is the left child of its parent; else b is false.

	void delete_2A(node* p, bool b);
	//Case 2A of delete_node; p points to the parent of double black node; b is true if double black is the left child of its parent; else b is false.

	void delete_2B(node* p, bool b);
	//Case 2B of delete_node; p points to the parent of double black node; b is true if double black is the left child of its parent; else b is false.


	void delete_3(node* p, bool b);
	//Case 3 of delete_node; p points to the parent of double black node; b is true if double black is the left child of its parent; else b is false.


	//For the following, during traveral, print (value, color) of each node.
	void InorderPrint(node * p);//Print all nodes of a subtree rooted at node pointed by p; Example: (12 R) (7 B) (11 R) ...

};

int main() {
	tree T1;
	T1.add_node(50);
	T1.add_node(100);
	T1.add_node(30);
	T1.add_node(200);
	T1.add_node(300);
	T1.add_node(250);
	T1.add_node(280);
	T1.delete_node(200);
	T1.InorderPrint(T1.root);
	cout << endl;

	return 0;
}