#include"container.hpp"
#include<iostream>
namespace lasd {

inline bool Container::Empty() const noexcept{
    return (size == 0);
}

inline ulong Container::Size() const noexcept{
    return size;
}

template <typename Data>
Data& LinearContainer<Data>::Front() const{
    if(Empty()){
        throw std::length_error("Container is empty");
    }else{
        return operator[](0);
    }
}

template <typename Data>
Data& LinearContainer<Data>::Back() const{
    if(Empty()){
        throw std::length_error("Container is empty");
    }else{
        return operator[](size-1);
    }
}


template<typename Data>
bool LinearContainer<Data>::operator==(const LinearContainer& otherLinearContainer) const noexcept{
    if(size == otherLinearContainer.size){
        for (ulong i = 0; i < size; i++)
        {
            if(otherLinearContainer[i] != operator[](i)){
                return false;
            }
        }
        return true;
    }
    return false;    
}

template<typename Data>
bool LinearContainer<Data>::operator!=(const LinearContainer& otherLinearContainer) const noexcept{
    return !(this == otherLinearContainer);
}

template<typename Data>
void compareFoldFunct(const Data& elementToFind, const void* elementToCompare, void* exist) noexcept {
    //std::cout<<(Data)elementToFind<<" "<< *((Data*)elementToCompare);
    if((Data)elementToFind == *((Data*)elementToCompare)){
        *((bool*)exist) = true;
    }
}

template<typename Data>
bool FoldableContainer<Data>::Exists(const Data& elementToFind) const noexcept{
    bool exist = false;
    Fold(&compareFoldFunct<Data>, &elementToFind, &exist);
    return exist;
}

template<typename Data>
void PreOrderMappableContainer<Data>::Map(MapFunctor funct, void* ptr){
    MapPreOrder(funct, ptr);
}


template<typename Data>
void PostOrderMappableContainer<Data>::Map(MapFunctor funct, void* ptr){
    MapPostOrder(funct, ptr);
}

template<typename Data>
void PreOrderFoldableContainer<Data>::Fold(FoldFunctor funct, const void* startvalue, void* accumulator) const {
    FoldPreOrder(funct, startvalue, accumulator);
}

template<typename Data>
void PostOrderFoldableContainer<Data>::Fold(FoldFunctor funct, const void* position, void* accumulator) const {
    FoldPostOrder(funct, position, accumulator);
}

template<typename Data>
void InOrderMappableContainer<Data>::Map(MapFunctor funct, void* ptr){
    MapInOrder(funct, ptr);
}


template<typename Data>
void InOrderFoldableContainer<Data>::Fold(FoldFunctor funct, const void* position, void* accumulator) const{
    FoldInOrder(funct, position, accumulator);
}

template<typename Data>
void BreadthMappableContainer<Data>::Map(MapFunctor funct, void* ptr){
    MapBreadth(funct, ptr);
}

template<typename Data>
void BreadthFoldableContainer<Data>::Fold(FoldFunctor funct, const void* position, void* accumulator) const{
    FoldBreadth(funct, position, accumulator);
}

template<typename Data>
bool DictionaryContainer<Data>::Insert(const LinearContainer<Data>& container) noexcept{
    for (ulong i = 0; i < container.Size(); i++)
        Insert(container[i]);
    return true;
}

template<typename Data>
bool DictionaryContainer<Data>::Insert(LinearContainer<Data>&& container) noexcept{
    for (ulong i = 0; i < container.Size(); i++)
        Insert(std::move(container[i]));
    return true;
}

template<typename Data>
bool DictionaryContainer<Data>::Remove(const LinearContainer<Data>& container) noexcept{
    for (ulong i = 0; i < container.Size(); i++)
        Remove(container[i]);
    return true;
}


}
