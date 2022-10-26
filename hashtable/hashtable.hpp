
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP
#include <random>

#include "../container/container.hpp"
#include "../vector/vector.hpp"


namespace lasd {
  
template <typename Data>
class Hash { 
public:

  ulong operator()(const Data&) const noexcept;

};

template <typename Data>
class HashTable : virtual public DictionaryContainer<Data>, 
                  virtual public MappableContainer<Data>, 
                  virtual public FoldableContainer<Data> {

private:


protected:
  const ulong p = 4294968949; //prime number > 2^32
  ulong a, b;
  using DictionaryContainer<Data>::size; 
  ulong tableSize = 1024; //2^10
  const ulong mytableSize = 128;
  Hash<Data> hash; 


public:
  HashTable();
  ~HashTable() = default;

  HashTable& operator=(const HashTable&) = delete; 
  HashTable& operator=(HashTable&&) = delete; 

  bool operator==(const HashTable&) const noexcept = delete;
  bool operator!=(const HashTable&) const noexcept = delete;

  virtual void Resize(const ulong&) noexcept = 0; 
protected:
  int generateRandom(int, int);
  ulong HashKey(const Data&) const; 
  ulong HashKey(const ulong&) const;
};

}

#include "hashtable.cpp"

#endif
