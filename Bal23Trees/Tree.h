#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include <string>

class Tree {
    public:
        Tree() : root(0) {}
        ~Tree();
        void preOrder() const;
        void inOrder() const;
        void postOrder() const;
        void insert(const string &);
        void remove(const string &);
        bool search(const string &) const;
    private:
        Node *root;
        Node* search(Node *, const string &) const;
        Node* getSibling(Node *);
        void split(Node *, const string &, Node *, Node *, Node *, Node *);
        void preOrder(Node *) const;
        void inOrder(Node *) const;
        void postOrder(Node *) const;
        void fix(Node *);
        void deleteNodes(Node *);
        bool isLeafNode(Node *) const;
        bool is2Node(Node *) const;
        bool is3Node(Node *) const;
};
#endif
