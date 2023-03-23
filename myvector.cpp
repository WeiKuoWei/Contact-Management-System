// #include<string>
// #include<fstream>
// #include<ostream>
// #include<exception>
// #include<sstream>
// #include<cstdlib>
// #include<ctime>
// #include<iomanip>
// #include<algorithm>
// #include<cctype>
// #include<typeinfo>

#include <iostream>
#include "myvector.h"
using namespace std;


template <typename T>
MyVector<T>::MyVector(){
    v_size = 0;
    v_capacity = 30;
    data = new T[30];

}//No argument constructor

template <typename T>
MyVector<T>::MyVector(int cap){
    v_size = 0;
    v_capacity = cap;
    data = new T[v_capacity];

    
}//One Argument Constructor

// template <typename T>
// MyVector<T>::MyVector(const MyVector& other){
    
// }//Copy Constructor

template <typename T>
MyVector<T>::~MyVector(){
    delete []data;
}//Destructor

template <typename T>
void MyVector<T>::push_back(T element){
    // # consider capacity
    if(v_size >= v_capacity) reserve(max(1,v_capacity*2));
    data[v_size] = element; 
    v_size++;

}//Add an element at the end of vector
template <typename T>
void MyVector<T>::insert(int index, T element){
    // exception
    // #
    if(v_size >= v_capacity) reserve(max(1,v_capacity*2));
    for(int i = v_size; i >= index; i--){
        data[i+1] = data[i];
    }
    data[index] = element;
    v_size++;
} //Add an element at the index 

template <typename T>
void MyVector<T>::erase(int index){
    // exception
    // #
    for(int i = index; i < v_size; i++){
        data[i] = data[i+1];
    }
    v_size--;
}//Removes an element from the index

template <typename T>
T& MyVector<T>::operator[](int index){
    return data[index];
}//return reference of the element at index

template <typename T>
T& MyVector<T>::at(int index){
    return data[index];
}//return reference of the element at index

template <typename T>
const T& MyVector<T>::front(){
    return data[0];
}//Returns reference of the first element in the vector

template <typename T>
const T& MyVector<T>::back(){
    return data[v_size-1];
}//Returns reference of the Last element in the vector

template <typename T>
int MyVector<T>::size() const{
    return v_size;
}//Return current size of vector

template <typename T>
int MyVector<T>::capacity() const{
    return v_capacity;
}//Return capacity of vector

template <typename T>
bool MyVector<T>::empty() const{
	return v_size == 0;
}//Return true if the vector is empty, False otherwise

template <typename T>
void MyVector<T>::shrink_to_fit(){
    T* temp = new T[v_size]; // #
    for(int i = 0; i < v_size; i++){
        temp[i] = data[i];
    }
    if(data != NULL) delete[] data;
    data = temp;
    v_capacity = v_size;
}//Reduce vector capacity to fit its size

template <typename T>
void MyVector<T>::reserve(int N){
    if(v_capacity >= N) return;
    T* temp = new T[N]; 
    for(int i = 0; i < N; i++){
        temp[i] = data[i];
    } cout << " 8";
    if(data != NULL) delete[] data;
    data = temp;
    v_capacity = N;
}

