#pragma once

template <typename T>
class BinaryTree
{
private:
	class Node
	{
	public:
		Node *left, *right;
		T *value;

	public:
		Node( T *val ) : value( val ), left( nullptr ), right( nullptr ) {};
		~Node() { delete value; };
	};

private:
	Node *head;

	void AddAscending( BinaryTree<T>::Node **arr, BinaryTree<T>::Node *top, int &ind );
	void AddDescending( BinaryTree<T>::Node **arr, BinaryTree<T>::Node *top, int &ind );
	void EmptyTreeH( Node *&ptr )
	{
		if ( !ptr )return;
		EmptyTreeH( ptr->left );
		EmptyTreeH( ptr->right );
		delete ptr;
		ptr = nullptr;
	}
	int SizeH( Node *ptr = head )
	{
		if ( !ptr )return 0;
		return 1 + SizeH( ptr->left ) + SizeH( ptr->right );
	}
public:
	BinaryTree() : head( nullptr ) {};
	~BinaryTree() { EmptyTree(); };

	void EmptyTree() { EmptyTreeH( head ); };
	int Size() { SizeH( head ); };


	void Insert( T *ValueToInsert );
	Node *Remove( T *ValueToRemove );
	Node *Find( T *ValueToFind );
	Node **GetAllAscending();
	Node **GetAllDescending();
	
};