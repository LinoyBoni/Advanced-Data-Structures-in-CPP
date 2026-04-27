/*Yael Otmazgin 212531115
Linoy Bony 211820824
Exercise 04*/
#pragma once
template<class T>
class LibraryDataStructure {
public:
    virtual void inorder() = 0;
    virtual void insert(T t) = 0;
    virtual T* search(int key) = 0;
    virtual ~LibraryDataStructure() {} // Virtual destructor
};