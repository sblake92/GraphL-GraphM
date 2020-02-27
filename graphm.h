/* GraphL
-------------------------------------------------------
 Scott Blake CSS 343
 18  July 2019
 24 July 2019
-------------------------------------------------------------------------------

This program builds a graph and used Dijkstra's algorithm to determine the
shortest path to each node from a source node
----------------------------------------------------------------------------
Dijkstras Algorithm
------------------------------------------------------------------------------*/
#pragma once
#include "nodedata.h"
#include <iostream>
#include <fstream>

using namespace std;

const int MAXNODES = 101; // node starts at 1 but has no more than 100

struct TableType
{
  bool visited;
  int dist;
  int path;
};

class GraphM
{
public:
  GraphM();
  ~GraphM();

  bool buildGraph(ifstream&);
  bool insertEdge(const int, const int, const int);
  bool removeEdge(const int, const int);
  void findShortestPath();

  void displayAll()const;
  void display(const int, const int)const;


private:
  NodeData data[MAXNODES];
  int AM[MAXNODES][MAXNODES];
  int size;
  TableType T[MAXNODES][MAXNODES];
  int next(TableType []); // helper function for fsp to find smallest path
  void makeFalse(); // sets all locations in table to false
  void path(const int, const int) const; // recursive funciton to get path
  void pathData(const int, const int) const; // same as path just prints data at each

};
#include "graphm.cpp"
