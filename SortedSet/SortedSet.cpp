#include "SortedSet.h"
SortedSet::SortedSet() : IntList() {}
SortedSet::SortedSet(const SortedSet &ss) :IntList(ss) {}
SortedSet::SortedSet(const IntList &il) :IntList(il) {
    this->remove_duplicates();
    this->selection_sort();
}
SortedSet::~SortedSet() {}
bool SortedSet::in(int data) const {
    for(IntNode *curr = head; curr != nullptr; curr = curr->next) {
        if(curr->data == data) {
            return true;
        }
    }
    return false;
}
SortedSet SortedSet::operator|(const SortedSet &ss) const  {
    SortedSet res;
    for(IntNode *curr = ss.head; curr != nullptr; curr = curr->next) {
        if(!res.in(curr->data)) {
            res.add(curr->data);
        }
    }
    for(IntNode *curr = head; curr != nullptr; curr = curr->next) {
        if(!res.in(curr->data)) {
            res.add(curr->data);
        }
    }
    return res;
}
SortedSet SortedSet::operator&(const SortedSet &ss) const  {
    SortedSet res;
    for(IntNode *curr = ss.head; curr != nullptr; curr = curr->next) {
        if(in(curr->data)) {
            res.add(curr->data);
        }
    }
    return res;
}
void SortedSet::add(int data) {
    ///empty
    if(head == nullptr) {
        IntList::push_front(data);
    }
    ///after tail
    else if(data > tail->data) {
        IntList::push_back(data);
    }
    ///before head
    else if(data < head->data) {
        IntList::push_front(data);
    }
    ///one element and unique data
    else if(head == tail && head->data != data) {
        if(data < head->data) {
            IntList::push_front(data);
        }
        else {
            IntList::push_back(data);
        }
    }
    ///dup val with head
    else if(head->data == data) {
        return;
    }
    ///dup val with tail
    else if(tail->data == data) {
        return;
    }
    ///in the middle
    else {
        IntNode* temp = head;
        IntNode* firstList;
        while((temp != nullptr)) {
            if(temp->next->data == data) {
                return;
            }
            else if(data < temp->next->data) {
                firstList = temp->next;SortedSet ss;
                temp->next = new IntNode(data);
                temp->next->next = firstList;
                return;
            }
            else {
                temp = temp->next;
            }
        }
    }
}
//override BELOW functions to utilize add function
void SortedSet::push_front(int data) {
    add(data);
}
void SortedSet::push_back(int data) {
    add(data);
}
void SortedSet::insert_ordered(int data){
    add(data);
}
//override ABOVE functions to utilize add function
SortedSet SortedSet::operator|=(const SortedSet &ss) {
    SortedSet res;
    for(IntNode *curr = ss.head; curr != nullptr; curr = curr->next) {
        if(!res.in(curr->data) ) {
            res.add(curr->data);
        }
    }
    for(IntNode *curr = head; curr != nullptr; curr = curr->next) {
        if(!res.in(curr->data)) {
            res.add(curr->data);
        }
    }
    *this = res;
    return res;
}
SortedSet SortedSet::operator&=(const SortedSet &ss) {
    SortedSet res;
    for(IntNode *curr = ss.head; curr != nullptr; curr = curr->next) {
        if(in(curr->data)) {
            res.add(curr->data);
        }
    }
    *this = res;
    return res;
}
