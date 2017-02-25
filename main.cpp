#include <iostream>
#include "cgraph.h"

int main(int argc, char **argv)
{
  CGraph myGraph(CGraph::NOT_ORIENTED);
  
  CNode* n = new CNode(0); 
  myGraph.addNode(n);
  
  myGraph.display();
  return 0;
}
