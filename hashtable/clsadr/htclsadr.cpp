
namespace lasd {
template<typename Data>
void Exists_(const Data& dato, const void* par, void* acc) noexcept{
    if((Data)dato == *((Data*)par))
        *((bool*)acc) = true;
}


template<typename Data>
bool Compare(const Data& dato, const void* hashtable2, void* isEqual){
    HashTableClsAdr<Data> * htable = (HashTableClsAdr<Data>*)hashtable2;
    *((bool*)isEqual) = htable->Exists((Data)dato);
    return isEqual;
}

template<typename Data>
void MapPrint(const Data& info, void* par){
    std::cout<<"-"<<info<<" ";
}

template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(){
    table.Resize(tableSize);
}

template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(ulong givenSize){
    table.Resize(givenSize);
    std::swap(tableSize, givenSize);
}

template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const LinearContainer<Data>& container){
    //se minore la dimensione della tabella non cambia
    if(container.Size() > tableSize){
        table.Resize(container.Size());
        tableSize = container.Size();
    }
    DictionaryContainer<Data>::Insert(container);
}

template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(ulong givenSize, LinearContainer<Data>& container){
    table.Resize(givenSize);
    std::swap(tableSize, givenSize);
    DictionaryContainer<Data>::Insert(container);
}

template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr<Data>& hashtable){
    table.Resize(hashtable.tableSize);
    for (ulong i = 0; i < hashtable.tableSize; i++)
        table[i] = hashtable.table[i];
    size = hashtable.size;
    tableSize = hashtable.tableSize;
    HashTable<Data>::a = hashtable.a;
    HashTable<Data>::b = hashtable.b;
}


template<typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr<Data>&& hashtable){
    table.Resize(hashtable.tableSize);
    std::swap(table, hashtable.table);
    std::swap(size, hashtable.size);
    std::swap(tableSize, hashtable.tableSize);
    HashTable<Data>::a = hashtable.a;
    HashTable<Data>::b = hashtable.b;
}

template<typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(const HashTableClsAdr<Data>& hashtable2){
    Clear();
    Resize(hashtable2.tableSize);
    size = hashtable2.size;
    table = hashtable2.table;
    return *this;
}
template<typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(HashTableClsAdr<Data>&& hashtable2){
    Clear();
    Resize(hashtable2.tableSize);
    std::swap(size, hashtable2.size);
    std::swap(table, hashtable2.table);
    return *this;
}


template<typename Data>
bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr<Data>& hashtable2) const noexcept{
    // if(size == hashtable2.size){
    //     for (ulong i = 0; i < tableSize; i++)
    //     {
    //         BTPreOrderIterator it(hashtable2.table[i]);
    //         for (; !it.Terminated(); ++it)
    //         {
    //             ulong index = HashTable<Data>::HashKey(*it);
    //             if(!table[index].Exists(*it))
    //                 return false;
    //         }
    //     }
    //     return true;
    // }
    // return false;
    bool isEqual = false;
    if(size == hashtable2.size){
        Fold(&Compare<Data>, &hashtable2, &isEqual);
        return isEqual;
    }
    return false;
}

template<typename Data>
bool HashTableClsAdr<Data>::operator!=(const HashTableClsAdr<Data>& hashtable2) const noexcept{
    return !(*this == hashtable2);
}

template<typename Data>
void HashTableClsAdr<Data>::Resize(const ulong& newSize) noexcept{
    Vector<BST<Data>> table2(table);
    table.Clear();
    table.Resize(newSize);
    tableSize = newSize;
    size = 0;
    for (ulong i = 0; i < table2.Size(); i++)
    {
        BTPreOrderIterator<Data> it(table2[i]);
        for (; !it.Terminated(); ++it)
            Insert(*it);
    }
    
    
}

template<typename Data>
bool HashTableClsAdr<Data>::Insert(const Data& dato) noexcept{
    ulong index = HashTable<Data>::HashKey(dato);
    if(table[index].Insert(dato)){
        size++;
        return true;
    }
    return false;
} 
template<typename Data>
bool HashTableClsAdr<Data>::Insert(Data&& dato) noexcept{
    ulong index = HashTable<Data>::HashKey(std::move(dato));
    if(table[index].Insert(std::move(dato))){
        size++;
        return true;
    }
    return false;
} 

template<typename Data>
bool HashTableClsAdr<Data>::Remove(const Data& dato) noexcept{
    ulong index = HashTable<Data>::HashKey(dato);
    if(table[index].Remove(dato)){
        size--;
        return true;
    }
    return false;    
}

template<typename Data>
bool HashTableClsAdr<Data>::Exists(const Data& dato) const noexcept {
    bool exist = false;
    Fold(&Exists_<Data>, &dato, &exist);
    return exist;
} 

template<typename Data>
void HashTableClsAdr<Data>::Map(MapFunctor funct, void* par){
    for(ulong i = 0; i < tableSize; i++)
            table[i].Map(funct, par);
}

template<typename Data>
void HashTableClsAdr<Data>::Fold(FoldFunctor funct, const void* par, void* acc) const {
    for(ulong i = 0; i < tableSize; i++)
        table[i].Fold(funct, par, acc);
}

template<typename Data>
void HashTableClsAdr<Data>::Clear() noexcept {
    table.Clear();
    table.Resize(HashTable<Data>::mytableSize);
    tableSize = HashTable<Data>::mytableSize;
    size = 0;
}

template<typename Data>
void HashTableClsAdr<Data>::print() const noexcept{
    std::cout<<"Inizio"<<std::endl;
    for (ulong i = 0; i < tableSize; i++)
    {
        if(!table[i].Empty())
            table[i].Map(&MapPrint<Data>, 0);
        else
            std::cout<<"X";
        std::cout<<std::endl;
        
    }
    std::cout<<"Fine"<<std::endl;
    
}

}
