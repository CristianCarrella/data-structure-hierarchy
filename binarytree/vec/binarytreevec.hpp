
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP
#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

namespace lasd {

template <typename Data>
class BinaryTreeVec : virtual public BinaryTree<Data>{

  struct NodeVec : virtual public BinaryTree<Data>::Node {

  private:
    using BinaryTree<Data>::Node::info;
    ulong pos;
    Vector<NodeVec*> &vect; //riferimento al vettore della classe BinaryTreeVec

  public:

    NodeVec() = default;
    NodeVec(Vector<NodeVec*>&, ulong, const Data&);
    NodeVec(Vector<NodeVec*>&, ulong, Data&&);
    NodeVec(const NodeVec&);
    NodeVec(NodeVec&&);
    ~NodeVec() = default;

    void printVect();

    Data& Element() noexcept; 
    const Data& Element() const noexcept; 

    bool IsLeaf() const noexcept; 
    bool HasLeftChild() const noexcept; 
    bool HasRightChild() const noexcept; 

    NodeVec& LeftChild(); 
    NodeVec& RightChild(); 

  };
protected:
  Vector<NodeVec*> Elements;
  using BinaryTree<Data>::size;
public:
  BinaryTreeVec() = default;
  BinaryTreeVec(const LinearContainer<Data>&);
  BinaryTreeVec(const BinaryTreeVec<Data>&);
  BinaryTreeVec(BinaryTreeVec<Data>&&);
  ~BinaryTreeVec();

  BinaryTreeVec & operator=(const BinaryTreeVec&);
  BinaryTreeVec & operator=(BinaryTreeVec&&);

  bool operator==(const BinaryTreeVec&) const noexcept; 
  bool operator!=(const BinaryTreeVec&) const noexcept;

  NodeVec& Root() const override; 

  void Clear() noexcept override; 
  using typename MappableContainer<Data>::MapFunctor;
  using typename FoldableContainer<Data>::FoldFunctor;
  void MapBreadth(MapFunctor, void*) override; 
  void FoldBreadth(FoldFunctor, const void*, void*) const override;
};

}

#include "binarytreevec.cpp"

#endif
