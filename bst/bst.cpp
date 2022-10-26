
namespace lasd {

template<typename Data>
int partition (Vector<Data>& arr, int low, int high)
{
    Data pivot = arr[high];
    int i = (low - 1);
 
    for (int j = low; j <= high - 1; j++){
        if (arr[j] < pivot){
            i++; 
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

template<typename Data>
void quickSort(Vector<Data>& arr, int low, int high)
{
    if (low < high){
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

template<typename Data>
BST<Data>::BST(const LinearContainer<Data>& container){
    /*Costruzione albero più efficiente - evita costruzioni alberi di genere*/
    // Vector<Data> v(container);
    // quickSort(v, 0, v.Size() - 1);
    // root = createBST(v, 0, v.Size() - 1);
    for (ulong i = 0; i < container.Size(); i++)
        Insert(container[i]);
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* BST<Data>::createBST(Vector<Data>& vect, long low, long high){
    if (low > high)
        return nullptr;

    long i = (high + low)/2;
    typename BinaryTreeLnk<Data>::NodeLnk *temp = new typename BinaryTreeLnk<Data>::NodeLnk(vect[i]);
    temp->left_son = createBST(vect, low, i - 1);
    temp->right_son = createBST(vect, i + 1, high);

    return temp;
}

template<typename Data>
BST<Data>::BST(const BST<Data>& bst) : BinaryTreeLnk<Data>(bst){}

template<typename Data>
BST<Data>::BST(BST<Data>&& bst) : BinaryTreeLnk<Data>(std::move(bst)){}

template<typename Data>
BST<Data>& BST<Data>::operator=(const BST& bst){
    BinaryTreeLnk<Data>::operator=(bst);
    return *this;
}

template<typename Data>
BST<Data>& BST<Data>::operator=(BST&& bst){
    BinaryTreeLnk<Data>::operator=(std::move(bst));
    return *this;
}

template<typename Data>
bool BST<Data>::operator==(const BST<Data>& bst) const noexcept{
    BTInOrderIterator<Data> it1(bst);
    BTInOrderIterator<Data> it2(*this);
    if(bst.size == size){
        for (ulong i = 0; i < size; i++)
        {
            if(*it1 != *it2)
                return false;
            ++it1; 
            ++it2;
        }
        return true;
    }
    return false;
}

template<typename Data>
bool BST<Data>::operator!=(const BST<Data>& bst) const noexcept{
    return !(*this == bst);
}

template<typename Data>
Data& BST<Data>::Min() const{
    if(size != 0){
        return FindPointerToMin(root)->Element();
    }
    else
        throw std::length_error("BST is empty!");
}

template<typename Data>
Data BST<Data>::MinNRemove(){
    Data min;
    if(size != 0){
        NodeLnk *& tmp = FindPointerToMin(root);
        if(tmp != nullptr)
            min = DataNDelete(tmp);     
        return min;
    }
    else
        throw std::length_error("BST is empty!");
}

template<typename Data>
void BST<Data>::RemoveMin(){
    NodeLnk * detachedNode;
    if(size != 0){
        NodeLnk *& tmp = FindPointerToMin(root);
        if(tmp != nullptr)
            detachedNode = Detach(tmp);    
        delete(detachedNode); 
    }
    else
        throw std::length_error("BST is empty!");
}

template<typename Data>
Data& BST<Data>::Max() const{
    if(size != 0)
        return FindPointerToMax(root)->Element();
    else
        throw std::length_error("BST is empty!");
}

template<typename Data>
Data BST<Data>::MaxNRemove(){
    Data max;
    if(size != 0){
        NodeLnk *& tmp = FindPointerToMax(root);
        if(tmp != nullptr)
            max = DataNDelete(tmp);     
        return max;
    }
    else
        throw std::length_error("BST is empty!");
}

template<typename Data>
void BST<Data>::RemoveMax(){
    NodeLnk * detachedNode;
    if(size != 0){
        NodeLnk *& tmp = FindPointerToMax(root);
        if(tmp != nullptr)
            detachedNode = Detach(tmp);    
        delete(detachedNode); 
    }
    else
        throw std::length_error("BST is empty!");
}

template<typename Data>
Data& BST<Data>::Predecessor(const Data& info) const{
    NodeLnk* const* tmp = FindPointerToPredecessor(root, info);
    if(tmp != nullptr)
        return (*tmp)->Element();
    else
        throw std::length_error("Predecessor Not Found");
}

template<typename Data>
Data BST<Data>::PredecessorNRemove(const Data& info){
    Data result;
    if(size != 0){
        NodeLnk ** tmp = FindPointerToPredecessor(root, info);
        if(tmp != nullptr)
            result = DataNDelete(*tmp);     
        return result;
    }
    else
        throw std::length_error("BST is empty!");
}

template<typename Data>
void BST<Data>::RemovePredecessor(const Data& info){
    NodeLnk * detachedNode;
    if(size != 0){
        NodeLnk ** tmp = FindPointerToPredecessor(root, info);
        if(tmp != nullptr)
            detachedNode = Detach(*tmp);    
            delete(detachedNode);    
    }else{
        throw std::length_error("BST is empty!");
    }
}

template<typename Data>
Data& BST<Data>::Successor(const Data& info) const{
    NodeLnk* const* tmp = FindPointerToSuccessor(root, info);
    if(tmp != nullptr)
        return (*tmp)->Element();
    else
        throw std::length_error("Successor Not Found");
}

template<typename Data>
Data BST<Data>::SuccessorNRemove(const Data& info){
    Data result;
    if(size != 0){
        NodeLnk ** tmp = FindPointerToSuccessor(root, info);
        if(tmp != nullptr)
            result = DataNDelete(*tmp);     
        return result;
    }
    else
        throw std::length_error("BST is empty!");
}

template<typename Data>
void BST<Data>::RemoveSuccessor(const Data& info){
    NodeLnk * detachedNode;
    if(size != 0){
        NodeLnk ** tmp = FindPointerToSuccessor(root, info);
        if(tmp != nullptr)
            detachedNode = Detach(*tmp);    
            delete(detachedNode);    
    }else{
        throw std::length_error("BST is empty!");
    }
}

template<typename Data>
bool BST<Data>::Insert(const Data& info) noexcept{
NodeLnk * newNodo = new NodeLnk(info);
    if(size == 0){
        size++;
        root = newNodo;
        return true;
    }
    else{
        ulong oldSize = size;
        Insertion(newNodo, root);
        //BinaryTreeLnk<Data>::printTree("", &BinaryTreeLnk<Data>::Root(), false);

        if(oldSize + 1 == size)
            return true;
        else
            return false;
    }
}

template<typename Data>
bool BST<Data>::Insert(Data&& info) noexcept{
    NodeLnk * newNodo = new NodeLnk(std::move(info));
    if(size == 0){
        size++;
        root = newNodo;
        return true;
    }
    else{
        ulong oldSize = size;
        Insertion(newNodo, root);
        //BinaryTreeLnk<Data>::printTree("", &BinaryTreeLnk<Data>::Root(), false);

        if(oldSize + 1 == size)
            return true;
        else
            return false;
    }
}

template<typename Data>
bool BST<Data>::Remove(const Data& info) noexcept{
    //BinaryTreeLnk<Data>::printTree("", &BinaryTreeLnk<Data>::Root(), false);
    NodeLnk *& tmp = FindPointerTo(root, info);
    NodeLnk * detachedNode;
    if(tmp != nullptr){
        delete(Detach(tmp));
        return true;
    }
    return false;
}

template<typename Data>
bool BST<Data>::Exists(const Data& info) const noexcept{
    if(FindPointerTo(root, info) != nullptr)
        return true;
    return false;
}

template<typename Data>
Data BST<Data>::DataNDelete(typename BinaryTreeLnk<Data>::NodeLnk*& node){
    NodeLnk * detachedNode;
    Data result;

    if(node != nullptr){
        result = node->info;
        if(node->HasLeftChild() && node->HasRightChild()){
            detachedNode = DetachMin(node);
            node->info = detachedNode->info;
        }
        else if(node->HasLeftChild() && !node->HasRightChild())
            detachedNode = Skip2Left(node);
        else if(!node->HasLeftChild() && node->HasRightChild())
            detachedNode = Skip2Right(node);
        else if(node->IsLeaf()){
            detachedNode = node;
            node = nullptr;
            size--;
        }
    }
    delete(detachedNode);

    return result;    
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* BST<Data>::Detach(typename BinaryTreeLnk<Data>::NodeLnk*& node) noexcept{
    NodeLnk * detachedNode;

    if(node != nullptr){
        if(node->HasLeftChild() && node->HasRightChild()){
            detachedNode = DetachMin(node->right_son);
            node->info = detachedNode->info;
        }
        else if(node->HasLeftChild() && !node->HasRightChild())
            detachedNode = Skip2Left(node);
        else if(!node->HasLeftChild() && node->HasRightChild())
            detachedNode = Skip2Right(node);
        else if(node->IsLeaf()){
            detachedNode = node;
            node = nullptr;
            size--;
        }
    }
    return detachedNode;
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* BST<Data>::DetachMin(typename BinaryTreeLnk<Data>::NodeLnk*& node) noexcept{
    NodeLnk *& minOfSubTree = FindPointerToMin(node);
    NodeLnk * tmp = minOfSubTree;
    if (minOfSubTree->HasRightChild()){
        Skip2Right(minOfSubTree);
        size--;
    }
    else
        minOfSubTree = nullptr;
    
    return tmp;
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* BST<Data>::DetachMax(typename BinaryTreeLnk<Data>::NodeLnk*& node) noexcept{
    NodeLnk *& maxOfSubTree = FindPointerToMax(node);
    NodeLnk * tmp = maxOfSubTree;
    if (maxOfSubTree->HasRightChild()){
        Skip2Left(maxOfSubTree);
        size--;
    }
    else
        maxOfSubTree = nullptr;
    return tmp;    
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* BST<Data>::Insertion(typename BinaryTreeLnk<Data>::NodeLnk* newNodo, typename BinaryTreeLnk<Data>::NodeLnk * current) noexcept{
    if(current != nullptr){
        if(current->Element() < newNodo->Element()){
            current->right_son = Insertion(newNodo, current->right_son);
        }else if(current->Element() > newNodo->Element()){
            current->left_son = Insertion(newNodo, current->left_son);
        }
    }else{
        current = newNodo;
        size++;
    }
    return current;

    // bool found = false;
    // if(current != nullptr){
    //     while(found == false && current != nullptr){
    //         if(current->Element() > newNodo->Element()){
    //             if(current->HasLeftChild())
    //                 current = current->left_son;
    //             else{
    //                 current->left_son = newNodo;
    //                 found = true;
    //             }
    //         }else if(current->Element() < newNodo->Element()){
    //             if(current->HasRightChild())
    //                 current = current->right_son;     
    //             else{
    //                 current->left_son = newNodo; 
    //                 found = true; 
    //             }       
    //         }else{
    //             found = true;
    //         }
    //     }
    // }
    // return nullptr;

}


template<typename Data> //input : riferimento al puntatore a nodo
typename BinaryTreeLnk<Data>::NodeLnk* BST<Data>::Skip2Left(typename BinaryTreeLnk<Data>::NodeLnk*& node) noexcept{
    NodeLnk * current = nullptr;
    if(node != nullptr){
        std::swap(current, node->left_son);
        std::swap(node, current);
        size--;
    }
    return current;
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* BST<Data>::Skip2Right(typename BinaryTreeLnk<Data>::NodeLnk*& node) noexcept{
    NodeLnk * current = nullptr;
    if(node != nullptr){
        std::swap(current, node->right_son);
        std::swap(node, current);
        size--;
    }
    return current;
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk*& BST<Data>::FindPointerToMin(typename BinaryTreeLnk<Data>::NodeLnk*& node) noexcept{
    return const_cast<NodeLnk*&>(static_cast<const BST<Data>*> (this)->FindPointerToMin(node));
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* const& BST<Data>::FindPointerToMin(typename BinaryTreeLnk<Data>::NodeLnk* const& node) const noexcept{
    NodeLnk * const* tmp = &node;
    NodeLnk * current = node;
    if(current != nullptr){
        while(current->HasLeftChild()){
            tmp = &current->left_son;
            current = current->left_son;
        }
    }
    return *tmp;
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk*& BST<Data>::FindPointerToMax(typename BinaryTreeLnk<Data>::NodeLnk*& node) noexcept{
    return const_cast<NodeLnk*&>(static_cast<const BST<Data>*> (this)->FindPointerToMax(node));
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* const& BST<Data>::FindPointerToMax(typename BinaryTreeLnk<Data>::NodeLnk* const& node) const noexcept{
    NodeLnk * const* tmp = &node;
    NodeLnk * current = node;
    if(current != nullptr){
        while(current->HasRightChild()){
            tmp = &current->right_son;
            current = current->right_son;
        }
    }
    return *tmp;    
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk*& BST<Data>::FindPointerTo(typename BinaryTreeLnk<Data>::NodeLnk*& node, const Data dato) noexcept{
    return const_cast<NodeLnk*&>(static_cast<const BST<Data>*> (this)->FindPointerTo(node, dato));
}


template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* const& BST<Data>::FindPointerTo(typename BinaryTreeLnk<Data>::NodeLnk* const& node, const Data dato) const noexcept{
    NodeLnk * const* tmp = &node;
    NodeLnk * current = node;
    bool found = false;
    if(current != nullptr){
        while(found == false && current != nullptr){
            if(current->Element() > dato){
                    tmp = &current->left_son;
                    current = current->left_son;
            }else if(current->Element() < dato){
                    tmp = &current->right_son;
                    current = current->right_son;              
            }else{
                found = true;
            }
        }
    }

    return *tmp; 
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk** BST<Data>::FindPointerToPredecessor(typename BinaryTreeLnk<Data>::NodeLnk*& node, const Data dato) noexcept{
    return const_cast<NodeLnk**>(static_cast<const BST<Data>*> (this)->FindPointerToPredecessor(node, dato));
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* const* BST<Data>::FindPointerToPredecessor(typename BinaryTreeLnk<Data>::NodeLnk* const& node, const Data data) const noexcept{
    NodeLnk* const* estimation = nullptr;
    NodeLnk* const* tmp = &node;
    
    while(true){
        NodeLnk& current = **tmp;
        if(current.info < data){
            estimation = tmp;
            if(!current.HasRightChild())
                return estimation;
            else
                tmp = &current.right_son;        
        }else if(current.info > data){
            if(!current.HasLeftChild())
                return estimation;
            else
                tmp = &current.left_son;                
        }else{
            if(current.HasLeftChild())
                estimation = &FindPointerToMax(current.left_son);
            return estimation;
        }
    }
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk** BST<Data>::FindPointerToSuccessor(typename BinaryTreeLnk<Data>::NodeLnk*& node,const Data dato) noexcept{
    return const_cast<NodeLnk**>(static_cast<const BST<Data>*> (this)->FindPointerToSuccessor(node, dato));
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* const* BST<Data>::FindPointerToSuccessor(typename BinaryTreeLnk<Data>::NodeLnk* const& node, const Data data) const noexcept{
    NodeLnk* const* estimation = nullptr;
    NodeLnk* const* tmp = &node;
    
    while(true){
        NodeLnk& current = **tmp;
        if(current.info > data){
            estimation = tmp;
            if(!current.HasLeftChild())
                return estimation;
            else
                tmp = &current.left_son;        
        }else if(current.info < data){
            if(!current.HasRightChild())
                return estimation;
            else
                tmp = &current.right_son;                
        }else{
            if(current.HasRightChild())
                estimation = &FindPointerToMin(current.right_son);
            return estimation;
        }
    }
 
}


}
