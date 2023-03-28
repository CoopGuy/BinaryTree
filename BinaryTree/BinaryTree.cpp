#include "BinaryTree.h"
#include <exception>
#include <sstream>

// Following functions deal with I/O of the tree
template <typename T>
void BinaryTree<T>::Insert( T* ValueToInsert )
{
    /* 
    
    For Reference:
      treeLocationTracker : pointer to place we want to insert a pointer to a node of our value
     *treeLocationTracker : variable that we want to set to point to a node object of our value
    **treeLocationTracker : variable pointing to a node that is already in place where we want to insert our value
    
    */

    // start by wanting to insert at head
    Node **treeLocationTracker = &head;
    Node *NodeToBeInserted = new Node( ValueToInsert );

    do
    {
        // check if the place we want to insert is null 
        // (this starts at head (if the first deref causes a null ptr deref then msg the gcc maintainers because &head (address of a class instance field) returned a null ptr))
        if ( !*treeLocationTracker )
        {
            // if the spot we want to insert is free we insert the thing
            *treeLocationTracker = NodeToBeInserted;
        }
        else if ( *( **treeLocationTracker ).value > *ValueToInsert )
        {
            // if the value is less than the value at the place we want to insert then we want to insert to the left of that value
            treeLocationTracker = &( ( **treeLocationTracker ).left );
        }
        else if ( *( **treeLocationTracker ).value < *ValueToInsert )
        {
            // if the value is greater than the value at the place we want to insert then we want to insert to the right of that value
            treeLocationTracker = &( ( **treeLocationTracker ).right );
        }

        //exception handling
        else //( *( **treeLocationTracker ).value == *ValueToInsert )
        {
            // if the value is already in the list then throw an exception
            std::stringstream exc;
            exc << "Insert: Value " << *NodeToBeInserted->value << " already in tree\nLine: " << __LINE__ << "\nFile: " << __FILE__;
            delete NodeToBeInserted;
            throw std::exception( exc.str().c_str() );
        }
    } while ( *treeLocationTracker != NodeToBeInserted );
}

template <typename T>
typename BinaryTree<T>::Node *BinaryTree<T>::Remove( T *ValueToRemove )
{

}

template <typename T>
typename BinaryTree<T>::Node *BinaryTree<T>::Find(T* ValueToFind)
{

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