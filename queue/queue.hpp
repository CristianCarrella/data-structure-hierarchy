
#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "../container/container.hpp"

namespace lasd {

template <typename Data>
class Queue : virtual public Container{
public:
  virtual ~Queue() = default;

  Queue & operator=(const Queue&) = delete; 
  Queue & operator=(Queue&) = delete; 

  bool operator==(const Queue&) const noexcept = delete; 
  bool operator!=(const Queue&) const noexcept = delete; 

  virtual Data Head() const = 0; 
  virtual Data& Head() = 0; 
  virtual void Dequeue() = 0;
  virtual Data HeadNDequeue() = 0;
  virtual void Enqueue(const Data&) noexcept = 0;
  virtual void Enqueue(Data&&) noexcept = 0; 

};

}

#endif
