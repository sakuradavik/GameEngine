namespace Library
{
#pragma region Node

	template <typename T>
	SList<T>::Node::Node(const T& data, Node* next) :
		mData(data), mNext(next)
	{
	}

	template <typename T>
	typename SList<T>::Node* SList<T>::Node::Next()
	{
		return mNext;
	}

	template <typename T>
	T& SList<T>::Node::Data()
	{
		return mData;
	}

	template <typename T>
	void SList<T>::Node::SetNext(Node* next)
	{
		mNext = next;
	}

#pragma endregion

#pragma region Iterator

	template <typename T>
	SList<T>::Iterator::Iterator(const SList* owner, Node* node) :
		mOwner(owner), mNode(node)
	{
	}

	template <typename T>
	SList<T>::Iterator::Iterator() :
		mOwner(nullptr), mNode(nullptr)
	{
	}

	template <typename T>
	SList<T>::Iterator::Iterator(const Iterator& rhs) :
		mOwner(nullptr), mNode(nullptr)
	{
		operator=(rhs);
	}

	template <typename T>
	typename SList<T>::Iterator& SList<T>::Iterator::operator=(const Iterator& rhs)
	{
		if (this != &rhs)
		{
			mOwner = rhs.mOwner;
			mNode = rhs.mNode;
		}
		return *this;

	}

	template <typename T>
	SList<T>::Iterator::~Iterator()
	{
		mOwner = nullptr;
		mNode = nullptr;
	}

	template <typename T>
	T& SList<T>::Iterator::operator*()
	{
		if (mNode == nullptr)
		{
			throw std::exception("You are trying to derefrence a nullptr");
		}
		return mNode->Data();
	}

	template <typename T>
	bool SList<T>::Iterator::operator==(const Iterator& rhs) const
	{
		return ((rhs.mOwner == mOwner) && (rhs.mNode == mNode));
	}

	template <typename T>
	bool SList<T>::Iterator::operator!=(const Iterator& rhs) const
	{
		return !(operator==(rhs));
	}

	template <typename T>
	typename SList<T>::Iterator& SList<T>::Iterator::operator++()
	{
		if (mNode == nullptr)
		{
			throw std::exception("You are trying to advance a mullptr");
		}
		mNode = mNode->Next();
		return *this;
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::Iterator::operator++(int)
	{
		SList<T>::Iterator tempNode = *this;
		operator++();
		return tempNode;
	}
	
#pragma endregion

#pragma region SList

	//Constant Time Method
	template <typename T>
	SList<T>::SList() :
		mFront(nullptr), mBack(nullptr), mSize(0)
	{
	}

	template <typename T>
	void SList<T>::PushFront(const T& data)
	{
		if (mFront)
		{
			mFront = new Node(data, mFront);
		}
		else
		{
			mFront = new Node(data);
			mBack = mFront;
		}
		mSize++;
	}

	template <typename T>
	void SList<T>::PopFront()
	{
		//if the list is not empty
		if (mFront)
		{
			Node* tempFrontNextNode = mFront->Next();
			delete mFront;
			mFront = tempFrontNextNode;
			mSize--;
		}
		
	}

	template <typename T>
	void SList<T>::PushBack(const T& data)
	{
		//if the list is not empty
		if (mFront)
		{
			Node* newBackNode = new Node(data);
			mBack->SetNext(newBackNode);
			mBack = newBackNode;
		}
		else
		{
			mBack = new Node(data);
			mFront = mBack;
		}
		mSize++;
	}

	template <typename T>
	bool SList<T>::IsEmpty() const
	{
		return mSize == 0;
	}
	
	template <typename T>
	T& SList<T>::Front() 
	{
		if (IsEmpty())
		{
			throw std::exception("Empty List");
		}
		return mFront->Data();
		
	}

	template <typename T>
	T& SList<T>::Back() 
	{
		if (IsEmpty())
		{
			throw std::exception("Empty List");
		}
		return mBack->Data();
	}

	template <typename T>
	std::uint32_t SList<T>::Size() const
	{
		return mSize;
	}

	//Linear Time Methods
	template <typename T>
	 SList<T>::SList(const SList& rhs)
		 :mSize(0), mFront(nullptr), mBack(nullptr)
	{
		 operator=(rhs); 
	}

	template <typename T>
	SList<T>& SList<T>::operator=(const SList& rhs)
	{
		if (this != &rhs)
		{
			Clear();
			for (auto& it : rhs)
			{
				PushBack(it);
			}
		}
		return *this;
	}

	template <typename T>
	SList<T>::~SList()
	{
		Clear();
	}

	template <typename T>
	void SList<T>::Clear()
	{
		while (!IsEmpty())
		{
			PopFront();
		}
	}

	//Iterator Methods
	template <typename T>
	typename SList<T>::Iterator SList<T>::begin() const
	{
		return Iterator(this, mFront);
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::end() const
	{
		return Iterator(this, nullptr);
	}

	template <typename T>
	void SList<T>::InsertAfter(const Iterator& it, const T& data)
	{
		if (it.mOwner == this)
		{
			if (mFront && (it.mNode->Next() != nullptr))
			{
				Node* newNode = new Node(data, it.mNode->Next());
				it.mNode->SetNext(newNode);
				mSize++;
			}
			else
			{
				PushBack(data);
			}
		}
		else
		{
			throw std::exception("Invalid iterator. Owned by a different SList");
		}
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::Find(const T& value) const
	{
		auto it = begin();
		for (; it != end(); ++it)
		{
			if (*it == value)
			{
				break;
			}
		}
		return it;
	}

	template <typename T>
	void SList<T>::Remove(const T& value)
	{
			Node* previousNode = mFront;

			if (mFront && (mFront->Data() == value))
			{
				PopFront();
				return;
			}

			while (previousNode != nullptr)
			{
				Node* currentNode = previousNode->Next();
				if (currentNode->Data() == value)
				{
					if (currentNode->Next() != nullptr)
					{
						previousNode->SetNext(currentNode->Next());
						delete currentNode;
					}
					else if (currentNode->Next() == nullptr)
					{
						mBack = previousNode;
						previousNode->SetNext(nullptr);
						delete currentNode;
					}
					mSize--;
					return;
				}
				previousNode = previousNode->Next();
			}
	}

#pragma endregion
}