#include "Graph.h"
#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

 Graph::Graph() {}

Graph::Graph(ifstream& ifs) {
  int numNodes = 0;
  int numEdges = 0;
  string tempTitles = "";
  string edgeTitles = "";
  int tempWeight = 0;

  ifs >> numNodes;
  ifs >> numEdges;

  ifs.ignore();

  for (int i = 0; i < numNodes; ++i) {
    Vertex title;
    getline(ifs,tempTitles);
    title.label = tempTitles;
    vertices.push_back(title);
  }

  while (ifs >> edgeTitles) {
    int startIndex = 0;
    int tempIndex = 0;
    ifs >> tempTitles;
    ifs >> tempWeight;

    for(unsigned i = 0; i < vertices.size(); ++i){
      if(edgeTitles == vertices.at(i).label){
        startIndex = i;
      }
      if(tempTitles == vertices.at(i).label){
        tempIndex = i;
      }
    }
    vertices.at(startIndex).neighbors.push_back(make_pair(tempIndex,tempWeight));
  }

//    for(unsigned i = 0; i < vertices.size(); i++)
//        cout << vertices.at(i).label << endl;
}

Graph::~Graph() {}

void Graph::bfs()
{
//    cout << "bfs" << endl;
  vertices.at(0).distance = 0;
  //Vertex start = vertices.at(0);
  queue<Vertex*> q;
  q.push(&vertices.at(0));

  while(q.empty() == false)
  {
    Vertex* front = q.front();
    q.pop();
    front->color = "GREY";
    list<pair<int,int> >::iterator it;

    for(it = front->neighbors.begin();it != front->neighbors.end(); ++it)
    {
      if(vertices.at(it->first).color == "WHITE")
       {
         vertices.at(it->first).prev = front;
         vertices.at(it->first).distance = 0;
         vertices.at(it->first).color = "GREY";
         vertices.at(it->first).distance += vertices.at(it->first).prev->distance + it->second;
         q.push(&vertices.at(it->first));
       }

    }
    front->color = "BLACK";
    //cout <<vertices.at(0).color << endl;
    }
    //vertices.at(0).distance = 0;

//      for(unsigned i = 0; i < vertices.size(); ++i) {
//       cout << vertices.at(i).distance << endl;
//    }
}

void Graph::output_graph(const string &outputFilename) {
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    output_graph(outFS,vertices.at(0));
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void Graph::output_graph(ofstream & outFS, Vertex n)
{
  for(unsigned i = 0; i < vertices.size(); ++i)
  {
    if(vertices.at(i).distance != INT_MAX)
    {
      outFS << vertices.at(i).label << " [label= \"Label: " << vertices.at(i).label << ", Distance: " << vertices.at(i).distance << "\"];" << endl;
    }

    list<pair<int,int> >::iterator it;

    for(it = vertices.at(i).neighbors.begin();it != vertices.at(i).neighbors.end(); ++it)
    {
      if(vertices.at(i).distance != INT_MAX)
      {
         outFS << vertices.at(i).label << " -> " << vertices.at(it->first).label << endl;
      }
    }
  }
}

int Graph::distance(const string& key) {
//    cout << "distance" << endl;
//    cout << "key: " << key << endl;
    for(unsigned i = 0; i < vertices.size(); i++) {
        if(vertices.at(i).label == key) {
//            cout << "Distance is: " << vertices.at(i).distance << endl;
            return vertices.at(i).distance;
        }
    }
    return -1;
}

string Graph::previous(const string& key) {
//    cout << "previous" << endl;
//    cout << "key: " << key << endl;
    for(unsigned i = 0; i < vertices.size(); i++) {
        if(vertices.at(i).label == key && i != 0) {
//            cout << "Prev label is: " << vertices.at(i).prev->label << endl;
            return vertices.at(i).prev->label;
        }
    }
    return "";
}

