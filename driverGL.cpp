#include <iostream>
#include <fstream>
#include "graphl.h"
using namespace std;

int main()
{
  ifstream infile2("GLtest.txt");
  if (!infile2) {
    cout << "File could not be opened." << endl;
    return 1;
  }

  //for each graph, find the depth-first search ordering
  for (;;) {
    GraphL G;
    G.buildGraph(infile2);
    if (infile2.eof())
      break;
    G.displayGraph();
    
    G.depthFirstSearch();    // find and display depth-first ordering to cout
  }

  cout << endl;
  return 0;
};
