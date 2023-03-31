#include "BinaryTree.h"
#include "BinaryTree.cpp"
#include <random>
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

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

void testBinaryTree( bool *comparr, int j )
{
	BinaryTree<int> *bin = new BinaryTree<int>;
	constexpr int ARRSIZE = 10000;
	int *arr = new int[ARRSIZE];
	fillArray( arr, ARRSIZE, 1000000 );

	for ( int i = 0; i < ARRSIZE; i++ )
	{
		try
		{
			bin->Insert( new int( arr[i] ) );
		}
		catch ( std::exception &except )
		{
			std::cout << except.what() << "\n";
			i--;
		}
	}

	for ( int i = 0; i < ARRSIZE; i++ )
	{
		int *a = new int( arr[i] );
		if ( bin->Find( a ) == nullptr ) std::cout << "cannot find " << *a << " in list i = " << i << std::endl;
		delete a;
	}

	for ( int i = 0; i < ARRSIZE; i++ )
	{
		int *a = new int( arr[i] );
		delete bin->Remove( a );
		delete a;
	}

	delete bin;
	delete[ARRSIZE] arr;
	comparr[j] = true;
}

bool Completed( bool *arr, int size )
{
	for ( int i = 0; i < size; i++ )if ( !arr[i] )return false;
	return true;
}

void printbools( bool *arr, int size )
{
	//for ( int i = 0; i < 100; i++ )
	//{
	//	std::cout << '\b';
	//}
	std::cout << "\n";
	for ( int i = 0; i < size / 10; i++ )
	{
		int sum = 0;
		for ( int j = i * 10; j < (i * 10 + 10); j++ )
		{
			if ( arr[j] )sum++;
		}
		if ( sum < 5 )std::cout << "_";
		else if ( sum < 8 )std::cout << "-";
		else std::cout << '^';
	}
}

int main()
{
	unsigned seed = (unsigned) time( NULL );
	srand( seed );
	constexpr int THREADCOUNT = 1000;

	std::thread threads[THREADCOUNT];
	bool *completed = new bool[THREADCOUNT] { false };

	for ( int j = 0; j < THREADCOUNT; j++ )
	{
		threads[j] = std::thread(testBinaryTree, completed, j);
	}
	while ( !Completed( completed, THREADCOUNT ) )
	{
		std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
		printbools( completed, THREADCOUNT );
	}
	for ( int i = 0; i < THREADCOUNT; i++ )
	{
		threads[i].join();
	}
	return 0;
}

