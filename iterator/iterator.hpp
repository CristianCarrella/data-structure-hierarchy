
#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace lasd {

template <typename Data>
class Iterator {
public:
  virtual ~Iterator() = default;

  Iterator & operator=(const Iterator&) = delete;
  Iterator & operator=(Iterator&&) = delete;

  bool operator==(const Iterator&) const noexcept = delete;
  bool operator!=(const Iterator&) const noexcept = delete;

  virtual Data& operator*() const = 0; 
  virtual bool Terminated() const noexcept = 0; 

};


template <typename Data>
class ForwardIterator : virtual public Iterator<Data>{ 

public:
  virtual ~ForwardIterator() = default;

  ForwardIterator & operator=(const ForwardIterator&) = delete;
  ForwardIterator & operator=(ForwardIterator&&) = delete;

  bool operator==(const ForwardIterator&) const noexcept = delete;
  bool operator!=(const ForwardIterator&) const noexcept = delete;

  virtual void operator++() = 0; 

};


template <typename Data>
class BackwardIterator : virtual public Iterator<Data>{ 

public:
  virtual ~BackwardIterator() = default;

  BackwardIterator & operator=(const BackwardIterator&) = delete;
  BackwardIterator & operator=(BackwardIterator&&) = delete;

  bool operator==(const BackwardIterator&) const noexcept = delete;
  bool operator!=(const BackwardIterator&) const noexcept = delete;

  virtual void operator--() const = 0; 

};

template <typename Data>
class BidirectionalIterator : virtual public ForwardIterator<Data>, virtual public BackwardIterator<Data> {

public:
  virtual ~BidirectionalIterator() = default;

  BidirectionalIterator & operator=(const BidirectionalIterator&) = delete;
  BidirectionalIterator & operator=(BidirectionalIterator&&) = delete;

  bool operator==(const BidirectionalIterator&) const noexcept = delete;
  bool operator!=(const BidirectionalIterator&) const noexcept = delete;

  virtual bool Terminated() const noexcept override = 0; 
  virtual bool ForwardTerminated() const noexcept = 0; 
  virtual bool BackwardTerminated() const noexcept = 0; 

};


template <typename Data>
class ResettableIterator : virtual public Iterator<Data>{ 
  
public:
  virtual ~ResettableIterator() = default;

  ResettableIterator & operator=(const ResettableIterator&) = delete;
  ResettableIterator & operator=(ResettableIterator&&) = delete;

  bool operator==(const ResettableIterator&) const noexcept = delete;
  bool operator!=(const ResettableIterator&) const noexcept = delete;

  virtual void Reset() noexcept = 0; 

};


}

#endif
