
#ifndef STACKLST_HPP
#define STACKLST_HPP

#include "../stack.hpp"
#include "../../list/list.hpp"

namespace lasd {

template <typename Data>
class StackLst : virtual public Stack<Data>, virtual protected List<Data> {

protected:

  using List<Data>::size;
  using List<Data>::head;
  using List<Data>::tail;

public:
  void print(){};
  StackLst() = default;
  StackLst(const LinearContainer<Data>&);
  StackLst(const StackLst&);
  StackLst(StackLst&&);
  ~StackLst();

  StackLst & operator=(const StackLst&);
  StackLst & operator=(StackLst&&);

  bool operator==(const StackLst&) const noexcept;
  bool operator!=(const StackLst&) const noexcept;


  Data Top() const override; 
  Data& Top() override; 
  void Pop() override; 
  Data TopNPop() override; 
  void Push(const Data&) noexcept override; 
  void Push(Data&&) noexcept override; 
  void Clear() noexcept override; 

};

}

#include "stacklst.cpp"

#endif
