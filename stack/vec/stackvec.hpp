
#ifndef STACKVEC_HPP
#define STACKVEC_HPP

#include "../stack.hpp"
#include "../../vector/vector.hpp"

namespace lasd {

template <typename Data>
class StackVec : virtual public Stack<Data>, virtual protected Vector<Data>   {

protected:

  using Vector<Data>::Elements;
  using Vector<Data>::size;
  const float REDUCTION_CONSTANT = 0.25;
  const float EXPANSION_CONSTANT = 2;
  ulong head = 0;

public:
  ulong getRealSize(){
      return size;
  }
  StackVec(){ size = 0; };
  StackVec(const LinearContainer<Data>&); 
  StackVec(const StackVec&);
  StackVec(StackVec&&);
  ~StackVec();

  StackVec & operator=(const StackVec&);
  StackVec & operator=(StackVec&&);

  bool operator==(const StackVec&) const noexcept;
  bool operator!=(const StackVec&) const noexcept;

  Data Top() const override; 
  Data& Top() override; 
  void Pop() override; 
  Data TopNPop() override; 
  void Push(const Data&) noexcept override;
  void Push(Data&&) noexcept override; 

  bool Empty() const noexcept override;
  ulong Size() const noexcept override;
  void Clear() noexcept override; 

protected:
  void Expand();
  void Reduce();

};

}

#include "stackvec.cpp"

#endif
