
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

#include "../binarytree.hpp"

namespace lasd {

template <typename Data>
class BinaryTreeLnk : virtual public BinaryTree<Data>{
public:
  struct NodeLnk : virtual public BinaryTree<Data>::Node { 

  private:


  protected:

  public:
    Data info;
    NodeLnk * left_son = nullptr;
    NodeLnk * right_son = nullptr;

    NodeLnk() = default;
    NodeLnk(const Data&);
    NodeLnk(Data&&);
    NodeLnk(const NodeLnk&);
    NodeLnk(NodeLnk&&);
    ~NodeLnk();

    NodeLnk& operator=(const NodeLnk&);
    NodeLnk& operator=(NodeLnk&&);

    Data& Element() noexcept; // Mutable access to the element (concrete function should not throw exceptions)
    const Data& Element() const noexcept; // Immutable access to the element (concrete function should not throw exceptions)

    bool IsLeaf() const noexcept; // (concrete function should not throw exceptions)
    bool HasLeftChild() const noexcept; // (concrete function should not throw exceptions)
    bool HasRightChild() const noexcept; // (concrete function should not throw exceptions)

    NodeLnk& LeftChild(); // (concrete function must throw std::out_of_range when not existent)
    NodeLnk& RightChild(); // (concrete function must throw std::out_of_range when not existent)
  };
protected:
  NodeLnk * root = nullptr;
  NodeLnk * current = root;
  using BinaryTree<Data>::size;
public:
  void printTree(const std::string& prefix, NodeLnk* node, bool isLeft)
  {
      if(node != nullptr )
      {
          std::cout << prefix;
          std::cout << (isLeft ? "├──" : "└──" );
          std::cout << node->Element() << std::endl;
          if(node->HasLeftChild())
            printTree(prefix + (isLeft ? "│   " : "    "), node->left_son, true);
          if(node->HasRightChild())
            printTree(prefix +  (isLeft ? "│   " : "    "), node->right_son, false);
      }
  }

  BinaryTreeLnk() = default;
  BinaryTreeLnk(const LinearContainer<Data>&); // A binary tree obtained from a LinearContainer
  BinaryTreeLnk(const BinaryTreeLnk<Data>&);
  BinaryTreeLnk(BinaryTreeLnk<Data>&&);
  ~BinaryTreeLnk();

  BinaryTreeLnk & operator=(const BinaryTreeLnk&);
  BinaryTreeLnk & operator=(BinaryTreeLnk&&);

  // Comparison operators
  bool operator==(const BinaryTreeLnk&) const noexcept; //già implementate ma sovrascritte per efficienza
  bool operator!=(const BinaryTreeLnk&) const noexcept;

  NodeLnk& Root() const override; // Override BinaryTree member (throw std::length_error when empty)
  void Clear() noexcept override; // Override Container member

protected:
  void createTree(NodeLnk*, int, const LinearContainer<Data>&);
  void copyTree(NodeLnk *, NodeLnk *&);
  void Delete(NodeLnk *) noexcept;
};

}

#include "binarytreelnk.cpp"

#endif
