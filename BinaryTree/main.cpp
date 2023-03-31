#include "BinaryTree.h"
#include "BinaryTree.cpp"
#include <random>
#include <iostream>

bool inArray( int *arr, int num, int maxind )
{
	for ( int i = 0; i < maxind; i++ ) if ( arr[i] == num ) return false;
	return true;
}

void fillArray( int *arr, int size, int max )
{
	int insert;
	for ( int i = 0; i < size; i++ )
	{
		do
		{
			insert = rand() % max;
		} while ( !inArray( arr, insert, i ) );
		arr[i] = insert;
	}
}

int main()
{
	unsigned seed = 42; // (unsigned) time( NULL );
	srand( seed );
	for ( int j = 0; j < 100000; j++ )
	{
		BinaryTree<int> *bin = new BinaryTree<int>;
		constexpr int ARRSIZE = 100;
		int arr[ARRSIZE] = { -1 };
		fillArray( arr, ARRSIZE, 1000 );

		for ( int i = 0; i < ARRSIZE; i++ )
		{
			try
			{
				bin->Insert( new int(arr[i]) );
				if ( bin->Size() != i + 1 )std::cout << "Error on size j = " << j << " i = " << i << std::endl;
			}
			catch ( std::exception &except )
			{
				std::cout << except.what() << "\n";
				i--;
			}
		}

		//if ( !bin->isBalanced() )std::cout << "Balance Error" << std::endl;
		for ( int i = 0; i < ARRSIZE; i++ )
		{
			int *a = new int( arr[i] );
			if ( *a == -1 )break;
			if ( bin->Find( a ) == nullptr ) std::cout << "cannot find " << *a << " in list i = " << i << std::endl;
			delete a;
		}

		//bin->print();
		for ( int i = 0; i < ARRSIZE; i++ )
		{
			//std::cout << "\n\nRemoving " << arr[i] << "\n";
			int *a = new int( arr[i] );
			delete bin->Remove( a );
			delete a;
			//bin->print();
		}

		delete bin;
		if ( j % 1000 == 0 )std::cout << j / 1000 << std::endl;
	}
	return 0;
}