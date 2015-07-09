namespace Library
{
#pragma region Stack

	template <typename T>
	Stack<T>::Stack()
		:mSList()
	{
	}

	template <typename T>
	Stack<T>::Stack(const Stack& rhs)
		: mSList(rhs.mSList)
	{
	}

	template <typename T>
	Stack<T>& Stack<T>::operator=(const Stack& rhs)
	{
		if (this != &rhs)
		{
			mSList.operator=(rhs.mSList);
		}
		return *this;
	}

	template <typename T>
	Stack<T>::~Stack()
	{
		Clear();
	}

	template <typename T>
	void Stack<T>::Push(const T& item)
	{
		mSList.PushFront(item);
	}

	template <typename T>
	void Stack<T>::Pop()
	{
		mSList.PopFront();
	}

	template <typename T>
	T& Stack<T>::Top()
	{
		return mSList.Front();
	}

	template <typename T>
	const T& Stack<T>::Top() const
	{
		return mSList.Front();
	}

	template <typename T>
	std::uint32_t Stack<T>::Size() const
	{
		return mSList.Size();
	}

	template <typename T>
	bool Stack<T>::IsEmpty() const
	{
		return mSList.IsEmpty();
	}

	template <typename T>
	void Stack<T>::Clear()
	{
		mSList.Clear(); 
	}

#pragma endregion
}