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
#include <vector>
#include <cassert>

class CGraph;
class CNode;

class CEdge
{
public:
  CEdge(CNode* dst, std::uint32_t weight);
  virtual ~CEdge();
  
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
  
  /*
  setName(std::string& name)
  {
    
  }
  
  std::string name()
  {
  }*/
  
protected:
  void addEdge(CNode* dst, std::uint32_t weight); 
  
protected:
  std::uint32_t m_number;
  std::vector<CEdge*> m_edges;
  
private:

  friend CGraph;  
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
  
  bool addNode(CNode* node);
  CNode* getNode(std::uint32_t index);
  void addEdge(CNode* src, CNode* dst, std::uint32_t weight);
  
  void display(void);
  
protected:
  std::vector<CNode*> m_nodeList;
  
private:
  graphType m_type;
};

#endif // CGRAPH_H
