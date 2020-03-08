#include "IntList.h"
#include <iostream>
using namespace std;

IntList::IntList() {
    dummyHead = new IntNode(NULL);
    dummyTail = new IntNode(NULL);
    dummyHead->next = dummyTail;
    dummyTail->prev = dummyHead;
}

IntList::~IntList() {
	while( !empty() ) {
		pop_front();
	}
}

void IntList::push_front(int value) {
	//make the IntNode to be pushed to the front
	IntNode *newNodePtr = new IntNode(value);
	//cases:
	//if List is empty
	if( empty() ) {
		dummyHead->next = newNodePtr;
		newNodePtr->prev = dummyHead;
		dummyTail->prev = newNodePtr;
		newNodePtr->next = dummyTail;
	}
	//if List is not empty >0 elements
	else {
        IntNode *tempPtr = dummyHead->next;
        dummyHead->next = newNodePtr;
        newNodePtr->prev = dummyHead;
        newNodePtr->next = tempPtr;
        tempPtr->prev = newNodePtr;
	}
}

void IntList::pop_front() {
	//cases:
	//List is empty
	if( empty() ) {
		return;
	}
	//List is == 1 element, condition works as list is NOT empty
	else if(dummyHead->next == dummyTail->prev) {
        IntNode *tempPtr = dummyHead->next;
        dummyHead->next = dummyTail;
        dummyTail->prev = dummyHead;
        delete tempPtr;
	}
    else {
		IntNode *tempPtr = dummyHead->next; //for deleting
		dummyHead->next = tempPtr->next;
        dummyHead->next->prev = dummyHead;
        delete tempPtr;
	}
}

void IntList::push_back(int value) {
	//make the IntNode to be pushed to the back
	IntNode *addNode = new IntNode(value);
	//cases:
	//if List is empty
	if( empty() ) {
		dummyHead->next = addNode;
		addNode->prev = dummyHead;
		dummyTail->prev = addNode;
		addNode->next = dummyTail;
	}
	//if List is not empty
	else {
	    dummyTail->prev->next = addNode;
        addNode->prev = dummyTail->prev;
        addNode->next = dummyTail;
        dummyTail->prev = addNode;
	}
}

void IntList::pop_back() {
    //cases:
	//List is empty
	if( empty() ) {
		return;
	}
	//List is == 1 element, condition works as list is NOT empty
	else if(dummyHead->next == dummyTail->prev) {
        dummyHead->next = dummyTail;
        dummyTail->prev = dummyHead;
	}
    else {
		IntNode *tempPtr = dummyTail->prev; //for deleting
		dummyTail->prev = tempPtr->prev;
        dummyTail->prev->next = dummyTail;
        delete tempPtr;
	}
}

bool IntList::empty() {
	//determine if dummyHead next is dummyTail and if dummyTail prev is dummyHead
	//this would mean the list is empty if true, otherwise false
	return dummyHead->next == dummyTail;
}

ostream & operator<<(ostream &out, const IntList &rhs) {
	IntNode *tempPtr = rhs.dummyHead->next;
	//need to go two ahead, not one, for stopping the loop at the node
	//before the dummy tail
	while(tempPtr != rhs.dummyTail) {
		out << tempPtr->data;
		if(tempPtr->next != rhs.dummyTail)
            out << " ";
		tempPtr = tempPtr->next;
	}
	return out;
}

void IntList::printReverse() const {
	IntNode *tempPtr = dummyTail->prev;
	while(tempPtr != dummyHead) {
		cout << tempPtr->data;
		if(tempPtr->prev != dummyHead)
            cout << " ";
		tempPtr = tempPtr->prev;
	}
}




