
#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP
#include "../hashtable.hpp"
#include "../../vector/vector.hpp"

namespace lasd {

template <typename Data>
class HashTableOpnAdr : virtual public HashTable<Data> { 

protected:

  using HashTable<Data>::size;
  using HashTable<Data>::a;
  using HashTable<Data>::b;
  using HashTable<Data>::tableSize;
  Vector<Data> table;
  Vector<char> checkStatus;
public:
  HashTableOpnAdr(); 
  HashTableOpnAdr(ulong); 
  HashTableOpnAdr(const LinearContainer<Data>&); 
  HashTableOpnAdr(ulong, LinearContainer<Data>&); 
  HashTableOpnAdr(const HashTableOpnAdr<Data>&);
  HashTableOpnAdr(HashTableOpnAdr<Data>&&);
  ~HashTableOpnAdr() = default;

  HashTableOpnAdr& operator=(const HashTableOpnAdr&);
  HashTableOpnAdr& operator=(HashTableOpnAdr&&);

  bool operator==(const HashTableOpnAdr<Data>&) const noexcept;
  bool operator!=(const HashTableOpnAdr<Data>&) const noexcept;

  void Resize(const ulong&) noexcept override; 
  bool Insert(const Data&) noexcept override;
  bool Insert(Data&&) noexcept override; 
  bool Remove(const Data&) noexcept override; 

  bool Exists(const Data&) const noexcept override; 

  using typename MappableContainer<Data>::MapFunctor;
  using typename FoldableContainer<Data>::FoldFunctor;

  void Map(MapFunctor, void*) override; 
  void Fold(FoldFunctor, const void*, void*) const override; 
  void Clear() noexcept override; 

  void print() const noexcept;

public:

  // ulong Find(const Data&) const; //trova indice del dato
  // ulong FindEmpty() const; //prima locazione vuota
  bool RemoveFromIndex(const ulong&, const Data&); //rimuovi da un certo indice in poi
  ulong HashKey(const Data&, const ulong) const; //key - index  
  void ResetStatus();

};

}

#include "htopnadr.cpp"

#endif
