//HW5  AVL Tree
//Due: Monday (Nov. 14) at 11:59PM
//This homework requires more efforts. You should get started as soon as possible.
//You are not allowed to use any extra function.
//You are not allowed to add extra members to either class node or class avl_tree.

#include <iostream>
#include <algorithm>

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
	// // random input
	// t1.add_node(100);
	// t1.add_node(20); // 7 nodes
	// t1.add_node(20);
	// t1.add_node(20);
	// t1.delete_node(100);
	// t1.delete_node(34);
	// t1.delete_node(30);
	// t1.delete_node(45);
  // t1.add_node(38);
  // t1.add_node(78);
  // t1.add_node(28);
  // t1.add_node(55);
  // t1.add_node(92);
  // t1.add_node(34);
  // t1.add_node(88);
	// t1.delete_node(45);
	// t1.delete_node(50);
	// t1.delete_node(46);
	// t1.delete_node(30);
	// t1.delete_node(34);
  // t1.delete_node(28);
  // t1.delete_node(55);
  // t1.delete_node(92);
  // t1.delete_node(34);
  // t1.delete_node(88);
	// // left heavy 7 0, pat 3
	// t1.add_node(0);
	// t1.add_node(0);
	// t1.add_node(0);
	// t1.add_node(0);
	// t1.add_node(0);
	// t1.add_node(0);
	// t1.add_node(0);
	// t1.delete_node(0);
	// t1.delete_node(0);
	// t1.delete_node(0);
  // t1.delete_node(88);
	// t1.delete_node(0);
	// t1.delete_node(0);
	// t1.delete_node(0);
	// t1.delete_node(0);	
  // t1.delete_node(0);
  // // right heavy, pat 1
  // t1.add_node(1);
  // t1.add_node(2);
  // t1.add_node(3);
  // t1.add_node(4);
  // t1.add_node(5);
  // t1.add_node(6);
  // t1.add_node(7);
  // t1.add_node(8);
  // t1.add_node(9);
  // t1.add_node(10);
  // t1.add_node(11);
  // t1.add_node(12);
  // t1.add_node(13);
  // t1.delete_node(1);
  // t1.delete_node(2);
  // t1.delete_node(3);
  // t1.delete_node(4);
  // t1.delete_node(5);
  // t1.delete_node(6);
  // t1.delete_node(7);
  // t1.delete_node(8);
  // t1.delete_node(9);
  // t1.delete_node(10);
  // t1.delete_node(11);
  // t1.delete_node(12);
  // t1.delete_node(13);

	return 0;
}

void avl_tree::in_order_traversal(node *p){
  if(p == nullptr) return;
  in_order_traversal(p->l_child);
  cout << "(" << p->value << " " << p->height << ") ";
	if(p->l_child)
		cout << p->l_child->value << "/ ";
	if(p->r_child)
		cout << "\\" << p->r_child->value << " ";
  in_order_traversal(p->r_child);
}

void avl_tree::add_node(int i){
  // add first node
  node* addn = new node(i);
  if(root == nullptr){
		root = addn;
		return;
	} 
  // find the leaf position of new node
  node* now = root;
  while(now != nullptr){
    if(i <= now->value){
      if(now->l_child)
        now = now->l_child;
      else{
        now->l_child = addn;  
        addn->parent = now;
        break;
      }
    } 
    else if(i > now->value) {
      if(now->r_child)
        now = now->r_child;
      else{
        now->r_child = addn;
        addn->parent = now;
        break;
      }
    }
  }
	// cout << endl << "Add: node=" << addn << ", value=" << addn->value;
	cout << endl;
	in_order_traversal(root);
  // update height and solve violation
  node *an = nullptr; int pat = -1;
	auto pr = height_update(addn);
	an = pr.first; pat = pr.second;
  if(!an) return;
  else if(pat == 1){ // RR
    L_Rotate(an);
    if(!an->l_child) an->height = 1;
    else an->height = an->l_child->height+1;
    if((height_update(addn)).first) 
      cout << endl << "RR pattern violated after adding node " << addn << ". value = " << i;
  } else if(pat == 2){ // RL
    now = an->r_child;
    an->height -= 2;
    R_Rotate(an->r_child);
    L_Rotate(an);
    if((height_update(now)).first) 
      cout << endl << "RL pattern violated after adding node " << addn << ". value = " << i;
  } else if(pat == 3){ // LL
    R_Rotate(an);
    an->height = an->parent->height-1;
    if((height_update(addn)).first) 
      cout << endl << "LL pattern violated after adding node " << addn << ". value = " << i;
  } else if(pat == 4){ // LR
    now = an->l_child;
    an->height -= 2;
    L_Rotate(an->l_child);
    R_Rotate(an);
    if((height_update(now)).first) 
      cout << endl << "LR pattern violated after adding node " << addn << ". value = " << i;
  }
}
void avl_tree::delete_node(int i){
  if(!root){
    cout << endl << "Root is not existed";
    return;
  }
  node* dlt = root;
  node* up = root;
  while(dlt){
    if(i < dlt->value) dlt = dlt->l_child;
    else if(i > dlt->value) dlt = dlt->r_child;
    else break; // i == dlt->value
  }
  cout << endl;
  in_order_traversal(root);
	cout << endl << "Del: node=" << dlt << ", value=" << i;
  if(dlt) cout << ", hei=" << dlt->height;
  if(!dlt){
    cout << endl << "Node with value " << i << " is not existed in this tree. Root=" << root;
    return;
  } else if(!dlt->l_child || !dlt->r_child){ // trivial case
    // node* op = root;
    // if(i <= dlt->parent->value) op = dlt->parent->l_child;
    // else if(i > dlt->parent->value) op = dlt->parent->r_child;    
    if(!dlt->parent){
      up = nullptr;
      if(!dlt->l_child && !dlt->r_child){
        root = nullptr;
      } else if(!dlt->l_child){
        up = dlt->r_child;
      } else if(!dlt->r_child){
        up = dlt->l_child;
      }
      delete dlt;
      if(up){
        root = up;
        root->parent = nullptr;
        up->height = 1;
      }
      return;
    }
    if(!dlt->l_child && !dlt->r_child){
      // op = nullptr;
      // if(i <= dlt->parent->value) dlt->parent->l_child = nullptr;
      // else if(i > dlt->parent->value) dlt->parent->r_child = nullptr;
      if(dlt == dlt->parent->l_child) dlt->parent->l_child = nullptr;
      else if(dlt == dlt->parent->r_child) dlt->parent->r_child = nullptr;
    } else if(!dlt->r_child){
      // op = dlt->l_child;
      // if(i <= dlt->parent->value) dlt->parent->l_child = dlt->l_child;
      // else if(i > dlt->parent->value) dlt->parent->r_child = dlt->l_child;
      if(dlt == dlt->parent->l_child) dlt->parent->l_child = dlt->l_child;
      else if(dlt == dlt->parent->r_child) dlt->parent->r_child = dlt->l_child;
      dlt->l_child->parent = dlt->parent;
    } else if(!dlt->l_child){
      // op = dlt->r_child;
      // if(i <= dlt->parent->value) dlt->parent->l_child = dlt->r_child;
      // else if(i > dlt->parent->value) dlt->parent->r_child = dlt->r_child;
      if(dlt == dlt->parent->l_child) dlt->parent->l_child = dlt->r_child;
      else if(dlt == dlt->parent->r_child) dlt->parent->r_child = dlt->r_child;
      dlt->r_child->parent = dlt->parent;
    } 
    up = dlt->parent;
    delete dlt;
  } else{ // delete node in the middle of tree
    // replace the value of delete node to its successor
    node* suc = dlt->r_child;
    while(suc->l_child){
      suc = suc->l_child;
    }
    dlt->value = suc->value;
    // reconnect parent of suc
    if(suc == suc->parent->l_child){
      suc->parent->l_child = suc->r_child;
    } else if(suc == suc->parent->r_child){
      suc->parent->r_child = suc->r_child;
    }
    // reconnect the rchild of successor
    if(suc->r_child){
      suc->r_child->parent = suc->parent;
      up = suc->r_child;
    } else{
      up = suc->parent;
    }
    delete suc;
  }
  node *an{up}; int pat{0};
  do{
    auto pr = height_update(an);
		an = pr.first; pat = pr.second;
    if(!an) break;
    if(pat == 1){ // RR
      L_Rotate(an);
      if(!an->l_child) an->height = 1;
      else an->height = an->l_child->height+1;
    } else if(pat == 2){ // RL
      an->height -= 2;
      up = an->r_child;
      R_Rotate(an->r_child);
      L_Rotate(an);
      an = up;
    } else if(pat == 3){ // LL
      R_Rotate(an);
      an->height = an->parent->height-1;
    } else if(pat == 4){ // LR
      an->height -= 2;
      up = an->l_child;
      L_Rotate(an->l_child);
      R_Rotate(an);
      an = up;
    }

  } while(an);
	cout << endl;
	in_order_traversal(root);
}
pair<node *, int> avl_tree::height_update(node *p){
  if(!p){
    cout << endl << "Node passed is not existed.";
    return make_pair(nullptr, -1);
  }
	cout << endl << "Height: " << "node=" << p << ", val=" << p->value << ", hei=" << p->height;
  node *op = p;
  do{
    // update height
    if(!op->l_child && !op->r_child){
      op->height = 1;
    } else if(!op->l_child){
      op->height = 1 + op->r_child->height;
    } else if(!op->r_child){
      op->height = 1 + op->l_child->height;
    } else{
      op->height = 1 + max(op->l_child->height, op->r_child->height);
    }
    // check violation
		if(!op->l_child && !op->r_child) ; // pass
		else if(!op->l_child && op->r_child && op->r_child->height > 1)
			break;
		else if(!op->r_child && op->l_child && op->l_child->height > 1)
			break;
    else if(op->l_child && op->r_child && abs(op->l_child->height-op->r_child->height) > 1){
      break;
    } 
    if(op == root) return make_pair(nullptr, 0);
    op = op->parent;
  } while(1);
  {
    int pat = 0;
    node *p1, *p2;
    p1 = p2 = nullptr;
		if(!op->l_child && !op->r_child)
			cout << endl << "Action node is leaf node. node=" << op << ", value=" << op->value;
    if((op->l_child && !op->r_child) ||
			op->r_child && op->l_child &&
			op->l_child->height > op->r_child->height) 
			p1 = op->l_child;
    else if((op->r_child && !op->l_child) ||
			op->r_child && op->l_child &&
			op->l_child->height < op->r_child->height) 
			p1 = op->r_child;
    else if(op->l_child->height == op->r_child->height){
      cout << endl << "First part of left and right branch share the same height=" << op->l_child->height << ", of AN=" << op << ", val=" << op->value;
    }
    if((p1->l_child && !p1->r_child) ||
			p1->r_child && p1->l_child &&
      p1->l_child->height >= p1->r_child->height &&
      p1 == op->l_child
      ) 
			p2 = p1->l_child;
    else if((p1->r_child && !p1->l_child) ||
			p1->r_child && p1->l_child &&
      p1->l_child->height <= p1->r_child->height &&
      p1 == op->r_child
      ) 
			p2 = p1->r_child;
    if(p1 == op->r_child && p2 == p1->r_child) pat = 1;
    else if(p1 == op->r_child && p2 == p1->l_child) pat = 2;
    else if(p1 == op->l_child && p2 == p1->l_child) pat = 3;
    else if(p1 == op->l_child && p2 == p1->r_child) pat = 4;
		cout << ". pat=" << pat;
    return make_pair(op, pat);
  }
}
void avl_tree::L_Rotate(node *p){
  if(!p){
    cout << endl << "Pointer is nullptr.";
    return;
  } else if(!p->r_child){
    cout << endl << "Nullptr of right child of pointer " << p << ". p=" << p->value;
    return;
  }
  // parent node
  if(p->parent){
    if(p == p->parent->l_child){ // p/
      p->parent->l_child = p->r_child;
    } else if(p == p->parent->r_child){ // \p
      p->parent->r_child = p->r_child;
    } else{
      cout << endl << "Pointer is disconnected from parent node. p=" << p << ", p.value=" << p->value;
      return;
    }
    p->r_child->parent = p->parent;
  } else{
    root = p->r_child;
    root->parent = nullptr;
  }
  // branch nodes
  node *rt = p->r_child;
  if(p->r_child->l_child){
    p->r_child->l_child->parent = p;
    p->r_child = rt->l_child;
  } else{
    p->r_child = nullptr;
  }
  // main nodes
  rt->l_child = p;
  p->parent = rt;
}
void avl_tree::R_Rotate(node *p){
  if(!p){
    cout << endl << "Pointer is nullptr.";
    return;
  } else if(!p->l_child){
    cout << endl << "Nullptr of left child of pointer " << p << ". p=" << p->value;
    return;
  }
  // parent node
  if(p->parent){
    if(p == p->parent->l_child){ // p/
      p->parent->l_child = p->l_child;
    } else if(p == p->parent->r_child){ // \p
      p->parent->r_child = p->l_child;
    } else{
      cout << endl << "Pointer is disconnected from parent node. p=" << p << ", p.value=" << p->value;
      return;
    }
    p->l_child->parent = p->parent;
  } else{
    root = p->l_child;
    root->parent = nullptr;
  }
  // branch nodes
  node *lf = p->l_child;
  if(p->l_child->r_child){
    p->l_child->r_child->parent = p;
    p->l_child = lf->r_child;
  } else{
    p->l_child = nullptr;
  }
  // main nodes
  lf->r_child = p;
  p->parent = lf;
}
