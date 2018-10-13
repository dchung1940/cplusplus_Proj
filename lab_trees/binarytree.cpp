/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>
#include <stack>
/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
    template <typename T>
void BinaryTree<T>::mirror()
{
  mirror(root);
  cout<<endl;
    //your code here
}

template <typename T>
void BinaryTree<T>::mirror( Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
    {
      return;
    }
    else if (subRoot->left != NULL && subRoot->right == NULL)
    {
      subRoot->right = subRoot->left;
      subRoot->left = NULL;
      return;
    }
    else if (subRoot->right != NULL && subRoot->left == NULL)
    {
      subRoot->left = subRoot->right;
      subRoot->right = NULL;
      return;
    }
      mirror(subRoot->left);
      mirror(subRoot->right);
      Node* temp = subRoot->left;
      subRoot->left = subRoot->right;
      subRoot->right = temp;
      // Recursive definition
}



/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    // return isOrderedIterative(root);
    // return Iterative(root);
    return false;
}


template <typename T>
bool BinaryTree<T>::Iterative(const Node *root) const
{
  // stack< Node *> S;
  // Node * curr = root;
  // int curr_elem;
  // int prev_elem = -1;
  // while(curr != NULL || !S.empty())
  // {
  //   if(curr != nullptr)
  //   {
  //     S.push(root);
  //     curr = curr->left;
  //   }
  //   else{
  //     curr = S.top();
  //     curr_elem = root->elem;
  //     if(curr_elem < prev_elem)
  //     {
  //       return false;
  //     }
  //     // curr_one = curr;
  //     prev_elem = curr_elem;
  //     S.pop();
  //     curr = curr->right;
  //   }
  //   }
  //   return true;
  }


/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    // your code here
    return isOrderedRecursive(root);
}


template <typename T>
bool BinaryTree<T>::isOrderedRecursive(const Node *root) const
{
    // your code here
    if(!root)
    {
      return true;
    }
    if(!root->left && !root->right)
    {
      return true;
    }
    bool valid = true;
    if(!root->right){
      valid = valid && (root->left->elem < root->elem) && (isOrderedRecursive(root->left));
      return valid;
    }
    if(!root->left){
      valid = valid && (root->elem < root->right->elem) && (isOrderedRecursive(root->right));
      return valid;
    }
    valid = valid && (root->left->elem < root->elem) && (root->elem < root->right->elem)&&isOrderedRecursive(root->left)&&isOrderedRecursive(root->right);
    return valid;
}

/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::getPaths(vector<vector<T> > &paths) const
{
    // your code here
}


/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    return -1;
}
