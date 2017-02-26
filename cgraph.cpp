/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2017  Mickael Sergent <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "cgraph.h"
#include <iostream>
#include <stack>

CGraph::CGraph(graphType type)
{
  m_type = type;
}

CGraph::~CGraph()
{

}

bool CGraph::insertNode(CNode* node)
{
  bool rc;
  rc = false;
  if (getNode(node->number()) == nullptr)
  {
    m_nodeList.push_back(node);
    rc = true;
  }
  return rc;
}

CNode* CGraph::getNode(uint32_t index)
{
  CNode* pFound;
  pFound = nullptr;

  for (std::uint32_t i = 0; i < m_nodeList.size(); i++)
  {
    if (m_nodeList.at(i)->number() == index)
    {
      pFound = m_nodeList.at(i);
      return pFound;
    }
  }
  return pFound;
}


void CGraph::display(void)
{
  CNode* pCurrent;

  std::cout << "graph" << std::endl;

  for (std::uint32_t i = 0; i < m_nodeList.size(); i++)
  {
    pCurrent = m_nodeList.at(i);
    std::cout << pCurrent->number() << " : ";
    pCurrent->displayEdges();
    std::cout << std::endl;
  }
}


void CGraph::addEdge(CNode* src, CNode* dst, uint32_t weight)
{
  switch (m_type)
  {
    case NOT_ORIENTED:
      dst->createEdge(src, weight);
    //break; no break to build the two edge in case on not oriented graph

    case ORIENTED:
      src->createEdge(dst, weight);
      break;

    default:
      assert(false);
      break;
  }
}


void CGraph::depthFirstSearchInitialize(std::vector< uint32_t >& visited)
{
  visited.clear();
  visited.resize(m_nodeList.size(), false);
}

//parcours en profondeur
void CGraph::depthFirstSearch(CNode* start, std::vector<std::uint32_t>& visited, CGraphObserver* observer)
{
  std::stack<CNode*> stack;
  std::vector<std::uint32_t> indexOfNodeToVisite(m_nodeList.size(), -1);
  CNode* currentNode;

  assert(start != nullptr);

  currentNode = start;
  visited[currentNode->number()] = true;
  if (currentNode->nbSuccessors() > 0)
  {
    stack.push(currentNode);
    indexOfNodeToVisite[currentNode->number()] = 0;
    observer->action(currentNode);
  }

  while (stack.empty() == false)
  {
    currentNode = stack.top();
    stack.pop();

    while (indexOfNodeToVisite[currentNode->number()] < currentNode->nbSuccessors())
    {
      CNode* nextNode;
      nextNode = currentNode->successorAt(indexOfNodeToVisite[currentNode->number()]);
      if (visited[nextNode->number()] == false)
      {
        visited[nextNode->number()] = true;
        stack.push(currentNode);
        //go to next node
        CNode* backup = currentNode;
        currentNode = nextNode;
        indexOfNodeToVisite[nextNode->number()] = 0;
        indexOfNodeToVisite[backup->number()]++;
        observer->action(currentNode);
      }
      else
      {
        indexOfNodeToVisite[currentNode->number()]++;
      }
    }
  }
}

CNode::CNode(uint32_t index)
{
  m_number = index;
}

CNode::~CNode()
{

}

void CNode::createEdge(CNode* dst, uint32_t weight)
{
  CEdge* e = new CEdge(dst, weight);
  m_edges.push_back(e);
}


CEdge::CEdge(CNode* dst, std::uint32_t weight)
{
  m_dst = dst;
  m_weight = weight;
}

void CNode::displayEdges(void)
{
  CEdge* pCurrent;

  for (std::uint32_t i = 0; i < m_edges.size(); i++)
  {
    pCurrent = m_edges.at(i);
    std::cout << pCurrent->node()->number() << " (" << pCurrent->weigth() << ") ";
  }
}


CEdge::~CEdge()
{

}
