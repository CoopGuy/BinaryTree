#include "BinaryTree.h"
#include <exception>
#include <sstream>

// Following functions deal with I/O of the tree
template <typename T>
void BinaryTree<T>::InsertH( T *ValueToInsert, Node *tRoot )
{
    if ( *tRoot->value > *ValueToInsert )
    {
        if ( !tRoot->left )
        {
            tRoot->left = new Node( ValueToInsert );
            tRoot->lHeight++;
        }
        else
        {
            InsertH( ValueToInsert, tRoot->left );
            tRoot->lHeight = 1 + std::max( tRoot->left->lHeight, tRoot->left->rHeight );
        }
    }
    else if ( *tRoot->value < *ValueToInsert )
    {
        if ( !tRoot->right )
        {
            tRoot->right = new Node( ValueToInsert );
            tRoot->rHeight++;
        }
        else
        {
            InsertH( ValueToInsert, tRoot->right );
            tRoot->rHeight = 1 + std::max( tRoot->right->lHeight, tRoot->right->rHeight );
        }
    }
    else
    {
        std::stringstream exc;
        exc << "Insert: Value " << *ValueToInsert << " already in tree\nLine: " << __LINE__ << "\nFile: " << __FILE__;
        throw std::exception( exc.str().c_str() );
    }

    if ( tRoot->left && std::abs( tRoot->left->lHeight - tRoot->left->rHeight ) > 1 )
    {
        Balance( tRoot->left );
        tRoot->setHeight( Node::direction::dleft );
    }
    if ( tRoot->right && std::abs( tRoot->right->lHeight - tRoot->right->rHeight ) > 1 )
    {
        Balance( tRoot->right );
        tRoot->setHeight( Node::direction::dright );
    }
}

template <typename T>
void BinaryTree<T>::Insert( T *ValueToInsert )
{
    if ( head == nullptr )head = new Node( ValueToInsert );
    else InsertH( ValueToInsert, head );
    if ( std::abs( head->lHeight - head->rHeight ) > 1 ) Balance( head );
}

template <typename T>
typename BinaryTree<T>::Node *BinaryTree<T>::Remove( T *ValueToRemove )
{
    /*
    Cases reference:
    Node has no children
    Node has one child
    Node has two children
    */
    Node *res;
    Node **ptrToNodeWithVal = addrFind( ValueToRemove );
    if ( !(*ptrToNodeWithVal)->left && !(*ptrToNodeWithVal)->right )
    {
        res = *ptrToNodeWithVal;
        *ptrToNodeWithVal = nullptr;
        
    }
    else if ( ( *ptrToNodeWithVal )->left && ( *ptrToNodeWithVal )->right )
    {
        // find next highest val in subtree of children and have it assume the place of the node being removed
    }
    else // Node has only one child
    {
        res = *ptrToNodeWithVal;
        *ptrToNodeWithVal = ( *ptrToNodeWithVal )->left == nullptr ? ( *ptrToNodeWithVal )->right : ( *ptrToNodeWithVal )->left;
    }
    return res;
}

template <typename T>
typename BinaryTree<T>::Node **BinaryTree<T>::addrFind( T* ValueToFind )
{
    Node **temp = &head;

    while ( !( *temp == nullptr || *(*temp)->value == *ValueToFind ) )
    {
             if ( *( *temp )->value < *ValueToFind )temp = &( ( *temp )->right );
        else if ( *( *temp )->value > *ValueToFind )temp = &( ( *temp )->left  );
    }
    return temp;
}

template <typename T>
typename BinaryTree<T>::Node *BinaryTree<T>::FindNextLower()
{

}

template <typename T>
typename BinaryTree<T>::Node *BinaryTree<T>::Find( T* ValueToFind )
{
    Node *temp = head;
    while ( !( temp == nullptr || *temp->value == *ValueToFind ) )
    {
             if ( *temp->value < *ValueToFind )temp = temp->right;
        else if ( *temp->value > *ValueToFind )temp = temp->left;
    }
    return temp;
}

// Following functions balance (or help balance) an unbalanced tree
template <typename T>
void BinaryTree<T>::Balance( Node *&parentsptr )
{
    if ( parentsptr->lHeight > parentsptr->rHeight )
    {
        if ( parentsptr->left->lHeight > parentsptr->left->rHeight )
            RotateLeftLeft( parentsptr );
        else
            RotateLeftRight( parentsptr );
    }
    else
    {
        if ( parentsptr->right->lHeight > parentsptr->right->rHeight )
            RotateRightLeft( parentsptr );
        else
            RotateRightRight( parentsptr );
    }
}

template<typename T>
void BinaryTree<T>::RotateLeftLeft( Node *&parentsptr )
{
    // rotate the nodes
    Node *unbalancedNode = parentsptr;
    parentsptr = unbalancedNode->left;
    unbalancedNode->left = parentsptr->right;
    parentsptr->right = unbalancedNode;

    //re-set the heights that may have changed
    parentsptr->right->setHeight( Node::direction::dleft );
    parentsptr->setHeight( Node::direction::dright );
}

template<typename T>
void BinaryTree<T>::RotateRightRight( Node *&parentsptr )
{
    // rotate the nodes
    Node *unbalancedNode = parentsptr;
    parentsptr = unbalancedNode->right;
    unbalancedNode->right = parentsptr->left;
    parentsptr->left = unbalancedNode;
    
    //re-set the heights that may have changed
    parentsptr->left->setHeight( Node::direction::dright );
    parentsptr->setHeight( Node::direction::dleft );
}

template<typename T>
void BinaryTree<T>::RotateLeftRight( Node *&parentsptr )
{
    // rotate the nodes
    Node *b = parentsptr->left->right->left;
    Node *c = parentsptr->left->right->right;
    parentsptr->left->right->right = parentsptr;
    parentsptr->left->right->left = parentsptr->left;
    parentsptr = parentsptr->left->right;
    parentsptr->left->right = b;
    parentsptr->right->left = c;

    //re-set the heights that may have changed
    parentsptr->left->setHeight( Node::direction::dright );
    parentsptr->right->setHeight( Node::direction::dleft );
    parentsptr->setHeight( Node::direction::dleft );
    parentsptr->setHeight( Node::direction::dright );
}

template <typename T>
void BinaryTree<T>::RotateRightLeft( Node *&parentsptr )
{
    // rotate the nodes
    Node *b = parentsptr->right->left->left;
    Node *c = parentsptr->right->left->right;
    parentsptr->right->left->left = parentsptr;
    parentsptr->right->left->right = parentsptr->right;
    parentsptr = parentsptr->right->left;
    parentsptr->left->right = b;
    parentsptr->right->left = c;

    //re-set the heights that may have changed
    parentsptr->right->setHeight( Node::direction::dleft );
    parentsptr->left->setHeight( Node::direction::dright );
    parentsptr->setHeight( Node::direction::dleft );
    parentsptr->setHeight( Node::direction::dright );
}

// Following functions convert (or help convert) the tree into an array
template <typename T>
void BinaryTree<T>::AddAscending( BinaryTree<T>::Node **arr, BinaryTree<T>::Node *top, int &ind )
{
    if ( top->left )AddAscending( arr, top->left, ind );
    arr[ind] = top;
    ind++;
    if ( top->right )AddAscending( arr, top->right, ind );
}

template <typename T>
void BinaryTree<T>::AddDescending( BinaryTree<T>::Node **arr, BinaryTree<T>::Node *top, int &ind )
{
    if ( top->right )AddDescending( arr, top->right, ind );
    arr[ind] = top;
    ind++;
    if ( top->left )AddDescending( arr, top->left, ind );
}

template <typename T>
typename BinaryTree<T>::Node **BinaryTree<T>::GetAllDescending()
{
    Node **arr = new Node *[Size()];
    int a = 0;
    AddDescending( arr, head, a );
    return arr;
}

template <typename T>
typename BinaryTree<T>::Node **BinaryTree<T>::GetAllAscending()
{
    Node **arr = new Node *[Size()];
    int a = 0;
    AddAscending( arr, head, a );
    return arr;
}