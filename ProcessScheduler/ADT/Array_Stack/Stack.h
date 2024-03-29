//	This is an updated version of code originally
//  created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** ADT stack: Array-based implementation.
 @file Stack.h */

#ifndef STACK_
#define STACK_

#include "StackADT.h"
#include <iostream>
 //Unless specified by the stack user, the default size is 100
template<typename T>
class Stack : public StackADT<T>
{
private:
	T* items;		// Array of stack items
	int  top;            // Index to top of stack
	const int STACK_SIZE;

public:

	Stack(int MaxSize) : STACK_SIZE(MaxSize)
	{
		items = new T[STACK_SIZE];
		top = -1;
	}  // end default constructor

	bool isEmpty() const
	{
		return top == -1;
	}  // end isEmpty

	bool push(const T& newEntry)
	{
		if (top == STACK_SIZE - 1) return false;	//Stack is FULL

		top++;
		items[top] = newEntry;
		return true;
	}  // end push

	bool pop(T& TopEntry)
	{
		if (isEmpty()) return false;

		TopEntry = items[top];
		top--;
		return true;
	}  // end pop

	bool peek(T& TopEntry) const
	{
		if (isEmpty()) return false;

		TopEntry = items[top];
		return true;
	}  // end peek
	void print() override 
	{
		for (const auto& item : items)
		{
			std::cout << item;
		}
	}

	int count() override {
		return top + 1;
	}
}; // end Stack

#endif
