#include "Heap.h"
#include <iostream>
using namespace std;

//const int MAX_HEAP_SIZE = 10;
//  PrintJob* arr[MAX_HEAP_SIZE];      // Notice this is an array of PrintJob pointers
//  int numItems;  //current number of items in heap

/*Initializes an empty heap.*/
Heap::Heap() {
    numItems = 0;
}

/*Inserts a PrintJob to the heap without
 violating max-heap properties.*/
void Heap::enqueue(PrintJob* enJob) {
    //if it's full, return
    if(numItems == MAX_HEAP_SIZE) {
        cout << "Cannot enqueue new job. Queue is full.";
        return;
    }
    //since there's atleast one open spot, enqueue
    int pos = numItems; //curr position of enJob is at last possible slot
    arr[pos] = enJob;
    numItems++;
    //sort enJob in arr according to max heap rules
    while(pos > 0 && arr[pos]->getPriority() > arr[(pos - 1) / 2]->getPriority()) {
        //swap arr[pos] and arr[pos / 2]
        PrintJob* temp = arr[pos];
        arr[pos] = arr[pos / 2];
        arr[pos / 2] = temp;

        pos = pos / 2;
    }
}

/*Removes the node with highest priority from the heap.
Follow the algorithm on priority-queue slides. */
void Heap::dequeue() {
    //if numItems is 0, return
    if(numItems == 0) {
        cout << "ERROR: Cannot dequeue an empty list." << endl;
        return;
    }
    //replace first element with last element and decrease numItems by one
    arr[0] = arr[numItems - 1];
    numItems--;
    trickleDown(0);
}

/*Returns the node with highest priority.*/
PrintJob* Heap::highest () {
    return arr[0];
}

/*Prints the PrintJob with highest priority in the following format:
 Priority: priority, Job Number: jobNum, Number of Pages: numPages
 (Add a new line at the end.)*/
void Heap::print() {
    if(numItems != 0) {
    cout << "Priority: " << highest()->getPriority() << ", Job Number: "
        << highest()->getJobNumber() << ", Number of Pages: " << highest()->getPages() << endl;
    }
    else {
        cout << "Cannot print out an empty list" << endl;
    }
}

/*This function is called by dequeue function
 to move the new root down the heap to the
 appropriate location.*/
void Heap::trickleDown(int idx) {
    //BASE CASE: queue is empty or idx is not a parent node or if parent node is >=
    //both child nodes
    if(numItems == 0 || 2*idx+1>=numItems || 2*idx+2>=numItems
       || (arr[idx] >= arr[2*idx + 1] && arr[idx] >= arr[2*idx + 2])) {
        return;
    }
    //numItems > 0 and one of the child nodes is > parent node
    if(arr[2*idx + 1] >= arr[2*idx + 2]) {
        //swap parent and arr[2*idx+1]
        PrintJob* temp = arr[idx];
        arr[idx] = arr[2*idx+1];
        arr[2*idx+1] = temp;
        //call trickleDown with 2*idx+1
        trickleDown(2*idx+1);
    }
    else {
        //swap parent and arr[2*idx+2]
        PrintJob* temp = arr[idx];
        arr[idx] = arr[2*idx+2];
        arr[2*idx+2] = temp;
        //call trickleDown with 2*idx+2
        trickleDown(2*idx+2);
    }
}
