#include<iostream>
namespace lasd {

template<typename Data>
Vector<Data>::Vector(ulong dimension){
    Elements = new Data[dimension];
    size = dimension;
}

template<typename Data>
Vector<Data>::Vector(const LinearContainer<Data> &container){
    size = container.Size();
    Elements = new Data[container.Size()];
    for (ulong i = 0; i < container.Size(); i++)
    {
        Elements[i] = container[i];
    }
}

template<typename Data>
Vector<Data>::Vector(const Vector<Data>& vect2){
    Elements = new Data[vect2.size];
    std::copy(vect2.Elements, vect2.Elements + vect2.size, Elements);
    size = vect2.Size();
}

template<typename Data>
Vector<Data>::Vector(Vector<Data>&& vect2){
    std::swap(size, vect2.size);
    std::swap(Elements, vect2.Elements);
}
  
template<typename Data>
Vector<Data>::~Vector(){
    delete[] Elements;
    size = 0;
}

template<typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data>& vect2){
    Vector<Data>* temporaryVector = new Vector<Data>(vect2);
    std::swap(*temporaryVector, *this);
    delete temporaryVector;
    return *this;
}

template<typename Data>
Vector<Data>& Vector<Data>::operator=(Vector<Data>&& vect2){
    std::swap(Elements, vect2.Elements);
    std::swap(size, vect2.size);
    return *this;
}

template<typename Data>
bool Vector<Data>::operator==(const Vector<Data>& vect2) const noexcept{
    if(vect2.Size() == size){
        for (ulong i = 0; i < vect2.Size(); i++){
            if(vect2[i] != Elements[i]){
                return false;
            }
        }
        return true;
    }
    return false;
}

template<typename Data>
bool Vector<Data>::operator!=(const Vector<Data>& vect2) const noexcept{
    return !(vect2 == *this);
}

template<typename Data>
void Vector<Data>::Resize(ulong newsize){
    if(newsize == 0){
        Clear();
    }else if(newsize != size){
        Data * Elements2 = new Data[newsize]{};
        if(newsize > size){
            for (ulong i = 0; i < size; i++){
                Elements2[i] = Elements[i];
            } 
        }else{
            for (ulong i = 0; i < newsize; i++){
                Elements2[i] = Elements[i];
            }
        }
        std::swap(Elements, Elements2);
        size = newsize;
        delete[] Elements2;
    }

}

template<typename Data>
void Vector<Data>::Clear() noexcept{
    delete[] Elements;
    Elements = nullptr;
    size = 0;
}

template<typename Data>
Data& Vector<Data>::Front() const{
    if(!this->Empty()){
        return Elements[0];
    }else{
        throw std::length_error("Vector is empty");
    }
}

template<typename Data>
Data& Vector<Data>::Back() const{
    if(!this->Empty()){
        return Elements[size-1];
    }else{
        throw std::length_error("Vector is empty");
    }
    
}

template<typename Data>
Data& Vector<Data>::operator[](const ulong index) const{
    if(index >= size){
        throw std::out_of_range("Index out of range");
    }
    return Elements[index];
}

template<typename Data>
void Vector<Data>::Map(MapFunctor func, void* param)
{
	MapPreOrder(func, param);
}

template<typename Data>
void Vector<Data>::MapPreOrder(MapFunctor func, void* param)
{
	for (unsigned long i = 0; i < size; ++i)
		func(Elements[i], param);
}

template<typename Data>
void Vector<Data>::MapPostOrder(MapFunctor func, void* param)
{
	unsigned long i = size;
	while(i > 0)
		func(Elements[--i], param);
}

template<typename Data>
void Vector<Data>::Fold(FoldFunctor func, const void* param, void* acc) const
{
    FoldPreOrder(func,param,acc);
}
	
template<typename Data>
void Vector<Data>::FoldPreOrder(FoldFunctor func, const void* param, void* acc) const
{
	for (unsigned long i = 0; i < size; ++i)
		func(Elements[i], param, acc);
}

template<typename Data>
void Vector<Data>::FoldPostOrder(FoldFunctor func, const void* param, void* acc) const
{
	unsigned long i = size;
	while (i > 0)
		func(Elements[--i], param, acc);
}
}
