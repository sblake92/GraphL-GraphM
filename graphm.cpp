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
#include "graphm.h"
#include <climits>
#include <fstream>

using namespace std;

/* Constructor sets all default values for the matrix, path, and Distance
          also sets all nodes.visited to false */
GraphM:: GraphM()
{
    size = 0;
    for(int i = 1; i < MAXNODES; i++)
    {
      for(int j = 1; j < MAXNODES; j++)
      {
        AM[i][j] = INT_MAX;
        T[i][j].visited = false;
        T[i][j].dist = INT_MAX;
        T[i][j].path = 0;
      }
    }
}

GraphM::~GraphM()
{
}

/*---------------buildGraph----------------------------------
Description: takes in information from file and places it into adjecncy matrix.
allocates memory for array, array data and uses NodeData.setData function, and
insertEdge to place item.
preconditions: file has been created containing data to be input
postconditons: array is build with corresponding data
--------------------------------------------------------------*/
bool GraphM::buildGraph(ifstream& infile1)
{
  int source, to, weight = 0; //variables to be used later
  infile1 >> size; // first line in file sets size

  if(size <= 0) // test for good data
  {
    return false;
  }
  else
  {
    infile1.get(); // first grabs additional characters '/' 'n'
    infile1.get();
    for(int i = 1; i <= size; i++)
    {
      data[i].setData(infile1); // usess NodeData's setData function to
    }                           // set data of node
    for(;;) // until broken
    {
      infile1 >> source >> to >> weight; // input into variables
      if(infile1.eof())
      {
         break;
      }
      if(source == 0 || to == 0 || weight == 0)
      {
        break;
      }
      insertEdge(source, to, weight); // uses insert edge to assign values
      }
    }
  return true;
}

/*---------------InsertEdge----------------------------------
Description: Sets the distance between the source and to node
to the weight designated
preconditions: array has been allocated a
postconditons: EdgeNode is inserted into array index "node"
--------------------------------------------------------------*/
bool GraphM::insertEdge(const int source, const int to, const int weight)
{
  if((source <= size && source >= 1)  && (to <= size && to >= 1)
  && weight > 0)
  {
    AM[source][to] = weight;
  }
  return true;
}

/* to remove, simply set the value of the indexes ot INT_MAX */
bool GraphM::removeEdge(const int source, const int to)
{
  AM[source][to] = INT_MAX;
}

/*---------------findShortestPath----------------------------------
Description: finds path to every node by first making every "visited" value
false
preconditions: graph has been created with node and node data
postconditons: Depth First Search completed for all nodes from starting node.
Special Algorithms: uses Dijkstras algorithm. Uses next() function
to find the minimum weight of adjacent nodes
--------------------------------------------------------------*/
void GraphM::findShortestPath()
{
  int v = 0; // variable used to track smallest unmarked distance
  int count = 1;
  for(int source = 1; source <= size; source++)
  {
    T[source][source].dist = 0;

    while(count != size)
    {

    v = next(T[source]); // next smallest
    T[source][v].visited = true; // mark it true

    for(int i = 0; i <= size; i++)
    {
      if(T[source][i].visited == false && AM[v][i] != INT_MAX)
      {
        // check if current or v is the smaller path
        if(T[source][v].dist + AM[v][i] < T[source][i].dist)
        {
          T[source][i].dist = T[source][v].dist + AM[v][i];
          T[source][i].path = v;
        }
      }
    }
    count++;
  }
  count = 1;
  makeFalse(); // set values to false for if edges are added in
  }
}

/* function to help find the smallest value for v */
int GraphM::next(TableType t[])
{
  int min = 1, low = INT_MAX;
  for(int i = 1; i <= size; i++)
  {
    if(t[i].visited == false && t[i].dist < low)
    {
      low = t[i].dist;
      min = i;
    }
  }
  return min;
}

/* sets all values to false in T*/
void GraphM::makeFalse()
{
  for(int i = 1; i <= size; i++)
  {
    for(int j = 1; j <= size; j++)
    {
      T[i][j].visited = false;
    }
  }
}


/* Displays the entire Table */
void GraphM::displayAll() const
{
  for(int i = 1; i <= size; i++)
  {
    cout << "Description:"  << endl;
    cout << data[i] << endl;
    cout <<"From:     To:     Dijkstra:   Path:" << endl;
    for(int j = 1; j <= size; j++)
    {
      if(i != j)
      {
        cout << i << "         " << j << "       ";
        if(T[i][j].dist > 0 && T[i][j].dist != INT_MAX)
        {
          cout << T[i][j].dist <<"           ";
          path(i, j);

        }
        else
        {
          cout << "----";
        }
        cout << endl;
      }
    }
    cout << endl;
  }
}

/* Prints only the path to and from specfied nodes */
void GraphM::display(const int from, const int to) const
{
  cout << "From " << "To " << "Distance " << "Path" << endl;
  if(!(T[from][to].dist != INT_MAX))
  {
    cout << from << "    " << to << "   ----   "<< "NO PATH" << endl;
  }
  else
  {
    cout << from << "    " << to << "   " <<T[from][to].dist <<
     "      ";
    path(from, to);
    pathData(from, to);
    cout << data[to] << endl;
  }
  cout << endl;
}

/* Recursive function to print the path to and from nodes */
void GraphM::path(const int from, const int to) const
{
  if(from != to)
  {
    if(T[from][to].path != 0)
    {
      path(from, T[from][to].path); // Finds previous path node
    }
  }
  cout << to << " ";
}

                /*
Same logic as path, however this function
prints the data on each nodesUsed for convienence
      for display funciton
                */
void GraphM::pathData(const int from, const int to) const
{
  if(from != to)
  {
    if(T[from][to].path > 0)
    {
      pathData(from, T[from][to].path);
    }
  }
  cout << data[T[from][to].path] << endl;
}
