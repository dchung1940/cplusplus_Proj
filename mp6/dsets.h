/* Your code here! */
#pragma once

#include <iostream>
#include <vector>

using namespace std;

class DisjointSets
{
public:
  //constructor
  // DisjointSets::DisjointSets();
  /**
   * Creates n unconnected root nodes at the end of the vector.
   */
  void addelements(int num);

  /**
   * This function should compress paths and works as described in lecture.
   */
  int find(int elem);

  /**
   * This function should be implemented as union-by-size
   */
  void setunion(int a, int b);

  /**
   * This function should return the number of nodes in the up-tree containing the element.
   */
  int size(int elem);

private:
  vector<int> nodes;
};
/* Your code here! */
