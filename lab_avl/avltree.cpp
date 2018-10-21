/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */


template <class K, class V>
int AVLTree<K,V>::Balance(Node* subtree)
{
  return heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
}

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    // std::cout<<"rotateLeft1"<<std::endl;

    Node* y = t->right;
    t->right = y->left;
    y->left = t;
    t =y;
    t->left->height = std::max(heightOrNeg1(t->left->right), heightOrNeg1(t->left->left))+1;
    t->height = std::max(heightOrNeg1(t->right), heightOrNeg1(t->left))+1;


}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    // std::cout<<"rotateLeftRight"<<std::endl;
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    // std::cout<<"rotateRight1"<<std::endl;
    Node* y = t->left;
    t->left = y->right;
    y->right = t;
    t = y;
    t->right->height = std::max(heightOrNeg1(t->right->right), heightOrNeg1(t->right->left))+1;
    t->height = std::max(heightOrNeg1(t->right), heightOrNeg1(t->left))+1;

}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    // std::cout<<"rotateRightLeft1"<<std::endl;

    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if(subtree == nullptr)
      return;

    if(Balance(subtree) == -2)
    {
      if(Balance(subtree->left) == -1)
      {
        rotateRight(subtree);
      }
      else
      {
        rotateLeftRight(subtree);
      }
    }
    else if (Balance(subtree)==2)
    {

      if(Balance(subtree->right) == 1)
      {
        rotateLeft(subtree);
      }
      else
      {
        rotateRightLeft(subtree);
      }
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here

    if(subtree == nullptr)
    {
      Node *& curr = subtree;
      curr = new Node(key,value);
      curr->left = nullptr;
      curr->right = nullptr;
      curr->height = 0;
    }
    else if (key < subtree->key)
    {
      int sub_left = heightOrNeg1(subtree->left);
      int sub_right = heightOrNeg1(subtree->right);
      insert(subtree->left,key,value);
      if(sub_left == heightOrNeg1(subtree->left) && sub_right == heightOrNeg1(subtree->right))
      {
        subtree -> height = subtree->height;
      }
      else if(heightOrNeg1(subtree->right) < heightOrNeg1(subtree->left))
      {
      subtree->height = subtree->height +1;
      }

      rebalance(subtree);
    }
    else if (key > subtree->key)
    {
      int sub_left = heightOrNeg1(subtree->left);
      int sub_right = heightOrNeg1(subtree->right);
      insert(subtree->right,key,value);
      if(sub_left == heightOrNeg1(subtree->left) && sub_right == heightOrNeg1(subtree->right))
      {
        subtree ->height = subtree ->height;
      }
      else if(heightOrNeg1(subtree->left) < heightOrNeg1(subtree->right))
      {
      subtree->height = subtree->height +1;
      }

      rebalance(subtree);
    }
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left,key);
        subtree->height = std::max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right))+1;
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right,key);
        subtree->height = std::max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right))+1;
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // std::cout<<"Before remove "<<subtree->key<<" part1"<<std::endl;
            delete subtree;
            subtree = nullptr;
            // std::cout<<" height is "<<heightOrNeg1(subtree)<<"part1"<<std::endl;
            // your code here
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            // std::cout<<"Before remove "<<subtree->key<<" part2"<<" height is "<<subtree->height<<std::endl;
            Node* iop = subtree;
            Node* parent = subtree;
            iop = iop->left;
            while(iop ->right!= nullptr)
            {
              parent = iop;
              iop = iop->right;
            }
            // std::cout<<subtree->key<<" height is "<<heightOrNeg1(subtree)<<"part2"<<std::endl;
            swap(iop,subtree);
            // std::cout<<temp->key<<" This is the key"<<std::endl;
            // std::cout<<temp->value<<" This is the value"<<std::endl;
            if(iop == subtree->left)
            {
              subtree ->left = iop->left;
            }
            else
            {
              parent->right = iop->left;
            }
            delete iop;
            iop = nullptr;
        } else {
            /* one-child remove */
            if(subtree->left == NULL)
            {
              // std::cout<<"Before remove "<<"part3"<<std::endl;
              Node * temp = subtree;
              subtree = subtree->right;
              // std::cout<<subtree->key<<" height is "<<heightOrNeg1(subtree)<<"part3"<<" height is "<<subtree->height<<std::endl;
              delete temp;
              temp = nullptr;
            }
            else if (subtree ->right == NULL)
            {
              // std::cout<<"Before remove "<<"part4"<<std::endl;
              Node * temp = subtree;
              subtree = subtree->left;
              // std::cout<<subtree->key<<" height is "<<heightOrNeg1(subtree)<<"part4"<<std::endl;
              delete temp;
              temp = nullptr;
            }
            // your code here
        }
        // your code here

    }
    rebalance(subtree);


}
