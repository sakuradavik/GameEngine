#pragma once

#include "SList.h"

namespace Library
{
	template <typename T>
	class Stack
	{
	public:
		/**
		* Default Constructor
		*/
		Stack();

		/**
		* @brief Copy Constructor. Makes a deep copy of the Stack.
		* @param rhs The Stack that will be copied onto this Stack
		*/
		Stack(const Stack& rhs);

		/**
		* @brief Overloading the assignment operator
		* @param rhs The Stack whose data will be copied
		* @return a reference to this Stack
		*/
		Stack& operator=(const Stack& rhs);

		/**
		* Deconstructor
		*/
		~Stack();

		/**
		* @brief Increase size of stack by 1 and assign top of stack to given value
		* @param item The value that will be added
		* @return void
		*/
		void Push(const T& item);

		/**
		* @brief Will delete the top element in the stack
		* @param none
		* @return void
		*/
		void Pop();

		/**
		* @brief Return item at top of stack
		* @param none
		* @return Returns a reference to the item at the top
		*/
		T& Top();

		/**
		* @brief Retuen item at top of stack, const version
		* @param none 
		* @return Returns a reference to the item at the top
		*/
		const T& Top() const;

		/**
		* @brief Return the size of the stack
		* @param none
		* @return Returns the size of the stack
		*/
		std::uint32_t Size() const;

		/**
		* @brief Returns whether the stack is empty
		* @param none
		* @return Returns whether stack is emmpty
		*/
		bool IsEmpty() const;

		/**
		* @brief Clears constent from the stack
		* @paramm none
		* @return void
		*/
		void Clear();

	private:
		SList<T> mSList;
	};
}

#include "Stack.inl"