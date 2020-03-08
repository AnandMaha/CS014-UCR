#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

using namespace std;
class Node {
    friend class AVLTree;
private:
    Node(string);
    string data;
    int count;
    Node *left;
    Node *right;
    Node *parent;
};

#endif
