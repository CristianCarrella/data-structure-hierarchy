
namespace lasd {

template<typename Data>
StackLst<Data>::StackLst(const LinearContainer<Data> & container){
    ulong i = container.Size() - 1;
    ulong j = 0;
    while (j < container.Size())
    {
        Push(container[i]);
        i--;
        j++;
    }
        
}

template<typename Data>
StackLst<Data>::StackLst(const StackLst<Data> & stk){
    ulong i = stk.size - 1;
    ulong j = 0;
    while (j < stk.size)
    {
        Push(stk[i]);
        i--;
        j++;
    }
        
}


template<typename Data>
StackLst<Data>::StackLst(StackLst<Data> && stk){
    // ulong i = stk.size - 1;
    // ulong j = 0;
    // while (j < stk.size)
    // {
    //     Push(std::move(stk[i]));
    //     i--;
    //     j++;
    // }
    // stk.Clear();
    std::swap(size, stk.size);
    std::swap(tail, stk.tail);
    std::swap(head, stk.head);
}

template<typename Data>
StackLst<Data>& StackLst<Data>::operator=(const StackLst<Data>& stk){
    Clear();
    ulong i = stk.size - 1;
    ulong j = 0;
    while (j < stk.size)
    {
        Push(stk[i]);
        i--;
        j++;
    }
    return *this;
}

template<typename Data>
StackLst<Data>::~StackLst(){
    ulong sizetmp = List<Data>::Size();
    for (ulong i = 0; i < sizetmp; i++)
        Pop();
}


template<typename Data>
StackLst<Data>& StackLst<Data>::operator=(StackLst<Data>&& stk){
    // Clear();
    // ulong i = stk.size - 1;
    // ulong j = 0;
    // while (j < stk.size)
    // {
    //     Push(std::move(stk[i]));
    //     i--;
    //     j++;
    // }
    // stk.Clear();
    std::swap(size, stk.size);
    std::swap(tail, stk.tail);
    std::swap(head, stk.head);
    return *this;
}

template<typename Data>
bool StackLst<Data>::operator==(const StackLst& stk) const noexcept{
    StackLst tmp = stk;
    StackLst tmp2 = *this;
    if(stk.size == size){
        for (ulong i = 0; i < stk.Size(); i++)
        {
            if(tmp2.TopNPop() != tmp.TopNPop())
                return false;
        }
        return true;
    }else{
        return false;
    }
}

template<typename Data>
bool StackLst<Data>::operator!=(const StackLst& stk) const noexcept{
    return !(*this == stk);
}

template<typename Data>
Data StackLst<Data>::Top() const{
    if(!Container::Empty())
        return List<Data>::Front();
    else
        throw std::length_error("Stack empty");
}

template<typename Data>
Data& StackLst<Data>::Top(){
    if(!Container::Empty())
        return List<Data>::Front();
    else
        throw std::length_error("Stack empty");
}

template<typename Data>
void StackLst<Data>::Pop(){
    if(!List<Data>::Empty())
        List<Data>::RemoveFromFront();
    else
        throw std::length_error("Stack empty");
}

template<typename Data>
Data StackLst<Data>::TopNPop(){
    if(!Container::Empty()){
        Data value = Top();
        Pop();
        return value;
    }else{
        throw std::length_error("Stack empty");
    }
}

template<typename Data>
void StackLst<Data>::Push(const Data& value) noexcept{
    List<Data>::InsertAtFront(value);
}

template<typename Data>
void StackLst<Data>::Push(Data&& value) noexcept{
    List<Data>::InsertAtFront(std::move(value));
}

template<typename Data>
void StackLst<Data>::Clear() noexcept{
    ulong sizetmp = List<Data>::Size();
    for (ulong i = 0; i < sizetmp; i++)
        Pop();
}

}
