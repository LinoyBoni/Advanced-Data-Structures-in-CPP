/*Yael Otmazgin 212531115
Linoy Bony 211820824 
Exercise 02*/
#pragma once
#include"HashTable.h"

template <class T>
class StringHash :public HashTable<string, T>
{
private:
	//TODO: implement h1 and h2

    int h1(string k)
    {
        // First hashing function for strings.
        unsigned long int result = 0;
        for (int i = 0; i < k.size(); i++)
	        result += ((int)k[i]) * powl(256, i);
        return result % this->size;
    }

    int h2(string k)
    {
        /// Double hashing for strings.
        return 1; // Linear probing
    }

public:
	StringHash(int m = 10) :HashTable<string, T>(m) {}
};
