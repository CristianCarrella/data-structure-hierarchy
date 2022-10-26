#include<math.h>

namespace lasd {

template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(){
    table.Resize(tableSize);
    checkStatus.Resize(tableSize);
    ResetStatus();
}

template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(ulong givenSize){
    ulong newSize = 0;
    double log = ceil(log2(givenSize));
    newSize = pow(2, log);
    table.Resize(newSize);
    checkStatus.Resize(newSize);
    tableSize = newSize;
    ResetStatus();
}

template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const LinearContainer<Data>& container){
    ulong newSize = 0;
    if(container.Size() > tableSize){        
        double log = ceil(log2(container.Size()));
        newSize = pow(2, log);
        table.Resize(newSize);
        checkStatus.Resize(newSize);
        tableSize = newSize;
        ResetStatus();
    }
    DictionaryContainer<Data>::Insert(container);
}

template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(ulong givenSize, LinearContainer<Data>& container){
    ulong newSize = 0;
    if(container.Size()>givenSize){
        double log = ceil(log2(container.Size()));
        newSize = pow(2, log);
        table.Resize(newSize);
        checkStatus.Resize(newSize);
        tableSize = newSize;
    }
    else {
        double log = ceil(log2(givenSize));
        newSize = pow(2, log);
        table.Resize(newSize);
        checkStatus.Resize(newSize);
        std::swap(tableSize, newSize);
    }
    ResetStatus();
    DictionaryContainer<Data>::Insert(container);
}

template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr<Data>& hashtable){
    table.Resize(hashtable.tableSize);
    checkStatus.Resize(hashtable.tableSize);
    for (ulong i = 0; i < hashtable.tableSize; i++){
        table[i] = hashtable.table[i];
        checkStatus[i] = hashtable.checkStatus[i];
    }
    size = hashtable.size;
    tableSize = hashtable.tableSize;
    HashTable<Data>::a = hashtable.a;
    HashTable<Data>::b = hashtable.b;
}

template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr<Data>&& hashtable){
    table.Resize(hashtable.tableSize);
    checkStatus.Resize(hashtable.tableSize);
    std::swap(table, hashtable.table);
    std::swap(checkStatus, hashtable.checkStatus);
    std::swap(size, hashtable.size);
    std::swap(tableSize, hashtable.tableSize);
    HashTable<Data>::a = hashtable.a;
    HashTable<Data>::b = hashtable.b;
}

template<typename Data>
void HashTableOpnAdr<Data>::ResetStatus(){
    for (ulong i = 0; i < checkStatus.Size(); i++)
        checkStatus[i] = 'e';
}

template<typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr<Data>& hashtable){
    Clear();
    table.Resize(hashtable.tableSize);
    checkStatus.Resize(hashtable.tableSize);
    for (ulong i = 0; i < hashtable.tableSize; i++){
        table[i] = hashtable.table[i];
        checkStatus[i] = hashtable.checkStatus[i];
    }
    size = hashtable.size;
    tableSize = hashtable.tableSize;
    HashTable<Data>::a = hashtable.a;
    HashTable<Data>::b = hashtable.b;
    ResetStatus();
    return *this;
}

template<typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(HashTableOpnAdr<Data>&& hashtable){
    Clear();
    table.Resize(hashtable.tableSize);
    checkStatus.Resize(hashtable.tableSize);
    std::swap(table, hashtable.table);
    std::swap(checkStatus, hashtable.checkStatus);
    std::swap(size, hashtable.size);
    std::swap(tableSize, hashtable.tableSize);
    HashTable<Data>::a = hashtable.a;
    HashTable<Data>::b = hashtable.b;
    ResetStatus();
    return *this;
}

template<typename Data>
bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr<Data>& hashtable2) const noexcept{
    if(size == hashtable2.size){
        for (ulong i = 0; i < tableSize; i++){
            if(checkStatus[i] == 'f'){
                if(!hashtable2.Exists(table[i]))
                    return false;
            }
        }
        return true;
    }else{
        return false;
    }    

}

template<typename Data>
bool HashTableOpnAdr<Data>::operator!=(const HashTableOpnAdr<Data>& hashtable2) const noexcept{
    return !(*this == hashtable2);
}

template<typename Data>
void HashTableOpnAdr<Data>::Resize(const ulong& tmpSize) noexcept{
    ulong newSize = 0;
    Vector<Data> tmp(table);
    Vector<char> tmpStatus(checkStatus);
    
    if(tmpSize > size){
        double log = ceil(log2(tmpSize));
        newSize = pow(2, log);
    }
    else
        newSize = tableSize * 2;

    checkStatus.Clear();
    checkStatus.Resize(newSize);
    ResetStatus();
    table.Clear();
    table.Resize(newSize);
    tableSize = newSize;
    size = 0;

    for (ulong i = 0; i < tmpStatus.Size(); i++)
    {
        if(tmpStatus[i] == 'f')
            Insert(tmp[i]);
    }
    
}

template<typename Data>
bool HashTableOpnAdr<Data>::Insert(const Data& dato) noexcept {    
    ulong i = 0;
    ulong index = 0;
    if(size == tableSize/2)
        Resize(tableSize*2);

    while (i < tableSize)
    {
        index = HashKey(dato, i);
        if(table[index] == dato && checkStatus[index] == 'f')
            return false;
        if(checkStatus[index] == 'e' || checkStatus[index] == 'o'){
            RemoveFromIndex(i, dato);
            size++;
            checkStatus[index] = 'f';
            table[index] = dato;
            return true;
        }else
            i++;
    }

    return false;
} 

template<typename Data>
bool HashTableOpnAdr<Data>::Insert(Data&& dato) noexcept {
    ulong i = 0;
    ulong index = 0;

    if(size == tableSize/2)
        Resize(tableSize*2);

    while (i < tableSize)
    {
        index = HashKey(dato, i);
        if(table[index] == dato && checkStatus[index] == 'f')
            return false;
        if(checkStatus[index] == 'e' || checkStatus[index] == 'o'){
            RemoveFromIndex(i, dato);
            size++;
            table[index] = std::move(dato);
            checkStatus[index] = 'f';
            return true;
        }else
            i++;
    }
    return false;

}

template<typename Data>
bool HashTableOpnAdr<Data>::Remove(const Data& dato) noexcept{
    return RemoveFromIndex(0, dato);
}

template<typename Data>
bool HashTableOpnAdr<Data>::Exists(const Data& dato) const noexcept{
    ulong i = 0;
    ulong index = 0;
    while (i < tableSize)
    {
        index = HashKey(dato, i);
        if(checkStatus[index] == 'f' && table[index] == dato){
            return true;
        }else if(checkStatus[index] == 'o' || checkStatus[index] == 'f')
            i++;
        else
            return false;
    }
    return false;
}

template<typename Data>
void HashTableOpnAdr<Data>::Map(MapFunctor funct, void* par){
    for (ulong i = 0; i < tableSize; i++)
    {
        if(checkStatus[i] == 'f')
            funct(table[i], par);
    }
    
}

template<typename Data>
void HashTableOpnAdr<Data>::Fold(FoldFunctor funct, const void* par, void* acc) const{
    for (ulong i = 0; i < tableSize; i++)
    {
        if(checkStatus[i] == 'f')
            funct(table[i], par, acc);
    }
}

template<typename Data>
void HashTableOpnAdr<Data>::Clear() noexcept{
    tableSize = 1024;
    size = 0;
    table.Clear();
    table.Resize(tableSize);
    checkStatus.Clear();
    checkStatus.Resize(tableSize);
    ResetStatus();
    
}

template<typename Data>
void HashTableOpnAdr<Data>::print() const noexcept{
    for(ulong i = 0; i < tableSize; i++){
        if(checkStatus[i] == 'f')
            std::cout<<table[i]<<std::endl;
        else if(checkStatus[i] == 'o')
            std::cout<<"o"<<std::endl;
        else
            std::cout<<"e"<<std::endl;
    }
    
}

// template<typename Data>
// ulong HashTableOpnAdr<Data>::Find(const Data&) const {

// }

// template<typename Data>
// ulong HashTableOpnAdr<Data>::FindEmpty() const{

// }

template<typename Data>
bool HashTableOpnAdr<Data>::RemoveFromIndex(const ulong& j, const Data& dato) {
    ulong i = j;
    ulong index = 0;
    while (i < tableSize)
    {
        index = HashKey(dato, i);
        if(checkStatus[index] == 'f' && table[index] == dato){
            checkStatus[index] = 'o';
            size--;
            return true;
        }else if(checkStatus[index] == 'e')
            return false;
        else
            i++;
    }  
    return false;
}

template<typename Data>
ulong HashTableOpnAdr<Data>::HashKey(const Data& key, const ulong index) const{
    // //Doppio hashing
    // ulong f1 = HashKey(HashKey(key));
    // c = HashTable<Data>::generateRandom(0, HashTable<Data>::p);
    // d = HashTable<Data>::generateRandom(0, HashTable<Data>::p);
    // ulong keylong = HashKey(key);
    // ulong f2 = ((c*keylong + d) % p) % tableSize;
    // return (f1 + (f2 * index)) % tableSize;

    //probing lineare
    ulong f1 = HashTable<Data>::HashKey(HashTable<Data>::HashKey(key));
    return (f1 + (index * 43891)) % tableSize; //43891 è un numero primo - sicuramente coprimo con tableSize, ciò permette mediante proving lineare di coprire tutta la tabella

    // //probing quadratico
    // ulong f1 = HashTable<Data>::HashKey(HashTable<Data>::HashKey(key));
    // return (f1 + ((index * index) + 1)/2) % tableSize;

}

}
