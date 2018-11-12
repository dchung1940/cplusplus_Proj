/* Your code here! */
#include "dsets.h"
#include <iostream>

using namespace std;

/**
 * Parameters: num	The number of nodes to create
 */
void DisjointSets::addelements(int num)
{
  for(int i=0; i < num; i++)
  {
    nodes.push_back(-1);
  }
}

/**
 * Returns
 *  the index of the root of the up-tree in which the parameter element resides.
 */
int DisjointSets::find(int elem)
{
  if ( nodes[elem] < 0 )
  {
    return elem;
  }
  else
  {
    return find(nodes[elem]);
  }
}

/**
 * Parameters
 *  a	Index of the first element to union
 *  b	Index of the second element to union
 */
void DisjointSets::setunion(int a, int b)
{
  int rootA = find(a);
  int rootB = find(b);
  int newSize = nodes[rootA] + nodes[rootB];

  if(size(a) >= size(b))
  {
    nodes[rootB] = a;
    nodes[rootA] = newSize;
  }
  else
  {
    nodes[rootA] = b;
    nodes[rootB] = newSize;
  }
}

/**
 * Returns:
 *  number of nodes in the up-tree containing the element
 */
int DisjointSets::size(int elem)
{
  if(elem >= (int)nodes.size())
    return 0;
//cout << "-- Size -- " << endl;
  int temp;
  int size;
  temp = find(elem);
  size = nodes[temp] * -1;
  return size;
}
