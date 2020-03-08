#ifndef JUG_H
#define JUG_H

#include <string>
#include <vector>
#include <climits>
using namespace std;

//vertex from the lab
struct Vertex {
  public:
    pair<int, int> neighbors [6];
    pair<int, int> state;
    int distance;
    Vertex* prev;

    Vertex():state(0,0),distance(INT_MAX),prev(nullptr){}
    ~Vertex(){}
};

class Jug {
    public:
        Jug(int,int,int,int,int,int,int,int,int);
        ~Jug();

        //solve is used to check input and find the solution if one exists
        //returns -1 invalid inputs. solution set to empty string.
        //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
        //returns 1 if solution is found and stores solution steps in solution string.
        int solve(string &solution);
    private:
        int cA; //capacity A
        int cB; //capacity B
        int goal; //int for final result
        int cFA; //cost to fill A
        int cFB; //cost to fill B
        int cEA; //cost to empty A
        int cEB; //cost to empty B
        int cPAB; //cost to pour A to B
        int cPBA; //cost to pour B to A
        vector<Vertex> aList; //adjacency list

        int find(Vertex &);
        void fillA(Vertex &);
        void fillB(Vertex &);
        void emptyA(Vertex &);
        void emptyB(Vertex &);
        void pourAtoB(Vertex &);
        void pourBtoA(Vertex &);
        void makeGraph(vector<Vertex> &);
        bool exists(Vertex &);
        void dijkstra();
};

#endif
