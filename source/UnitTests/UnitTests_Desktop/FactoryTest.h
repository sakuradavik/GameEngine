#include <cxxtest/TestSuite.h>
#include "Factory.h"
#include "Foo.h"
#include "Scope.h"
#include "Attribute.h"

using namespace Library;
using namespace Unit_Tests;

ConcreteFactory(RTTI, Foo)
ConcreteFactory(RTTI,Scope)
ConcreteFactory(RTTI,Attribute)

class FactoryTestSuite : public CxxTest::TestSuite
{
public:

	void TestClassNameAndFind()
	{
		FooFactory fooFactory;
		Factory<RTTI>* fooFactoryPointer = Factory<RTTI>::Find("Foo");
		TS_ASSERT_EQUALS(fooFactoryPointer->ClassName(), "Foo");
		TS_ASSERT_EQUALS(fooFactory.ClassName(), "Foo");
		TS_ASSERT_EQUALS(fooFactoryPointer->ClassName(), fooFactory.ClassName());

		ScopeFactory scopeFactory;
		Factory<RTTI>* scopeFactoryPointer = Factory<RTTI>::Find("Scope");
		TS_ASSERT_EQUALS(scopeFactoryPointer->ClassName(), "Scope");
		TS_ASSERT_EQUALS(scopeFactory.ClassName(), "Scope");
		TS_ASSERT_EQUALS(scopeFactoryPointer->ClassName(), scopeFactory.ClassName());

		AttributeFactory attributeFactory;
		Factory<RTTI>* attributeFactoryPointer = Factory<RTTI>::Find("Attribute");
		TS_ASSERT_EQUALS(attributeFactoryPointer->ClassName(), "Attribute");
		TS_ASSERT_EQUALS(attributeFactory.ClassName(), "Attribute");
		TS_ASSERT_EQUALS(attributeFactoryPointer->ClassName(), attributeFactory.ClassName());
	}

	void TestCreate()
	{
		FooFactory fooFactory;
		RTTI* foo = Factory<RTTI>::Create("Foo");
		TS_ASSERT_DIFFERS(foo, nullptr);
		TS_ASSERT(foo->Is("Foo"));
		delete foo;

		foo = fooFactory.Create();
		TS_ASSERT_DIFFERS(foo, nullptr);
		TS_ASSERT(foo->Is("Foo"));
		delete foo;

		ScopeFactory scopeFactory;
		RTTI* scope = Factory<RTTI>::Create("Scope");
		TS_ASSERT_DIFFERS(scope, nullptr);
		TS_ASSERT(scope->Is("Scope"));
		delete scope;

		scope = scopeFactory.Create();
		TS_ASSERT_DIFFERS(scope, nullptr);
		TS_ASSERT(scope->Is("Scope"));
		delete scope;

		AttributeFactory attributeFactory;
		RTTI* attribute = Factory<RTTI>::Create("Attribute");
		TS_ASSERT_DIFFERS(attribute, nullptr);
		TS_ASSERT(attribute->Is("Attribute"));
		delete attribute;

		attribute = attributeFactory.Create();
		TS_ASSERT_DIFFERS(attribute, nullptr);
		TS_ASSERT(attribute->Is("Attribute"));
		delete attribute;
	}

	void TestFind()
	{

	}

	void TestIterator()
	{
		FooFactory* fooFactory = new FooFactory();
		HashMap<std::string, Factory<RTTI>*>::Iterator it = Factory<RTTI>::begin();
		TS_ASSERT_EQUALS("Foo", (*it).second->ClassName());
		delete fooFactory;

		ScopeFactory* scopeFactory = new ScopeFactory();
		it = Factory<RTTI>::begin();
		TS_ASSERT_EQUALS("Scope", (*it).second->ClassName());
		delete scopeFactory;

		AttributeFactory* attributeFactory = new AttributeFactory();
		it = Factory<RTTI>::begin();
		TS_ASSERT_EQUALS("Attribute", (*it).second->ClassName());
		delete attributeFactory;
	}

	void TestException()
	{
		TS_ASSERT_THROWS_ANYTHING(Factory<RTTI>::Find(""));
		TS_ASSERT_THROWS_ANYTHING(Factory<RTTI>::Create(""));
	}

	void TestAdd()
	{
		Factory<RTTI>* fooFactory = Factory<RTTI>::Find("Foo");
		TS_ASSERT_EQUALS(fooFactory, nullptr);

		FooFactory fooFactory2;
		fooFactory = Factory<RTTI>::Find("Foo");
		TS_ASSERT_EQUALS(fooFactory, &fooFactory2);

		Factory<RTTI>* scopeFactory = Factory<RTTI>::Find("Scope");
		TS_ASSERT_EQUALS(scopeFactory, nullptr);

		ScopeFactory scopeFactory2;
		scopeFactory = Factory<RTTI>::Find("Scope");
		TS_ASSERT_EQUALS(scopeFactory, &scopeFactory2);

		Factory<RTTI>* attributeFactory = Factory<RTTI>::Find("Attribute");
		TS_ASSERT_EQUALS(attributeFactory, nullptr);

		AttributeFactory attributeFactory2;
		attributeFactory = Factory<RTTI>::Find("Attribute");
		TS_ASSERT_EQUALS(attributeFactory, &attributeFactory2);
	}

	void TestRemove()
	{
		FooFactory* fooFactory = new FooFactory();
		Factory<RTTI>* fooFactory2 = Factory<RTTI>::Find("Foo");
		TS_ASSERT_EQUALS(fooFactory, fooFactory2);

		delete fooFactory;
		fooFactory2 = Factory<RTTI>::Find("Foo");
		TS_ASSERT_EQUALS(fooFactory2, nullptr);

		ScopeFactory* scopeFactory = new ScopeFactory();
		Factory<RTTI>* scopeFactory2 = Factory<RTTI>::Find("Scope");
		TS_ASSERT_EQUALS(scopeFactory, scopeFactory2);

		delete scopeFactory;
		scopeFactory2 = Factory<RTTI>::Find("Scope");
		TS_ASSERT_EQUALS(scopeFactory2, nullptr);

		AttributeFactory* attributeFactory = new AttributeFactory();
		Factory<RTTI>* attributeFactory2 = Factory<RTTI>::Find("Attribute");
		TS_ASSERT_EQUALS(attributeFactory2, attributeFactory);

		delete attributeFactory;
		attributeFactory2 = Factory<RTTI>::Find("Attribute");
		TS_ASSERT_EQUALS(attributeFactory2, nullptr);

	}
};