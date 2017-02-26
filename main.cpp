#include <iostream>
#include "cgraph.h"

class CGraphDisplayObserver : public CGraphObserver
{
  virtual bool action(CNode* c);
};

bool CGraphDisplayObserver::action(CNode* c)
{
  std::cout << c->number() << std::endl;
  return true;
}

void test_deptFirstSearch(void);


int main(int argc, char** argv)
{
  test_deptFirstSearch();
  /*
  CGraph myGraph(CGraph::NOT_ORIENTED);

  CNode* n = new CNode(0);
  myGraph.insertNode(n);
  CNode* n1 = new CNode(1);
  myGraph.insertNode(n1);
  CNode* n2 = new CNode(2);
  myGraph.insertNode(n2);

  myGraph.addEdge(n, n1, 1);

  myGraph.display();

  CGraphDisplayObserver obsever;

  bool r;
  std::cout << "depthFirstSearch" << std::endl;
  r = myGraph.depthFirstSearch(n, &obsever);
  */
  return 0;
}

bool isAllNodeVisited(std::vector<std::uint32_t>& visitedNode, std::uint32_t& next)
{
  for (std::uint32_t i = 0; i < visitedNode.size(); i++)
  {
    if (visitedNode[i] == false)
    {
      next = i;
      return false;
    }
  }

  return true;
}

void test_deptFirstSearch(void)
{
  CGraph myGraph(CGraph::ORIENTED);
  std::uint32_t i;
  CNode* nodes[10];

  nodes[0] = nullptr;
  for (i = 1; i < 10; i++)
  {
    nodes[i] = new CNode(i);
    myGraph.insertNode(nodes[i]);
  }

  myGraph.addEdge(nodes[1], nodes[3], 1);
  myGraph.addEdge(nodes[1], nodes[5], 1);
  myGraph.addEdge(nodes[1], nodes[6], 1);
  myGraph.addEdge(nodes[1], nodes[7], 1);
  myGraph.addEdge(nodes[2], nodes[1], 1);
  myGraph.addEdge(nodes[3], nodes[2], 1);
  myGraph.addEdge(nodes[3], nodes[6], 1);
  myGraph.addEdge(nodes[4], nodes[2], 1);
  myGraph.addEdge(nodes[4], nodes[9], 1);
  myGraph.addEdge(nodes[7], nodes[3], 1);
  myGraph.addEdge(nodes[8], nodes[2], 1);
  myGraph.addEdge(nodes[8], nodes[4], 1);
  myGraph.addEdge(nodes[8], nodes[5], 1);

  myGraph.display();

  CGraphDisplayObserver observer;

  std::cout << "depthFirstSearch" << std::endl;
  std::vector<std::uint32_t> visitedNode;
  myGraph.depthFirstSearchInitialize(visitedNode);
  visitedNode[0] = true; //doesn't exist
  std::uint32_t next;
  while (isAllNodeVisited(visitedNode, next) == false)
  {
    myGraph.depthFirstSearch(nodes[next], visitedNode, &observer);
  }

}
