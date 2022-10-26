
#ifndef LIST_HPP
#define LIST_HPP
#include "../container/container.hpp"

namespace lasd {

template <typename Data>
class List : virtual public LinearContainer<Data>,
             virtual public PreOrderMappableContainer<Data>,
             virtual public PostOrderMappableContainer<Data>,
             virtual public PreOrderFoldableContainer<Data>,
             virtual public PostOrderFoldableContainer<Data> {

protected:

  using LinearContainer<Data>::size;
  struct Node {
    Data info;
    Node *next = nullptr;

    Node() = default;
    Node(const Data&);
    Node(Data&&);
    Node(Node&&);
    Node(const Node&);
    ~Node() = default;

    bool operator==(const Node&) const noexcept;
    bool operator!=(const Node&) const noexcept;
    Node & operator=(const Node&);
    Node & operator=(Node&&);

    // Specific member functions

    // ...

  };
  Node *head = nullptr;
  Node *tail = head;
public:
  List() = default;
  List(LinearContainer<Data>&);
  List(const List<Data>&);
  List(List<Data>&&);
  ~List();
  Node getHead(){
    return *head;
  }
  //operators
  List & operator=(const List&);
  List & operator=(List&&);
  bool operator==(const List&) const noexcept;
  bool operator!=(const List&) const noexcept;
  Data& operator[](const ulong) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

  void InsertAtFront(const Data&) noexcept; // Copy of the value
  void InsertAtFront(Data&&) noexcept; // Move of the value
  void RemoveFromFront(); // (must throw std::length_error when empty)
  Data FrontNRemove(); // (must throw std::length_error when empty)

  void InsertAtBack(const Data&) noexcept; // Copy of the value
  void InsertAtBack(Data&&) noexcept; // Move of the value
  void Clear() noexcept override; // Override Container member
  Data& Front() const override; // Override LinearContainer member (must throw std::length_error when empty)
  Data& Back() const override; // Override LinearContainer member (must throw std::length_error when empty) 
  using typename MappableContainer<Data>::MapFunctor;
  void Map(MapFunctor, void*) override;
  void MapPreOrder(MapFunctor, void*) override;
  void MapPostOrder(MapFunctor, void*) override;
  
  using typename FoldableContainer<Data>::FoldFunctor;
  void Fold(FoldFunctor, const void*, void*) const override;
  void FoldPreOrder(FoldFunctor, const void*, void*) const override;
  void FoldPostOrder(FoldFunctor, const void*, void*) const override;

protected:
  void DeleteAll(); //used for Destructor and Clear

  void MapPreOrder(MapFunctor, void*, Node*); // Accessory function executing from one point of the list onwards
  void MapPostOrder(MapFunctor, void*, Node*); // Accessory function executing from one point of the list onwards

  void FoldPreOrder(FoldFunctor, const void*, void*, Node*) const; // Accessory function executing from one point of the list onwards
  void FoldPostOrder(FoldFunctor, const void*, void*, Node*) const; // Accessory function executing from one point of the list onwards

};
}

#include "list.cpp"

#endif
