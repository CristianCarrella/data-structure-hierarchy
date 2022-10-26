
namespace lasd {

template<typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(Vector<BinaryTreeVec<Data>::NodeVec*>& vec, ulong pos, const Data& info) : vect(vec){
    this->pos = pos;
    this->info = info;
}

template<typename Data>
void BinaryTreeVec<Data>::NodeVec::printVect(){
     for (ulong i = 0; i < vect.Size(); i++)
    {
        std::cout<<vect[i]<<std::endl;
    }
    std::cout<<std::endl;
}

template<typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(Vector<BinaryTreeVec<Data>::NodeVec*>& vec, ulong pos, Data&& info) : vect(vec) {
    this->pos = pos;
    std::swap(this.info, info);
}

template<typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(const NodeVec& nodo){
    this->vect = nodo.vect;
    this->pos = nodo.pos;
    this->info = nodo.info;
}


template<typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(NodeVec&& nodo){
    std::swap(this->vect, nodo.vect);
    std::swap(this->pos, nodo.pos);
    std::swap(this->info, nodo.info);
}

template<typename Data>
Data& BinaryTreeVec<Data>::NodeVec::Element() noexcept{
    return info;
}

template<typename Data>
const Data& BinaryTreeVec<Data>::NodeVec::Element() const noexcept{
    return info;
}

template<typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept{
    if(2 * pos + 1 < vect.Size()){
        if(vect[2 * pos + 1] != nullptr)
            return true;
    }
    return false;
}

template<typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept{
    if(2 * pos + 2 < vect.Size()){
        if(vect[2* pos + 2] != nullptr)
            return true;
    }
    return false;
}

template<typename Data>
bool BinaryTreeVec<Data>::NodeVec::IsLeaf() const noexcept{
    if(!(HasLeftChild() && HasRightChild()))
        return true;
    return false;
}

template<typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild(){
    if(HasLeftChild())
        return *vect[2 * pos + 1];
    else
        throw std::out_of_range("Out of range");
}


template<typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild(){
    if(HasRightChild())
        return *vect[2 * pos + 2];
    else
        throw std::out_of_range("Out of range");
}

template<typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const LinearContainer<Data> &container){
    Elements.Resize(container.Size());
    for (ulong i = 0; i < container.Size(); i++)
        Elements[i] = new NodeVec(Elements, i, container[i]);
    size = container.Size();
}

template<typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& tree){
    Clear();
    Elements.Resize(tree.size);
    Elements = tree.Elements;
    size = tree.size;
}

template<typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&& tree){
    Clear();
    Elements.Resize(tree.size);
    std::swap(Elements, tree.Elements);
    std::swap(size, tree.size);
}

template<typename Data>
BinaryTreeVec<Data>::~BinaryTreeVec(){
    Clear();
}

template<typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data>& tree){
    Clear();
    Elements.Resize(tree.size);
    Elements = tree.Elements;
    size = tree.size;
    return *this;
}

template<typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data>&& tree){
    Clear();
    Elements.Resize(tree.size);
    std::swap(Elements, tree.Elements);
    std::swap(size, tree.size);
    return *this;
}

template<typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const{
    if(!Container::Empty())
        return *Elements[0];
    else
        throw std::length_error("Tree is Empty");
}

template<typename Data>
void BinaryTreeVec<Data>::Clear() noexcept{
    Elements.Clear();
    Elements.Resize(0);
    size = 0;
}

template<typename Data>
void BinaryTreeVec<Data>::MapBreadth(MapFunctor funct, void* par){
    for (ulong i = 0; i < size; ++i)
        funct(Elements[i]->Element(), par);  
}

template<typename Data>
void BinaryTreeVec<Data>::FoldBreadth(FoldFunctor funct, const void* acc, void* par) const{
    for (ulong i = 0; i < size; ++i)
        funct(Elements[i]->Element(), acc, par);  
}

}
