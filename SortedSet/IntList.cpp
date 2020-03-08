#include "IntList.h"
#include <vector>
#include <algorithm>
ostream & operator<<(ostream &out, const IntList &rhs) {
    if(rhs.head == nullptr) {
        return out;
    }
    IntNode *temp = rhs.head;
    do {
        if(temp->next != nullptr)
            out << temp->data << " ";
        else
            out << temp->data;
        temp = temp->next;
    }while(temp != nullptr);
    return out;
}
IntList & IntList::operator=(const IntList &rhs) {
  //list = list; case
  if(head == rhs.head)
    return *this;
  clear();
  IntNode *curr = rhs.head;
  while(curr) {
    push_back(curr->data);
    curr = curr->next;
  }
  return *this;
}
IntList::IntList() {
    head = nullptr;
    tail = nullptr;
}
IntList::~IntList() {
    while(head != nullptr) {
        IntNode *currNode = head->next;
        delete head;
        head = currNode;
    }
}
void IntList::push_front(int value) {
    if(head == nullptr) {
        head = new IntNode(value);
        tail = head;
    }
    else {
        IntNode *newNode = new IntNode(value);
        newNode->next = head;
        head = newNode;
    }
}

void IntList::push_back(int value) {
    if(head == nullptr) {
        head = new IntNode(value);
        tail = head;
    }
    //for non-empty list
    else {
        //get currNode to the tail node
        IntNode *currNode = head;
        while(currNode->next != nullptr) {
            currNode = currNode->next;
        }
        //now currNode is the tail of the list
        currNode->next = new IntNode(value);
        tail = currNode->next;
    }
}

void IntList::pop_front() {
    if(head == nullptr)
        return;
    IntNode *next = head->next;
    delete head;
    head = next;
    ///if LinkedList was only 1 element
    if(head == nullptr)
        tail = nullptr;
}
bool IntList::empty() const {
    return (head == nullptr);
}
void IntList::clear() {
    while(head)
        pop_front();
}
const int & IntList::front() const {
    return head->data;
}
const int & IntList::back() const {
    return tail->data;
}
IntList::IntList(const IntList &cpy) {
    head = nullptr;
    tail = nullptr;

    for(IntNode* curr = cpy.head; curr != nullptr; curr = curr->next)
    {
        push_back(curr->data);
    }
}

void IntList::selection_sort() {
   for(IntNode* i = head; i != 0; i = i->next)
    {
        int minimum = i->data;
        for(IntNode* j = i->next; j != 0; j = j->next)
        {
            if(j->data < minimum)
            {
                minimum = j->data;
                j->data = i->data;
                i->data = minimum;
            }
        }
    }
}
void IntList::insert_ordered(int value) {
    if(head == 0)
        push_front(value);
    else if(head->next == 0) {
        if(head->data >= value)
            push_front(value);
        else
            push_back(value);
    }
    else if(tail->data <= value)
        push_back(value);
    else if(head->data >= value)
        push_front(value);
    else{
        IntNode* i = head;
        IntNode* prevNode = head;
        IntNode* currNode = head->next;

        while(!((prevNode->data <= value) && (value <= currNode->data))) {
            prevNode = i->next;
            currNode = i ->next->next;
            i = i->next;
        }

        IntNode* tempNode = new IntNode(value);
        tempNode->next = currNode;
        prevNode->next = tempNode;
    }
}
void IntList::remove_duplicates() {
   for(IntNode* i = head; i != 0; i = i->next)
    {
        int compare = i->data;
        IntNode* previous = i;
        for(IntNode* j = i->next; j != 0;)
        {
            if(compare == j->data && j->next != 0)
            {
                previous->next = j->next;
                delete j;
                j = previous;
            }
            else if(compare == j->data && j == tail)
            {
                tail = previous;
                delete j;
                tail->next = 0;
            }

            if(j == previous)
            {
                j = j->next;
            }
            else
            {
                j = j->next;
                previous = previous->next;
            }
        }
    }
}



