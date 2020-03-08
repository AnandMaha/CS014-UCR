#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <stack>
#include <queue>
#include "WordLadder.h"
using namespace std;

/* Passes in the name of a file that contains a dictionary of 5-letter words.
       Fills the list (dict) with the words within this file.
       If the file does not open for any reason or if any word within the file
       does not have exactly 5 characters, this function should output an
       error message and return.
*/
WordLadder::WordLadder(const string &fileName) {
    //try to open file for reading
    //if it doesn't work, output error message and return
    ifstream inputFS;
    inputFS.open(fileName);
    if(!inputFS.is_open()) {
        cout << "Cannot open file: " << fileName << endl;
        return;
    }
    //iterate through file, and return if any word is not equal to 5 letters in length
    string word;
    while(inputFS >> word) {
        if(word.size() != 5) {
            cout << "Error: all words in dictionary file must be exactly 5 letters in length" << endl;
            return;
        }
        //push_back the word to dict
        dict.push_back(word);
    }
    //close file
    inputFS.close();
}

void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile) {
    //ofstream object to write to ouputFile
    ofstream outputFS;
    outputFS.open(outputFile);

    //make sure both words are in dict
    list<string>::iterator dictIt;
    bool startExists = false, endExists = false;
    for(dictIt = dict.begin(); dictIt != dict.end(); dictIt++) {
        if(*dictIt == start)
            startExists = true;
        if(*dictIt == end)
            endExists = true;
    }
    //if either start or end don't exist in dict, return
    if(!startExists || !endExists) {
        cout << "Please enter a valid word(s) for start and/or end words" << endl;
        return;
    }

    list<string>::iterator it;
    queue<stack<string>> stckQ;
    stack<string> wrdLddr;
    wrdLddr.push(start);
    stckQ.push(wrdLddr);
    if(start == end) {
        outputFS << wrdLddr.top() << endl;
        return;
    }
    bool isEnd = false;
    while(!stckQ.empty() && !isEnd) {
        it = dict.begin();
        while(it != dict.end() && !isEnd) {
            if(isOneLetterOff(stckQ.front().top(), *it)) {
                if(*it == end) {
                    isEnd = true;
                }
                stack<string> newStack = stckQ.front();
                newStack.push(*it);
                stckQ.push(newStack);
                it = dict.erase(it);
            }
            else
                it++;
        }
        stckQ.pop();
    }
    if(!isEnd) {
        outputFS << "No Word Ladder Found." << endl;
    }
    else {
        stack<string> otptStck;
        while(!stckQ.back().empty()) {
            otptStck.push(stckQ.back().top());
            stckQ.back().pop();
        }
        while(!otptStck.empty()) {
            outputFS << otptStck.top() << endl;
            otptStck.pop();
        }
    }
    outputFS.close();
}
/* Assume both words are the same length */
bool WordLadder::isOneLetterOff(const string &word1, const string &word2) const {
    int diffChars = 0;
    for(unsigned i = 0; i < word1.size(); i++) {
        if(word1.at(i) != word2.at(i))
            diffChars++;
    }
    return (diffChars == 1);
}
