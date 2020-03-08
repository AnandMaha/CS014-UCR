#ifndef INTLIST_H_INCLUDED
#define INTLIST_H_INCLUDED

#include <iostream>
using namespace std;
struct IntNode {
    int data;
    IntNode *next;
    IntNode(int data) : data(data), next(0) {}
};

class IntList
{
    protected:
        IntNode* head;
        IntNode* tail;

    public:
        friend ostream & operator<<(ostream &out, const IntList &);
        IntList();
        ~IntList();
        void push_front(int);
        void pop_front();
        bool empty() const;
        const int& front() const;
        const int & back() const;
        IntList(const IntList &);
        void push_back(int);
        void selection_sort();
        void insert_ordered(int);
        void remove_duplicates();
        IntList & operator=(const IntList&);
        void clear();
};





#endif // INTLIST_H_INCLUDED
