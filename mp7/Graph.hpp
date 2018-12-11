#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>

/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::size() const {

  return vertexMap.size();
}


/**
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {

  return adjList.at(v.key()).size();
}


/**
* Inserts a Vertex into the Graph by adding it to the Vertex map and adjacency list
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  // TODO: Part 2
  V & v = *(new V(key));
  std::pair<std::string, V &> vertex (key,v);
  vertexMap.insert(vertex);
  std::list<edgeListIter> empty;
  std::pair<std::string,std::list<edgeListIter>> adj (key,empty);
  adjList.insert(adj);
  return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
  V vertex = vertexMap.at(key);
  std::list<edgeListIter> & edge_ = adjList.at(key);
  // std::cout<<"1"<<std::endl;
  for(auto it=edge_.begin(); it != edge_.end(); ++it)
  {
    // std::cout<<"2"<<std::endl;
    std::string temp = "";
    if((*it)->get().source().key() == key)
    {
      temp = (*it)->get().dest().key();
    }
    else
      temp = (*it)->get().source().key();

    std::list<edgeListIter> & edge_temp = adjList.at(temp);
    for(auto it_1 = edge_temp.begin(); it_1 != edge_temp.end(); ++it_1)
    {
      if((*it_1) == (*it))
      {
        edge_temp.erase(it_1);
        break;
      }
    }
    edgeList.erase(*it);

    // std::cout<<"3"<<std::endl;
  }
  // std::cout<<"4"<<std::endl;
  adjList.erase(key);
  vertexMap.erase(key);
}


/**
* Inserts an Edge into the adjacency list
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  // TODO: Part 2
  E & e = *(new E(v1, v2));
  edgeList.push_front(e);
  edgeListIter edge_ = edgeList.begin();
  adjList.at(v1.key()).push_front(edge_);
  adjList.at(v2.key()).push_front(edge_);
  return e;
}


/**
* Removes an Edge from the Graph
* @param key1 The key of the ource Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {
  E edge_ = E(key1,key2);
  std::list<edgeListIter> edge_1 = adjList.at(key1);
  for(auto it_1=edge_1.begin(); it_1 != edge_1.end(); ++it_1)
  {
    if(edge_ == **it_1)
    {
      removeEdge(*it_1);
      break;
    }
  }

}


/**
* Removes an Edge from the adjacency list at the location of the given iterator
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  std::string key1 = (*it).get().source().key();
  std::string key2 = (*it).get().dest().key();
  E edge = *it;
  std::list<edgeListIter> & edge_1 = adjList.at(key1);
  std::list<edgeListIter> & edge_2 = adjList.at(key2);
  for(auto it_1=edge_1.begin(); it_1 != edge_1.end(); ++it_1)
  {
    if(edge == **it_1)
    {
      edge_1.erase(it_1);
     }
  }
  for(auto it_1=edge_2.begin(); it_1 != edge_2.end(); ++it_1)
  {
    if(edge == **it_1)
    {
      edge_2.erase(it_1);
     }
  }
  edgeList.erase(it);
}


/**
* @param key The key of an arbitrary Vertex "v"
* @return The list edges (by reference) that are adjacent to "v"
*/
template <class V, class E>
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  // TODO: Part 2
  std::list<std::reference_wrapper<E>> edges;
  std::list<edgeListIter> edge_1 = adjList.at(key);
  for(auto it=edge_1.begin(); it != edge_1.end(); ++it)
  {
    E edge = **it;
    if(edge.directed())
    {
      if(edge.source().key() == key)
      {
        edges.push_front(**it);
      }
    }
    else
      edges.push_front(**it);
  }
  return edges;
}


/**
* Return whether the two vertices are adjacent to one another
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
  std::string vert_1 = "";
  std::string vert_2 = "";

  if(degree(vertexMap.at(key1)) > degree(vertexMap.at(key2)))
  {
    vert_1 = key2;
    vert_2 = key1;
  }
  else
  {
    vert_1 = key1;
    vert_2 = key2;
  }
  std::list<edgeListIter> edge_1 = adjList.at(vert_1);
  for(auto it = edge_1.begin(); it != edge_1.end(); ++it)
  {
    if((*it)->get().directed())
    {
      if((*it)->get().source().key() == vert_1 && (*it)->get().dest().key() == vert_2)
        return true;
    }
    else if((*it)->get().source().key() == vert_2 || (*it)->get().dest().key() == vert_2)
    {
      return true;
    }
  }
  return false;
}
