
#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <stdexcept>
#include <functional>

namespace lasd {

class Container {
  
protected:
  ulong size = 0;

public:
  virtual ~Container() = default;
  Container & operator=(const Container&) = delete;
  Container & operator=(Container&&) = delete;
  bool operator==(const Container&) const noexcept = delete;
  bool operator!=(const Container&) const noexcept = delete;


  virtual bool Empty() const noexcept;
  virtual ulong Size() const noexcept;
  virtual void Clear() = 0;

};

template <typename Data>
class LinearContainer : virtual public Container{ 
public:

  virtual ~LinearContainer() = default;

  LinearContainer & operator=(const LinearContainer&) = delete;
  LinearContainer & operator=(LinearContainer&&) = delete;

  bool operator==(const LinearContainer&) const noexcept;
  bool operator!=(const LinearContainer&) const noexcept;


  virtual Data& Front() const; 
  virtual Data& Back() const; 
  virtual Data& operator[](const ulong) const = 0; 

};


template <typename Data>
class TestableContainer : virtual public Container{ 

public:
  virtual ~TestableContainer() = default;

  TestableContainer & operator=(const TestableContainer&) = delete;
  TestableContainer & operator=(TestableContainer&&) = delete;

  bool operator==(const TestableContainer&) const noexcept = delete;
  bool operator!=(const TestableContainer&) const noexcept = delete;


  virtual bool Exists(const Data&) const noexcept = 0;

};


template <typename Data>
class DictionaryContainer : virtual public TestableContainer<Data> { 

public:
  virtual ~DictionaryContainer() = default;

  DictionaryContainer& operator=(const DictionaryContainer&) = delete; 
  DictionaryContainer& operator=(DictionaryContainer&&) = delete; 


  bool operator==(const DictionaryContainer&) const noexcept = delete;
  bool operator!=(const DictionaryContainer&) const noexcept = delete;

  virtual bool Insert(const Data&) noexcept = 0; 
  virtual bool Insert(Data&&) noexcept = 0; 
  virtual bool Remove(const Data&) noexcept = 0;

  virtual bool Insert(const LinearContainer<Data>&) noexcept;
  virtual bool Insert(LinearContainer<Data>&&) noexcept; 
  virtual bool Remove(const LinearContainer<Data>&) noexcept;

};


template <typename Data>
class MappableContainer : virtual public Container{ 
public:
  ~MappableContainer() = default;

  MappableContainer & operator=(const MappableContainer&) = delete;
  MappableContainer & operator=(MappableContainer&&) = delete;

  bool operator==(const MappableContainer&) const noexcept = delete;
  bool operator!=(const MappableContainer&) const noexcept = delete;

  typedef std::function<void(Data&, void*)> MapFunctor;
  virtual void Map(MapFunctor, void*) = 0;

};

template <typename Data>
class FoldableContainer : virtual public TestableContainer<Data>{ 
public:

  virtual ~FoldableContainer() = default;

  FoldableContainer & operator=(const FoldableContainer&) = delete;
  FoldableContainer & operator=(FoldableContainer&&) = delete;

  bool operator==(const FoldableContainer&) const noexcept = delete;
  bool operator!=(const FoldableContainer&) const noexcept = delete;

  typedef std::function<void(const Data&, const void*, void*)> FoldFunctor;
  virtual void Fold(FoldFunctor, const void*, void*) const = 0;

  bool Exists(const Data&) const noexcept override; 

};

template <typename Data>
class PreOrderMappableContainer : virtual public MappableContainer<Data>{
public:
  virtual ~PreOrderMappableContainer() = default;

  PreOrderMappableContainer & operator=(const PreOrderMappableContainer&) = delete;
  PreOrderMappableContainer & operator=(PreOrderMappableContainer&&) = delete;

  bool operator==(const PreOrderMappableContainer&) const noexcept = delete;
  bool operator!=(const PreOrderMappableContainer&) const noexcept = delete;

  using typename MappableContainer<Data>::MapFunctor;
  virtual void MapPreOrder(MapFunctor, void*) = 0;

  virtual void Map(MapFunctor, void*) override; 

};

template <typename Data>
class PreOrderFoldableContainer : virtual public FoldableContainer<Data>{

public:
  virtual ~PreOrderFoldableContainer() = default;

  PreOrderFoldableContainer & operator=(const PreOrderFoldableContainer&) = delete;
  PreOrderFoldableContainer & operator=(PreOrderFoldableContainer&&) = delete;

  bool operator==(const PreOrderFoldableContainer&) const noexcept = delete;
  bool operator!=(const PreOrderFoldableContainer&) const noexcept = delete;

  using typename FoldableContainer<Data>::FoldFunctor;
  virtual void FoldPreOrder(FoldFunctor, const void*, void*) const = 0;

  virtual void Fold(FoldFunctor, const void*, void*) const override; 

};


template <typename Data>
class PostOrderMappableContainer : virtual public MappableContainer<Data> {  

public:
  virtual ~PostOrderMappableContainer() = default;

  PostOrderMappableContainer & operator=(const PostOrderMappableContainer&) = delete;
  PostOrderMappableContainer & operator=(PostOrderMappableContainer&&) = delete;

  bool operator==(const PostOrderMappableContainer&) const noexcept = delete;
  bool operator!=(const PostOrderMappableContainer&) const noexcept = delete;

  using typename MappableContainer<Data>::MapFunctor;
  virtual void MapPostOrder(MapFunctor, void*) = 0;
  virtual void Map(MapFunctor, void*) override;

};

template <typename Data>
class PostOrderFoldableContainer : virtual public FoldableContainer<Data>{ 
public:
  virtual ~PostOrderFoldableContainer() = default;

  PostOrderFoldableContainer & operator=(const PostOrderFoldableContainer&) = delete;
  PostOrderFoldableContainer & operator=(PostOrderFoldableContainer&&) = delete;

  bool operator==(const PostOrderFoldableContainer&) const noexcept = delete;
  bool operator!=(const PostOrderFoldableContainer&) const noexcept = delete;

  using typename FoldableContainer<Data>::FoldFunctor;

  virtual void FoldPostOrder(FoldFunctor, const void*, void*) const = 0;
  virtual void Fold(FoldFunctor, const void*, void*) const override;

};

template <typename Data>
class InOrderMappableContainer : virtual public MappableContainer<Data>{
public:
  virtual ~InOrderMappableContainer() = default;

  InOrderMappableContainer & operator=(const InOrderMappableContainer&) = delete;
  InOrderMappableContainer & operator=(InOrderMappableContainer&&) = delete;

  bool operator==(const InOrderMappableContainer&) const noexcept = delete;
  bool operator!=(const InOrderMappableContainer&) const noexcept = delete;

  using typename MappableContainer<Data>::MapFunctor;

  virtual void MapInOrder(MapFunctor, void*) = 0;
  virtual void Map(MapFunctor, void*) override;

};

template <typename Data>
class InOrderFoldableContainer : virtual public FoldableContainer<Data>{

public:
  virtual ~InOrderFoldableContainer() = default;

  InOrderFoldableContainer & operator=(const InOrderFoldableContainer&) = delete;
  InOrderFoldableContainer & operator=(InOrderFoldableContainer&&) = delete;

  bool operator==(const InOrderFoldableContainer&) const noexcept = delete;
  bool operator!=(const InOrderFoldableContainer&) const noexcept = delete;

  using typename FoldableContainer<Data>::FoldFunctor;

  virtual void FoldInOrder(FoldFunctor, const void*, void*) const = 0;
  virtual void Fold(FoldFunctor, const void*, void*) const override;

};

template <typename Data>
class BreadthMappableContainer : virtual public MappableContainer<Data> {
public:
  virtual ~BreadthMappableContainer() = default;

  BreadthMappableContainer & operator=(const BreadthMappableContainer&) = delete;
  BreadthMappableContainer & operator=(BreadthMappableContainer&&) = delete;

  bool operator==(const BreadthMappableContainer&) const noexcept = delete;
  bool operator!=(const BreadthMappableContainer&) const noexcept = delete;

  using typename MappableContainer<Data>::MapFunctor;
  virtual void MapBreadth(MapFunctor, void*) = 0;
  virtual void Map(MapFunctor, void*) override; 

};

template <typename Data>
class BreadthFoldableContainer : virtual public FoldableContainer<Data>{ 

public:
  virtual ~BreadthFoldableContainer() = default;

  BreadthFoldableContainer & operator=(const BreadthFoldableContainer&) = delete;
  BreadthFoldableContainer & operator=(BreadthFoldableContainer&&) = delete;

  bool operator==(const BreadthFoldableContainer&) const noexcept = delete;
  bool operator!=(const BreadthFoldableContainer&) const noexcept = delete;

  using typename FoldableContainer<Data>::FoldFunctor;

  virtual void FoldBreadth(FoldFunctor, const void*, void*) const = 0;
  virtual void Fold(FoldFunctor, const void*, void*) const override; 

};

}

#include "container.cpp"

#endif
