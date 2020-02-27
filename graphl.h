/* GraphL
-------------------------------------------------------
 Scott Blake CSS 343
 18  July 2019
 22 July 2019
-------------------------------------------------------------------------------

This program builds an adjecncy list and uses Depth First Search to find
edges to and from all nodes
----------------------------------------------------------------------------
None
------------------------------------------------------------------------------*/
#pragma once
#include "nodedata.h"
#include <iostream>
#include <fstream>

using namespace std;

struct EdgeNode
{
  int adjGraphNode;
  EdgeNode* eNext;
};

struct GraphNode
{
  EdgeNode* eHead;
  NodeData* data;
  bool visited;
};

class GraphL
{
public:
  GraphL();
  ~GraphL();

  bool buildGraph(ifstream&);
  void depthFirstSearch();
  void displayGraph() const;

private:
  GraphNode* arr; //array of graphnodes
  int size;
  void deleteGraph(); // deletes all memory
  bool insert(const int, const int);// helper function to insert data
  void dfs(int); // recursive function to assist depthFirstSearch
  void makeFalse(); // used to assign all values in arr to false
};
#include "graphl.cpp"
