/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
#include <iostream>

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // : graded in MP3.1

  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  return List<T>::ListIterator(tail_->next);
}

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <typename T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  _destroy();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode* node = head_;
  while(node != nullptr)
  {
    ListNode* temp = node;
    node = node->next;
    delete (temp);
    temp = nullptr;
  }
  tail_ = nullptr;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  if(!head_){
  ListNode* node = new ListNode(ndata);
  node ->next = nullptr;
  node ->prev = nullptr;
  tail_ = node;
  head_ = node;
  length_+=1;
}
else{
  ListNode * node = new ListNode(ndata);
  node->next = head_;
  node ->prev = nullptr;
  head_ ->prev = node;
  head_ = node;
  length_+=1;
}
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  if(!tail_){
  ListNode* node = new ListNode(ndata);
  node ->next = nullptr;
  node ->prev = nullptr;
  tail_ = node;
  head_ = node;
  length_+=1;
}
else{
  ListNode * node = new ListNode(ndata);
  node->next = nullptr;
  node ->prev = tail_;
  tail_->next = node;
  tail_ = node;
  length_+=1;
}

}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_ );
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
 //Referenced from GeeksforGeek for reversing
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {

ListNode * node = startPoint;
ListNode * next = nullptr;
ListNode * previous = startPoint->prev;
ListNode * first_num = startPoint->prev;
ListNode * edge = endPoint -> next;
if(startPoint == head_ && endPoint == tail_)
{
  while(node != edge)
  {
    next = node ->next;
    node->next = previous;
    previous = node;
    node = next;
  }
  endPoint = startPoint;
  startPoint = previous;
  // std::cout << "1"<<std::endl;
  endPoint -> next = edge;
  if(edge!= nullptr)
  {edge->prev = endPoint;}
  // std::cout << "2"<<std::endl;
  if(first_num != nullptr)
  {first_num ->next= startPoint;}
  // std::cout << "3"<<std::endl;
  startPoint->prev= first_num;
  // std::cout << "4"<<std::endl;
  head_ = startPoint;
  tail_ = endPoint;
}
else if (startPoint == head_)
{
  while(node != edge)
  {
    next = node ->next;
    node->next = previous;
    previous = node;
    node = next;
  }
  endPoint = startPoint;
  startPoint = previous;
  endPoint -> next = edge;
  // std::cout << "1"<<std::endl;
  if(edge!= nullptr)
  {edge->prev = endPoint;}
  // std::cout << "2"<<std::endl;
  if(first_num != nullptr)
  {first_num ->next= startPoint;}
  // std::cout << "3"<<std::endl;
  startPoint->prev= first_num;
  // std::cout << "4"<<std::endl;

  head_ = startPoint;
}
else if (endPoint == tail_)
{
  while(node != edge)
  {
    next = node ->next;
    node->next = previous;
    previous = node;
    node = next;
  }
  endPoint = startPoint;
  startPoint = previous;
  // std::cout << "1"<<std::endl;
  endPoint -> next = edge;
  // std::cout << "2"<<std::endl;
  if(edge!= nullptr)
  {edge->prev = endPoint;}
  // std::cout << "3"<<std::endl;
  if(first_num != nullptr)
  {first_num ->next= startPoint;}
  // std::cout << "4"<<std::endl;

  startPoint->prev= first_num;

  tail_ = endPoint;
}
else{
while(node != edge)
{
  next = node ->next;
  node->next = previous;
  previous = node;
  node = next;
}
endPoint = startPoint;
startPoint = previous;
// std::cout << "0"<<std::endl;
endPoint -> next = edge;
// std::cout << "1"<<std::endl;
{edge->prev = endPoint;}
if(first_num != nullptr)
{first_num ->next= startPoint;}
startPoint->prev= first_num;

}

}


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  ListNode * startPoint = head_;
  ListNode * node = startPoint;
  while(startPoint != nullptr)
  {
    node = startPoint;
  for (int i=1; i<n; i++)
  {
    if (node->next != nullptr) {
      node = node->next;
    }
  }
  ListNode *endPoint = node;
  //ListNode *nextIteration = endPoint->next;
  // std::cout << "ok" << std::endl;
  reverse(startPoint,endPoint);
  // std::cout << "1" << std::endl;
  startPoint = endPoint->next;
  }
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  if(!head_)
  {
    return;
  }
  else{
  ListNode *curr = head_;
  while (curr ->next != NULL)
  {
    ListNode *temp = curr->next;
    ListNode *temp_one = temp ->next;

    curr ->next = temp_one;

    if (temp_one != nullptr) {
      temp_one ->prev = curr;
    }
    else{
      return;
    }
    tail_ ->next = temp;

    temp ->prev = tail_;

    temp ->next = nullptr;

    tail_ = temp;
    curr = curr->next;
    if(curr ->next == tail_)
    {
      return;
    }
  }
}
  /// @todo Graded in MP3.1
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <typename T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
  ListNode* head_ptr = start;
  ListNode* new_head = nullptr;
  if(!start)
  {
    return nullptr;
  }
  if(splitPoint <1)
  {
    return nullptr;
  }
  for(int i=0; i<splitPoint-1; i++)
  {
    if(start != nullptr)
    start = start->next;
  }
  new_head = start->next;
  start->next = nullptr;
  new_head -> prev = nullptr;
  return new_head;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if(first == nullptr && second == nullptr)
  {
    return nullptr;
  }
  else if (first == nullptr)
  {
    return second;
  }
  else if (second == nullptr)
  {
    return first;
  }
  else
  {
    ListNode *greater = second;
    ListNode *prev_one = nullptr;
    ListNode *node = first;
    if(second->data < first->data)
    {
      node = second;
      greater = first;
    }
    ListNode* head_ptr = node;
    while(node != nullptr)
    {
      if(node->data < greater->data)
      {
        prev_one = node;
        node = node->next;
      }
      else if (node ->data == greater ->data)
      {
        prev_one = node;
        node = node->next;
      }
      else
      {
        ListNode* temp = nullptr;
        prev_one ->next = greater;
        greater->prev = prev_one;
        temp = node;
        node = greater;
        greater = temp;
        prev_one = node;
        node = node->next;
      }
    }
    if(greater!=nullptr && node == nullptr)
    {
      prev_one ->next = greater;
      greater->prev = prev_one;
      }
    return head_ptr;
  }
}


/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <typename T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  // @todo Graded in MP3.2
  ListNode* new_head;

  ListNode* temp;
  if(chainLength == 1)
    return start;
  else{
    new_head = split(start,chainLength/2);
    // std::cout<<new_head ->data<<std::endl;
    // std::cout<<"new_head!"<<std::endl;
    ListNode*& first =mergesort(start, chainLength/2);
    ListNode*& second =mergesort(new_head, chainLength-chainLength/2);
    
    // std::cout<<first ->data<<std::endl;
    // std::cout<<"first"<<std::endl;
    // std::cout<<second ->data<<std::endl;
    // std::cout<<"second"<<std::endl;
    temp =merge(first,second);
    while(temp != NULL){
      std::cout<<temp->data<<std::endl;
      temp = temp->next;
      }
    std::cout<<"break"<<std::endl;

  }

  return start;
}
