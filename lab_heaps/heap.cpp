
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

 // template<class T>
 // void swap(std::vector<T> &elem_,size_t currentIdx, size_t minChildIndex);

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return currentIdx*2;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return 2*currentIdx+1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return currentIdx/2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    if(_elems.size()-1 < currentIdx*2)
      return false;
    else
      return true;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
// if(leftChild(currentIdx) == _elems.size()-1)
// {
//   return leftChild(currentIdx);
// }
if(rightChild(currentIdx) >= _elems.size())
{
  return leftChild(currentIdx);
}
else
{
    T T_left = _elems[leftChild(currentIdx)];
    T T_right = _elems[rightChild(currentIdx)];
    if(T_left <= T_right)
      return leftChild(currentIdx);
    else
      return rightChild(currentIdx);
}
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    if(hasAChild(currentIdx))
    {
      size_t temp = maxPriorityChild(currentIdx);
      if(_elems[temp]<_elems[currentIdx])
      {
        std::swap(_elems[temp],_elems[currentIdx]);
        heapifyDown(temp);
      }
    }
}

// template<class T>
// void swap(std::vector<T> &elem_,size_t currentIdx, size_t minChildIndex)
// {
//   T temp = elem_[currentIdx];
//   elem_[currentIdx] = elem_[minChildIndex];
//   elem_[minChildIndex] = temp;
// }

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
  if(currentIdx != 1)
  {
    size_t parent_ = parent(currentIdx);
    if(_elems[parent_] > _elems[currentIdx])
    {
      std::swap(_elems[parent_],_elems[currentIdx]);
      heapifyUp(parent_);
    }
  }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    _elems.push_back(T());

}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    // @TODO Construct a heap using the buildHeap algorithm
    _elems.push_back(T());
    for(auto i = elems.begin(); i<elems.end(); ++i)
    {
      _elems.push_back(*i);
    }
    unsigned half = _elems.size()/2;
    for (unsigned i = half; i>0; i--)
    {
       heapifyDown(i);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    T temp = _elems[root()];
    std::swap(_elems[root()], _elems[_elems.size()-1]);
    _elems.pop_back();
    heapifyDown(root());
    return temp;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    return _elems[root()];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size()-1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    T current_elem = _elems[idx+1];
    // std::cout<<_elems[idx]<<"huh"<<idx<<std::endl;
    _elems[idx+1] = elem;
    // std::cout<<_elems[idx]<<"LOL"<<idx<<std::endl;

    if(elem>current_elem)
    {
      heapifyDown(idx+1);
    }
    else
    {
      heapifyUp(idx+1);
    }

}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    if(_elems.size() == 1)
      return true;
    else
      return false;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
