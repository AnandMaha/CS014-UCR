#include "AVLTree.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

AVLTree::AVLTree() {
    root = nullptr;
}

void AVLTree::insert(const string &str) {
    Node *iNode = new Node(str);
    insert(root,iNode);
}

void AVLTree::insert(Node* curr, Node* newNode) {
   if (root == nullptr) {
      root = newNode;
      root->parent = nullptr;
      return;
   }
   //atleast one node already
   //search for place to insert, and ....
   curr = root;
   while (curr != nullptr) {
      if (newNode->data == curr->data) {
          curr->count++;
          curr = nullptr;
      }
      else if (newNode->data < curr->data) {
         if (curr->left == nullptr) {
            curr->left = newNode;
            newNode->parent = curr;
            curr = nullptr;
         }
         else
            curr = curr->left;
      }
      else {
         if (curr->right == nullptr) {
            curr->right = newNode;
            newNode->parent = curr;
            curr = nullptr;
         }
         else
            curr = curr->right;
      }
   }
  //rotate nodes around for AVL Tree properties
  newNode = newNode->parent;
  while(newNode != nullptr) {
      rotate(newNode);
      newNode = newNode->parent;
  }
}

void AVLTree::rotate(Node* curr) {
    //2 more nodes on the left of curr compared to right
    if(balanceFactor(curr) == 2) {
        //Left-right rotation
        if(balanceFactor(curr->left) == -1) {
            rotateLeft(curr->left);
        }
        rotateRight(curr);
    }
    //2 more nodes on the right of curr compared to left
    else if(balanceFactor(curr) == -2) {
        if(balanceFactor(curr->right) == 1) {
            rotateRight(curr->right);
        }
        rotateLeft(curr);
    }
}


int AVLTree::balanceFactor(Node* curr) const {
    return height(curr->left) - height(curr->right);
}

int AVLTree::height(Node* curr) const {
    if (curr != nullptr){
        int finalHeight = 0;
        height(0,finalHeight,curr);
        return finalHeight - 1;
    }
    //if curr is nullptr
    return -1;
}

void AVLTree::height(int heightCounter, int &finalHeight, Node* curr) const {
    if(curr != nullptr) {
        heightCounter++;
        if(heightCounter > finalHeight){
            finalHeight = heightCounter;
        }
        //recursively traverse tree
        height(heightCounter,finalHeight,curr->left);
        height(heightCounter,finalHeight,curr->right);
    }
}

void AVLTree::rotateRight(Node* curr) {
    Node *temp = curr->left->right;
    if(curr->parent != nullptr) {
        replaceChild(curr->parent,curr,curr->left);
    }
    else {
        root = curr->left;
        root->parent = nullptr;
    }
    setChild(curr->left,"right",curr);
    setChild(curr,"left",temp);
}

void AVLTree::rotateLeft(Node* curr) {
    Node *temp = curr->right->left;
    if(curr->parent != nullptr) {
        replaceChild(curr->parent,curr,curr->right);
    }
    else {
        root = curr->right;
        root->parent = nullptr;
    }
    setChild(curr->right,"left",curr);
    setChild(curr,"right",temp);
}

void AVLTree::replaceChild(Node* parent, Node* curr,Node* newChild) {
    if(parent->left == curr) {
        setChild(parent,"left",newChild);
    }
    else if(parent->right == curr) {
        setChild(parent,"right",newChild);
    }
}

void AVLTree::setChild(Node* parent, string whichChild, Node* child) {
    if(whichChild == "left") {
        parent->left = child;
    }
    else {
        parent->right = child;
    }
    if(child != nullptr) {
        child->parent = parent;
    }
}


void AVLTree::printBalanceFactors() const {
    printBalanceFactors(root);
    cout << endl;
}

void AVLTree::printBalanceFactors(Node* curr) const {
    if(curr != nullptr) {
        printBalanceFactors(curr->left);
        cout << curr->data << "(" << balanceFactor(curr) << "), ";
        printBalanceFactors(curr->right);
    }
}



void AVLTree::visualizeTree(const string &outputFilename) {
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<<n->data <<" -> " <<n->left->data<<";"<<endl;
        }

        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<<n->data <<" -> " <<n->right->data<<";"<<endl;
        }
    }
}
