
namespace lasd {

template<typename Data>
List<Data>::Node::Node(const Data &data){
    info = data;
}

template<typename Data>
List<Data>::Node::Node(Data &&data){
    std::swap(data, info);
}

template<typename Data>
List<Data>::Node::Node(Node &&nodo){
    std::swap(info, nodo.info);
    std::swap(next, nodo.next);
}

template<typename Data>
List<Data>::Node::Node(const Node &nodo){
    info = nodo.info;
    next = nodo.next;
}

template<typename Data>
bool List<Data>::Node::operator==(const Node& nodo) const noexcept{
    if(nodo.info == info && nodo.next == next){
        return true;
    } else {
        return false;
    }
}

template<typename Data>
bool List<Data>::Node::operator!=(const Node& nodo) const noexcept{
    return !(nodo == *this);
}

template<typename Data>
typename List<Data>::Node& List<Data>::Node::operator=(const Node& nodo){
    info = nodo.info;
    next = nodo.next;
    return *this;
}

template<typename Data>
typename List<Data>::Node& List<Data>::Node::operator=(Node&& nodo){
    info = std::move(nodo.info);
    next = std::move(nodo.next);
    return *this;
}

template<typename Data>
List<Data>::List(LinearContainer<Data>& container){
    for (ulong i = 0; i < container.Size(); i++)
    {
        InsertAtBack(container[i]);
    }

    // for (ulong i = 0; i < container.size; i++)
    // {
    //     Node newnode = new Node(container[i]);
    //     newnode.next = *head;
    //     *head = newnode
    // }
}


template<typename Data>
List<Data>::List(const List<Data>& list2){

    for (ulong i = 0; i < list2.Size(); i++)
    {
        InsertAtBack(list2[i]);
    }

}


template<typename Data>
List<Data>::List(List<Data>&& list2){

    for (ulong i = 0; i < list2.Size(); i++)
    {
        InsertAtBack(std::move(list2[i]));
    }

}

template<typename Data>
List<Data>& List<Data>::operator=(const List& list2){
    Clear();
    for (ulong i = 0; i < list2.Size(); i++)
    {
        InsertAtBack(list2[i]);

    }
    return *this;
}

template<typename Data>
List<Data>& List<Data>::operator=(List&& list2){
    std::swap(size, list2.size);
    std::swap(head, list2.head);
    return *this;
}

template<typename Data>
void List<Data>::DeleteAll(){
    Node *tmp = head;
    Node *next = nullptr;
    size = 0;

    while (tmp != nullptr)
    {
        next = tmp->next;
        delete tmp;
        tmp = next;
    }

    head = nullptr;
}

template<typename Data>
List<Data>::~List(){
    DeleteAll();
}


template<typename Data>
Data& List<Data>::operator[](const ulong index) const{
    Node *tmp = head;
    ulong i = 0;
    if(index < size){
        while(tmp != nullptr && i != index){
            tmp = tmp->next;
            i++;
        }
        return tmp->info;
    } else {
        throw std::out_of_range("Index out of range");
    }
}
  
template<typename Data>
bool List<Data>::operator==(const List& list2) const noexcept{
    if(list2.size == size){
        for (ulong i = 0; i < size; i++)
        {
            if(operator[](i) != list2[i]){
                return false;
            }
        }
        return true;
    }
    return false;
}

template<typename Data>
bool List<Data>::operator!=(const List& list) const noexcept{
    return !(*this == list);
}


template<typename Data>
void List<Data>::RemoveFromFront(){
    Node * nodo = new Node();
    if(!LinearContainer<Data>::Empty()){
        size--;
        nodo = head;
        head = head->next;
        delete nodo;
    }else{
        throw std::length_error("List is Empty");
    }
}

template<typename Data>
Data List<Data>::FrontNRemove(){
    Data info;
    Node * nodo = new Node();
    if(!LinearContainer<Data>::Empty()){
        size--;
        nodo = head;
        head = head->next;
        info = nodo->info;
        delete nodo;
        return info;
    }else{
        throw std::length_error("List is Empty");
    }

}

template<typename Data>
void List<Data>::InsertAtFront(const Data& dato) noexcept{
    size++;
    Node * nodo = new Node(dato);
    nodo->next = head;
    head = nodo;
}

template<typename Data>
void List<Data>::InsertAtFront(Data&& dato) noexcept{
    size++;
    Node * nodo = new Node(std::move(dato));
    nodo->next = head;
    head = nodo;
}

template<typename Data>
void List<Data>::InsertAtBack(const Data& dato) noexcept{
    size++;
    Node * nodo = new Node(dato);
    nodo->next = nullptr;
    Node * tmp = head;
    if(head == nullptr) {
        head = nodo;
    }else{
        while(tmp->next != nullptr){
            tmp = tmp->next;
        }
        tmp->next = nodo;
        tail = nodo;
    }
}

template<typename Data>
void List<Data>::InsertAtBack(Data&& dato) noexcept{
    size++;
    Node * nodo = new Node(std::move(dato));
    nodo->next = nullptr;
    Node * tmp = head;
    if(head == nullptr) {
        head = nodo;
    }else{
        while(tmp->next != nullptr){
            tmp = tmp->next;
        }
        tmp->next = nodo;
        tail = nodo;
    }
}

template<typename Data>
void List<Data>::Clear() noexcept{
    DeleteAll();
}

template<typename Data>
Data& List<Data>::Front()const{
    if(!LinearContainer<Data>::Empty()){
        return head->info;
    }else{
        throw std::length_error("List is Empty");
    }
}

template<typename Data>
Data& List<Data>::Back() const{
    if(!LinearContainer<Data>::Empty()){
        //std::cout<<operator[](size-1)<<"asdasdsa"<<std::endl;
        //return operator[](size-1);
        return tail->info;
    }else{
        throw std::length_error("List is Empty");
    }
}

template<typename Data>
void List<Data>::Map(MapFunctor funct, void* par) {
    MapPreOrder(funct, par);
}

template<typename Data>
void List<Data>::MapPreOrder(MapFunctor funct, void* par) {
    MapPreOrder(funct, par, head);
}

template<typename Data>
void List<Data>::MapPostOrder(MapFunctor funct, void*par) {
    MapPostOrder(funct, par, head);
}

template<typename Data>
void List<Data>::Fold(FoldFunctor funct, const void* par, void* accumulator) const{
    FoldPreOrder(funct, par, accumulator);
}

template<typename Data>
void List<Data>::FoldPreOrder(FoldFunctor funct, const void*par, void*accumulator) const {
    FoldPreOrder(funct, par, accumulator, head);
}

template<typename Data>
void List<Data>::FoldPostOrder(FoldFunctor funct, const void*par, void*accumulator) const {
    FoldPostOrder(funct, par, accumulator, head);
}

template<typename Data>
void List<Data>::MapPreOrder(MapFunctor funct, void*par, Node*nodo) {
    for (; nodo != nullptr; nodo = nodo->next)
    {
        funct(nodo->info, par);
    } 
}

template<typename Data>
void List<Data>::MapPostOrder(MapFunctor funct, void*par, Node*nodo) {
    if(nodo != nullptr){
        MapPostOrder(funct, par, nodo->next);
        funct(nodo->info, par);
    }
}

template<typename Data>
void List<Data>::FoldPreOrder(FoldFunctor funct, const void*par, void*accumulator, Node* nodo) const {
    for (; nodo != nullptr; nodo = nodo->next)
    {
        funct(nodo->info, par, accumulator);
    } 
}

template<typename Data>
void List<Data>::FoldPostOrder(FoldFunctor funct, const void*par, void*accumulator, Node* nodo) const {
    if(nodo != nullptr){
        FoldPostOrder(funct, par, accumulator, nodo->next);
        funct(nodo->info, par, accumulator);
    }
}



}