#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

/**
 * FUNCTION: smallerDimVal
 * Description:
 *     This function should take in two templatized Points and a dimension and
 *   return a boolean value representing whether or not the first Point has a
 *   smaller value than the second in the dimension specified. That is, if the
 *   dimension passed in is k, then this should be true if the coordinate of
 *   the first point at k is less than the coordinate of the second point at k.
 *   If there is a tie, break it using Point’s operator<.
 */
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(curDim < 0) // Check to see if in bounds
      return false;
    if(first[curDim] < second[curDim]) // true?
      return true;
    else
      if(first[curDim] > second[curDim]) // YO FALSE????
        return false;
//cout << endl;
//cout << first[curDim] << "smaller?? " << second[curDim] << " : "<< (first<second) << endl;
    return first < second; // if first[curDim] == second[curDim]
}

/**
 * Function: shouldReplace
 * Description:
 *    This function should take three templated Points: target, currentBest,
 * and potential. This should return true if potential is closer (i.e., has a
 * smaller distance) to target than currentBest (with a tie being broken by the
 * operator< in the Point class: potential < currentBest).
 */
template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     // Variables
     double distance1 = 0;
     double distance2 = 0;

     for(int i=0; i < Dim; i++) // Add up all the square values
     {
       distance1 += pow(currentBest[i]-target[i], 2);
       distance2 += pow(potential[i]-target[i], 2);
     }

     if(sqrt(distance1) < sqrt(distance2)) // Potential is bigger
        return false;
     else if(sqrt(distance1) > sqrt(distance2)) // Potential works
        return true;
     return potential < currentBest; // if they are equal
}

/**
 *  Constructor for KDTree
 *  Description:
 *    This takes a single parameter, a reference to a constant std::vector of
 *  Point<Dim>s. The constructor should build the tree using recursive helper function(s).
 */
template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    root = NULL;
    if(newPoints.empty()) // Check for empty vector
      return;

    // Variables
    int mid = (newPoints.size()-1) / 2;
    //tree_vec = newPoints;
    // Create tree
    //cout << "___INITIAL___" << endl;
    for(unsigned i=0; i<newPoints.size(); i++)
      tree_vec.push_back(newPoints[i]);
      // for(unsigned i=0; i<tree_vec.size(); i++)
      //   cout << " " << tree_vec[i][0];
//cout << "mid: " << mid << endl;
    root = new KDTreeNode(quickSelect(tree_vec, 0, 0, tree_vec.size()-1, mid));
// cout << "list:";
// for(unsigned i=0; i<tree_vec.size(); i++)
//   cout << " " << tree_vec[i][0];
// cout << "root: " << root->point[0] << endl;
    construct(tree_vec, root, 1, 0, tree_vec.size()-1);
}

/**
 * Method: Construct
 * Description:
 *  Recursive function that sorts the array on different dimensions
 */
template <int Dim>
void KDTree<Dim>::construct(vector<Point<Dim>> &tree_vec, KDTreeNode* node, int dim, int l, int r)
{
  if(l == r)
    return;
  if(dim >= Dim) // Lol just in case
    dim = dim % Dim;
//cout << "node: " << node->point[dim] << endl;
  int mid = (r-l) / 2;
  mid += l;
//cout << "MIDDLE: " << mid << endl;

//cout << "left " << endl;
  if(mid > l) // Check to see if it's leaf node
    node->left = new KDTreeNode(quickSelect(tree_vec, dim, l, mid-1, (l+mid-1)/2));
//cout << "right " << endl;
  if(mid < r)
    node->right = new KDTreeNode(quickSelect(tree_vec, dim, mid+1, r, (mid+1+r)/2));

  if(node->left != NULL) // Prevent going on to uncreated node
    construct(tree_vec, node->left, (dim+1)%Dim, l, mid-1);
  if(node->right != NULL)
    construct(tree_vec, node->right, (dim+1)%Dim, mid+1, r);
}

/**
 * Method: Quicksort
 * Description:
 *  Sorts the vector for the kd tree_equals_output
 */
template <int Dim>
Point<Dim> KDTree<Dim>::quickSelect(vector<Point<Dim>> &newPoints, int dim, int l, int r, int m)
{
    /**
     * @todo Implement this function!
     */
//cout << "--We in bois--" << endl;
 // for(int i=l; i<=r; i++)
 //   cout << " " << newPoints[i][0];
 //  cout << endl;

    if(l == r) // check to see if the index is found
      return newPoints[l];

    if(dim >= Dim) // Lol just in case
      dim = dim % Dim;

    int j = partition(newPoints, dim, l, r); // find rotating point
//cout << "m: " << m << " | rotating: " << j << endl;
    if(j == m)
      return newPoints[j];
    else if(m < j)
      return quickSelect(newPoints, dim, l, j-1, m);
    else
      return quickSelect(newPoints, dim, j+1, r, m);
}

/**
 * Method: partition
 * Description:
 *  Rearranges the elements from the range [first,last), in such a way that all
 * the elements for which pred returns true precede all those for which it returns
 * false. The iterator returned points to the first element of the second group.
 */
 template <int Dim>
 int KDTree<Dim>::partition(vector<Point<Dim>> &newPoints, int dim, int l, int r)
 {
    //Point<Dim> pivot = newPoints[r];
    if(dim >= Dim) // Lol just in case
      dim = dim % Dim;

    int i = l-1;

    for (int j = l; j <= r-1; j++) {
        if (smallerDimVal(newPoints[j], newPoints[r], dim))
        {
          i++;
            //cout << "swapping: " << newPoints[i][dim] << " and " << newPoints[j][dim] << endl;
            swap(newPoints[i], newPoints[j]);
            //cout << "Swapped: " << newPoints[i][dim] << " and " << newPoints[j][dim] << endl;
        }
    }
    swap(newPoints[i+1], newPoints[r]);
    return i+1;
 }


template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
   this = other;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  root = rhs.root;
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  if(root != NULL)
    Destroy(root);
}

/**
 * Recursive algorithm for the tree desutrctor
 *
 */
template <int Dim>
void KDTree<Dim>::Destroy(KDTreeNode* node)
{
    if(node != NULL)
    {
      if(node->left != NULL)
        Destroy(node->left);
      if(node->right != NULL)
        Destroy(node->right);
      delete node;
      node = NULL;
    }
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    Point<Dim> here = query;
    if(root != NULL)
    {
      return nearest(here, root, 0);
    }
    return Point<Dim>();
}

/**
 * Method: nearest
 * Description:
 * Returns the nearest point to the target point.
 */
template <int Dim>
Point<Dim> KDTree<Dim>::nearest(Point<Dim>& target, KDTreeNode* node, int dim) const
{
  // Variables
  int within = 0;
  bool left = false;
  bool right = false;
  double rad = 0;
  Point<Dim> closest = node->point;
  Point<Dim> maybe = node->point;


  if(node->left != NULL && (smallerDimVal(target, node->point, dim)))
  {
    closest = nearest(target, node->left, (dim+1)%Dim);
    left = true;
  }
  else if(node->right != NULL)
  {
    closest = nearest(target, node->right, (dim+1)%Dim);
    right = true;
  }

  rad = calcRad(closest, target);
  if((double)node->point[dim] <= (double)target[dim]+rad && (double)node->point[dim] >= (double)target[dim]-rad)
  {
    within++;
  }

  if(within>0 && node->left != NULL && !left)
    maybe = nearest(target, node->left, (dim+1)%Dim);
  if(within>0 && node->right != NULL && !right)
    maybe = nearest(target, node->right, (dim+1)%Dim);

  if(shouldReplace(target, closest, maybe))
    closest = maybe;
  if(shouldReplace(target, closest, node->point))
    closest = node->point;

  return closest;
}

/**
 * Method: calcRad
 * Description:
 * Calculates radius between two points.
 */
template <int Dim>
double KDTree<Dim>::calcRad(Point<Dim> point1, Point<Dim>point2) const
{
  double distance = 0.0;
  for(int i=0; i < Dim; i++) // Add up all the square values
  {
    distance += pow(point1[i]-point2[i], 2);
  }

  return(sqrt(distance));
}

/**
 * Method: within
 * Description:
 * Checks if a point is within the radius;
 */
// template <int Dim>
// bool KDTree<Dim>::within(Point<Dim> point1, Point<Dim>point2) const
// {
//   if(calcRad(point1, point2) <= radius || radius < 0)
//     return true;
//   return false;
// }
