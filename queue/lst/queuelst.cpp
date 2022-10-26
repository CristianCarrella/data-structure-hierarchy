
namespace lasd {

template<typename Data>
QueueLst<Data>::QueueLst(const LinearContainer<Data>& container){
    for (ulong i = 0; i < container.Size(); i++)
        Enqueue(container[i]);
}

template<typename Data>
QueueLst<Data>::QueueLst(const QueueLst<Data>& queue){
    for (ulong i = 0; i < queue.size; i++)
        Enqueue(queue[i]);
}

template<typename Data>
QueueLst<Data>::QueueLst(QueueLst<Data>&& queue){
    // for (ulong i = 0; i < queue.size; i++)
    //     Enqueue(std::move(queue[i]));
    std::swap(head, queue.head);
    std::swap(tail, queue.tail);
    std::swap(size, queue.size);
}

template<typename Data>
QueueLst<Data>::~QueueLst(){
    Clear();
}

template<typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(const QueueLst<Data>& queue){
    Clear();
    QueueLst tmp = queue;
    for (ulong i = 0; i < queue.size; i++)
        Enqueue(tmp.HeadNDequeue());
    
    return *this;
}

template<typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(QueueLst<Data>&& queue){
    Clear();
    std::swap(head, queue.head);
    std::swap(tail, queue.tail);
    std::swap(size, queue.size);
    return *this;
}

template<typename Data>
bool QueueLst<Data>::operator==(const QueueLst& queue) const noexcept{
    QueueLst tmp1 = *this;
    QueueLst tmp2 = queue;
    if(size == queue.size){
        for (ulong i = 0; i < size; i++)
        {
            if(tmp1.HeadNDequeue() != tmp2.HeadNDequeue())
                return false;
        }
        return true;
    }
    return false;
}

template<typename Data>
bool QueueLst<Data>::operator!=(const QueueLst& queue) const noexcept{
    return !(*this == queue);
}

template<typename Data>
Data QueueLst<Data>::Head() const {
    if(!Container::Empty())
        return head->info;
    else
        throw std::length_error("Queue empty");
}

template<typename Data>
Data& QueueLst<Data>::Head() {
    if(!Container::Empty())
        return head->info;
    else
        throw std::length_error("Queue empty");
}

template<typename Data>
void QueueLst<Data>::Dequeue() {
    if(!Container::Empty())
        List<Data>::RemoveFromFront();
    else   
        throw std::length_error("Queue empty");
}

template<typename Data>
Data QueueLst<Data>::HeadNDequeue() {
    if(!Container::Empty()){
        Data tmp = List<Data>::Front();
        Dequeue();
        return tmp;
    }
    else{
        throw std::length_error("Queue empty");
    }
}

template<typename Data>
void QueueLst<Data>::Enqueue(const Data& value) noexcept {
    List<Data>::InsertAtBack(value);
}

template<typename Data>
void QueueLst<Data>::Enqueue(Data&& value) noexcept {
    List<Data>::InsertAtBack(std::move(value));
}


template<typename Data>
void QueueLst<Data>::Clear() noexcept {
    ulong tmp = size;
    for (ulong i = 0; i < tmp; i++)
        Dequeue();
}

}
