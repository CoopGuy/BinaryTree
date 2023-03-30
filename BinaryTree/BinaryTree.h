#pragma once
#include <algorithm>

template <typename T>
class BinaryTree
{
private:
	class Node
	{
	public:
		T *value;
		Node *left, *right;
		int lHeight, rHeight;
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
	};

private:
	Node *head;

	void AddAscending( BinaryTree<T>::Node **arr, BinaryTree<T>::Node *top, int &ind );
	void AddDescending( BinaryTree<T>::Node **arr, BinaryTree<T>::Node *top, int &ind );
	
	void InsertH( T *ValueToInsert, Node *tRoot );
	
	Node **addrFind( T* ValueToFind );
	Node *FindNextLower();

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

	void RotateLeftLeft( Node *&parentsptr );
	void RotateRightRight( Node *&parentsptr );
	void RotateLeftRight( Node *&parent );
	void RotateRightLeft( Node *&parent );

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