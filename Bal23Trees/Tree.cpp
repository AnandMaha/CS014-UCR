#include "Tree.h"
#include "Node.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

Tree::~Tree() {
    deleteNodes(root);
}

//used by destructor
void Tree::deleteNodes(Node *current) {
    //starts deleting from the leaves and goes up
    //to prevent double free error!!!
    if (isLeafNode(current)) {
        delete current;
        current = 0;
    }
    else if (is2Node(current)) {
        deleteNodes(current->left);
        deleteNodes(current->right);
    }
    else { //if current is a 3 Node
        deleteNodes(current->left);
        deleteNodes(current->middle);
        deleteNodes(current->right);
    }
}

bool Tree::isLeafNode(Node *current) const {
    if (current->left == 0 && current->middle == 0 && current->right == 0) {
        return true;
    }
    return false;
}

bool Tree::is2Node(Node *current) const {
    if (current->large.empty()) { //is 2 Node if large is empty
        return true;
    }
    return false;
}

bool Tree::is3Node(Node *current) const {
    if (!current->small.empty() && !current->large.empty()) { //is 3 Node if BOTH small and large data exist
        return true;
    }
    return false;
}

void Tree::preOrder(Node *current) const {
    if (current) {
        cout << current->small << ", ";
        preOrder(current->left);
        if (is3Node(current)) {
            cout << current->large << ", ";
            preOrder(current->middle);
        }
        preOrder(current->right);
    }
}

void Tree::preOrder() const {
    preOrder(root); //calls recursive preOrder starting at the root.
    cout << endl;
}

void Tree::inOrder(Node *current) const {
    if (current) {
        inOrder(current->left);
        cout << current->small << ", ";
        if(is3Node(current)){
            inOrder(current->middle);
            cout << current->large << ", ";
        }
        inOrder(current->right);
    }
}

void Tree::inOrder() const {
    inOrder(root); //calls recursive inOrder starting at the root.
    cout << endl;
}

void Tree::postOrder(Node *current) const {
    if (current) {
        postOrder(current ->left);
        if (is3Node(current)) {
            postOrder(current->middle);
            cout << current->small << ", ";
        }
        postOrder(current -> right);
        if (is2Node(current)) {
            cout << current->small << ", ";
        }
        if (is3Node(current)) {
            cout << current->large << ", ";
        }
    }
}

void Tree::postOrder() const {
    postOrder(root); //calls recursive postOrder starting at the root.
    cout << endl;
}
//given starting node, return node that contains userWord
//if it doesn't exist, return nullptr
Node* Tree::search(Node *current, const string & userWord) const {
    if (current) {
        if(isLeafNode(current)) {
            return current;
        }
        else if(is2Node(current)) { // no middle node
            if(userWord == current->small) {
                return current;
            }
            else if(userWord < current->small) {
                return search(current->left, userWord);
            }
            else {
                return search(current->right, userWord);
            }
        }
        else { //is3Node
            if(userWord == current->small || userWord == current->large) {
                return current;
            }
            else if(userWord < current->small) {
                return search(current->left, userWord);
            }
            else if(userWord > current->large) {
                return search(current->right, userWord);
            }
            else {
                return search(current->middle, userWord);
            }
        }
   }
   return nullptr;
}

bool Tree::search(const string & userWord) const {
    Node *match = search(root, userWord); //assigns a Node pointer to the Node pointer returned from searching
    if(match == nullptr) // only needed when tree is initially empty
        return false;
    // this works even if it's a 2 node...
    if (match->small == userWord || match->large == userWord) {
        return true;
    }
    return false;
}

void Tree::insert(const string & userWord) {
    Node *current = root;
    //empty tree
    if (root == 0) {
        root = new Node(userWord);
        return;
    }

    //locates the leaf node of where to insert
    while (current->left != 0 || current->right != 0) {
        if (userWord < current->small) {
            current = current->left;
        }
        else if (userWord > current->large) {
            current = current->right;
        }
        else {
            if (current->middle != 0) {
                current = current->middle;
            }
        }
    }
    //if there's space in the node
    if (is2Node(current)) {
        if (userWord < current->small) {
            current->large = current->small;
            current->small = userWord;
        }
        else {
            current->large = userWord;
        }
    }
    else { //split full node
        // cout << "splitting with " << userWord << endl;
        split(current, userWord, 0, 0, 0, 0);
    }
}


void Tree::split(Node *n, const string & userWord, Node *left1, Node *left2, Node *right1, Node *right2) {
   //simple way to order the data
   string smallVal, midVal, largeVal;
   string arr[] = {userWord, n->small, n->large};
   sort(arr, arr+3);
   smallVal = arr[0]; midVal = arr[1]; largeVal = arr[2];

   Node *p = 0;
   Node *child1 = 0;
   Node *child2 = 0;
   Node *child3 = 0;
   Node *child4 = 0;

   if(n == root) {
      p = new Node(midVal);
   }
   else {
      p = n->parent;
   }

   Node *n1 = new Node(smallVal); // small
   Node *n2 = new Node(largeVal); //large

   n1->parent = p;
   n2->parent = p;

   //case if not a leaf node
   if (!isLeafNode(n)) {
      //assign n1 as parent of n's two leftmost children
      left1->parent = n1;
      left2->parent = n1;

      //point n1 back to left and right
      n1->left = left1;
      n1->right = left2;

      //assign n2 as parent of n's two rightmost children
      right1->parent = n2;
      right2->parent = n2;

      //point n2 back to left and right
      n2->left = right1;
      n2->right = right2;
   }

   //case if adding midVal to p would make p have 3 items
   //assign child1, child2, child3, and child4 for split function on parent
   //node
   if(is3Node(p) && is3Node(n)) {
      if(p->left == n) {
         child1 = n1;
         child2 = n2;
         child3 = p->left;
         child4 = p->right;
      }
      else if (p->right == n) {
         child1 = p->left;
         child2 = p->middle;
         child3 = n1;
         child4 = n2;
      }
      else { //if middle
         child1 = p->left;
         child2 = n1;
         child3 = n2;
         child4 = p->right;
      }
      split(p, midVal, child1, child2, child3, child4); //now calls split on the children
   }

   //case when there are 4 children under a 2 node
   if(is2Node(p)) {
      //case when root is 3 node, and inserting another value
      if(n == root) {
         root = p;
         p->left = n1;
         p->right = n2;
      }
      else if (p->left == n) {
         p->left = n1;
         p->middle = n2;
        //p->small is largest out of the four in this case
         p->large = p->small;
         p->small = midVal;
      }
      else { //if n is p's right
         //since n is already greater than p, ordering is as such
         p->middle = n1;
         p->right = n2;
         p->large = midVal;
      }
   }
}

void Tree::remove(const string & userWord) {
    Node *leafNode = search(root, userWord);
    //make sure to do nothing if leaf node returned by search doesn't match userWord
    if (leafNode) {
        //deletes the item from leafNode
        if (userWord == leafNode->large) {
            leafNode->large = "";
        }
        else if(userWord == leafNode->small) {
            leafNode->small = leafNode->large;
            leafNode->large = "";
        }

        //fixes if leafNode contains no items
        if (leafNode->small.empty()) {
            fix(leafNode);
        }
    }
}
//used in fix()
Node* Tree::getSibling(Node *current) {
    Node *p = current->parent;
    if (is2Node(p)) {
        if (p->left == current) {
            return p->right;
        }
        else if (p->right == current) {
            return p->left;
        }
    }
    else { //if p is a 3 Node
        if (p->right == current || p->left == current) {
            return p->middle;
        }
        else {
            if (is3Node(p->left) && is3Node(p->right)) {
                return p->right;
            }
            else if (is2Node(p->left) && is2Node(p->right)) {
                return p->left;
            }
            else if (is3Node(p->left)) {
                return p->left;
            }
            else { //if p's right is a 3 Node
                return p->right;
            }
        }
    }
    return 0;
}

void Tree::fix(Node* n) {
    if (n == root) {
        if (isLeafNode(n)) {
            delete n;
            root = 0;
            return;
        }
        else {
            if (root->right == 0) {
                root = root->left;
            }
            else {
                root = root->right;
            }
        }
        return;
    }
    else {
        Node* p = n->parent;
        Node* s = getSibling(n);
        if (is3Node(s)) {
            if (p->left == n){
                if (is2Node(p)){
                    n->small = p->small;
                    p->small = s->small;
                    s->small = s->large;
                    s->large = "";
                }
                else{ //if p is a 3 Node
                    if (is2Node(p->right)) {
                        n->small = p->small;
                        p->small = s->small;
                        s->small = s->large;
                        s->large = "";
                    }
                    else { //if p's right is a 3 Node
                        n->small = p->small;
                        p->small = s->small;
                        s->small = s->large;
                        s->large = "";
                    }
                }
            }
            else if (p->middle == n) { //p WILL be a 3 Node
                if (p->left == s){
                    n->small = p->small;
                    p->small = s->large;
                    s->large = "";
                }
                else{
                    n->small = p->large;
                    p->large = s->small;
                    s->small = s->large;
                    s->large = "";
                }
            }
            else { //n is p's right
                if (is2Node(p)) {
                    n->small = p->small;
                    p->small = s->large;
                    s->large = "";
                }
                else{ //if p is a 3 Node
                    if (is2Node(p->left)) {
                        n->small = p->large;
                        p->large = s->small;
                        s->small = s->large;
                        s->large = "";
                    }
                    else{ //if p's left is a 3 Node
                        n->small = p->large;
                        p->large = s->large;
                        s->large = "";
                    }
                }
            }

            //if internal node
            if ((n->left != 0 && n->right == 0) || (n->right != 0 && n->left == 0)) {
                if (p->right == n) {
                    if (n->left == 0){
                        n->left = s->right;
                        s->right = s->middle;
                        s->middle = 0;
                    }
                    else{
                        n->right = n->left;
                        n->left = s->right;
                        s->right = s->middle;
                        s->middle = 0;
                    }
                }
                else {
                    if (n->right == 0) {
                        n->right = s->left;
                        s->left = s->middle;
                        s->middle = 0;
                    }
                    else{
                        n->left = n->right;
                        n->right = s->left;
                        s->left = s->middle;
                        s->middle = 0;
                    }
                }
            }
        }
        else {
            if (is2Node(p)) {
                if (p->left == n) {
                    s->large = s->small;
                    s->small = p->small;
                    p->small = "";
                }
                else {
                    s->large = p->small;
                    p->small = "";
                }
            }
            else {
                if (p->left == n) {
                    if (is2Node(p->right)) {
                        s->large = s->small;
                        s->small = p->small;
                        p->small = p->large;
                        p->large = "";
                        p->left = s;
                        p->middle = 0;
                    }
                    else {
                        n->small = p->small;
                        p->small = s->small;
                        s->small = p->large;
                        p->large = p->right->small;
                        p->right->small = p->right->large;
                        p->right->large = "";
                    }
                }
                else if (p->middle == n) {
                    s->large = p->small;
                    p->small = p->large;
                    p->large = "";
                    p->middle = 0;
                }
                else { //n is p's right
                    if (is2Node(p->left)) {
                        s->large = p->large;
                        p->large = "";
                        p->right = s;
                        p->middle = 0;
                    }
                    else {
                        n->small = p->large;
                        p->large = s->small;
                        s->small = p->small;
                        p->small = p->left->large;
                        p->left->large = "";
                    }
                }
            }

            //if n is internal (n is empty, but has a child)
            if ((n->left != 0 && n->right == 0) || (n->right !=0 && n->left == 0)) {
                if (p->right == n) {
                    s->middle = s->right;
                    if (n->left == 0) {
                        s->right = n->right;
                    }
                    else {
                        s->right = n->left;
                    }
                }
                else {
                    s->middle = s->left;
                    if (n->right == 0) {
                        s->left = n->left;
                    }
                    else {
                        s->left = n->right;
                    }
                }
            }
            n = 0;
            //call fix if p is empty
            if (p->small.empty() && p->large.empty()){
                fix(p);
            }
        }
    }
}
