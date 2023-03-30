#include "BinaryTree.h"
#include "BinaryTree.cpp"
#include <random>
#include <iostream>

int main()
{
	srand( time(NULL) );
	for ( int j = 0; j < 1000000; j++ )
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

		if ( j % 100000 == 0 )
		{
			std::cout << "{ ";
			for ( int i = 0; i < j / 100000; i++ )
			{
				std::cout << " [] ";
			}
			std::cout << " }" << std::endl;
		}
	}
}