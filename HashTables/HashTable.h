/*Yael Otmazgin 212531115
Linoy Bony 211820824 
Exercise 02*/
#pragma once
#include <iostream>
#include "PrimeUtil.h"
using namespace std;

enum state { EMPTY, FULL, DELETED };

template<class K, class T>
class HashTable
{
protected:
	class Item
	{
	public:
		T data;			//The record information
		K key;			//The record key
		state flag;		//An indicator for the vacancy of the cell
		//Constructors
		Item() { flag = EMPTY; }
		Item(K k, T d) { data = d; key = k; flag = FULL; }
	};

	int size;
	Item* table;

	// TODO: Add any additional required attributes
	// TODO: Add here the declaration of the functions h1, h2.
 
	// Virtual function: hashing logic. 1st hash.
	virtual int h1(K k) = 0; 
	// Virtual function: double hashing. 2nd hash.
	virtual int h2(K k) = 0; 

	// TODO: Based on the functions, define the hash function, using double hashing

	// Hash function: Combine h1 and h2.
	int hash(K k, int i);

public:
	// Constructor: Init hash table, adjust size.
	HashTable(int m = 10);
	// Destructor: Deallocate memory.
	~HashTable();

	// TODO: add here the declaration of the functions insert, search and remove.

	// Insert key-value pair.
	void insert(K k, T t);

	// Search by key, return value
	T search(K k);

	// Remove value by key.
	void remove(K k);

	// Print keys and indices.
	void print();
};
///////////////////////////////////////////////


template<class K, class T>
HashTable<K, T>::HashTable(int m) : size(m)
{
	// TODO: implement
	// HashTable constructor: Initialize hash table, adjust size.
	while (!(PrimeUtil::prime(size))) size += 1; /// Adjust size to the next prime
	table = new Item[size]; /// Allocate dynamic memory
}

template<class K, class T>
HashTable<K, T>::~HashTable()
{
	// Destructor: Deallocate memory.
	delete[] table;
}

// TODO: implement here the functions hash, insert, search and remove.

template<class K, class T>
int HashTable<K, T>::hash(K k, int i)
{
	// Hash function: Combine h1 and h2.
	return (h1(k) + i * h2(k)) % size;
}

template<class K, class T>
void HashTable<K, T>::insert(K k, T t)
{
	/// Insert key-value, handle collisions with linear probing.
	int i = 0, index = hash(k, i);

	while (table[index].flag == FULL) index = hash(k, ++i);

	table[index].data = t;
    table[index].key = k;
    table[index].flag = FULL;
}

template<class K, class T>
T HashTable<K, T>::search(K k)
{
    // Search for a key in the hash table and return the associated value.
    // If the key is found, the corresponding value is returned.
    // If the key is not found and all slots are marked as DELETED, an exception is thrown.
    // If the key is not found and an EMPTY slot is encountered, an exception is thrown.
    
    int i = 0;
    int index = hash(k, i);
    int deletedCounter = 0;  // Counter for deleted slots

    // Search loop
    while (true)
    {
        // Check if the current slot is FULL and the key matches
        if (table[index].flag == FULL && table[index].key == k)
            return table[index].data; // Key found

        // Check if the current slot is marked as DELETED
        if (table[index].flag == DELETED)
        {
            deletedCounter++;

            // If all slots are deleted, throw an exception
            if (deletedCounter == size)
                throw "Key does not exist in table";
        }

        // Check if the current slot is EMPTY, indicating the key is not in the table
        if (table[index].flag == EMPTY)
            throw "Key does not exist in table"; // Key not found

        // Move to the next index using double hashing
        index = hash(k, ++i);
    }
}

template<class K, class T>
void HashTable<K, T>::remove(K k)
{
	/// Remove key and its associated value.
	int i = 0;
	int index = hash(k, i);

	while (table[index].flag != EMPTY && (table[index].key != k || table[index].flag == DELETED))
	{
		index = hash(k, ++i);
	}

	if (table[index].flag != EMPTY)
		table[index].flag = DELETED;
}

template<class K, class T>
inline void HashTable<K, T>::print()
{
	// Print keys and their indices in the hash table.
	for (int i = 0; i < size; i++)
	{
		if (table[i].flag == FULL)
			cout << i << ":\t" << table[i].key << '\n';
		if (table[i].flag == DELETED)
			cout << i << ":\t" << "DELETED" << '\n';
	}
}



