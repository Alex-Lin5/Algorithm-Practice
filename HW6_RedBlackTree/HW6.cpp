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
	node() { p_parent = p_Lchild = p_Rchild = nullptr; }
	node(int i) { value = i; p_parent = p_Lchild = p_Rchild = nullptr; }
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
void tree::L_rotate(node* p){
  if(!p){
    cout << endl << "Pointer is nullptr.";
    return;
  } else if(!p->p_Rchild){
    cout << endl << "Nullptr of right child of pointer " << p << ". p=" << p->value;
    return;
  }
  // parent node
  if(p->p_parent){
    if(p == p->p_parent->p_Lchild){ // p/
      p->p_parent->p_Lchild = p->p_Rchild;
    } else if(p == p->p_parent->p_Rchild){ // \p
      p->p_parent->p_Rchild = p->p_Rchild;
    } else{
      cout << endl << "Pointer is disconnected from parent node. p=" << p << ", p.value=" << p->value;
      return;
    }
    p->p_Rchild->p_parent = p->p_parent;
  } else{
    root = p->p_Rchild;
    root->p_parent = nullptr;
  }
  // branch nodes
  node *rt = p->p_Rchild;
  if(p->p_Rchild->p_Lchild){
    p->p_Rchild->p_Lchild->p_parent = p;
    p->p_Rchild = rt->p_Lchild;
  } else{
    p->p_Rchild = nullptr;
  }
  // main nodes
  rt->p_Lchild = p;
  p->p_parent = rt;
}
void tree::R_rotate(node* p){
  if(!p){
    cout << endl << "Pointer is nullptr.";
    return;
  } else if(!p->p_Lchild){
    cout << endl << "Nullptr of left child of pointer " << p << ". p=" << p->value;
    return;
  }
  // parent node
  if(p->p_parent){
    if(p == p->p_parent->p_Lchild){ // p/
      p->p_parent->p_Lchild = p->p_Lchild;
    } else if(p == p->p_parent->p_Rchild){ // \p
      p->p_parent->p_Rchild = p->p_Lchild;
    } else{
      cout << endl << "Pointer is disconnected from parent node. p=" << p << ", p.value=" << p->value;
      return;
    }
    p->p_Lchild->p_parent = p->p_parent;
  } else{
    root = p->p_Lchild;
    root->p_parent = nullptr;
  }
  // branch nodes
  node *lf = p->p_Lchild;
  if(p->p_Lchild->p_Rchild){
    p->p_Lchild->p_Rchild->p_parent = p;
    p->p_Lchild = lf->p_Rchild;
  } else{
    p->p_Lchild = nullptr;
  }
  // main nodes
  lf->p_Rchild = p;
  p->p_parent = lf;
}
void tree::add_node(int i){
  node *ad, *uncle, *op, *gc;
  int casee{0};
  ad = new node(i);
  ad->color = true;
  if(root == nullptr){
		root = ad;
    root->color = false;
		return;
	} 
  if(root->color) root->color = false; //always keep root node in block
  cout << endl;
  InorderPrint(root);
  // find the leaf position of new adding node
  op = root;
  while(op != nullptr){
    if(i <= op->value){
      if(op->p_Lchild)
        op = op->p_Lchild;
      else{
        op->p_Lchild = ad;  
        ad->p_parent = op;
        break;
      }
    } 
    else if(i > op->value) {
      if(op->p_Rchild)
        op = op->p_Rchild;
      else{
        op->p_Rchild = ad;
        ad->p_parent = op;
        break;
      }
    }
  }  
  // change color of nodes
  gc = ad;
  op = ad->p_parent->p_parent;
  if(ad->p_parent->color == false)
    return;
  do{ // parent node is red
    // find uncle node
    if(gc->p_parent == gc->p_parent->p_parent->p_Lchild)
      uncle = gc->p_parent->p_parent->p_Rchild;
    else if(gc->p_parent == gc->p_parent->p_parent->p_Rchild)
      uncle = gc->p_parent->p_parent->p_Lchild;
    else{
      uncle = nullptr;
      cout << endl << "Cannot find conncection between parent and grandparent nodes during adding node=" << gc << ", val=" << i;
    }
    if(!uncle || 
      uncle && !uncle->color){// case 1, would not propogate
      // check violation pattern, non trivial
      enum Pattern {LL, LR, RR, RL, None};
      Pattern pat = None;
      casee = 1; 
      node *p1, *p2;
      p2 = gc; p1 = gc->p_parent;
      if(p1 == op->p_Rchild && p2 == p1->p_Rchild) pat = RR;
      else if(p1 == op->p_Rchild && p2 == p1->p_Lchild) pat = RL;
      else if(p1 == op->p_Lchild && p2 == p1->p_Lchild) pat = LL;
      else if(p1 == op->p_Lchild && p2 == p1->p_Rchild) pat = LR;
      // rotation perform
      if(pat == LL){
        op->color = (!op->color)? true:false;
        op->p_Lchild->color = (!op->p_Lchild->color)? true:false;
        R_rotate(op);
      } else if(pat == RR){
        op->color = (!op->color)? true:false;
        op->p_Rchild->color = (!op->p_Rchild->color)? true:false;
        L_rotate(op);
      } else if(pat == LR){
        op->color = (!op->color)? true:false;
        gc->color = (!gc->color)? true:false;
        L_rotate(op->p_Lchild);
        R_rotate(op);
      } else if(pat == RL){
        op->color = (!op->color)? true:false;
        gc->color = (!gc->color)? true:false;
        R_rotate(op->p_Rchild);
        L_rotate(op);
      }
    } else if(uncle && uncle->color){// case 2, might propogate
      casee = 2;
      gc->p_parent->color = (!gc->p_parent->color)? true:false;
      uncle->color = (!uncle->color)? true:false;
      op->color = (!op->color)? true:false;
    } else{
      cout << endl << "Unkown status from uncle node during adding " << gc << ", val=" << i;
    }
    // break condition
    if(casee == 1) break;
    if(op == root){
      root->color = false;
      // gc->color = false;
      break;
    } else{
      op = op->p_parent;
      gc = gc->p_parent;
    }
  } while(op);
}
void tree::delete_node(int i){
  node *dlt, *suc, *sib, *op, *db;
  if(!root){
    cout << endl << "Root is not existed";
    return;
  }
  // find delete node in tree
  dlt = root;
  while(dlt){
    if(i < dlt->value) dlt = dlt->p_Lchild;
    else if(i > dlt->value) dlt = dlt->p_Rchild;
    else break; // i == dlt->value
  }
  cout << endl;
  InorderPrint(root);
	cout << endl << "Del: node=" << dlt << ", value=" << i;
  if(!dlt){
    cout << endl << "Node with value " << i << " is not existed in this tree. Root=" << root;
    return;
  }
  // delete root node of tree
  if(!dlt->p_parent){
    delete dlt;
    root = nullptr;
    return;
  }
  
  // if(!dlt->p_Lchild || !dlt->p_Rchild){
  //   if(!dlt->p_Lchild && !dlt->p_Rchild && dlt->color){
  //     delete dlt;
  //   } else if(!dlt->p_Lchild && dlt->p_Rchild && dlt->p_Rchild->color){
  //     dlt->value = dlt->p_Rchild->value;
  //     delete dlt->p_Rchild;
  //   } else if(!dlt->p_Rchild && dlt->p_Lchild && dlt->p_Lchild->color){
  //     dlt->value = dlt->p_Lchild->value;
  //     delete dlt->p_Lchild;
  //   }
  //   return;    
  // }
// else if(suc && !suc->p_Lchild && !suc->p_Rchild && suc->color ||
//       !suc && dlt->p_Lchild && dlt->p_Lchild->color){
//       dlt->value = suc->value;
//       delete suc;  

  // find successor of delete node
  suc = dlt->p_Rchild;
  while(suc->p_Lchild){
    suc = suc->p_Lchild;
  }
  // delete trival cases
  if(!suc) suc = dlt;
  dlt->value = suc->value;
  if(suc->p_Rchild && !suc->color){
    suc->value = suc->p_Rchild->value;
    delete suc->p_Rchild;
    suc->p_Rchild = nullptr;
    return;
  } else if(!suc->p_Lchild || !suc->p_Rchild){
    op = suc->p_parent;
    if(!suc->p_Lchild && !suc->p_Rchild && suc->color){
      if(suc == op->p_Lchild) op->p_Lchild = nullptr;
      else if(suc == op->p_Rchild) op->p_Rchild = nullptr;
      else cout << endl << "Disconnected from parent node of " << suc << ", val=" << suc->value << ". When deleting value " << i;
      delete suc;
    } else if(!suc->p_Lchild && suc->p_Rchild && suc->p_Rchild->color){
      suc->value = suc->p_Rchild->value;
      delete suc->p_Rchild;
      suc->p_Rchild = nullptr;
    } else if(!suc->p_Rchild && suc->p_Lchild && suc->p_Lchild->color){
      suc->value = suc->p_Lchild->value;
      delete suc->p_Lchild;
      suc->p_Lchild = nullptr;
    }
    return;    
  }

  // delete general cases
  db = suc;
  do{
    // enum Cases {1, 2A, 2B, 3, None};
    // Cases cas = None;
    bool isLeft{true};
    sib = nullptr;
    if(db == db->p_parent->p_Lchild) 
      sib = db->p_parent->p_Rchild;
    else if(db == db->p_parent->p_Rchild)
      sib = db->p_parent->p_Lchild;
    else
      cout << endl << "Unknown sibling from double black node " << db << ", val=" << db->value << ". When deleting value " << i;
    if(db == db->p_parent->p_Lchild) isLeft = true;
    else if(db == db->p_parent->p_Rchild) isLeft = false;
    else cout << endl << "Disconnected from parent node of DB " << db << ", val=" << db->value << ". When deleting value " << i;
    if(!db->color && !sib->color &&
      sib->p_Lchild && sib->p_Lchild->color ||
      sib->p_Rchild && sib->p_Rchild->color
      ){
      delete_1(db, isLeft);
      // cas = Cases.1;
      db = nullptr;
    } else if(!db->color && !sib->color &&
      !sib->p_Lchild && !sib->p_Rchild ||
      sib->p_Lchild && !sib->p_Lchild->color &&
      sib->p_Rchild && !sib->p_Rchild->color
      ){
      if(!db->p_parent->color){
        db = db->p_parent;
        delete_2A(db, isLeft);
        // cas = Cases.2A;
      } else if(db->p_parent->color){
        db = nullptr;
        delete_2B(db, isLeft);
        // cas = Cases.2B;
      } else
        cout << endl << "Unknown status from case 2 when deleting " << dlt << ", val=" << i;
    } else if(!db->color && sib->color){
      db = db;
      delete_3(db, isLeft);
      // cas = Cases.3;
    } else
      cout << endl << "Unknown status during deleting node " << dlt << ", val=" << i;
    // if(cas == Cases.1 || cas == Cases.2B) break;
  } while(db);
  // change color of nodes with rotation
  //   //true: red, false: black
  // if(!suc) suc = dlt->p_Lchild;    
  // if(suc->color || 
  //   suc->p_Lchild && suc->p_Lchild->color || 
  //   suc->p_Rchild && suc->p_Rchild->color){ // trivial cases
  //   if(suc->color) delete suc;
  //   else if(suc->p_Lchild && suc->p_Lchild->color)
  //     cout << endl << "Left child of successor is existed during deleting node=" << suc << ", val=" << i;
  //   else if(suc->p_Rchild && suc->p_Rchild->color){
  //     suc->value = suc->p_Rchild->value;
  //     delete suc->p_Rchild;
  //   }
  // }
}
void tree::delete_1(node* p, bool b){
  if(!p) cout << endl << "In delete case 1, nullptr is passed.";
  enum Pattern {LL, LR, RR, RL, None};
  Pattern pat = None;
  node *p1, *an;
  an = p->p_parent; 
  p1 = nullptr;
  if(p == an->p_Lchild)
    p1 = an->p_Rchild;
  else if(p == an->p_Rchild)
    p1 = an->p_Lchild;
  else
    cout << endl << "In delete case 1, unknown status arise from action node " << an << ", val=" << an->value;
  if(p1 == an->p_Lchild && p1->p_Lchild) pat = LL;
  else if(p1 == an->p_Lchild && p1->p_Rchild) pat = LR;
  else if(p1 == an->p_Rchild && p1->p_Rchild) pat = RR;
  else if(p1 == an->p_Rchild && p1->p_Lchild) pat = RL;
  else cout << endl << "In delete case 1, unknown status arise from violation pattern check of action node " << an << ", val=" << an->value;
  // rotation perform
  if(pat == LL){
    p1->p_Lchild->color = p1->color;
    p1->color = an->color;
    an->color = p->color;
    R_rotate(an);
    an->p_Rchild = nullptr;
  } else if(pat == RR){
    p1->p_Rchild->color = p1->color;
    p1->color = an->color;
    an->color = p->color;
    L_rotate(an);
    an->p_Lchild = nullptr;
  } else if(pat == LR){
    p1->p_Rchild->color = p1->color;
    p1->color = an->color;
    an->color = p->color;
    L_rotate(an->p_Lchild);
    R_rotate(an);
    an->p_Rchild = nullptr;
  } else if(pat == RL){
    p1->p_Lchild->color = p1->color;
    p1->color = an->color;
    an->color = p->color;
    R_rotate(an->p_Rchild);
    L_rotate(an);
    an->p_Lchild = nullptr;
  }
  delete p;
}
void tree::delete_2A(node* p, bool b){
  if(!p) cout << endl << "In delete case 2A, nullptr is passed.";
  node *an;
  an = p->p_parent;
  if(p == an->p_Lchild){
    // an->p_Lchild = nullptr;
    an->p_Rchild->color = true;
  } else if(p == an->p_Rchild){
    // an->p_Rchild = nullptr;
    an->p_Lchild->color = true;
  } else cout << endl << "In delete case 2A, parent connection lost from action node " << an << ", val=" << an->value;
  // delete p;
}
void tree::delete_2B(node* p, bool b){
  if(!p) cout << endl << "In delete case 2B, nullptr is passed.";
  node *an;
  an = p->p_parent;
  an->color = false;
  if(p == an->p_Lchild){
    an->p_Lchild = nullptr;
    an->p_Rchild->color = true;
  } else if(p == an->p_Rchild){
    an->p_Rchild = nullptr;
    an->p_Lchild->color = true;
  } else cout << endl << "In delete case 2B, parent connection lost from action node " << an << ", val=" << an->value;
  delete p;
}
void tree::delete_3(node* p, bool b){
  if(!p) cout << endl << "In delete case 3, nullptr is passed.";
  node *an;
  an = p->p_parent;
  // perform rotation
  if(p == an->p_Lchild){ // pattern R
    an->color = true;
    an->p_Rchild->color = false;
    L_rotate(an);
  } else if(p == an->p_Rchild){ // pattern L
    an->color = true;
    an->p_Lchild->color = false;
    R_rotate(an);
  }
}
void tree::InorderPrint(node * p){ //Print all nodes of a subtree rooted at node pointed by p; Example: (12 R) (7 B) (11 R) ...
  InorderPrint(p->p_Lchild);
  cout << "(" << p->value << " "; 
  if(p->color)
    cout << "R";
  else
    cout << "B";
  cout << ") ";
  if(p->p_Lchild)
    cout << p->p_Lchild->value << "/";
  if(p->p_Rchild)
    cout << "\\" << p->p_Rchild->value << " ";
  InorderPrint(p->p_Rchild);
}