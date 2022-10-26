
namespace lasd {

template<typename Data>
QueueVec<Data>::QueueVec(const LinearContainer<Data>& container){
    Elements = new Data[container.Size()];
    size = container.Size();
    tail = container.Size();
    head = 0;
    realsize = container.Size();
    for (ulong i = 0; i < size; i++)
        Elements[i] = container[i];
}

template<typename Data>
QueueVec<Data>::QueueVec(const QueueVec<Data>& queue){
    Elements = new Data[queue.size];
    size = queue.size;
    tail = queue.realsize;
    head = 0;
    realsize = queue.realsize;
    for (ulong i = 0, j = queue.head; i < tail; i++){
        Elements[i] = queue.Elements[j];
        j = (j + 1) % queue.size;
    }
        
}

template<typename Data>
QueueVec<Data>::QueueVec(QueueVec<Data>&& queue){
    Elements = new Data[queue.size];
    std::swap(size, queue.size);
    std::swap(realsize, queue.realsize);
    std::swap(head, queue.head);
    tail = realsize;
    head = 0;
    for (ulong i = 0, j = head; i < tail; i++){
        std::swap(Elements[i], queue.Elements[j]);
        j = (j + 1) % size;
    }
        
}

template<typename Data>
QueueVec<Data>::~QueueVec(){
    head = 0;
    tail = 0;
    size = 0;
    realsize = 0;
}
template<typename Data>
QueueVec<Data> & QueueVec<Data>::operator=(const QueueVec<Data>& queue){
    Clear();
    ulong j = 0;
    Elements = new Data[queue.size];
    size = queue.size;
    tail = queue.realsize;
    realsize = queue.realsize;
    head = 0;
    for (ulong i = 0, j = queue.head; i < tail; i++){
        Elements[i] = queue.Elements[j];
        j = (j + 1) % queue.size;
    }
        
    return *this;
}

template<typename Data>
QueueVec<Data> & QueueVec<Data>::operator=(QueueVec<Data>&& queue){
    Clear();
    ulong j = 0;
    Elements = new Data[queue.size];
    size = std::move(queue.size);
    tail = std::move(queue.realsize);
    realsize = std::move(queue.realsize);
    head = 0;
    for (ulong i = 0, j = queue.head; i < tail; i++){
        Elements[i] = std::move(queue.Elements[j]);
        j = (j + 1) % queue.size;
    }
        
    return *this;
}

template<typename Data>
bool QueueVec<Data>::operator==(const QueueVec& queue) const noexcept{
    if(realsize == queue.realsize){
        for (ulong i = head, j = queue.head, k = 0 ; k < realsize; k++)
        {
            if(Elements[i] != queue.Elements[j])
                return false;
            i = (i + 1) % size;
            j = (j + 1) % queue.size;
        }
        return true;
    }
    return false;
}

template<typename Data>
bool QueueVec<Data>::operator!=(const QueueVec& queue) const noexcept{
    return !(*this == queue);
}

template<typename Data>
Data QueueVec<Data>::Head() const{
    if(!Empty())
        return Elements[head];
    else
        throw std::length_error("Queue empty");
}

template<typename Data>
Data& QueueVec<Data>::Head(){
    if(!Empty())
        return Elements[head];
    else
        throw std::length_error("Queue empty");    
}

template<typename Data>
void QueueVec<Data>::Dequeue(){
    if(!Empty()){
        if(realsize > size/4){
            head = (head + 1) % size;
        }  
        else{
            Reduce();
            head = (head + 1) % size;
        }
    }else{
        throw std::length_error("Queue empty"); 
    }
    realsize--;

}

template<typename Data>
Data QueueVec<Data>::HeadNDequeue(){
    if(!Empty()){
        Data tmp = Head();
        Dequeue();
        return tmp;
    }
    else{
        throw std::length_error("Queue empty"); 
    }

}

template<typename Data>
void QueueVec<Data>::Enqueue(const Data&value) noexcept{
    if(size != 0){
        if((tail + 1) % size == head)
            Expand();
    }else{
        Expand();
    }
    Elements[tail] = value;
    tail = (tail + 1) % size;
    realsize++;
}

template<typename Data>
void QueueVec<Data>::Enqueue(Data&& value) noexcept{
    if(size != 0){
        if((tail + 1) % size == head)
            Expand();
    }else{
        Expand();
    }
    Elements[tail] = std::move(value);
    tail = (tail + 1) % size; 
    realsize++;
}

template<typename Data>
bool QueueVec<Data>::Empty() const noexcept{
    return (realsize == 0);
}

template<typename Data>
void QueueVec<Data>::Clear() noexcept{
    if(Elements != nullptr){
        head = 0;
        tail = 0;
        size = 0;
        realsize = 0;
        delete[] Elements;
        Elements = nullptr;
        Vector<Data>::Resize(0);
    }

}


template<typename Data>
ulong QueueVec<Data>::Size() const noexcept{
    return realsize;
}


template<typename Data>
void QueueVec<Data>::Expand() {
    ulong tmp, newsize;
    if(size == 0)
        tmp = (size + 1) * EXPANSION_CONSTANT;
    else
        tmp = size * EXPANSION_CONSTANT;
    newsize = tmp;
    Data * Elements2 = new Data[tmp];
    SwapVectors(Elements2, newsize);

} 


template<typename Data>
void QueueVec<Data>::Reduce() {
    ulong tmp, newsize;
    tmp = size / EXPANSION_CONSTANT;
    newsize = tmp;
    Data * Elements2 = new Data[tmp];
    SwapVectors(Elements2 , newsize);
} 

template<typename Data>
void QueueVec<Data>::SwapVectors(Data * TmpElements, ulong newsize) {
    for(ulong i = 0, j = head; i < realsize; i++){
        std::swap(Elements[j], TmpElements[i]);
        j = (j + 1) % size;
    }
        
    size = newsize;
    head = 0;
    tail = realsize;
    std::swap(Elements, TmpElements);
    delete[] TmpElements;
} 

}
