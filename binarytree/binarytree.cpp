
#include "../queue/lst/queuelst.hpp"
namespace lasd {

template<typename Data>
bool BinaryTree<Data>::Node::operator==(const Node& nodo) const noexcept{
    return Element() == nodo.Element();
}


template<typename Data>
bool BinaryTree<Data>::Node::operator!=(const Node& nodo) const noexcept{
    return !(*this == nodo);
}

template<typename Data>
bool BinaryTree<Data>::operator==(const BinaryTree& tree) const noexcept{
    if(size == tree.size && size != 0)
        return Compare(Root(), tree.Root());
    else if(size == tree.size && size == 0)
        return true;
    else
        return false;

}

template<typename Data>
bool BinaryTree<Data>::operator!=(const BinaryTree& tree) const noexcept{
    return !(*this == tree);
}

template<typename Data>
bool BinaryTree<Data>::Compare(Node& current1, Node& current2) const noexcept{
    bool result1 = true, result2 = true;
    if(current1.Element() == current2.Element()){
        if(current1.HasLeftChild() && current2.HasLeftChild())
            result1 = Compare(current1.LeftChild(), current2.LeftChild());
        else if (!(current1.HasLeftChild() && current2.HasLeftChild()))
            result1 = true;
        else
            result1 = false;

        if(current1.HasRightChild()&& current2.HasRightChild() && result1 == true)
            result2 = Compare(current1.RightChild(), current2.RightChild());
        else if (!(current1.HasRightChild() && current2.HasRightChild()))
            result2 = true;
        else
            result2 = false;

        return  result1 && result2;
    }

    return false;
}

template<typename Data>
void BinaryTree<Data>::Map(MapFunctor funct, void* par){
    if(!Container::Empty())
        MapPreOrder(funct, par);
}

template<typename Data>
void BinaryTree<Data>::Fold(FoldFunctor funct, const void* pos, void* acc) const{
    if(!Container::Empty())
        FoldPreOrder(funct, pos, acc);
}

template<typename Data>
void BinaryTree<Data>::MapPreOrder(MapFunctor funct, void* par){
    if(!Container::Empty())
        MapPreOrder(funct, par, Root());

}

template<typename Data>
void BinaryTree<Data>::MapPreOrder(MapFunctor funct, void* par, Node& current){
    funct(current.Element(), par);
    if(current.HasLeftChild())
        MapPreOrder(funct, par, current.LeftChild());
    if(current.HasRightChild())
        MapPreOrder(funct, par, current.RightChild());
}

template<typename Data>
void BinaryTree<Data>::MapPostOrder(MapFunctor funct, void* par){
    if(!Container::Empty())
        MapPostOrder(funct, par, Root());
    
}

template<typename Data>
void BinaryTree<Data>::MapPostOrder(MapFunctor funct, void* par, Node& current){
    if(current.HasLeftChild())
        MapPostOrder(funct, par, current.LeftChild());
    if(current.HasRightChild())
        MapPostOrder(funct, par, current.RightChild());
    funct(current.Element(), par);
}

template<typename Data>
void BinaryTree<Data>::MapInOrder(MapFunctor funct, void* par){
    if(!Container::Empty())
        MapInOrder(funct, par, Root());

    
}

template<typename Data>
void BinaryTree<Data>::MapInOrder(MapFunctor funct, void* par, Node& current){ 
    if(current.HasLeftChild())
        MapInOrder(funct, par, current.LeftChild());
    funct(current.Element(), par);
    if(current.HasRightChild())
        MapInOrder(funct, par, current.RightChild());
}

template<typename Data>
void BinaryTree<Data>::MapBreadth(MapFunctor funct, void* par){
    QueueLst<Node*> queue;
    Node * tmp = &Root();
    queue.Enqueue(tmp);
    while (!queue.Empty())
    {
        tmp = queue.Head();
        funct(tmp->Element(), par);
        if(tmp->HasLeftChild())
            queue.Enqueue(&tmp->LeftChild());
        if(tmp->HasRightChild())
            queue.Enqueue(&tmp->RightChild());
        queue.Dequeue();
    }
}


template<typename Data>
void BinaryTree<Data>::FoldPreOrder(FoldFunctor funct, const void* par, void* acc) const {
    if(!Container::Empty())
        FoldPreOrder(funct, par, acc, Root());
}


template<typename Data>
void BinaryTree<Data>::FoldPreOrder(FoldFunctor funct, const void* par, void* acc, Node& current)const{
    funct(current.Element(), par, acc);
    if(current.HasLeftChild())
        FoldPreOrder(funct, par, acc, current.LeftChild());
    if(current.HasRightChild())
        FoldPreOrder(funct, par, acc, current.RightChild());
}

template<typename Data>
void BinaryTree<Data>::FoldPostOrder(FoldFunctor funct, const void* par, void* acc) const{
    if(!Container::Empty())
        FoldPostOrder(funct, par, acc, Root());
}


template<typename Data>
void BinaryTree<Data>::FoldPostOrder(FoldFunctor funct, const void* par, void* acc, Node& current)const {
    if(current.HasLeftChild())
        FoldPostOrder(funct, par, acc, current.LeftChild());
    if(current.HasRightChild())
        FoldPostOrder(funct, par, acc, current.RightChild());
    funct(current.Element(), par, acc);
}

template<typename Data>
void BinaryTree<Data>::FoldInOrder(FoldFunctor funct, const void* par, void* acc) const{
    if(!Container::Empty())
        FoldInOrder(funct, par, acc, Root());
}

template<typename Data>
void BinaryTree<Data>::FoldInOrder(FoldFunctor funct, const void* par, void* acc, Node& current) const{
    if(current.HasLeftChild())
        FoldInOrder(funct, par, acc, current.LeftChild()); 
    funct(current.Element(), par, acc); 
    if(current.HasRightChild())
        FoldInOrder(funct, par, acc, current.RightChild());
}

template<typename Data>
void BinaryTree<Data>::FoldBreadth(FoldFunctor funct, const void* par, void* acc) const{
    QueueLst<Node*> queue;
    Node * tmp = &Root();
    queue.Enqueue(tmp);
    while (!queue.Empty())
    {
        tmp = queue.Head();
        funct(tmp->Element(), par, acc);
        if(tmp->HasLeftChild())
            queue.Enqueue(&tmp->LeftChild());
        if(tmp->HasRightChild())
            queue.Enqueue(&tmp->RightChild());
        queue.Dequeue();
    }
}

/* PreOrderIterator */
template<typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& tree){
    try
    {
        root = &tree.Root();
    }
    catch(const std::exception& e)
    {
        root = nullptr;
    }
    current = root;
}

template<typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator<Data>& iterator){
    current = iterator.current;
    root = iterator.root;
    stk = iterator.stk;
}

template<typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator<Data>&& iterator){
    std::swap(current, iterator.current);
    root = iterator.root;
    std::swap(iterator.stk, stk);
}

template<typename Data>
Data& BTPreOrderIterator<Data>::operator*() const{
    if(!Terminated()){
        return current->Element();
    }else{
        throw std::out_of_range("Out of range");
    }
}

template<typename Data>
bool BTPreOrderIterator<Data>::Terminated() const noexcept{
    if(current == nullptr)
        return true;
    return false;
}

template<typename Data>
void BTPreOrderIterator<Data>::operator++(){
    if(!Terminated()){
        if(current->HasLeftChild()){
                if(current->HasRightChild())
                    stk.Push(&current->RightChild());
            current = &current->LeftChild();
        }else{
            if(current->HasRightChild())
                current = &current->RightChild();
            else if(!stk.Empty())
                current = stk.TopNPop();
            else 
                current = nullptr;
        }
    }else{
        throw std::out_of_range("Out of range");
    }
}

template<typename Data>
void BTPreOrderIterator<Data>::Reset() noexcept{
    current = root;
    stk.Clear();
}

template<typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data>& it){
    current = it.current;
    root = it.root;
    stk = it.stk;
}

template<typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data>&& iterator){
    std::swap(current, iterator.current);
    root = iterator.root;
    std::swap(iterator.stk, stk);
}

template<typename Data>
bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator<Data>& it) const noexcept{
    if(it.root == root && it.current == current && stk == it.stk)
        return true;
    return false;
}

template<typename Data>
bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator<Data>& it) const noexcept{
    return !(*this == it);
}


/* PostOrderIterator */
template<typename Data>
void BTPostOrderIterator<Data>::LeafFarLeft(){
    if(!Terminated()){
        if(current->HasLeftChild()){
            stk.Push(current);
            current = &current->LeftChild();
            LeafFarLeft();
        }else if(current->HasRightChild()){
            stk.Push(current);
            current = &current->RightChild();
            LeafFarLeft();
        }
    }
}

template<typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& tree){
    try
    {
        root = &tree.Root();
    }
    catch(const std::exception& e)
    {
        root = nullptr;
    }
    current = root;
    // stk.Push(current);
    LeafFarLeft();
}

template<typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator<Data>& iterator){
    current = iterator.current;
    root = iterator.root;
    stk = iterator.stk;
}

template<typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator<Data>&& iterator){
    std::swap(current, iterator.current);
    root = iterator.root;
    std::swap(iterator.stk, stk);
}

template<typename Data>
Data& BTPostOrderIterator<Data>::operator*() const{
    if(!Terminated()){
        return current->Element();
    }else{
        throw std::out_of_range("Out of range");
    }
}

template<typename Data>
bool BTPostOrderIterator<Data>::Terminated() const noexcept{
    if(current == nullptr)
        return true;
    return false;
}

template<typename Data>
void BTPostOrderIterator<Data>::operator++(){
    if(!Terminated()){
        if(!stk.Empty()){
            if(stk.Top()->HasRightChild() && &stk.Top()->RightChild() == current){
                current = stk.TopNPop();
            }
            else if(stk.Top()->HasLeftChild() && &stk.Top()->LeftChild() == current && stk.Top()->HasRightChild()){ 
                current = &stk.Top()->RightChild();
                LeafFarLeft();
            }
            else
                current = stk.TopNPop();
        }
        else
            current = nullptr;
    }
}

template<typename Data>
void BTPostOrderIterator<Data>::Reset() noexcept{
    current = root;
    stk.Clear();
    LeafFarLeft();
}

template<typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator<Data>& it){
    current = it.current;
    root = it.root;
    stk = it.stk;
}

template<typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator<Data>&& iterator){
    std::swap(current, iterator.current);
    root = iterator.root;
    std::swap(iterator.stk, stk);
}

template<typename Data>
bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator<Data>& it) const noexcept{
    if(it.root == root && it.current == current && stk == it.stk)
        return true;
    return false;
}

template<typename Data>
bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator<Data>& it) const noexcept{
    return !(*this == it);
}

/* InOrderIterator */
template<typename Data>
void BTInOrderIterator<Data>::FarLeft(){
    if(!Terminated()){
        while(current->HasLeftChild()){
            stk.Push(current); 
            current = &current->LeftChild();
        }
    }
}

template<typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data>& tree){
    try
    {
        root = &tree.Root();
    }
    catch(const std::exception& e)
    {
        root = nullptr;
    }

    current = root;
    FarLeft();
}

template<typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator<Data>& iterator){
    current = iterator.current;
    root = iterator.root;
    stk = iterator.stk;
}

template<typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator<Data>&& iterator){
    std::swap(current, iterator.current);
    root = iterator.root;
    std::swap(iterator.stk, stk);
}

template<typename Data>
Data& BTInOrderIterator<Data>::operator*() const{
    if(!Terminated()){
        return current->Element();
    }else{
        throw std::out_of_range("Out of range");
    }
}

template<typename Data>
bool BTInOrderIterator<Data>::Terminated() const noexcept{
    if(current == nullptr) 
        return true;
    return false;
}

template<typename Data>
void BTInOrderIterator<Data>::operator++(){
    if(current->HasRightChild()){
        current = &current->RightChild();
        FarLeft();
    }else if(!stk.Empty()){
        current = stk.TopNPop();
    }else{
        current = nullptr;
    }
}

template<typename Data>
void BTInOrderIterator<Data>::Reset() noexcept{
    current = root;
    stk.Clear();
    FarLeft();
}

template<typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(const BTInOrderIterator<Data>& it){
    current = it.current;
    root = it.root;
    stk = it.stk;
}

template<typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(BTInOrderIterator<Data>&& iterator){
    std::swap(current, iterator.current);
    root = iterator.root;
    std::swap(iterator.stk, stk);
}

template<typename Data>
bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator<Data>& it) const noexcept{
    if(it.root == root && it.current == current && stk == it.stk)
        return true;
    return false;
}

template<typename Data>
bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator<Data>& it) const noexcept{
    return !(*this == it);
}

/* BreathOrderIterator */

template<typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& tree){
    try
    {
        root = &tree.Root();
    }
    catch(const std::exception& e)
    {
        root = nullptr;
    }
    current = root;
}

template<typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator<Data>& iterator){
    current = iterator.current;
    root = iterator.root;
    queue = iterator.queue;
}

template<typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator<Data>&& iterator){
    std::swap(current, iterator.current);
    root = iterator.root;
    std::swap(iterator.queue, queue);
}

template<typename Data>
Data& BTBreadthIterator<Data>::operator*() const{
    if(!Terminated())
        return current->Element();
    else
        throw std::out_of_range("Out of range");
}

template<typename Data>
bool BTBreadthIterator<Data>::Terminated() const noexcept{
    if(current == nullptr)
        return true;
    return false;
}

template<typename Data>
void BTBreadthIterator<Data>::operator++(){
    if(!Terminated()){
        if(current != nullptr){
            if(current->HasLeftChild() || current->HasRightChild() || !queue.Empty()){
                if(current->HasLeftChild())
                    queue.Enqueue(&current->LeftChild());
                if(current->HasRightChild())
                    queue.Enqueue(&current->RightChild());
                current = queue.HeadNDequeue();
            }else
                current = nullptr;
        }else{
            throw std::out_of_range("Out of range");
        }
    }
}

template<typename Data>
void BTBreadthIterator<Data>::Reset() noexcept{
    current = root;
    queue.Clear();
}

template<typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator<Data>& it){
    current = it.current;
    root = it.root;
    queue = it.queue;
}

template<typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator<Data>&& it){
    std::swap(current, it.current);
    root = it.root;
    std::swap(it.queue, queue);
}

template<typename Data>
bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator<Data>& it) const noexcept{
    if(it.root == root && it.current == current && queue == it.queue)
        return true;
    return false;
}

template<typename Data>
bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator<Data>& it) const noexcept{
    return !(*this == it);
}

 

}
