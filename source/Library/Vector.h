#pragma once

#include <cstdint>
#include <exception>

namespace Library
{
	template <typename T>
	class Vector
	{
	public:
		class Iterator
		{
			friend class Vector;

		public:
			/**
			* Default Constructor. Does not have a Vector that it iterates through
			* There is no method that will later bound the iterator to a Vector
			*/
			Iterator();

			/**
			* Copy Constructor
			*/
			Iterator(const Iterator& rhs);

			/**
			* Assignment Operator Overload
			*/
			Iterator& operator=(const Iterator& rhs);

			/**
			* Deconstructor
			*/
			~Iterator();

			/**
			* @brief Overloading the derefrencing operator. This will return the currently
			* pointed to data
			* @param none
			* @return The data that the currently pointed to data is storing
			*/
			T& operator*();

			/**
			* @brief Overloading the == operator. Check to see if this Iterator's data and owner's
			* matched the ones in rhs
			* @param rhs Iterator to compare against
			* @return The boolean value of whether the rhs's owner and data value match this classe's
			* owner and data value
			*/
			bool operator==(const Iterator& rhs) const;

			/**
			* @brief Overloading the != operator. Check to see if this Iterator's data and owner's
			* don't match the ones in rhs
			* @param rhs Iterator to compare against
			* @return The boolean value of whether this iterator is not equal to rhs
			*/
			bool operator!=(const Iterator& rhs) const;

			/**
			* @brief Overloading the pre-increment operator. Makes this iterator's data point to
			* the next data in the Vector
			* @param none
			* @return Return a iterator who is pointing to the next data in the Vector
			*/
			Iterator& operator++();

			/**
			* @brief Overloading the post-increment operator. Makes this iterator's data point to the
			* next data in the Vector
			* @param int Default method signature
			* @return Return this current Iterator, who is not pointing to the next data
			*/
			Iterator operator++(int);

		private:
			Iterator(Vector* owner, std::uint32_t index);

			Vector* mOwner;
			std::uint32_t mIndex;

		};

		/**
		* Default Constructor. Will Initialize size and capacity to 3.
		*/
		explicit Vector(std::uint32_t capacity = DefaultCapacity);

		/**
		* @brief Overloading the [] Operator.
		* @param index The indes of the item whose's refrence should be returned
		* @return Returns the refrence to the item at the given index
		*/
		T& operator[](std::uint32_t index);
		
		/**
		* @brief Overloading the [] Operator.
		* @param index The indes of the item whose's const refrence should be returned
		* @return Returns the const refrence to the item at the given index
		*/
		T& operator[](std::uint32_t index) const;

		/**
		* @brief Removes the last item in Vector. Does not reduce the capacity
		* @param none
		* @return void
		*/
		void PopBack();

		/**
		* @brief Checks if Vector is empty.
		* @param none
		* @return Returns the boolean value of whether list is empty
		*/
		bool IsEmpty();

		/**
		* @brief Returns the templated data stored in the first item in the Vector
		* @param none
		* @return Reference to data stored in the Vector's first item
		*/
		T& Front();

		/**
		* @brief Returns a const reference to the templated data of the first item in the Vector
		* @param none
		* @return  A const reference to the data stored in the Vector's first item
		*/
		T& Front() const;

		/**
		* @brief Returns a reference to the templated data of the last item in the Vector
		* @param none
		* @return Returns a reference to the data stored in the Vector's last item
		*/
		T& Back();

		/**
		* @brief Returns a const reference to the templated data of the last item in the Vector
		* @param none
		* @return Returns a const reference to the data stored in the Vector's last item
		*/
		T& Back() const;

		/**
		* @brief The size of the Vector
		* @param none
		* @return Returns the size of the Vector
		*/
		std::uint32_t Size() const;

		/**
		* @brief Returns an iterator pointing to the first item in the Vector
		* @param none
		* @return Returns an iterator
		*/
		Iterator begin() const;

		/**
		* @brief Returns an interator pointing to the item after the last item in the Vector, which is a nullptr
		* @param none
		* @return Returns an iterator
		*/
		Iterator end() const;

		/**
		* @brief Appends given item after the end of the list. Will increase size of array capacity if necessary
		* @param data the Data of type T to be appended
		* @return void
		*/
		void PushBack(const T& data);

		/**
		* @brief Copy Constructor. Makes a deep copy of the Vector. 
		* @param rhs The Vector that will be copied onto this Vector
		*/
		Vector(const Vector& rhs);

		/**
		* @brief Overloading the assignment operator
		* @param rhs The Vector whose data will be copied
		* @return a reference to this Vector
		*/
		Vector& operator=(const Vector& rhs);

		/**
		* @brief Takes an unsign integer index and returns a reference to the item at the given index
		* Will throw exception if the index is greater than capacity. If capacity sufficient and index is
		* greater than size, it will increase the Vector's size to accomidate the index.
		* @param index The index of the item whose reference is desired
		* @return a Reference to item at the index
		*/
		T& At(std::uint32_t index);

		/**
		* Destructor
		*/
		~Vector();

		/**
		* @brief Reserves more memory for the array
		* @param reserveCapacity Indicates the capacity to reserve
		* @return void
		*/
		void Reserve(std::uint32_t reserveCapacity);

		/**
		* @brief Returns an iterator pointing to the first item in the container mmatching the value passed
		* @param value The value that is being looked for
		* @return Returns an Iterator pointing the the item found
		*/
		Iterator Find(const T& value) const;

		/**
		* @brief Empties the container
		* @param none
		* @return void
		*/
		void Clear();

		/**
		* @brief 
		* @param
		* @return
		*/
		T& Remove(std::uint32_t index);

		/**
		* For testing purposes
		*/
		std::uint32_t Capacity();

		static const std::uint32_t DefaultCapacity;

		private:
			std::uint32_t mSize;
			std::uint32_t mCapacity;
			T* mItems;
	};
}

#include "Vector.inl"
