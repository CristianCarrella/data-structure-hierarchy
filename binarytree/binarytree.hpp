
#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include "../container/container.hpp"

#include "../iterator/iterator.hpp"

#include "../queue/lst/queuelst.hpp"
#include "../stack/lst/stacklst.hpp"


namespace lasd {
template <typename Data>
class BinaryTree : virtual public PreOrderMappableContainer<Data>,
                   virtual public PostOrderMappableContainer<Data>,
                   virtual public InOrderMappableContainer<Data>,
                   virtual public BreadthMappableContainer<Data>,
                   virtual public PreOrderFoldableContainer<Data>,
                   virtual public PostOrderFoldableContainer<Data>,
                   virtual public InOrderFoldableContainer<Data>,
                   virtual public BreadthFoldableContainer<Data>{
                                 

public:
  struct Node {
  protected:
    Data info;
    //Assumo che due nodi sono uguali se hanno lo stesso valore
    bool operator==(const Node&) const noexcept;// Comparison of abstract types is possible, but should not be visible.
    bool operator!=(const Node&) const noexcept;// Comparison of abstract types is possible, but should not be visible.

  public:

    friend class BinaryTree<Data>; //così ho accesso ai campi protetti del nodo da BinaryTree
    // Destructor
    virtual ~Node() = default;

    Node& operator=(const Node&) = delete;
    Node& operator=(Node&&) = delete;
    
    virtual Data& Element() noexcept = 0; // Mutable access to the element (concrete function should not throw exceptions)
    virtual const Data& Element() const noexcept = 0; // Immutable access to the element (concrete function should not throw exceptions)

    virtual bool IsLeaf() const noexcept = 0; // (concrete function should not throw exceptions)
    virtual bool HasLeftChild() const noexcept = 0; // (concrete function should not throw exceptions)
    virtual bool HasRightChild() const noexcept = 0; // (concrete function should not throw exceptions)

    virtual Node& LeftChild() = 0; // (concrete function must throw std::out_of_range when not existent)
    virtual Node& RightChild() = 0; // (concrete function must throw std::out_of_range when not existent)

  };
protected:
  using Container::size;

public:
  virtual ~BinaryTree() = default;


  BinaryTree & operator=(const BinaryTree&) = delete;
  BinaryTree & operator=(BinaryTree&&) = delete;

  bool operator==(const BinaryTree&) const noexcept;
  bool operator!=(const BinaryTree&) const noexcept;
  virtual Node& Root() const = 0; 

  using typename MappableContainer<Data>::MapFunctor;
  virtual void Map(MapFunctor, void*) override;

  using typename FoldableContainer<Data>::FoldFunctor;
  virtual void Fold(FoldFunctor, const void*, void*) const override; 

  virtual void MapPreOrder(MapFunctor, void*) override; 
  virtual void MapPostOrder(MapFunctor, void*) override;
  virtual void MapInOrder(MapFunctor, void*) override; 
  virtual void MapBreadth(MapFunctor, void*) override; 
  
  virtual void FoldPreOrder(FoldFunctor, const void*, void*) const override; 
  virtual void FoldPostOrder(FoldFunctor, const void*, void*) const override;
  virtual void FoldInOrder(FoldFunctor, const void*, void*) const override; 
  virtual void FoldBreadth(FoldFunctor, const void*, void*) const override; 
  

protected:
  bool Compare(Node&, Node&) const noexcept;
  void MapPreOrder(MapFunctor, void*, Node&); 
  void FoldPreOrder(FoldFunctor, const void*, void*, Node&) const; 
  void MapPostOrder(MapFunctor, void*, Node&); 
  void FoldPostOrder(FoldFunctor, const void*, void*, Node&) const; 
  void MapInOrder(MapFunctor, void*, Node&); 
  void FoldInOrder(FoldFunctor, const void*, void*, Node&) const; 

};


template <typename Data>
class BTPreOrderIterator : virtual public ForwardIterator<Data>,
                           virtual public ResettableIterator<Data>{
private: 
  StackLst<typename BinaryTree<Data>::Node*> stk;
  typename  BinaryTree<Data>::Node * current = nullptr;
  typename BinaryTree<Data>::Node * root;

public:

  BTPreOrderIterator(const BinaryTree<Data>&); 
  BTPreOrderIterator(const BTPreOrderIterator<Data>&);
  BTPreOrderIterator(BTPreOrderIterator<Data>&&);
  ~BTPreOrderIterator() = default;

  BTPreOrderIterator & operator=(const BTPreOrderIterator&);
  BTPreOrderIterator & operator=(BTPreOrderIterator&&);

  // Comparison operators
  bool operator==(const BTPreOrderIterator&) const noexcept;
  bool operator!=(const BTPreOrderIterator&) const noexcept;

  Data& operator*() const; 
  bool Terminated() const noexcept; 
  void operator++(); 
  void Reset() noexcept; 

};

template <typename Data>
class BTPostOrderIterator : public virtual ForwardIterator<Data>,
                            public virtual ResettableIterator<Data>{
private: 
  StackLst<typename BinaryTree<Data>::Node*> stk;
  typename BinaryTree<Data>::Node * current = nullptr;
  typename BinaryTree<Data>::Node * root;

public:
  
  BTPostOrderIterator(const BinaryTree<Data>&); 
  BTPostOrderIterator(const BTPostOrderIterator<Data>&);
  BTPostOrderIterator(BTPostOrderIterator<Data>&&);
  ~BTPostOrderIterator() = default;

  BTPostOrderIterator & operator=(const BTPostOrderIterator&);
  BTPostOrderIterator & operator=(BTPostOrderIterator&&);

  bool operator==(const BTPostOrderIterator&) const noexcept;
  bool operator!=(const BTPostOrderIterator&) const noexcept;

  Data& operator*() const; 
  bool Terminated() const noexcept; 
  void operator++(); 
  void Reset() noexcept; 
  void LeafFarLeft();
};


template <typename Data>
class BTInOrderIterator : public virtual ForwardIterator<Data>,
                          public virtual ResettableIterator<Data>{
private: 
  StackLst<typename BinaryTree<Data>::Node*> stk;
  typename BinaryTree<Data>::Node * current = nullptr;
  typename BinaryTree<Data>::Node * root;

public:

  BTInOrderIterator(const BinaryTree<Data>&);
  BTInOrderIterator(const BTInOrderIterator<Data>&);
  BTInOrderIterator(BTInOrderIterator<Data>&&);
  ~BTInOrderIterator() = default;

  BTInOrderIterator & operator=(const BTInOrderIterator&);
  BTInOrderIterator & operator=(BTInOrderIterator&&);

  bool operator==(const BTInOrderIterator&) const noexcept;
  bool operator!=(const BTInOrderIterator&) const noexcept;

  Data& operator*() const; 
  bool Terminated() const noexcept; 
  void operator++(); 
  void Reset() noexcept; 

protected:
  void FarLeft();

};


template <typename Data>
class BTBreadthIterator : public virtual ForwardIterator<Data>,
                          public virtual ResettableIterator<Data>{

private: 
  QueueLst<typename BinaryTree<Data>::Node*> queue;
  typename BinaryTree<Data>::Node * current = nullptr;
  typename BinaryTree<Data>::Node * root;

public:

  BTBreadthIterator(const BinaryTree<Data>&); 
  BTBreadthIterator(const BTBreadthIterator<Data>&);
  BTBreadthIterator(BTBreadthIterator<Data>&&);
  ~BTBreadthIterator() = default;

  BTBreadthIterator & operator=(const BTBreadthIterator&);
  BTBreadthIterator & operator=(BTBreadthIterator&&);

  bool operator==(const BTBreadthIterator&) const noexcept;
  bool operator!=(const BTBreadthIterator&) const noexcept;

  Data& operator*() const; 
  bool Terminated() const noexcept; 
  void operator++(); 
  void Reset() noexcept;

};

}

#include "binarytree.cpp"

#endif
