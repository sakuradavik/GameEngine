namespace Library
{
	template <typename T>
	RTTI_DEFINITIONS(Event<T>);

	template <typename T>
	SList<EventSubscriber*> Event<T>::sSubscriber = SList<EventSubscriber*>();

	template <typename T>
	std::mutex Event<T>::mMutex = std::mutex();

	template <typename T>
	Event<T>::Event(const T& message) :
		EventPublisher(sSubscriber, mMutex), mMessage(message)
	{
	}

	template <typename T>
	void Event<T>::Subscribe(EventSubscriber& eventSubscriber)
	{
		std::lock_guard<std::mutex> lock(mMutex);
		sSubscriber.PushBack(&eventSubscriber);
	}

	template <typename T>
	void Event<T>::Unsubscribe(EventSubscriber& eventSubscriber)
	{
		std::lock_guard<std::mutex> lock(mMutex);
		sSubscriber.Remove(&eventSubscriber);
	}

	template <typename T>
	void Event<T>::UnsubscribeAll()
	{
		std::lock_guard<std::mutex> lock(mMutex);
		sSubscriber.Clear();
	}

	template <typename T>
	T& Event<T>::Message()
	{
		std::lock_guard<std::mutex> lock(mMutex);
		return mMessage;
	}
}