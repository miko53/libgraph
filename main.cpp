#include <iostream>
#include "cgraph.h"

int main(int argc, char** argv)
{
  CGraph myGraph(CGraph::NOT_ORIENTED);

  CNode* n = new CNode(0);
  myGraph.insertNode(n);
  CNode* n1 = new CNode(1);
  myGraph.insertNode(n1);
  CNode* n2 = new CNode(2);
  myGraph.insertNode(n2);

  myGraph.addEdge(n, n1, 1);

  myGraph.display();
  return 0;
}
