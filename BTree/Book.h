/*Yael Otmazgin 212531115
Linoy Bony 211820824
Exercise 04*/
#pragma once
#include<iostream>
using namespace std;
class Book
{
private:
	int catalogNumber;
	int shelf;
	bool available;
public:
	int getKey() { return catalogNumber; }
	Book(int catalog = 0, int _self = 0);
	bool borrowBook();
	bool returnBook();

	// TODO: fix operators
	// Comparison operators
	bool operator<(Book b) { return (catalogNumber < b.catalogNumber); } // TODO: fix
	bool operator>(Book b) { return (catalogNumber > b.catalogNumber); } // TODO: fix
	bool operator<=(Book b) { return (catalogNumber <= b.catalogNumber); } // TODO: fix
	bool operator==(Book b) { return (catalogNumber == b.catalogNumber); } // TODO: fix
	bool operator!=(Book b) { return (catalogNumber != b.catalogNumber); } // TODO: fix

	friend ostream& operator<<(ostream& os, Book b);
	friend istream& operator>>(istream& is, Book& b);
};