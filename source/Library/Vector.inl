namespace Library
{
#pragma region Iterator

	template <typename T>
	Vector<T>::Iterator::Iterator(Vector* owner, std::uint32_t index) :
		mOwner(owner), mIndex(index)
	{
	}

	template <typename T>
	Vector<T>::Iterator::Iterator() :
		mOwner(nullptr), mIndex(0)
	{

	}

	template <typename T>
	Vector<T>::Iterator::Iterator(const Iterator& rhs) :
		mOwner(rhs.mOwner), mIndex(rhs.mIndex)
	{
	}

	template <typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator=(const Iterator& rhs)
	{
		if (*this != rhs)
		{
			mOwner = rhs.mOwner;
			mIndex = rhs.mIndex;
		}
		return *this;
	}

	template <typename T>
	Vector<T>::Iterator::~Iterator()
	{
		mOwner = nullptr;
		mIndex =0;
	}

	template <typename T>
	T& Vector<T>::Iterator::operator*()
	{
		if (mIndex == mOwner->Size())
		{
			throw std::exception("You are trying to dereference a non-valid index");
		}
		return (*mOwner)[mIndex];
	}

	template <typename T>
	bool Vector<T>::Iterator::operator==(const Iterator& rhs) const
	{
		return ((rhs.mOwner == mOwner) && (rhs.mIndex == mIndex));
	}

	template <typename T>
	bool Vector<T>::Iterator::operator!=(const Iterator& rhs) const
	{
		return !(operator==(rhs));
	}

	template <typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator++()
	{
		if (mIndex == mOwner->Size())
		{
			throw std::exception("You are trying to advance past the suze of the vector");
		}
		mIndex++;
		return *this;
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int)
	{
		Vector<T>::Iterator tempIterator = *this;
		operator++();
		return tempIterator;
	}

#pragma endregion

#pragma region Vector

	template <typename T>
	const uint32_t Vector<T>::DefaultCapacity = 3;

	template <typename T>
	Vector<T>::Vector(std::uint32_t DefaultCapacity) :
		mSize(0), mCapacity(0), mItems(nullptr)
	{
		Reserve(DefaultCapacity);
	}

	template <typename T>
	T& Vector<T>::operator[](std::uint32_t index)
	{
		if (index >= mSize)
		{
			throw std::exception("Index is greater than the size");
		}
		return mItems[index];
	}

	template <typename T>
	T& Vector<T>::operator[](std::uint32_t index) const
	{
		if (index >= mSize)
		{
			throw std::exception("Index is greater than the size");
		}
		return mItems[index];
	}

	template <typename T>
	void Vector<T>::PopBack()
	{
		if (mItems)
		{
			mSize--;
		}
	}

	template <typename T>
	bool Vector<T>::IsEmpty()
	{
		return (mSize == 0);
	}

	template <typename T>
	T& Vector<T>::Front()
	{
		if (IsEmpty())
		{
			throw std::exception("Empty Vector");
		}
		return mItems[0];
	}

	template <typename T>
	T& Vector<T>::Front() const
	{
		if (IsEmpty())
		{
			throw std::exception("Empty Vector");
		}
		return mItems[0];
	}

	template <typename T>
	T& Vector<T>::Back()
	{
		if (IsEmpty())
		{
			throw std::exception("Empty Vector");
		}
		return mItems[mSize - 1];
	}

	template <typename T>
	T& Vector<T>::Back() const
	{
		if (IsEmpty())
		{
			throw std::exception("Empty Vector");
		}
		return mItems[mSize - 1];
	}

	template <typename T>
	std::uint32_t Vector<T>::Size() const
	{

		return mSize;
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::begin() const
	{
		return Iterator(const_cast<Vector<T>*>(this), 0);
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::end() const
	{
		return Iterator(const_cast<Vector<T>*>(this), mSize);
	}

	template <typename T>
	void Vector<T>::PushBack(const T& data)
	{
		if (mCapacity == 0)
		{
			Reserve(3);
		}

		if (mSize >= mCapacity)
		{
			Reserve(2*mCapacity);
		}

		mItems[mSize] = data;
		mSize++;
	}

	template <typename T>
	Vector<T>::Vector(const Vector& rhs) :
		mSize(0), mCapacity(0), mItems(nullptr)
	{
		operator=(rhs);
	}

	template <typename T>
	Vector<T>& Vector<T>::operator=(const Vector& rhs)
	{
		if (this != &rhs)
		{
			Clear();
			auto it = rhs.begin();
			for (; it != rhs.end(); ++it)
			{
				PushBack(*it);
			}
		}
		return *this;
	}

	template <typename T>
	T& Vector<T>::At(std::uint32_t index)
	{
		if (index > mCapacity)
		{
			throw std::exception("Index is beyond the capacity");
		}
		if (index > mSize)
			mSize = index+1;

		return mItems[index];
	}

	template <typename T>
	Vector<T>::~Vector()
	{
		Clear();
	}

	template <typename T>
	void Vector<T>::Reserve(std::uint32_t reserveCapacity)
	{
		if (reserveCapacity > mCapacity)
		{
			T* newItems = new T[reserveCapacity];
			if (mSize > 0)
			{
				int i = 0;
				for (auto it = begin(); it != end(); ++it)
				{
					newItems[i++] = *it;
				}
			}
			delete[] mItems;
			mItems = newItems;
			mCapacity = reserveCapacity;
		}
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::Find(const T& value) const
	{
		auto it = begin();
		for (; it != end(); ++it)
		{
			if(*it == value)
			{
				break;
			}
		}
		return it;
	}

	template <typename T>
	void Vector<T>::Clear()
	{
		delete[] mItems;
		mSize = 0;
		mCapacity = 0;
		mItems = nullptr;

	}

	template <typename T>
	T& Vector<T>::Remove(std::uint32_t index)
	{
		T& removedItem = mItems[index];

		if (mSize > 1)
		{
			for (std::uint32_t i = index; i < mSize - 1; ++i)
			{
				mItems[i] = mItems[i + 1];
			}
		}

		--mSize;
		return removedItem;
	}

	template <typename T>
	std::uint32_t Vector<T>::Capacity()
	{
		return mCapacity;
	}

#pragma endregion
}