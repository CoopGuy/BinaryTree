#pragma once
#include <algorithm>

template <typename T>
class BinaryTree
{
public:
	class Node
	{
	private:
		void setLHeight()
		{
			if ( !left )lHeight = 0;
			else lHeight = 1 + std::max( left->lHeight, left->rHeight );
		}
		void setRHeight()
		{
			if ( !right )rHeight = 0;
			else rHeight = 1 + std::max( right->lHeight, right->rHeight );
		}
	
	public:
		T *value;
		Node *left, *right;
		int lHeight, rHeight;
	public:
		Node( T *val ) : value( val ), left( nullptr ), right( nullptr ), lHeight(0), rHeight(0) {};
		~Node() { delete value; };
		enum direction { dleft, dright };
		void setHeight( direction dir )
		{
			if ( dir == dleft )
			{
				setLHeight();
			}
			else // if dir == right
			{
				setRHeight();
			}
		}
		bool isLeaf() { return !left && !right; };
		bool isBalanced()
		{
			bool res = true;
			if ( left )res = res && left->isBalanced();
			if ( right )res = res && right->isBalanced();
			res = res && std::abs( lHeight - rHeight ) < 2;
			return res;
		}
		void print( int depth = 0 );
	};

private:
	Node *head;

	void AddAscending( BinaryTree<T>::Node **arr, BinaryTree<T>::Node *top, int &ind );
	void AddDescending( BinaryTree<T>::Node **arr, BinaryTree<T>::Node *top, int &ind );
	
	void InsertH( T *ValueToInsert, Node *tRoot );

	Node *RemoveH( T *ValueToRemove, Node *&root );
	Node *RemoveNextHighest( Node *&root );

	void EmptyTreeH( Node *&ptr )
	{
		if ( !ptr )return;
		EmptyTreeH( ptr->left );
		EmptyTreeH( ptr->right );
		delete ptr;
		ptr = nullptr;
	}
	int SizeH( Node *ptr )
	{
		if ( !ptr )return 0;
		return 1 + SizeH( ptr->left ) + SizeH( ptr->right );
	}
	
	void Balance( Node *&parent );

	void RotateLeftLeft  ( Node *&parentsptr );
	void RotateRightRight( Node *&parentsptr );
	void RotateLeftRight ( Node *&parentsptr );
	void RotateRightLeft ( Node *&parentsptr );

public:
	BinaryTree() : head( nullptr ) {};
	~BinaryTree() { EmptyTree(); };
	void EmptyTree() { EmptyTreeH( head ); };

	int Size() { return SizeH( head ); };

	void Insert( T *ValueToInsert );
	Node *Remove( T *ValueToRemove );
	Node *Find( T *ValueToFind );

	Node **GetAllAscending();
	Node **GetAllDescending();

	//debugging
	bool isBalanced() { return head->isBalanced(); };
	void print() { if ( head )head->print(); };
	
};