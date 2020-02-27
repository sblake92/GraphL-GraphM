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
#include "graphl.h"
#include <iostream>
#include <fstream>

using namespace std;

// constructor just assigns size to 0
GraphL:: GraphL()
{
  size = 0;
}

/*---------------Deconstructor----------------------------
Description: deallocates memory of each EdgeNode in the array, sets them to NULL
then; deletes the array data, sets it to NULL; then finally deletes the array
and sets it to NULL by calling deleteGraph
preconditions: memory has been allocated for the array and its nodes
postconditons: all memory is deallocated
--------------------------------------------------------------*/
GraphL::~GraphL()
{
  deleteGraph();
}

void GraphL::deleteGraph()
{
  if(size > 0)
  {
    for(int i = 1; i <= size; i++)
    {
      while(arr[i].eHead != NULL)
      {
        EdgeNode* curr = arr[i].eHead; // created to traverse
        arr[i].eHead = arr[i].eHead->eNext;
        curr->eNext = NULL;
        delete curr;
      }
        delete arr[i].data;
        arr[i].data = NULL;
      }
      delete [] arr; // delete array
      //arr =  NULL; // set array = NULL
  }
}


/*---------------Insert----------------------------------
Description: Allocates new memory for EdgeNode then places it in the
array in the location designated by int node
preconditions: array has been allocated
postconditons: EdgeNode is inserted into array index "node"
--------------------------------------------------------------*/
bool GraphL::insert(const int node, const  int edge)
{
  if(node != edge)
  {
    EdgeNode* curr = new EdgeNode;
    curr->adjGraphNode = edge;
    if(node != edge)
    {
      if(arr[node].eHead == NULL) // if head is empty, set as head
      {
        curr->eNext = NULL;
        arr[node].eHead = curr;
      }
      else // otherwise move the head to the next node and assign to head
      {
        curr->eNext = arr[node].eHead;
        arr[node].eHead = curr;
      }
      return true;
    }
  }
  return false;
}

/*---------------buildGraph----------------------------------
Description: takes in information from file and places it into graph. allocates
memory for array, array data and uses NodeData.setData function, and insert to
place item.
preconditions: file has been created containing data to be input
postconditons: array is build with corresponding data
--------------------------------------------------------------*/
bool GraphL::buildGraph(ifstream& infile2)
{
  int node, edge = 0; // variables to be assigned later
  infile2 >> size; // first line of file is size

  if(size <= 0) // testing for good input
  {
    return false;
  }
  else
  {
    infile2.get(); // forces file to skip first line as its already
    infile2.get(); // been used for size. Takes in first line following
    arr = new GraphNode[size + 1]; // dynamicaly allocate new memory for array
    for(int i = 1; i <= size; i++)
    {
        arr[i].data = new NodeData; // new memory for data
        arr[i].data->setData(infile2); // uses NodeData setData function
        arr[i].eHead = NULL;
        arr[i].visited = false;
    }
    for(;;) // until empty
    {
      infile2 >> node >> edge; // input from file
      if(infile2.eof()) break; // end of file, end.
      if(node == 0 || edge == 0) break; // discard 0 values.

      insert(node, edge); // inserts into array
    }
  }
  return true;
}

/*---------------depthFirstSearch----------------------------------
Description: finds path to every node by first making every "visited" value
false
preconditions: graph has been created with node and node data
postconditons: Depth First Search completed for all nodes from starting node.
Special Algorithms: uses dfs() recursive function
--------------------------------------------------------------*/
void GraphL::depthFirstSearch()
{
  makeFalse(); // first sets all values to false
  cout << "Depth First Search: ";
  for(int i = 1; i <= size; i++) // for each location in the array
  {
    if(!arr[i].visited)
    {
      dfs(i); // recursive funciton for each location in array
    }
  }
  cout << endl;
  cout << endl;
}

/* recursive helper function to find all edges to nodes */
void GraphL::dfs(int n)
{
  arr[n].visited = true; // sets first location to true
  cout << n << " ";
  EdgeNode* curr = arr[n].eHead;
  while(curr != NULL)
  {
    if(!arr[curr->adjGraphNode].visited) // if it has been visited
    {
      dfs(curr->adjGraphNode); //check the next node
    }
    curr = curr->eNext; // otherwise move to the next node
  }
}

/* sets all values to false in array */
void GraphL::makeFalse()
{
  for(int i = 1; i <= size; i++)
  {
    arr[i].visited = false;
  }
}

/* Displays all edges from each Node and the Nodes data */
void GraphL::displayGraph() const
{
  cout << "Graph:" << endl;
  for(int i = 1; i <= size; i++)
  {
    cout << "Node " << i << " " << *arr[i].data << endl;
    if(arr[i].eHead != NULL)
    {
      EdgeNode* curr = arr[i].eHead;
      while(curr != NULL)
      {
        cout << "    Edge " << i << " " << curr->adjGraphNode << endl;
        curr = curr->eNext;
      }
    }
  }
}
