//HW5  AVL Tree
//Due: Monday (Nov. 14) at 11:59PM
//This homework requires more efforts. You should get started as soon as possible.
//You are not allowed to use any extra function.
//You are not allowed to add extra members to either class node or class avl_tree.

#include <iostream>

using namespace std;

//You need to use the following node class for each node of the AVL tree
class node {
public:
	int value;
	int height;//this is tree height. Leaf node is 1; empty node (i.e., NIL) is 0
	node * parent;//nullptr for root
	node * l_child;
	node * r_child;
	node() {}
	node(int i) { value = i; height = 1; parent = l_child = r_child = nullptr;}
};

class avl_tree {
public:
	node * root;
	avl_tree() {
		root = nullptr;
	}

	//************************************************************************************
	//Implement the following member functions
	void add_node(int i);
	//in case of a tie, go to the left branch.

	void delete_node(int i);
	//Delete the node with value i.  in case of multiple nodes with value i, delete the first node encountered.
	//If it is not a trivial case, always replace it with successor


	//If the node to delete is a leaf node, just delete it.
	//If the node is parent of only a left leaf node, replace it with the leaf node.
	//For all other cases, replace it with in-oreder successor

	void in_order_traversal(node *p); //such as (2 5) (3 3) (5 2) (6 1) .....  (value height)
					  //Height of leaf node is 1.

	pair<node *, int> height_update(node *p); 
	/*
	This function will be invoked by add_node and delete_node.
	p points to the first node that we need to check for possible height update.  We then need to check possible height update toward root.
	All nodes whose heights need to be updated will be performed in this function.
	In case of a violation, the function will return 
	{address of Action Node, pattern}, where violation pattern = 1, 2, 3, 4 for RR, RL LL, LR, respectively.
	In case of no violation, the function will return {nullptr, 0}.
	*/
	void L_Rotate(node *p);
	//p points to the node at which the rotation will be performed.

	void R_Rotate(node *p); 
	//p points to the node at which the rotation will be performed.
};


int main() {
//Different test cases will be used during grading.
	avl_tree t1;
	t1.add_node(45);
	t1.add_node(50);
	t1.add_node(46);
	t1.add_node(30);
	t1.add_node(34);
	t1.in_order_traversal(t1.root);
	t1.delete_node(48);
	t1.in_order_traversal(t1.root);
	return 0;
}