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

#ifndef CGRAPH_H
#define CGRAPH_H

#include <cstdint>
#include <cassert>
#include <vector>
#include <list>

class CGraph;
class CNode;

class CEdge
{
public:
  CEdge(CNode* dst, std::uint32_t weight);
  virtual ~CEdge();

  CNode* node(void)
  {
    return m_dst;
  }

  std::uint32_t weigth(void)
  {
    return m_weight;
  }

protected:
  CNode* m_dst;
  std::uint32_t m_weight;
};

class CNode
{
public:
  CNode(std::uint32_t index);
  virtual ~CNode();

  std::uint32_t number()
  {
    return m_number;
  }

  std::uint32_t nbSuccessors(void)
  {
    return m_edges.size();
  }

  CNode* successorAt(std::uint32_t index)
  {
    return m_edges.at(index)->node();
  }

  std::uint32_t weigthAt(std::uint32_t index)
  {
    return m_edges.at(index)->weigth();
  }

  void displayEdges(void);
  /*
  setName(std::string& name)
  {

  }

  std::string name()
  {
  }*/

protected:
  void createEdge(CNode* dst, std::uint32_t weight);

protected:
  std::uint32_t m_number;
  std::vector<CEdge*> m_edges;

private:

  friend CGraph;
};

class CGraphObserver
{
public:
  virtual bool action(CNode* c) = 0;
protected:
private:
};

class CGraph
{
public:

  typedef enum
  {
    NOT_ORIENTED,
    ORIENTED
  } graphType;

  CGraph(graphType type);
  virtual ~CGraph();

  bool insertNode(CNode* node);
  CNode* getNode(std::uint32_t index);
  void addEdge(CNode* src, CNode* dst, std::uint32_t weight);

  std::uint32_t nodeNumber()
  {
    return m_nodeList.size();
  }

  //debug
  void display(void);

  //parcours en profondeur
  void depthFirstSearchInitialize(std::vector< uint32_t >& visited);
  void depthFirstSearch(CNode* start, std::vector<std::uint32_t>& visited, CGraphObserver* observer);

  //parcours en largeur
  void breadthFirstSearchInitialize(std::vector< uint32_t >& visited);
  void breadthFirstSearch(CNode* start, std::vector<std::uint32_t>& visited, CGraphObserver* observer);

  //recherche du chemin le plus court (Dijkstra)
  void bestShortPathSearch(CNode* start, std::vector<std::uint32_t>& dist, std::vector<CNode*>& father);

private:
  void initializeVisitedVector(std::vector< uint32_t >& visited);
  std::uint32_t cost(CNode* s, CNode* e);
  CNode* selectMin(std::list<CNode*>& m, std::vector< uint32_t >& dist);

protected:
  std::vector<CNode*> m_nodeList;

private:
  graphType m_type;
};

#endif // CGRAPH_H
