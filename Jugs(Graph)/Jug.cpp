#include "Jug.h"

#include <iostream> //to remove

#include <vector>
#include <string>
#include <list>
#include <queue>
#include <sstream>
#include <stack>
#include <climits>

using namespace std;

//initialize all variables right away
Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA) :
     cA(Ca), cB(Cb), goal(N), cFA(cfA), cFB(cfB), cEA(ceA), cEB(ceB),
     cPAB(cpAB), cPBA(cpBA) {
      //return if invalid input
      //solve() will return -1 if invalid input...

      //none of the costs can be less than zero
      //(to avoid negative edge weight cycle)
      if (cFA < 0 || cFB < 0 || cEA < 0 || cEB < 0 || cPAB < 0 || cPBA < 0) {
            return;
      }
      //0 < capA <= capB
      if (0 >= cA || cA > cB) {
            return;
      }
      //goal <= capB <= 1000
      if (goal > cB || cB > 1000) {
            return;
      }

       //build graph with empty vector (aList)
       makeGraph(aList);
     }

Jug::~Jug() { }

//HELPER FUNCTIONS
void Jug::fillA(Vertex & v) { //fill first jug with A's capacity
  v.state.first = cA;
}

void Jug::fillB(Vertex & v) { //fill second jug with B's capacity
  v.state.second = cB;
}

void Jug::emptyA(Vertex & v) { //make first jug empty
  v.state.first = 0;
}

void Jug::emptyB(Vertex & v) { //make second jug empty
  v.state.second = 0;
}

void Jug::pourAtoB(Vertex & v) {
  //pours from A to B until B is full or A is empty
  while (v.state.first != 0 && v.state.second != cB) {
    v.state.first--;
    v.state.second++;
  }
}

void Jug::pourBtoA(Vertex & v) {
  //pours from B to A until A is full or B is empty
  while (v.state.second != 0 && v.state.first != cA) {
    v.state.first++;
    v.state.second--;
  }
}
//HELPER FUNCTIONS

//v is adjacency list
void Jug::makeGraph(vector<Vertex> & v) {
  Vertex start;
  v.push_back(start); //start vertex is
    //needed for when pushing vertices onto aList
  for (unsigned i = 0; i < v.size(); i++) {
    Vertex center = v.at(i);
    //make the 6 to-be edges of the center vertex
    Vertex v1 = center;
    Vertex v2 = center;
    Vertex v3 = center;
    Vertex v4 = center;
    Vertex v5 = center;
    Vertex v6 = center;

    fillA(v1);
    fillB(v2);
    emptyA(v3);
    emptyB(v4);
    pourAtoB(v5);
    pourBtoA(v6);

    //checks if state is in adjacency list; if not, add state
    if (!exists(v1)) {
       aList.push_back(v1);
    }
    if (!exists(v2)) {
       aList.push_back(v2);
    }
    if (!exists(v3)) {
       aList.push_back(v3);
    }
    if (!exists(v4)) {
       aList.push_back(v4);
    }
    if (!exists(v5)) {
       aList.push_back(v5);
    }
    if (!exists(v6)) {
       aList.push_back(v6);
    }
    //attach the 6 vertices to the center vertex
    //neighbor first is index in aList
    //neighbor second is edge weight
    center.neighbors[0] = pair<int,int>(find(v1),cFA);
    center.neighbors[1] = pair<int,int>(find(v2),cFB);
    center.neighbors[2] = pair<int,int>(find(v3),cEA);
    center.neighbors[3] = pair<int,int>(find(v4),cEB);
    center.neighbors[4] = pair<int,int>(find(v5),cPAB);
    center.neighbors[5] = pair<int,int>(find(v6),cPBA);
    //make sure to replace v.at(i) with center vertex with new neighbors
    v.at(i) = center;
  }
}
//checks if v's first and second match aList.at(i) first and second values
bool Jug::exists(Vertex & v) {
  for (unsigned i = 0; i < aList.size(); ++i) {
    if (aList.at(i).state.first == v.state.first && aList.at(i).state.second == v.state.second) {
      return true;
    }
  }
  return false;
}
//returns index in aList where Vertex is...
//return -1 if doesn't exist
int Jug::find(Vertex & v) {
  for (unsigned i = 0; i < aList.size(); ++i) {
    if (aList.at(i).state.first == v.state.first && aList.at(i).state.second == v.state.second) {
      return i;
    }
  }
  return -1;
}
//solution is a vertex with "jug a" being empty and "jug b" being goal
//return -1 if the input isn't proper
//return 0 if no solution exists
//return 1 if solution exists
int Jug::solve(string & solution) {
  stringstream ss;
  //make sure input is good

  //none of the costs can be less than zero
  //(to avoid negative edge weight cycle)
  if (cFA < 0 || cFB < 0 || cEA < 0 || cEB < 0 || cPAB < 0 || cPBA < 0) {
    solution = "";
    return -1;
  }
  //0 < capA <= capB
  if (0 >= cA || cA > cB) {
    solution = "";
    return -1;
  }
  //goal <= capB <= 1000
  if (goal > cB || cB > 1000) {
    solution = "";
    return -1;
  }

  int index = -1; //if index changes, then a solution exists
  for(unsigned i = 0; i < aList.size(); ++i){
      //solution is first being 0 and second being goal
      if(aList.at(i).state.first == 0 && aList.at(i).state.second == goal){
          index = i;
      }
  }

  //error if solution wasn't found
  if(index == -1){
      solution = "";
      return 0;
  }

  dijkstra(); //sets distance and prev for all vertices

  stack<Vertex*> vStack;
  //current is pointer to solution vertex
  Vertex *current = &aList.at(index);

  //pushes the  vertex and pushes all the prev vertices
  while(current != nullptr){
      vStack.push(current);
      current = current->prev;
  }

  //if current and prev vertex indices match, print out the proper action
  while(vStack.size() - 1 != 0){
      current = vStack.top();
      vStack.pop();
      Vertex *prev = vStack.top();

      if (&aList.at(current->neighbors[0].first) == prev) {
        ss << "fill A" << endl;
      }
      if (&aList.at(current->neighbors[1].first) == prev) {
        ss << "fill B" << endl;
      }
      if (&aList.at(current->neighbors[2].first) == prev) {
        ss << "empty A" << endl;
      }
      if (&aList.at(current->neighbors[3].first) == prev) {
        ss << "empty B" << endl;
      }
      if (&aList.at(current->neighbors[4].first) == prev) {
        ss << "pour A B" << endl;
      }
      if (&aList.at(current->neighbors[5].first) == prev) {
        ss << "pour B A" << endl;
      }
  }

  ss << "success " << aList.at(index).distance;
  solution = ss.str();

  return 1;
}

void Jug::dijkstra() { //used dijkstra's algorithm from ZyBooks
    //needs to be Vertex pointers because when changing aList vertices, queue needs to change as well
  queue<Vertex*> q; //queue of unvisited vertices
    //assign distance and prev vertex to "infinity" and nullptr respectively
  for (unsigned i = 0; i < aList.size(); ++i) {
//    aList.at(i).distance = INT_MAX;
//    aList.at(i).prev = nullptr;
    q.push(&aList.at(i));
  }
  //at this point all vertices are unvisited
  //"visit" start node
  aList.at(0).distance = 0;
  //until all vertices are visited...
  while (!q.empty()) {
    Vertex *currentV = q.front(); //visits vertex and assigns to currentV
    q.pop(); //remove front element as it's already visited
    for (unsigned i = 0; i < 6; ++i) {
      int edgeWeight = currentV->neighbors[i].second;
      int alternativePathDistance = currentV->distance + edgeWeight;

      //relaxation
      //use neighbor's first to find proper vertex in aList
      int index = currentV->neighbors[i].first;
      if (alternativePathDistance < aList.at(index).distance) {
        aList.at(index).distance = alternativePathDistance;
        aList.at(index).prev = currentV;
      }
    }
  }
}
