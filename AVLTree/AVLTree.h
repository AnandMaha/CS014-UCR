#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED

#include "Node.h"
#include <string>
using namespace std;

class AVLTree {
    private:
      Node* root;

    public:
      AVLTree();
      void insert(const string &);
      void printBalanceFactors() const;
      int balanceFactor(Node*) const;
      void visualizeTree(const string &);

    private:
      void insert(Node*,Node*);
      void rotate(Node*);
      void rotateLeft(Node*);
      void rotateRight(Node*);
      void printBalanceFactors(Node*) const;
      void visualizeTree(ofstream &, Node*);
      int height(Node*) const;
      void height(int, int&, Node*) const;
      void setChild(Node*, string, Node*);
      void replaceChild(Node*, Node*,Node*);
};

#endif // AVLTREE_H_INCLUDED
