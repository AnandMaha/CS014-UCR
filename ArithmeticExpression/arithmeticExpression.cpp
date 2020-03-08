#include "arithmeticExpression.h"
#include <string>
#include <stack>
#include <fstream>
#include <sstream>
arithmeticExpression::arithmeticExpression(const string& iFE) {
    infixExpression = iFE;
    root = nullptr;
}

void arithmeticExpression::buildTree() {
	string postExpression = infix_to_postfix();
	stack <TreeNode*> s;

	for (unsigned i = 0; i < postExpression.size(); i++) {
		TreeNode *newNode = new TreeNode(postExpression.at(i), 'a' + i);
		//if number
		if (priority(postExpression.at(i)) == 0) {
			s.push(newNode);
		}
		//else operator
		else {
			newNode->right = s.top();
			s.pop();
			newNode->left = s.top();
			s.pop();
			s.push(newNode);
			root = newNode;
		}
	}
}

//helper functions
int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

void arithmeticExpression::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void arithmeticExpression::visualizeTree(ofstream &outFS, TreeNode *curr) {
    if (curr != nullptr) {
    	outFS << curr->key << "[ label = " << "\"" << curr->data << "\"" << " ]" <<endl;
        if (curr->left != nullptr) {
            outFS  << curr->key <<  "->" << curr->left->key << "[ label = " << "\"" << curr->left->data << "\"" << " ]" << endl;
            visualizeTree(outFS, curr->left);
        }
        if (curr->right != nullptr) {
            outFS  << curr->key << " -> " << curr->right->key << "[ label =  " << "\"" << curr->right->data << "\"" << " ]" << endl;
            visualizeTree(outFS, curr->right);
        }
        outFS << endl;
    }
}
