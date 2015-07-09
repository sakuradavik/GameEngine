#pragma once

#include "SList.h"
#include "Vector.h"
#include <utility>
#include <algorithm>
#include <string>

namespace Library
{
	static const std::uint32_t HashValue = 33;

	template <typename TKey>
	class DefaultHash
	{
	public:
		std::uint32_t operator()(const TKey& value) const;
	};

	template <typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	class HashMap
	{
		typedef std::pair<TKey, TData> PairType;

	private:
		typedef SList<PairType> ChainType;
		typedef Vector<ChainType> BucketType;
		
	public:
		class Iterator
		{
			friend class HashMap;
			typedef typename ChainType::Iterator ChainIterator;

		public:
			/**
			* Default Constructor. Does not have a HashMap that it iterates through
			* There is no method that will later bound the iterator to a HashMap
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
			* pointed to datas
			* @param none
			* @return The data that the currently pointed to Iterator is storing
			*/
			PairType& operator*();

			/**
			* @brief Overloading the arrow Operator. Will return a pointer to the currently pointed
			* to data
			* @param none
			* @returns A Pointer to the data the Iterator is pointing to
			*/
			PairType* operator->();

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
			* @brief Overloading the pre-increment operator. Makes this iterator point to the next
			* item in the HashMap
			* @param none
			* @return Return a iterator who is pointing to the next item in the HashMap
			*/
			Iterator& operator++();

			/**
			* @brief Overloading the post-increment operator. Makes this iterator point to the next
			* item in the HashMap
			* @param int Default method signature
			* @return Return this current Iterator, who is not pointing to the next item
			*/
			Iterator operator++(int);

		private:
			Iterator(HashMap* owner, std::uint32_t index, const ChainIterator& iterator);

			HashMap* mOwner; 
			std::uint32_t mIndex;
			ChainIterator mIterator;

		};

		/**
		* Constructor
		*/
		explicit HashMap(std::uint32_t size = 7);

		/**
		* Deconstructor
		*/
		~HashMap();

		/**
		* @brief Takes a key argument and returns an iterator
		* f@param TKey key used to find the item
		* @return Returns an Iterator pointing to the Data associated wiith the key
		*/
		Iterator Find(const TKey& key) const;

		/**
		* @brief Takes a PairType and returns an Iterator. If the key is already in use,
		* will return the iterator of the found key.
		* @param PairType which includes the TKey and TData
		* @return An Iterator to the key item in the HashMap
		*/
		Iterator Insert(const PairType& pair, bool& inserted);


		Iterator Insert(const PairType& pair);

		/**
		* @brief Overloading the assignment operator
		*
		*/
		HashMap& operator=(const HashMap& rhs);

		/**
		* @brief Takes a PairType and returns an Iterator. If the key is already in use,
		* will return the iterator of the found key.
		* @param TKey and TData to be inserted
		* @return An Iterator to the key item in the HashMap
		*/
		Iterator Insert(const TKey& key, const TData& data, bool& inserted);

		Iterator Insert(const TKey& key, const TData& data);

		/**
		* @brief Takes a key argument of the appropriate type and returns a reference to the
		* TData part. Create an entry with the associated key, if one isn't already in the HashMap.
		* @param TKey key of the item to return
		* @return Returns the data associated with a specific key
		*/
		TData& operator[](const TKey& key);

		/**
		* @brief Takes a TKey and removes the matching entry from the HashMap if it exists. 
		* If it doesn't exist then it doesn't do anything
		* @param TKey key of the item to remove
		* @return void
		*/
		void Remove(const TKey& key);

		/**
		* @brief Empties the Hash Table and deletes any memory it allocated
		* @param none
		* @return void
		*/
		void Clear();

		/**
		* @brief Returns the size of the table
		* @param none
		* @return Returns the Size of the HashMap
		*/
		std::uint32_t Size() const;

		/**
		* @brief Returns a Boolean indicating the presence of a key within the HashMap
		* @param TKey key that is being looked for
		* @return Returns a boolean indiicating presence of a key
		*/
		bool ContainsKey(const TKey& key) const;

		/**
		* @brief Returns an Iterator to the beginning of the contents
		* @param none
		* @return Returns an Iterator to the beginning of the contents
		*/
		Iterator begin() const;

		/**
		* @brief Returns an Iterator to the end of the contents
		* @param none
		* @return Returns an Iterator to the end of the contents
		*/
		Iterator end() const;

	private:
		BucketType mBucket;
		HashFunctor mHashFunctor;
		std::uint32_t mSize;

		std::uint32_t mBeginIndex;
	};
}

#include "HashMap.inl"