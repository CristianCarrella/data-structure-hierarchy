
#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

#include "../queue.hpp"
#include "../../vector/vector.hpp"

namespace lasd {

template <typename Data>
class QueueVec : virtual public Queue<Data>, virtual protected Vector<Data> {
protected:
  using Vector<Data>::Elements;
  using Vector<Data>::size; //dimensione vettore
  const float REDUCTION_CONSTANT = 0.25;
  const float EXPANSION_CONSTANT = 2;
  ulong realsize = 0; //elementi compresi tra head e tail
  ulong head = 0;
  ulong tail = 0; 

public:
  void printVec(){
    for (size_t i = 0; i < size; i++)
    {
      if(i == head){
        std::cout<<"head ->";
      }
      if(i == tail){
        std::cout<<"tail ->";
      }
      std::cout<<Elements[i] << " ";
    }
    std::cout<<std::endl;
  }

  QueueVec() = default;
  QueueVec(const LinearContainer<Data>&); 
  QueueVec(const QueueVec&);
  QueueVec(QueueVec&&);
  ~QueueVec();

  QueueVec& operator=(const QueueVec&);
  QueueVec& operator=(QueueVec&&);

  bool operator==(const QueueVec&) const noexcept;
  bool operator!=(const QueueVec&) const noexcept;


  Data Head() const override; 
  Data& Head() override; 
  void Dequeue() override; 
  Data HeadNDequeue() override;
  void Enqueue(const Data&) noexcept; 
  void Enqueue(Data&&) noexcept; 

  bool Empty() const noexcept override;
  ulong Size() const noexcept override;
  void Clear() noexcept override; 

protected:
  void Expand();
  void Reduce();
  void SwapVectors(Data *, ulong);

};

}

#include "queuevec.cpp"

#endif
