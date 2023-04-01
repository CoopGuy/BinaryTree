#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include "BinaryTree.h"
#include "BinaryTree.cpp"

class StringValuePair
{
public:
	std::string word;
	int count;
	StringValuePair( std::string w ) : word( w ), count( 1 ) {};
	bool operator>(const StringValuePair &a)
	{
		return word > a.word;
	}
	bool operator<( const StringValuePair &a )
	{
		return word < a.word;
	}
	bool operator==( const StringValuePair &a )
	{
		return word == a.word;
	}
	friend std::ostream &operator<<( std::ostream &os, const StringValuePair &dt );
};

std::ostream& operator<<(std::ostream&os, const StringValuePair &a )
{
	os << a.word;
	return os;
}

void openuserfile( std::fstream &reader )
{
	std::string filename = "";
	while ( !reader.is_open() )
	{ // if file doesn't exist, keep prompting
		if ( filename != "" )
		{
			std::cout << "ERROR: File could not be found or read. Please try again."
				<< std::endl;
		}
		std::cout << "Filename: ";
		std::cin >> filename; //get filename from user
		std::cin.ignore();
		if ( (int) filename.find( ".txt" ) < 0 )
		{
			filename.append( ".txt" );
		}
		reader.open( filename );
	}
}

void readData( std::fstream &reader, BinaryTree<StringValuePair> &data )
{
	while ( !reader.eof() )
	{
		std::string input, word;
		std::getline( reader, input );
		for ( char c : input )
		{
			if ( c == ' ' || c == '\n' || c == '-' )
			{
				StringValuePair *a = new StringValuePair( word );
				BinaryTree< StringValuePair>::Node *t = data.Find( a );
				if ( t == nullptr ) data.Insert( new StringValuePair( word ) );
				else t->value->count++;
				delete a;
				word = "";
			}
			else if ( 65 <= c && c <= 122 )
			{
				word += c;
			}
		}
	}
}

void runAnalysis( BinaryTree<StringValuePair> &info )
{
	std::fstream reader;
	openuserfile( reader ); // gets filename, attempts to open it, and prints error message on fail
	readData( reader, info );	// read data from doc
	reader.close();
}

void doUserActions( BinaryTree<StringValuePair> &info )
{
	std::string userinput;
	do
	{
		std::cout << "Menu \n1) Word Search\n2) Print\n(~ to exit) $: ";
		std::getline( std::cin, userinput );
		char inputchar = userinput[0];
		if ( inputchar == '1' )
		{
			std::cout << "Word Search\n(~ to exit) $: ";
			std::getline( std::cin, userinput );

			StringValuePair *a = new StringValuePair( userinput );
			BinaryTree< StringValuePair>::Node *n = info.Find( a );
			delete a;

			if ( n ) std::cout << "Word: " << n->value->word << "\nCount: " << n->value->count << '\n';
			else   std::cout << "Error: Word not found\n";
		}
		else if ( inputchar == '2' )
		{
			int i, s = info.Size();
			BinaryTree< StringValuePair>::Node **arr;

			std::cout << "1)Ascending Order\n2)Descending Order\n(~ to exit) $: ";
			std::getline( std::cin, userinput );

			if ( userinput[0] == '1' )
				arr = info.GetAllAscending();

			else
				arr = info.GetAllDescending();

			for ( i = 0; i < info.Size(); i++ )
				std::cout << arr[i]->value->word << " : " << arr[i]->value->count << "\n";
		}
		else
		{
			std::cout << "Exiting...\n";
		}
	} while ( userinput != "~" );
}

/*
Once the file is read and loaded to the tree, let the
user search for a word. If it is found, return the count. If it is not, indicate such. Also,
allow the user to see a list of all words with count in alphabetic order both ascending and
descending (Task 1 part f and g).
*/

int main()
{
	std::string userinput;
	do
	{
		BinaryTree<StringValuePair> info;
		info.print();
		runAnalysis( info );
		doUserActions( info );
		std::cout << "\nProcess another book? : ";
		std::cin >> userinput;
		std::cout << std::endl;
	} while ( toupper( ( userinput.c_str() )[0] ) == 'Y' );
	return 0;
}