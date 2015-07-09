#pragma once

#include <cstdint>
#include <exception>

namespace Library
{
	/**
	*Singly Linked List (SList) Template Implementation
	*/
	template <typename T>
	class SList
	{
	private:
		/**
		* Private Node class used by the SList to store the data of each Node of type T and a pointer to the next 
		* Node in the list
		*/
		class Node
		{
		public:
			/**
			* @brief Constructor for Node class 
			* @param data The templated data to be stored
			* @param next Pointer to the next node in the SList, default to nullptr if none is provided
			*/
			Node(const T& data, Node* next = nullptr);

			/**
			* @brief Returns the Node* of the Node following this one in the SList
			* @param none
			* @return The Next Node* this node is pointing to
			*/
			Node* Next();

			/**
			* @brief Returns the data this Node is storing
			* @param none
			* @return The templated data stored in this Node
			*/
			T& Data();

			/**
			* @brief Sets the pointer of the Node following this one in the SList
			* @param next The new Node that this Node should point to
			* @return void
			*/
			void SetNext(Node* next);

		private:
			Node(const Node& rhs) = delete;
			Node& operator=(const Node& rhs) = delete;
			Node() = delete;

			T mData;
			Node* mNext;
		};

	public:
		class Iterator
		{
			friend class SList;

		public:
			/**
			* Default Constructor. Does not have a SList that it iterates through
			* There is no method that will later bound the iterator to a SList
			*/
			Iterator();

			/**
			* Copy Constructor
			*/
			Iterator(const Iterator& rhs);

			/**
			* Assignment Operator Overload
			*/
			Iterator& operator=(const Iterator&);

			/**
			* Deconstructor
			*/
			~Iterator();

			/**
			* @brief Overloading the derefrencing operator. This will return the currently 
			* pointed to Node's data
			* @param none
			* @return The data that the currently pointed to Node is storing
			*/
			T& operator*();

			/**
			*@brief Overloading the == operator. Check to see if this Iterator's data and owner's
			* matched the ones in rhs
			* @param rhs Iterator to compare against
			* @return The boolean value of whether the rhs's owner and node value match this classe's
			* owner and node value
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
			* @brief Overloading the pre-increment operator. Makes this iterator's node point to 
			* the next node in the SList
			* @param none
			* @return Return a iterator who is pointing to the next node in the SList
			*/
			Iterator& operator++();

			/**
			* @brief Overloading the post-increment operator. Makes this iterator's node point to the 
			* next node in the SList
			* @param int Default method signature
			* @return Return this current Iterator, who is not pointing to the next node
			*/
			Iterator operator++(int);

		private:
			Iterator(const SList* owner, Node* node);

			const SList* mOwner;
			Node* mNode;

		};

		//Constant Time Methods

		/**
		* @brief Default Constructor for SList. Defaults the values of 
		the pointers to the front and back in the SList to nullptr and initializes size to 0
		* @param none
		*/
		SList();

		/**
		* @brief Allows us to add A Node to the begining of the SList and updates the SList 
		to store the new Node as its front Node
		* @param data Templated data to be stored in the newly added front Node
		* @return void
		*/
		void PushFront(const T& data);

		/**
		* @brief Removes the first element from the SList and deletes it. Also updates the SList's 
		front Node pointer
		* @param none
		* @return void
		*/
		void PopFront();

		/**
		* @brief Adds a new Node to the end of the lst and updates the the SList's back Node pointer
		* @param data Templated data to be stored in the newly added back Node
		* @return void
		*/
		void PushBack(const T& data);

		/**
		* @brief Checks to see if there are any elements in the SList
		* @param none
		* @return boolean Value of whether the SList is empty or not
		*/
		bool IsEmpty() const;

		/**
		* @brief Returns the templated data stored in the front Node
		* @param none
		* @return The templated data stored in the front Node
		*/
		T& Front();

		/**
		* @brief Returns the templated data stored in the last Node
		* @param none
		* @return The templated data stored in the last Node
		*/
		T& Back();

		/**
		* @brief Returns the Size of the SList
		* @param none
		* @return The size of the list as an integer
		*/
		std::uint32_t Size() const;
		//Linear Time Methods

		/**
		* @brief Copy Constructor. Makes a deep copy of the SList. Will initialize the
		front and back Node pointer's of the SList to nullptr and the size to 0
		* @param rhs The SList that will be copied onto this SList
		*/
		SList(const SList& rhs);

		/**
		* @brief Overloading the assignment operator
		* @return A pointer to this SList
		*/
		SList& operator=(const SList& rhs);

		/**
		* @brief Deconstructor. Called when a SList goes out of scope
		* @param void
		*/
		~SList();

		/**
		* @brief Will clear the SList and delete all the Nodes in it.
		* @param none
		* @return void
		*/
		void Clear();

		/**
		* @brief Returns an iterator pointing to the first node in the SList
		* @param none
		* @return Returns an iterator
		*/
		Iterator begin() const;

		/**
		* @brief Returns an interator pointing to the node after the last node, which is a nullptr
		* @param none
		* @return Returns an iterator
		*/
		Iterator end() const;

		/**
		* @brief Inserts a new node after the node that the iterator is pointing to
		* @param it, data Takes an iterator pointing to the node to insert the new 
		* node after and takes the data to be stored in new node
		* @return void
		*/
		void InsertAfter(const Iterator& it, const T& data);

		/**
		* @brief Will find if a node with this value exsits in the SList
		* @param value The value that is being looked for
		* @return An Iterator who is pointing to the found node, points to nullptr if non was found
		*/
		Iterator Find(const T& value) const;

		/**
		* @brief Will find a node if it exists in the SList and will delete it
		* @param vale the value that is being looked for to remove
		* @return void
		*/
		void Remove(const T& value);

	private:
		/**
		* @brief Points to the first Node in the SList
		*/
		Node* mFront;

		/**
		* @brief Points to the last Node in the SList
		*/
		Node* mBack;

		/**
		* @brief The size of the SList
		*/
		std::uint32_t mSize;
	};
}


#include "SList.inl"