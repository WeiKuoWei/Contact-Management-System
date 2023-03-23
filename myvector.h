#ifndef MyVector_H
#define MyVector_H

#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<stdexcept>
#include<sstream>
#include "contact.h"

using namespace std;
// typedef Contact T;
template <typename T>
class MyVector
{
	private:
		T *data;						//pointer to int(array) to store elements

	public:
		int v_size;						//current size of vector (number of elements in vector)
		int v_capacity;					//capacity of vector
		
		MyVector();						//No argument constructor
		MyVector(int cap);				//One Argument Constructor
		MyVector(const MyVector& other);//Copy Constructor
		~MyVector();					//Destructor
		T* getData(){return this->data;}
		void push_back(T element);		//Add an element at the end of vector
		void insert(int index, T element); //Add an element at the index 
		void erase(int index);			//Removes an element from the index
		T& operator[](int index);		//return reference of the element at index
		T& at(int index); 				//return reference of the element at index
		const T& front();				//Returns reference of the first element in the vector
		const T& back();				//Returns reference of the Last element in the vector
		int size() const;				//Return current size of vector
		int capacity() const;			//Return capacity of vector
		bool empty() const; 			//Return true if the vector is empty, False otherwise
		void shrink_to_fit();			//Reduce vector capacity to fit its size
        void reserve(int N);            //extend array size to N
};

#include "myvector.cpp"
#endif