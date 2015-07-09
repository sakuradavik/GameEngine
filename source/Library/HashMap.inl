namespace Library
{
	typedef std::uint8_t byte;

#define HashMapIterator typename HashMap<TKey, TData, HashFunctor>::Iterator

#pragma region HashFunctor

	template <typename TKey>
	std::uint32_t DefaultHash<TKey>::operator()(const TKey& value) const
	{
		uint32_t hash = 0;
		const byte* bytes = reinterpret_cast<const byte*>(&value);
		uint32_t size = sizeof(*bytes);

		for (uint32_t i = 0; i < size; ++i)
		{
			hash = bytes[i] + HashValue * hash;
		}
		return hash;
	}

	template <typename TKey>
	class DefaultHash<TKey*>
	{
	public:
		std::uint32_t operator()(const TKey* value) const
		{
			uint32_t hash = 0;
			const byte* bytes = reinterpret_cast<const byte*>(value);
			uint32_t size = sizeof(*bytes);

			for (uint32_t i = 0; i < size; ++i)
			{
				hash = bytes[i] + HashValue * hash;
			}
			return hash;
		}
	};

	template <>
	class DefaultHash<std::string>
	{
	public:
		std::uint32_t operator()(const std::string& value) const
		{
			uint32_t hash = 0;
			uint32_t size = value.length();

			for (uint32_t i = 0; i < size; ++i)
			{
				hash = value[i] + HashValue * hash;
			}
			return hash;
		}
	};

#pragma endregion

#pragma region Iterator

	template<typename TKey, typename TData, typename HashFunctor>
	HashMap<TKey, TData, HashFunctor>::Iterator::Iterator() :
		mOwner(nullptr), mIndex(0), mIterator()
	{
	}

	template<typename TKey, typename TData, typename HashFunctor>
	HashMap<TKey, TData, HashFunctor>::Iterator::Iterator(HashMap* owner, std::uint32_t index, const ChainIterator& iterator) :
		mOwner(owner), mIndex(index), mIterator(iterator)
	{
	}

	template<typename TKey, typename TData, typename HashFunctor>
	HashMap<TKey, TData, HashFunctor>::Iterator::Iterator(const Iterator& rhs) :
		mOwner(rhs.mOwner), mIndex(rhs.mIndex), mIterator(rhs.mIterator)
	{
	}

	template<typename TKey, typename TData, typename HashFunctor>
	HashMapIterator& HashMap<TKey, TData, HashFunctor>::Iterator::operator=(const Iterator& rhs)
	{
		if (this != &rhs)
		{
			mOwner = rhs.mOwner;
			mIndex = rhs.mIndex;
			mIterator = rhs.mIterator;
		}
		return *this;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	HashMap<TKey, TData, HashFunctor>::Iterator::~Iterator()
	{
		mOwner = nullptr;
		mIndex = 0;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	typename HashMap<TKey, TData, HashFunctor>::PairType& HashMap<TKey, TData, HashFunctor>::Iterator::operator*()
	{
		if (mOwner == nullptr)
		{
			throw std::exception("Your mOwner is nullptr");
		}
		return *mIterator;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	typename HashMap<TKey, TData, HashFunctor>::PairType* HashMap<TKey, TData, HashFunctor>::Iterator::operator->()
	{
		if (mOwner == nullptr)
		{
			throw std::exception("Your mOwner is nullptr");
		}
		return &(*mIterator);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	bool HashMap<TKey, TData, HashFunctor>::Iterator::operator==(const Iterator& rhs) const
	{
		return ((mOwner == rhs.mOwner) && (mIndex == rhs.mIndex) && (mIterator == rhs.mIterator));
	}

	template<typename TKey, typename TData, typename HashFunctor>
	bool HashMap<TKey, TData, HashFunctor>::Iterator::operator!=(const Iterator& rhs) const
	{
		return !(operator==(rhs));
	}

	template<typename TKey, typename TData, typename HashFunctor>
	HashMapIterator& HashMap<TKey, TData, HashFunctor>::Iterator::operator++()
	{
		if (mOwner)
		{
			if ((mOwner->mBucket)[mIndex].end() != ++mIterator)
			{
				return *this;
			}
		
			while (mIndex < mOwner->mBucket.Size())
			{
				mIterator = (mOwner->mBucket)[mIndex].begin();

				if (++mIndex >= (mOwner->mBucket).Size())
				{
					mIterator = ChainIterator();
					return *this;
				}
				if ((mOwner->mBucket)[mIndex].Size() != 0)
				{
					break;
				}
			}
			mIterator = (mOwner->mBucket)[mIndex].begin();

		}
		return *this;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	HashMapIterator HashMap<TKey, TData, HashFunctor>::Iterator::operator++(int)
	{
		HashMapIterator tempIterator = *this;
		operator++();
		return tempIterator;
	}

#pragma endregion

#pragma region HashMap
	template<typename TKey, typename TData, typename HashFunctor>
	HashMap<TKey, TData, HashFunctor>::HashMap(std::uint32_t size) :
		mSize(0), mBeginIndex(size), mBucket(size)
	{
		mBucket.At(size - 1);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	HashMap<TKey, TData, HashFunctor>::~HashMap()
	{
	}

	template<typename TKey, typename TData, typename HashFunctor>
	HashMap<TKey, TData, HashFunctor>& HashMap<TKey, TData, HashFunctor>::operator=(const HashMap& rhs)
	{
		if (this != &rhs)
		{
			Clear();

			mBucket = BucketType(rhs.mBucket.Size());
		    mBucket = (rhs.mBucket);
			mBeginIndex = rhs.mBeginIndex;
			mSize = rhs.mSize;
		}
		return *this;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	HashMapIterator HashMap<TKey, TData, HashFunctor>::Find(const TKey& key) const
	{
		if (mSize == 0)
		{
			return end();
		}

		uint32_t index = mHashFunctor(key) %  std::max<std::uint32_t>(mBucket.Size(), 1);

		for (auto it = (mBucket)[index].begin(); it != (mBucket)[index].end(); ++it)
		{
			PairType pair = *it;
			if (pair.first == key)
			{
				return Iterator(const_cast<HashMap<TKey,TData,HashFunctor>*>(this), index, it);
			}
		}
		return end();
 	}

	template<typename TKey, typename TData, typename HashFunctor>
	HashMapIterator HashMap<TKey, TData, HashFunctor>::Insert(const PairType& pair, bool& inserted) 
	{
		//Check if key already exist, if it does iit returns the iterator of the found key

		auto foundKey = Find(pair.first);
		if (foundKey != end())
		{
			inserted = false;
			return foundKey;
		}

		uint32_t index = mHashFunctor(pair.first) % std::max<std::uint32_t>(mBucket.Size(), 1);
		(mBucket)[index].PushFront(pair);

		if (mBeginIndex > index || mSize == 0)
		{
			mBeginIndex = index;
		}

		++mSize;
		inserted = true;
		return Iterator(this, index, (mBucket)[index].begin());
	}
	
	template<typename TKey, typename TData, typename HashFunctor>
	HashMapIterator HashMap<TKey, TData, HashFunctor>::Insert(const TKey& key, const TData& data, bool& inserted) 
	{
		return Insert(PairType(key,data), inserted);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	HashMapIterator HashMap<TKey, TData, HashFunctor>::Insert(const PairType& pair)
	{
		bool inserted;
		return Insert(pair, inserted);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	HashMapIterator  HashMap<TKey, TData, HashFunctor>::Insert(const TKey& key, const TData& data)
	{
		return Insert(PairType(key, data));
	}

	template<typename TKey, typename TData, typename HashFunctor>
	TData& HashMap<TKey, TData, HashFunctor>::operator[](const TKey& key)
	{
		PairType pair;
		pair.first = key;
		bool inserted;
		Iterator it = Insert(pair, inserted);
		return (*it).second;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	void HashMap<TKey, TData, HashFunctor>::Remove(const TKey& key)
	{
		uint32_t index = mHashFunctor(key) % std::max<std::uint32_t>(mBucket.Size(), 1);

		auto it = Find(key);

		if (index == mBeginIndex && (mBucket)[index].Size() == 1)
		{
			for (uint32_t i = 0; i < mBucket.Size(); i++)
			{
				if ((mBucket)[i].Size() != 0)
				{
					mBeginIndex = i;
					break;
				}
			}
		}

		if (it != end())
		{
			(mBucket)[index].Remove(*it);
			mSize--;
		}
		
	}

	template<typename TKey, typename TData, typename HashFunctor>
	void HashMap<TKey, TData, HashFunctor>::Clear()
	{
		mBeginIndex = mBucket.Size();
		for (uint32_t i = 0; i < mBucket.Size(); ++i)
		{
			(mBucket)[i].Clear();
		}
		mSize = 0;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	std::uint32_t HashMap<TKey, TData, HashFunctor>::Size() const
	{
		return mSize;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	bool HashMap<TKey, TData, HashFunctor>::ContainsKey(const TKey& key) const
	{
		return Find(key) != end();
	}

	template<typename TKey, typename TData, typename HashFunctor>
	HashMapIterator HashMap<TKey, TData, HashFunctor>::begin() const
	{
		if (mSize == 0)
		{
			return end();
		}
		ChainType::Iterator iter = (mBucket)[mBeginIndex].begin();
		return Iterator(const_cast<HashMap<TKey, TData, HashFunctor >*> (this), mBeginIndex, iter);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	HashMapIterator HashMap<TKey, TData, HashFunctor>::end() const
	{
		ChainType::Iterator iter = ChainType::Iterator();
		return Iterator(const_cast<HashMap<TKey, TData, HashFunctor>*>(this), mBucket.Size(), iter);
	}

#pragma endregion
}

