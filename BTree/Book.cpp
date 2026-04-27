/*Yael Otmazgin 212531115
Linoy Bony 211820824
Exercise 04*/
#include "Book.h"

// Constructor: Initializes catalog, shelf, and availability
Book::Book(int catalog, int _shelf)
{
	// TODO: fix
	catalogNumber = catalog;
	shelf = _shelf;
	available = true;
}

// Method to borrow a book
bool Book::borrowBook()
{
	// TODO: fix. Use the following lines to print the output according to the relevant case
	// Print success message
	if (available)
	{
		cout << "Successfully found the book " << catalogNumber << " on shelf " << shelf << " and borrowed it" << endl;
		available = false;
	}
	else
	{ 
		// Print error message for already borrowed book
		cout << "Error! The book " << catalogNumber << " is already borrowed!" << endl;
	}
	return true;
}

// Method to return a book
bool Book::returnBook()
{
	// TODO: fix. Use the following lines to print the output according to the relevant case
	if (available)
	{
		// Print error message for book not borrowed
		cout << "Error! The book " << catalogNumber << " is not borrowed!" << endl;
		return false;
	}
	else
	{
		// Mark the book as available and print success message
		available = true;
		cout << "Successfully returned the book " << catalogNumber << " to shelf " << shelf << endl;
	}
	return true;
}

// Output stream insertion operator for Book objects
ostream& operator<<(ostream& os, Book b)
{
	// Note: Output stream insertion operator for Book objects
	os << "{" << b.catalogNumber << ", " << b.shelf << ", ";
	os << (b.available ? "available" : "borrowed") << "}";
	return os;
}

// Input stream extraction operator for Book objects
istream& operator>>(istream& is, Book& b)
{
	// Note: Input stream extraction operator for Book objects
	is >> b.catalogNumber >> b.shelf;
	return is;
}
