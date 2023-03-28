#include "BinaryTree.h"
#include "BinaryTree.cpp"
#include <random>
#include <iostream>

int main()
{
	srand( time( NULL ) );
	for ( int a = 0; a < 1000000; a++ )
	{
		BinaryTree<int> *bin = new BinaryTree<int>;

		for ( int i = 0; i < 100; i++ )
		{
			int *a = new int( rand() % 100 );
			try
			{
				bin->Insert( a );
			}
			catch ( std::exception &except )
			{
				//std::cout << except.what() << "\n";
			}
		}
		delete bin;
	}
}