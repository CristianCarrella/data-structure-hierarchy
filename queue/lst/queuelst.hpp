
#ifndef QUEUELST_HPP
#define QUEUELST_HPP

#include "../queue.hpp"
#include "../../list/list.hpp"

namespace lasd {

template <typename Data>
class QueueLst : virtual public Queue<Data>, virtual protected List<Data>{
protected:

  using List<Data>::size;
  using List<Data>::head;
  using List<Data>::tail;

public:
  QueueLst() = default;
  QueueLst(const LinearContainer<Data>&);
  QueueLst(const QueueLst&);
  QueueLst(QueueLst&&);
  ~QueueLst();

  QueueLst& operator=(const QueueLst&);
  QueueLst& operator=(QueueLst&&);

  bool operator==(const QueueLst&) const noexcept;
  bool operator!=(const QueueLst&) const noexcept;

  Data Head() const override;
  Data& Head() override; 
  void Dequeue() override; 
  Data HeadNDequeue() override; 
  void Enqueue(const Data&) noexcept; 
  void Enqueue(Data&&) noexcept; 

  void Clear() noexcept override;

};

}

#include "queuelst.cpp"

#endif
