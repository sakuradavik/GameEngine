namespace Library
{
	template<typename T>
	typename HashMap<std::string, Factory<T>*> Factory<T>::sFactoryTable;

	template < typename T >
	Factory<T>* Factory<T>::Find(const std::string& strClassName)
	{
		if (strClassName.empty())
		{
			throw std::exception("Invalid Class Name");
		}

		auto found = sFactoryTable.Find(strClassName);
		if (found != sFactoryTable.end())
		{
			return found->second;
		}
		return nullptr;
	}

	template < typename T >
	T* Factory<T>::Create(const std::string& strClassName)
	{
		Factory* foundFactory = Find(strClassName);
		if (foundFactory)
		{
			return foundFactory->Create();
		}
		return nullptr;
	}

	template < typename T >
	typename HashMap<std::string, Factory<T>*>::Iterator Factory<T>::begin() 
	{
		return sFactoryTable.begin();
	}

	template < typename T >
	typename HashMap<std::string, Factory<T>*>::Iterator Factory<T>::end() 
	{
		return sFactoryTable.end();
	}

	template < typename T >
	void Factory<T>::Add(Factory<T>& pFactory)
	{
		if (pFactory.ClassName().empty())
		{
			throw std::exception("Invalid class name");
		}
		bool insert;
		sFactoryTable.Insert(pFactory.ClassName(), &pFactory, insert);
	}

	template < typename T >
	void Factory<T>::Remove(Factory<T>& pFactory)
	{
		if (pFactory.ClassName().empty())
		{
			throw std::exception("Invalid class name");
		}
		sFactoryTable.Remove(pFactory.ClassName());
	}

}