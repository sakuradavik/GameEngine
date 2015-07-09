#pragma once

#include "HashMap.h"

namespace Library
{
	template <typename T>
	class Factory
	{
	public:
		/**
		* @brief Returns a string representing the name of the class the factory instantiates
		* @param None
		* @return std::string& A string reference to the class this factory can create
		*/
		virtual const std::string& ClassName() const = 0;

		/**
		* @brief  Return the address of a concrete
		* product associated with this concrete factory class
		* @param None
		* @return Pointer to the template Type Class
		*/
		virtual T* Create() const = 0;

		/**
		* @brief Given a class name, it will return the associated concrete factory.
		* @param const string& a reference to the class's whose factory you want
		* @return A pointer to a factory that can create classes of this name
		*/
		static Factory* Find(const std::string& strClassName);

		/**
		* @brief Given a class name, return a new object of that type.
		* @param String Reference to the desired class name
		* @return A newly constructed class that is associated with this name
		*/
		static T* Create(const std::string& strClassName);

		/**
		* @brief Given a class name, return a new object of that type.
		* @param String Reference to the desired class name
		* @return A newly constructed class that is associated with this name
		*/
		static typename HashMap<std::string, Factory*>::Iterator begin();
		static typename HashMap<std::string, Factory*>::Iterator end();

	protected:
		/**
		* @brief  Given a reference to a concrete factory, add it to the 
		* list of factories for this abstract factory.
		* @param A reference to a Factory
		* @return void
		*/
		static void Add(Factory&  pFactory);

		/**
		* @brief Given a reference to a concrete factory, remove it
		* from the list of factories for this abstract factory.
		* @param A reference to a Factory
		* @return void
		*/
		static void Remove(Factory& pFactory);

	private:
		static HashMap<std::string, Factory*> sFactoryTable;
	};

}

#define ConcreteFactory(AbstractProduct, ConcreteProduct)					\
class ConcreteProduct ## Factory : public Factory < AbstractProduct >	    \
{																			\
public:																		\
	ConcreteProduct ## Factory() :											\
		mClassName(#ConcreteProduct)										\
	{																		\
		Add(*this);															\
	}																		\
																			\
	~ConcreteProduct ## Factory()												\
	{																		\
		Remove(*this);														\
	}																		\
																			\
	virtual const std::string& ClassName() const override					\
	{																		\
		return mClassName;													\
	}																		\
																			\
	virtual ConcreteProduct* Create() const override						\
	{																		\
		return new ConcreteProduct();										\
	}																		\
																			\
private:																	\
	std::string mClassName;													\
};																

#include "Factory.inl"