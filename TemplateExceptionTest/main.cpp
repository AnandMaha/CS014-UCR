#include <iostream>
#include <vector>
#include <cstdio>
#include <stdlib.h>
#include <time.h>
#include <stdexcept>
using namespace std;

/* Returns minimum index of a given vector given the starting index
    Parameter - vals --- vector used to find min index
                index --- starting index to be looking for in vector
    Return -              unsigned int of index of minimum value in vector
*/
template<typename T>
unsigned min_index(const vector<T> &vals, unsigned index) {
    //start with value at index
    T minVal = vals.at(index);
    unsigned minIdx = index;
    //iterate through vector until at the end and update minIndex and
    //min values accordingly
    for(unsigned i = index+1; i < vals.size(); i++) {
        if(vals.at(i) < minVal) {
            minVal = vals.at(i);
            minIdx = i;
        }
    }
    //return min index
    return minIdx;
}

/* Sorts vector in ascending order utilizing the
       Selection sort algorithm (O(N^2))
    Parameter - vals --- vector needed to be sorted
*/
template<typename T>
void selection_sort(vector<T> &vals) {
    //go through the vector
    for(unsigned i = 0; i < vals.size(); i++) {
        int minIdx = min_index(vals, i);
        //at each slot, swap curr val with val at min_index
        T temp = vals.at(i);
        vals.at(i) = vals.at(minIdx);
        vals.at(minIdx) = temp;
    }
}

/* Given function to create a char vector */
vector<char> createVector(){
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}

/* Returns element at the given index
        Throws std::outofrange exception
    Parameter - vals --- vector used to find min index
                index --- index of element to be returned
    Return -              value at index
*/
template<typename T>
T getElement(const vector<T>& vals, int index) {
    return vals.at(index);
}

int main() {
    //test min_index
    vector<int> testVec(10);
    srand(time(NULL));
    for(unsigned i = 0; i < testVec.size(); i++) {
        int randInt = rand() % 11;
        testVec.at(i) = randInt;
    }
    cout << "Testing min_index: ";
    for(int item : testVec) {
        cout << item << " ";
    }
    int minIdx = min_index(testVec, 0);
    cout << "The min index is: " << minIdx << endl;
    //test min_index

    //test selection_sort with int
    vector<int> intVec(10);
    cout << "Testing selection_sort with ints: ";
    for(unsigned i = 0; i < intVec.size(); i++) {
        //generate random number between 0 and 10 (inclusive)
        //to populate intVec
        int randInt = rand() % 11;
        intVec.at(i) = randInt;
    }
    selection_sort(intVec);
    //make sure vector is in ascending order
    for(int item : intVec) {
        cout << item << " ";
    }
    cout << endl;
    //test selection_sort with int


    //test selection_sort with double
    vector<double> dblVec(10);
    cout << "Testing selection_sort with doubles: ";
    for(unsigned i = 0; i < dblVec.size(); i++) {
        double randDbl = double(rand()) / 11.0;
        dblVec.at(i) = randDbl;
    }
    selection_sort(dblVec);
    //make sure vector is in ascending order
    for(double item : dblVec) {
        printf("%.2f ",item);
    }
    cout << endl;
    //test selection_sort with double

    //test selection_sort with string
    vector<string> strVec;
    cout << "Testing selection_sort with strings: ";
    strVec.push_back("qqq");
    strVec.push_back("ddd");
    strVec.push_back("rrr");
    strVec.push_back("lll");
    strVec.push_back("sss");
    strVec.push_back("mmm");
    strVec.push_back("yyy");
    strVec.push_back("iii");
    strVec.push_back("ppp");
    strVec.push_back("xxx");
    selection_sort(strVec);
    //make sure vector is in ascending order
    for(string item : strVec) {
        cout << item << " ";
    }
    //test selection_sort with string

     //Part B
     srand(time(0));
     vector<char> vals = createVector();
     char curChar;
     int index;
     int numOfRuns = 10;
     cout << endl;
     while(--numOfRuns >= 0){
         try {
            cout << "Enter a number: " << endl;
            cin >> index;
            curChar = getElement(vals,index);
            cout << "Element located at " << index << ": is " << curChar << endl;
         }
         catch(out_of_range& excpt) {
            cout << "out of range exception occurred" << endl;
         }
    }
    return 0;

}
