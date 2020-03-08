#include "IntList.h"
#include <iostream>
using namespace std;

int main() {
    //test constructor
    IntList il;

    //test push_front
 //   IntList il;
    il.push_front(1);
    il.push_front(1);
    il.push_front(2);
    il.push_front(3);
    cout << il << endl;

    //test pop_front()
   // IntList il;
    il.push_front(1);
    il.pop_front();
    il.push_front(2);
    cout << il;

    //test push_back
  //  IntList il;
    il.push_back(3);
    il.push_back(4);
    il.push_back(5);
    cout << il;

    //test pop_back
  //  IntList il;
    il.push_back(1);
    il.push_back(2);
    il.push_back(3);
    il.pop_back();
    il.pop_back();
    il.pop_back();
    il.push_back(55555555);
    cout << il;

    //test empty
 //   IntList il;
    il.push_back(1);
    il.pop_back();
    cout << il.empty();
    il.push_back(2);
    cout << il.empty();

    //test cout <<
   // IntList il;
    il.push_back(1);
    cout << il;

    //test printReverse
  //  IntList il;
    il.push_back(1);
    il.push_back(2);
    il.push_back(3);
    il.printReverse();
}

