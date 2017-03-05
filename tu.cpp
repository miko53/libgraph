#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include <vector>
#include "cgraph.h"
#include <cstdint>

class CGraphDisplayObserver : public CGraphObserver
{
  virtual bool action(CNode* c);
public:
  std::vector<std::uint32_t> m_visitedNode;
};

bool CGraphDisplayObserver::action(CNode* c)
{
  std::cout << c->number() << std::endl;
  m_visitedNode.push_back(c->number());
  return true;
}

bool isAllNodeVisited(std::vector<bool>& visitedNode, std::uint32_t& next)
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

TEST_CASE( "check that depth first search algo is ok", "[depth first search]" )
{
  //graph creation
  CGraph myGraph(CGraph::ORIENTED);
  std::uint32_t i;
  CNode* nodes[9];
  std::vector<bool> visitedNode;
  std::uint32_t next;

  for (i = 0; i < 9; i++)
  {
    nodes[i] = new CNode(i);
    myGraph.insertNode(nodes[i]);
  }

  myGraph.addEdge(nodes[0], nodes[2], 1);
  myGraph.addEdge(nodes[0], nodes[4], 1);
  myGraph.addEdge(nodes[0], nodes[5], 1);
  myGraph.addEdge(nodes[0], nodes[6], 1);
  myGraph.addEdge(nodes[1], nodes[0], 1);
  myGraph.addEdge(nodes[2], nodes[1], 1);
  myGraph.addEdge(nodes[2], nodes[5], 1);
  myGraph.addEdge(nodes[3], nodes[1], 1);
  myGraph.addEdge(nodes[3], nodes[8], 1);
  myGraph.addEdge(nodes[6], nodes[2], 1);
  myGraph.addEdge(nodes[7], nodes[1], 1);
  myGraph.addEdge(nodes[7], nodes[3], 1);
  myGraph.addEdge(nodes[7], nodes[4], 1);

  myGraph.display();

  CGraphDisplayObserver observer;

  myGraph.depthFirstSearchInitialize(visitedNode);

  REQUIRE(isAllNodeVisited(visitedNode, next) == false);

  while (isAllNodeVisited(visitedNode, next) == false)
  {
    myGraph.depthFirstSearch(nodes[next], visitedNode, &observer);
  }

  std::vector<std::uint32_t> depthFirstSearchResult { 0, 2, 1, 5, 4, 6, 3, 8, 7};
  REQUIRE(depthFirstSearchResult == observer.m_visitedNode);

}


TEST_CASE( "check that breath first search algo is ok", "[breath first search]" )
{
  //graph creation
  CGraph myGraph(CGraph::ORIENTED);
  std::uint32_t i;
  CNode* nodes[9];
  std::vector<bool> visitedNode;
  std::uint32_t next;

  for (i = 0; i < 9; i++)
  {
    nodes[i] = new CNode(i);
    myGraph.insertNode(nodes[i]);
  }

  myGraph.addEdge(nodes[0], nodes[2], 1);
  myGraph.addEdge(nodes[0], nodes[4], 1);
  myGraph.addEdge(nodes[0], nodes[5], 1);
  myGraph.addEdge(nodes[0], nodes[6], 1);
  myGraph.addEdge(nodes[1], nodes[0], 1);
  myGraph.addEdge(nodes[2], nodes[1], 1);
  myGraph.addEdge(nodes[2], nodes[5], 1);
  myGraph.addEdge(nodes[3], nodes[1], 1);
  myGraph.addEdge(nodes[3], nodes[8], 1);
  myGraph.addEdge(nodes[6], nodes[2], 1);
  myGraph.addEdge(nodes[7], nodes[1], 1);
  myGraph.addEdge(nodes[7], nodes[3], 1);
  myGraph.addEdge(nodes[7], nodes[4], 1);

  myGraph.display();

  CGraphDisplayObserver observer;

  myGraph.breadthFirstSearchInitialize(visitedNode);

  REQUIRE(isAllNodeVisited(visitedNode, next) == false);
  while (isAllNodeVisited(visitedNode, next) == false)
  {
    myGraph.breadthFirstSearch(nodes[next], visitedNode, &observer);
  }

  REQUIRE(visitedNode.size() == 9);
  for (i = 0; i < 9; i++)
  {
    REQUIRE(visitedNode[i] == true);
  }

  std::vector<std::uint32_t> breadthFirstSearchResult { 0, 2, 4, 5, 6, 1, 3, 8, 7};
  REQUIRE(breadthFirstSearchResult == observer.m_visitedNode);

}


TEST_CASE("check best short path algo", "[Dijkstra algo]")
{
  CGraph myGraph(CGraph::ORIENTED);
  std::uint32_t i;
  CNode* nodes[6];

  for (i = 0; i < 6; i++)
  {
    nodes[i] = new CNode(i);
    myGraph.insertNode(nodes[i]);
  }

  myGraph.addEdge(nodes[0], nodes[1], 10);
  myGraph.addEdge(nodes[0], nodes[2], 3);
  myGraph.addEdge(nodes[0], nodes[4], 6);
  myGraph.addEdge(nodes[1], nodes[0], 0);
  myGraph.addEdge(nodes[2], nodes[1], 4);
  myGraph.addEdge(nodes[2], nodes[4], 2);
  myGraph.addEdge(nodes[3], nodes[2], 1);
  myGraph.addEdge(nodes[3], nodes[4], 3);
  myGraph.addEdge(nodes[4], nodes[1], 0);
  myGraph.addEdge(nodes[4], nodes[5], 1);
  myGraph.addEdge(nodes[5], nodes[0], 2);
  myGraph.addEdge(nodes[5], nodes[1], 1);

  myGraph.display();
  std::vector<std::uint32_t> distance;
  std::vector<std::uint32_t> distanceResult = { 0, 5, 3, UINT32_MAX, 5, 6};
  std::vector<CNode*> father;
  std::vector<std::uint32_t> fatherByNumber;
  std::vector<std::uint32_t> fatherResult = { 0, 4, 0, 0, 2, 4};


  myGraph.bestShortPathSearch(nodes[0], distance, father);


  std::cout << "distance" << std::endl;
  std::uint32_t index;
  for (index = 0; index < 6; index++)
  {
    std::cout << distance[index] << std::endl;
  }

  REQUIRE(distance == distanceResult);

  std::cout << "father" << std::endl;
  for (index = 0; index < father.size(); index++)
  {
    fatherByNumber.push_back((father[index])->number());
    if (father[index] != nullptr)
    {
      std::cout << (father[index])->number() << std::endl;
    }
    else
    {
      std::cout << "nullptr" << std::endl;
    }
  }
  REQUIRE(fatherByNumber == fatherResult);
}
