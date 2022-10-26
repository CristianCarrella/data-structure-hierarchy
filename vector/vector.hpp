
#ifndef VECTOR_HPP
#define VECTOR_HPP
#include "../container/container.hpp"

namespace lasd {

template <typename Data>
class Vector : 
              virtual public LinearContainer<Data>, 
              virtual public PreOrderMappableContainer<Data>, 
              virtual public PostOrderMappableContainer<Data>, 
              virtual public PreOrderFoldableContainer<Data>, 
              virtual public PostOrderFoldableContainer<Data>
{
protected:
  using LinearContainer<Data>::size;
  Data * Elements = nullptr;
  
public:

  Vector() = default;
  Vector(ulong);
  Vector(const LinearContainer<Data>&); 
  Vector(const Vector<Data>&);
  Vector(Vector<Data>&&);
  virtual ~Vector();

  Vector & operator=(const Vector&);
  Vector & operator=(Vector&&);

  bool operator==(const Vector&) const noexcept;
  bool operator!=(const Vector&) const noexcept;
  Data& operator[](const ulong) const override;

  void Resize(ulong); 
  void Clear() noexcept override; 
  Data& Front() const override;
  Data& Back() const override;
  
  using typename MappableContainer<Data>::MapFunctor;
  void Map(MapFunctor, void*) override;
  void MapPreOrder(MapFunctor, void*) override;
  void MapPostOrder(MapFunctor, void*) override;

  using typename FoldableContainer<Data>::FoldFunctor;
  void Fold(FoldFunctor, const void*, void*) const override;
  void FoldPreOrder(FoldFunctor, const void*, void*) const override;
  void FoldPostOrder(FoldFunctor, const void*, void*) const override;

};

}

#include "vector.cpp"

#endif
