
#ifndef HTCLSADR_HPP
#define HTCLSADR_HPP

#include "../hashtable.hpp"
#include "../../vector/vector.hpp"
#include "../../bst/bst.hpp"

namespace lasd {

template <typename Data>
class HashTableClsAdr : public virtual HashTable<Data> {
protected:

  using HashTable<Data>::size;
  using HashTable<Data>::tableSize;
  Vector<BST<Data>> table;
public:
  HashTableClsAdr(); 
  HashTableClsAdr(ulong); 
  HashTableClsAdr(const LinearContainer<Data>&); 
  HashTableClsAdr(ulong, LinearContainer<Data>&); 
  HashTableClsAdr(const HashTableClsAdr<Data>&);
  HashTableClsAdr(HashTableClsAdr<Data>&&);
  ~HashTableClsAdr() = default;

  HashTableClsAdr& operator=(const HashTableClsAdr&);
  HashTableClsAdr& operator=(HashTableClsAdr&&);

  bool operator==(const HashTableClsAdr<Data>&) const noexcept; 
  bool operator!=(const HashTableClsAdr<Data>&) const noexcept;

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
};

}

#include "htclsadr.cpp"

#endif
