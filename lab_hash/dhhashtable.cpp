/**
 * @file dhhashtable.cpp
 * Implementation of the DHHashTable class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */
#include "dhhashtable.h"

using hashes::hash;
using hashes::secondary_hash;
using std::pair;


template <class K, class V>
DHHashTable<K, V>::DHHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new pair<K, V>*[size];
    should_probe = new bool[size];
    for (size_t i = 0; i < size; i++) {
        table[i] = NULL;
        should_probe[i] = false;
    }
    elems = 0;
}

template <class K, class V>
DHHashTable<K, V>::~DHHashTable()
{
    destroy();
}

template <class K, class V>
DHHashTable<K, V> const& DHHashTable<K, V>::operator=(DHHashTable const& rhs)
{
    if (this != &rhs) {
        destroy();

        copy(rhs);
    }
    return *this;
}

template <class K, class V>
DHHashTable<K, V>::DHHashTable(DHHashTable<K, V> const& other)
{
    copy(other);
}


template <class K, class V>
void DHHashTable<K, V>::destroy()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table; table = nullptr;
    delete[] should_probe; should_probe = nullptr;
}

template <class K, class V>
void DHHashTable<K, V>::copy(const DHHashTable<K, V>& other)
{
    table = new pair<K, V>*[other.size];
    should_probe = new bool[other.size];
    for (size_t i = 0; i < other.size; i++) {
        should_probe[i] = other.should_probe[i];
        if (other.table[i] == NULL)
            table[i] = NULL;
        else
            table[i] = new pair<K, V>(*(other.table[i]));
    }
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void DHHashTable<K, V>::insert(K const& key, V const& value)
{

    /**
     * @todo Implement this function.
     *
     * @note Remember to resize the table when necessary (load factor >=
     *  0.7). **Do this check *after* increasing elems!!** Also, don't
     *  forget to mark the cell for probing with should_probe!
     */

//     (void) key;   // prevent warnings... When you implement this function, remove this line.
//     (void) value; // prevent warnings... When you implement this function, remove this line.
//
    elems ++;
    if(shouldResize())
    {
      resizeTable();
    }
    pair<K,V> *temp = new pair<K,V>(key,value);
    size_t val_= hash(key,size);
    int i = 0;
    while(table[val_]!=nullptr)
    {
      i++;
      val_ = (hash(key,size)+i*secondary_hash(key,size))%size;
    }
    should_probe[val_] = true;
    table[val_] = temp;

}

template <class K, class V>
void DHHashTable<K, V>::remove(K const& key)
{
    /**
     * @todo Implement this function
     */
     if(findIndex(key) == -1)
      return;
    int temp = findIndex(key);
    delete table[temp];
    table[temp] = nullptr;
    elems --;

}

template <class K, class V>
int DHHashTable<K, V>::findIndex(const K& key) const
{
    /**
     * @todo Implement this function
     */
     for(unsigned i = 0; i < this->size; i++){
   if(table[i] != nullptr){
     if(table[i]->first == key)
       return i;
   }
 }
 return -1;
}

template <class K, class V>
V DHHashTable<K, V>::find(K const& key) const
{
    int idx = findIndex(key);
    if (idx != -1)
        return table[idx]->second;
    return V();
}

template <class K, class V>
V& DHHashTable<K, V>::operator[](K const& key)
{
    // First, attempt to find the key and return its value by reference
    int idx = findIndex(key);
    if (idx == -1) {
        // otherwise, insert the default value and return it
        insert(key, V());
        idx = findIndex(key);
    }
    return table[idx]->second;
}

template <class K, class V>
bool DHHashTable<K, V>::keyExists(K const& key) const
{
    return findIndex(key) != -1;
}

template <class K, class V>
void DHHashTable<K, V>::clear()
{
    destroy();

    table = new pair<K, V>*[17];
    should_probe = new bool[17];
    for (size_t i = 0; i < 17; i++)
        should_probe[i] = false;
    size = 17;
    elems = 0;
}

template <class K, class V>
void DHHashTable<K, V>::resizeTable()
{
  size_t new_size = findPrime(size*2);
  pair<K,V>** temp_1 = new pair<K,V>*[new_size];
  delete [] should_probe;
  should_probe = new bool[new_size];
  for(unsigned i=0; i<new_size; i++)
  {
    should_probe[i] = false;
    temp_1[i] = nullptr;
  }

  for(unsigned i = 0; i<size; i++)
  {
    if(table[i] != nullptr)
    {
    size_t new_hash = hash(table[i]->first,new_size);
    size_t new_hash_two = secondary_hash(table[i]->first,new_size);
    size_t a = 0;
    size_t idx = new_hash;
    while(temp_1[idx] != nullptr)
    {
      a += 1;
      idx = (new_hash + new_hash_two*a)%new_size;
    }
    temp_1[idx] = table[i];
    should_probe[idx] = true;
  }
  }
  delete [] table;

  table = temp_1;
  size = new_size;


}
