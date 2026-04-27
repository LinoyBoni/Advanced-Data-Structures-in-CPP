/*Yael Otmazgin 212531115
Linoy Bony 211820824 
Exercise 02*/
#pragma once
#include "HashTable.h"
#include<string>
using namespace std;
template <class T>
class IntHash :public HashTable<int, T>
{
private:
	//TODO: implement h1 and h2

    int h1(int k)
    {
        // First hashing function for integers.
        return k % this->size;
    }

    int h2(int k)
    {
        // Double hashing for integers.
        return (k % (this->size - 1)) + 1;
    }

public:
	IntHash(int m = 10) :HashTable<int, T>(m) {}
};

