#pragma once 
#include <iostream>
#include <cassert>

using namespace std;

template <typename T>
class Vector
{
private:
	size_t size;
	size_t capacity;
	T* arr;
	void destroy();
	void copy(const Vector<T>& other);
	void resize();
public:
	Vector();
	Vector (const Vector<T>& other);
	Vector<T>& operator= (const Vector<T>& other);
	~Vector();
	
	void addElement(const T& element);
	void removeElementAt(size_t index);
	T& operator [] (size_t index);
	const T& operator [] (size_t index) const;
	size_t getSize() const;
	
};

template <typename T>
void Vector<T>::destroy()
{
	delete [] this->arr;
}

template <typename T>
void Vector<T>::copy(const Vector<T>& other)
{
	this->capacity = other.capacity;
	this->size = other.size;
	this->arr = new T [this->capacity];
	for (int i = 0; i < this->size; i++)
	{
		this->arr[i] = other.arr[i];
	}
}

template <typename T>
void Vector<T>::resize()
{
	T* resizedArr = new T[this->capacity*2];
	for(int i = 0; i < this->size; i++)
	{
		resizedArr[i] = this->arr[i];
	}
	
	delete [] this->arr;
	this->arr = resizedArr;
	this->capacity *= 2; 
}

template <typename T>
Vector<T>::Vector()
{
	this->capacity = 4;
	this->size = 0;
	this->arr = new T [this->capacity];
}

template <typename T>
Vector<T>::Vector (const Vector<T>& other)
{
	this->copy(other);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if(this != &other)
	{
		this->destroy();
		this->copy(other);
	}
	return *this;
}

template <typename T>
Vector<T> :: ~Vector()
{
	this->destroy();
}

template <typename T>
void Vector<T>::addElement(const T& element)
{
	if(this->capacity == this->size)
	{
		this->resize();
	}
	this->arr[this->size++] = element;
}

template <typename T>
void Vector<T>::removeElementAt(size_t index)
{
	assert(index < this->size);
	for (int i = index; i < this->size - 1; i++)
	{
		this->arr[i] = this->arr[i+1];
	}
	this->size--;
}

template <typename T>
T& Vector<T>::operator [] (size_t index)
{
	if(index >= this->size)
	{
//		for (int i = 0; i < this->getSize(); ++i)
//		{
//			cout << this->arr[i] << endl;
//		}
		cout << index << " >= "<< size << endl;
	}
	
	assert(index < this->size);
	return this->arr[index];
}

template <typename T>
const T& Vector<T>::operator [] (size_t index) const
{
	if(index >= this->size)
	{
//		for (int i = 0; i < this->getSize(); ++i)
//		{
//			cout << this->arr[i] << endl;
//		}
		cout << index << " >= "<< size << endl;
	}
	assert(index < this->size);
	return this->arr[index];
}

template <typename T>
size_t Vector<T>::getSize() const
{
	return this->size;	
}


