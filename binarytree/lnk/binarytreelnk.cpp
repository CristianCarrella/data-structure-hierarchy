
namespace lasd {

template<typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const NodeLnk& nodo){
    info = nodo.info;
    left_son = nodo.left_son;
    right_son = nodo.right_son;
}
template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::operator=(const NodeLnk& nodo){
    info = nodo.info;
    left_son = nodo.left_son;
    right_son = nodo.right_son;
    return *this;
}

template<typename Data>
BinaryTreeLnk<Data>::NodeLnk::~NodeLnk(){
    left_son = nullptr;
    right_son = nullptr;
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::operator=(NodeLnk&& nodo){
    std::swap(info, nodo.info);
    std::swap(left_son, nodo.left_son);
    std::swap(right_son, nodo.right_son);
    return *this;
}

template<typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(NodeLnk&& nodo){
    std::swap(info, nodo.info);
    std::swap(left_son, nodo.left_son);
    std::swap(right_son, nodo.right_son);
}

template<typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const Data& info){
    this->info = info;
    this->left_son = nullptr;
    this->right_son = nullptr;
}

template<typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(Data&& info){
    std::swap(this->info, info);
    this->left_son = nullptr;
    this->right_son = nullptr;
}


template<typename Data>
Data& BinaryTreeLnk<Data>::NodeLnk::Element() noexcept{
    return info;
}

template<typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::IsLeaf() const noexcept{
    if(!(HasLeftChild() && HasRightChild()))
        return true;
    return false;
}

template<typename Data>
const Data& BinaryTreeLnk<Data>::NodeLnk::Element() const noexcept{
    return info;
}

template<typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasLeftChild() const noexcept{
    if(left_son != nullptr)
        return true;
    return false;
}

template<typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept{
    if(right_son != nullptr)
        return true;
    return false;
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild(){
    if(HasLeftChild())
        return *left_son;
    else
        throw std::out_of_range("Out of range");
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild(){
    if(HasRightChild())
        return *right_son;
    else
        throw std::out_of_range("Out of range");
}

/* Binary Tree */
template<typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const LinearContainer<Data>&container){
    size = container.Size();
    root = new NodeLnk(container[0]);
    createTree(root, 0, container);
}

template<typename Data>
void BinaryTreeLnk<Data>::createTree(NodeLnk* node, int i, const LinearContainer<Data>& arr) {
	if (node != nullptr) {
	    if (2 * i + 1 < size) {
	        node->left_son = new NodeLnk(arr[2 * i + 1]);
	        createTree(node->left_son, 2 * i + 1, arr);
	    }
	
	    if (2 * i + 2 < size) {
	        node->right_son = new NodeLnk(arr[2 * i + 2]);
	        createTree(node->right_son, 2 * i + 2, arr);
	    }
	}
}

template<typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data>& tree){
    Clear();
    size = tree.size;
    copyTree(tree.root, root);
    return *this;
}

template<typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk&&tree){
    Clear();
    std::swap(size, tree.size);
    std::swap(root, tree.root);
    return *this;
}


template<typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data>& tree){
    Clear();
    size = tree.size;
    copyTree(tree.root, root);
}

template<typename Data>
void BinaryTreeLnk<Data>::copyTree(NodeLnk * root1, NodeLnk *& root2){
    if(root1 == nullptr)
        root2 = nullptr;
    else {
        root2 = new NodeLnk(root1->Element());
        copyTree(root1->left_son, root2->left_son);
        copyTree(root1->right_son, root2->right_son);
    }
}

template<typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data>&& tree){
    Clear();
    std::swap(size, tree.size);
    std::swap(root, tree.root);
}


template<typename Data>
BinaryTreeLnk<Data>::~BinaryTreeLnk(){
    Clear();
}

template<typename Data>
void BinaryTreeLnk<Data>::Clear() noexcept{
    if(root != nullptr){
        Delete(root);
        size = 0;
    }
}

template<typename Data>
void BinaryTreeLnk<Data>::Delete(NodeLnk *curr) noexcept{
    if(curr->HasLeftChild() || curr->HasRightChild()){
        if(curr->HasLeftChild())
            Delete(&curr->LeftChild());
        if(curr->HasRightChild())
            Delete(&curr->RightChild());
        delete(curr);
        root = nullptr;
    }
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() const{
    if(size != 0)
        return *root;
    else
        throw std::length_error("Tree is Empty");
}

}
