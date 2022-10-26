
namespace lasd {

template<typename Data>
StackVec<Data>::StackVec(const LinearContainer<Data>& container){
    Elements = new Data[container.Size()];
    size = container.Size();
    head = size;
    for (ulong i = 0; i < size; i++)
        Elements[i] = container[i];
}

template<typename Data>
StackVec<Data>::StackVec(const StackVec& stackvect){
    Elements = new Data[stackvect.size];
    size = stackvect.size;
    head = stackvect.head;
    for (ulong i = 0; i < size; i++)
        Elements[i] = stackvect.Elements[i];
}


template<typename Data>
StackVec<Data>::StackVec(StackVec&& stackvect){
    std::swap(head, stackvect.head);
    std::swap(size, stackvect.size);
    std::swap(Elements, stackvect.Elements);
}

template<typename Data>
StackVec<Data>::~StackVec(){
    size = 0;
    head = 0;
}

template<typename Data>
StackVec<Data>& StackVec<Data>::operator=(const StackVec& stackvect){
    size = stackvect.size;
    head = stackvect.head;
    for (ulong i = 0; i < size; i++)
        Elements[i] = stackvect.Elements[i];
    return *this;
}

template<typename Data>
StackVec<Data>& StackVec<Data>::operator=(StackVec&& stackvect){
    size = std::move(stackvect.size);
    head = std::move(stackvect.head);
    for (ulong i = 0; i < size; i++)
        Elements[i] = std::move(stackvect.Elements[i]);
    return *this;
}

template<typename Data>
bool StackVec<Data>::operator==(const StackVec<Data>& stackvect) const noexcept{
    if(stackvect.Size() == Size()){
        for (ulong i = 0; i < stackvect.Size(); i++){
            if(stackvect.Elements[i] != Elements[i]){
                return false;
            }
        }
        return true;
    }
    return false;
}

template<typename Data>
bool StackVec<Data>::operator!=(const StackVec<Data>& stackvect) const noexcept{
    return !(stackvect == *this);
}

template<typename Data>
Data StackVec<Data>::Top() const{
    if(!Empty()){
        return Elements[head - 1];
    }else{
        throw std::length_error("Stack empty");
    }
}

template<typename Data>
Data& StackVec<Data>::Top(){
    if(!Empty()){
        return Elements[head - 1];
    }else{
        throw std::length_error("Stack empty");
    }
}

template<typename Data>
void StackVec<Data>::Pop(){
    if(!Empty()){
        if(head == (int)(size * REDUCTION_CONSTANT))
            Reduce();
        head--;
    }else{
        throw std::length_error("Stack empty");
    }
}

template<typename Data>
Data StackVec<Data>::TopNPop(){
    if(!Empty()){
        Data tmp = Top();
        Pop();
        return tmp;
    }else{
        throw std::length_error("Stack empty");
    }
}

template<typename Data>
void StackVec<Data>::Push(const Data& value) noexcept{  
    if(head == size)
        Expand();
    Elements[head] = value;
    head++;
}


template<typename Data>
void StackVec<Data>::Push(Data&& value) noexcept{  
    if(head == size)
        Expand();
    Elements[head] = std::move(value);
    head++;
}

template<typename Data>
bool StackVec<Data>::Empty() const noexcept {
    return (head == 0);
}

template<typename Data>
ulong StackVec<Data>::Size() const noexcept {
    return head;
}

template<typename Data>
void StackVec<Data>::Clear() noexcept {
    delete[] Elements;
    Elements = nullptr;
    size = 0;
    head = 0;
} 

template<typename Data>
void StackVec<Data>::Expand() {
    ulong tmp;
    if(size == 0)
        tmp = (size + 1) * EXPANSION_CONSTANT;
    else
        tmp = size * EXPANSION_CONSTANT;

    Vector<Data>::Resize(tmp);
} 

template<typename Data>
void StackVec<Data>::Reduce() {
    ulong tmp;
    if(size == 0)
        tmp = (size + 1) / EXPANSION_CONSTANT;
    else
        tmp = size / EXPANSION_CONSTANT;
    Vector<Data>::Resize(tmp);
} 




}
