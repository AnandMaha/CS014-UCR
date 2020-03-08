#ifndef SORTEDSET_H
#define SORTEDSET_H
#include "IntList.h"
class SortedSet : public IntList {
public:
    SortedSet();
    SortedSet(const SortedSet &);
    SortedSet(const IntList &);
    ~SortedSet();
    bool in(int data) const ;
    SortedSet operator|(const SortedSet &) const ;
    SortedSet operator&(const SortedSet &) const;
    void add(int data);
    //override BELOW functions to utilize add function
    void push_front(int data);
    void push_back(int data);
    void insert_ordered(int data);
    //override ABOVE functions to utilize add function
    SortedSet operator|=(const SortedSet &);
    SortedSet operator&=(const SortedSet &);
};

#endif // SORTEDSET_H
