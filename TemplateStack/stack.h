#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include <stdexcept>
using namespace std;

const int MAX_SIZE = 20;
template<typename T>
class stack {
private:
    T data[MAX_SIZE];
    int size;
public:
    stack() { size = 0; }
    void push(T val) {
        if(size == MAX_SIZE) {
            //throw overflow_error exception with error message "Called push on full stack"
            throw overflow_error("Called push on full stack.");
        }
        //there's atleast one open slot
        size++;
        data[size - 1] = val;
    }
    void pop() {
        if(empty()) {
            throw out_of_range("Called pop on empty stack.");
        }
        size--;
    }
    T top() {
        if(empty()) {
            throw underflow_error("Called top on empty stack.");
        }
        //at least one element
        return data[size - 1];
    }
    bool empty() { return size == 0; }
};

#endif // STACK_H_INCLUDED
