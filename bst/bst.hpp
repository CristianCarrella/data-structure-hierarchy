
#ifndef BST_HPP
#define BST_HPP
#include "../binarytree/lnk/binarytreelnk.hpp"
#include "../container/container.hpp"

namespace lasd {

template <typename Data>
class BST : virtual public BinaryTreeLnk<Data>, virtual public DictionaryContainer<Data> {
protected:
  using typename BinaryTreeLnk<Data>::NodeLnk;
  using BinaryTreeLnk<Data>::size;
  using BinaryTreeLnk<Data>::root;

public:

  BST() = default;
  BST(const LinearContainer<Data>&);
  BST(const BST<Data>&);
  BST(BST<Data>&&);
  ~BST() = default;

  BST& operator=(const BST&);
  BST& operator=(BST&&);

  bool operator==(const BST<Data>&) const noexcept; 
  bool operator!=(const BST<Data>&) const noexcept;

  Data& Min() const; 
  Data MinNRemove(); 
  void RemoveMin(); 

  Data& Max() const;
  Data MaxNRemove();
  void RemoveMax(); 


  Data& Predecessor(const Data&) const;
  Data PredecessorNRemove(const Data&);
  void RemovePredecessor(const Data&); 
  
  Data& Successor(const Data&) const; 
  Data SuccessorNRemove(const Data&); 
  void RemoveSuccessor(const Data&); 

  bool Insert(const Data&) noexcept override; 
  bool Insert(Data&&) noexcept override; 
  bool Remove(const Data&) noexcept override; 

  bool Exists(const Data&) const noexcept override;

protected:
  NodeLnk* Insertion(NodeLnk*, NodeLnk *) noexcept;
  NodeLnk* createBST(Vector<Data>&, long, long); 
  Data DataNDelete(NodeLnk*&); 
  NodeLnk* Detach(NodeLnk*&) noexcept; 
  NodeLnk* DetachMin(NodeLnk*&) noexcept;
  NodeLnk* DetachMax(NodeLnk*&) noexcept;

  NodeLnk* Skip2Left(NodeLnk*&) noexcept;
  NodeLnk* Skip2Right(NodeLnk*&) noexcept;

  NodeLnk*& FindPointerToMin(NodeLnk*&) noexcept; 
  NodeLnk* const& FindPointerToMin(NodeLnk* const&) const noexcept;

  NodeLnk*& FindPointerToMax(NodeLnk*&) noexcept; 
  NodeLnk* const& FindPointerToMax(NodeLnk* const&) const noexcept;

  NodeLnk*& FindPointerTo(NodeLnk*&, const Data) noexcept; 
  NodeLnk* const& FindPointerTo(NodeLnk* const&, const Data) const noexcept;

  NodeLnk** FindPointerToPredecessor(NodeLnk*&, const Data) noexcept; 
  NodeLnk* const* FindPointerToPredecessor(NodeLnk* const&, const Data) const noexcept;
  NodeLnk** FindPointerToSuccessor(NodeLnk*&,const Data) noexcept; 
  NodeLnk* const* FindPointerToSuccessor(NodeLnk* const&, const Data) const noexcept; 

};

}

#include "bst.cpp"

#endif
