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

TEST_CASE("check best short not oriented graph with stop at intermediate node", "[Dijkstra algo]")
{
  std::cout << "test start" << std::endl;
  CGraph myGraph(CGraph::NOT_ORIENTED);
  std::uint32_t i;
  CNode* nodeA = new CNode(0);
  CNode* nodeB = new CNode(1);
  CNode* nodeC = new CNode(2);
  CNode* nodeD = new CNode(3);
  CNode* nodeE = new CNode(4);
  CNode* nodeF = new CNode(5);
  CNode* nodeG = new CNode(6);
  CNode* nodeH = new CNode(7);
  CNode* nodeI = new CNode(8);
  CNode* nodeJ = new CNode(9);

  myGraph.insertNode(nodeA);
  myGraph.insertNode(nodeB);
  myGraph.insertNode(nodeC);
  myGraph.insertNode(nodeD);
  myGraph.insertNode(nodeE);
  myGraph.insertNode(nodeF);
  myGraph.insertNode(nodeG);
  myGraph.insertNode(nodeH);
  myGraph.insertNode(nodeI);
  myGraph.insertNode(nodeJ);

  myGraph.addEdge(nodeA, nodeB, 85);
  myGraph.addEdge(nodeA, nodeC, 217);
  myGraph.addEdge(nodeA, nodeE, 173);
  myGraph.addEdge(nodeB, nodeF, 80);
  myGraph.addEdge(nodeC, nodeG, 186);
  myGraph.addEdge(nodeC, nodeH, 103);
  myGraph.addEdge(nodeD, nodeH, 183);
  myGraph.addEdge(nodeE, nodeJ, 502);
  myGraph.addEdge(nodeF, nodeI, 250);
  myGraph.addEdge(nodeH, nodeJ, 167);
  myGraph.addEdge(nodeI, nodeJ, 84);

  myGraph.display();
  std::vector<std::uint32_t> distance;
  //std::vector<std::uint32_t> distanceResult = { 0, 85, 217, 503, 173, 165, 403, 320, 415, 487 };
  std::vector<std::uint32_t> distanceResult = { 0, 85, 217, UINT32_MAX, 173, 165, 403, 320, 415, 675 };
  std::vector<CNode*> father;
  std::vector<std::uint32_t> fatherByNumber;
  //std::vector<std::uint32_t> fatherResult = { 0, 0, 0, 7, 0, 1, 2, 2, 5, 7};
  std::vector<std::uint32_t> fatherResult = { 0, 0, 0, 0, 0, 1, 2, 2, 5, 4};


  myGraph.bestShortPathSearch(nodeA, distance, father, nodeH);


  std::cout << "distanceB" << std::endl;
  std::uint32_t index;
  for (index = 0; index < distance.size(); index++)
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