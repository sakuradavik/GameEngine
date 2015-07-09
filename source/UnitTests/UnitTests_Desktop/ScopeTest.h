#include <cxxtest/TestSuite.h>
#include "Foo.h"
#include "Scope.h"
#include "Datum.h"

using namespace Library;
using namespace Unit_Tests;

class ScopeTestSuite : public CxxTest::TestSuite
{
public:
	void setUp()
	{

	}

	void tearDown()
	{
		mScope.Clear();
	}

	void TestCopyConstructor(void)
	{
		std::string key = "hi";
		Scope& s = mScope.AppendScope(key);
		TS_ASSERT_EQUALS(s.GetParent(), &mScope);

		mScope.Append("bye", Datum::DatumType::Integer);
		mScope.Append("konichiwa", Datum::DatumType::Vector);
		mScope.Append("hola", Datum::DatumType::String);

		mScope[1] = 5;
		mScope[2] = glm::vec4(1.0f, 2.0f, 3.0f, 4.0f);
		mScope[3] = "hola";

		s.AppendScope("adois");

		Scope s2 = mScope;
		TS_ASSERT_EQUALS(s2 == mScope, true);
	}

	void TestAssignmentOperator(void)
	{
		std::string key = "hi";
		Scope& s = mScope.AppendScope(key);
		TS_ASSERT_EQUALS(s.GetParent(), &mScope);

		mScope.Append("bye", Datum::DatumType::Integer);
		mScope.Append("konichiwa", Datum::DatumType::Vector);
		mScope.Append("hola", Datum::DatumType::String);

		mScope[1] = 5;
		mScope[2] = glm::vec4(1.0f, 2.0f, 3.0f, 4.0f);
		mScope[3] = "hola";

		s.AppendScope("adois");
		
		Scope s2;
		s2 = mScope;
		TS_ASSERT_EQUALS(s2 == mScope, true);
	}

	void TestInitialization(void)
	{
		Scope *s = new Scope();
		TS_ASSERT_DIFFERS(s, nullptr);
		delete s;

	}

	void TestFind(void)
	{
		std::string key = "hi";
		Datum& d = mScope.Append(key);
		d.SetType(Datum::DatumType::Matrix);

		std::string key2 = "bye";
		Datum& d2 = mScope.Append(key2);
		d2.SetType(Datum::DatumType::Vector);

		std::string key3 = "konichiwa";
		Datum& d3 = mScope.Append(key3);
		d3.SetType(Datum::DatumType::String);

		Datum* d4 = mScope.Find(key);
		TS_ASSERT_EQUALS(*d4, d);

		d4 = mScope.Find(key2);
		TS_ASSERT_EQUALS(*d4, d2);

		d4 = mScope.Find(key3);
		TS_ASSERT_EQUALS(*d4, d3);

		std::string key4 = "hola";
		Datum& d5 = mScope.Append(key4);
		glm::vec4 * vec = new glm::vec4(1.0f, 2.0f, 3.0f, 4.0f);
		d5.SetStorage(vec, 1);

		Datum * d6 = mScope.Find(key4);
		TS_ASSERT_EQUALS(*d6, d5);
		delete vec;
	}

	void TestSearch(void)
	{
		std::string key = "hi";
		std::string key2 = "bye";
		std::string key3 = "hola";
		std::string key4 = "konichiwa";
		std::string key5 = "adios";

		Datum& d1 = mScope.Append(key, Datum::DatumType::Matrix);
		mScope.Append(key2,Datum::DatumType::Vector);
		mScope.Append(key3, Datum::DatumType::String);

		Datum * d = mScope.Search(key);
		TS_ASSERT_DIFFERS(d, nullptr);
		TS_ASSERT_EQUALS(d->GetType(), Datum::DatumType::Matrix);
		TS_ASSERT_EQUALS(d1, *d);

		d = mScope.Search(key4);
		TS_ASSERT_EQUALS(d, nullptr);

		Scope& s = mScope.AppendScope(key5);
		s.Append(key4, Datum::DatumType::String);
		Scope** foundScope = new Scope*();
		d = s.Search(key, foundScope);
		TS_ASSERT_EQUALS(*d, d1);
		TS_ASSERT_EQUALS(*foundScope, &mScope);

		delete foundScope;
	}

	void TestAppend(void)
	{
		std::string key = "hi";
		Datum& d = mScope.Append(key);
		d.SetType(Datum::DatumType::Integer);
		d = 5;
		Datum& d2 = mScope.Append(key);
		TS_ASSERT_EQUALS(d.GetType(), d2.GetType());
		TS_ASSERT_EQUALS(mScope[key].GetInteger(), 5);
		TS_ASSERT_EQUALS(mScope[0], d);

		std::string key2 = "bye";
		Datum& d3 = mScope.Append(key2);
		d3 = "bye";
		TS_ASSERT_EQUALS(d3.GetType(), Datum::DatumType::String);
		TS_ASSERT_EQUALS(mScope[key2].GetString(), "bye");
		TS_ASSERT_EQUALS(mScope[1], d3);
		TS_ASSERT_EQUALS(mScope[0], d);
	}

	void TestAppendScope(void)
	{
		std::string key = "hi";
		Scope& s = mScope.AppendScope(key);
		TS_ASSERT_EQUALS(s.GetParent(), &mScope);

		std::string key2 = "bye";
		Datum& d = s.Append(key2,Datum::DatumType::Integer);
		d = 20;

		std::string key3 = "hola";
		Scope& s2 = s.AppendScope(key3);
		TS_ASSERT_EQUALS(s2.GetParent(), &s);
		TS_ASSERT_EQUALS(s2.GetParent()->GetParent(), &mScope);
	}

	void TestOperatorEqualAndNotEqual(void)

	{
		std::string key = "hi";
		mScope.Append(key, Datum::DatumType::Vector);

		mScope["bye"].SetType(Datum::DatumType::Integer);
		mScope["konichiwa"].SetType(Datum::DatumType::Pointer);
		mScope["hola"].SetType(Datum::DatumType::String);

		Scope scope;
		scope.Append(key, Datum::DatumType::Vector);
		scope["bye"].SetType(Datum::DatumType::Integer);
		scope["konichiwa"].SetType(Datum::DatumType::Pointer);
		scope["hola"].SetType(Datum::DatumType::String);

		TS_ASSERT_EQUALS(scope == mScope,true);

		Scope scope2;
		scope2.Append(key, Datum::DatumType::Vector);
		scope2["konichiwa"].SetType(Datum::DatumType::Pointer);
		scope2["bye"].SetType(Datum::DatumType::Integer);

		TS_ASSERT_EQUALS(mScope != scope2, true);
	}

	void TestAdopt(void)
	{
		std::string key = "hi";
		Scope& s = mScope.AppendScope(key);
		TS_ASSERT_EQUALS(s.GetParent(), &mScope);

		mScope["bye"].SetType(Datum::DatumType::Integer);
		mScope["konichiwa"].SetType(Datum::DatumType::Pointer);
		mScope["hola"].SetType(Datum::DatumType::String);

		Datum * d = mScope.Find("hi");
		TS_ASSERT_EQUALS(d->Size(), 1);

		Scope * s2 = new Scope();
		mScope.Adopt(*s2, "hi", 1);
		
		TS_ASSERT_EQUALS(mScope[0], *d);
		TS_ASSERT_EQUALS(d->Size(), 2);
		TS_ASSERT_EQUALS(d->GetScope(1), s2);

		Scope * s3 = new Scope();
		mScope.Adopt(*s3, "hi", 0);
		d = mScope.Find("hi");
		TS_ASSERT_EQUALS(mScope[0], *d);
		TS_ASSERT_EQUALS(d->Size(), 3);
		TS_ASSERT_EQUALS(d->GetScope(0), s3);
		TS_ASSERT_EQUALS(d->GetScope(1), &s);
		TS_ASSERT_EQUALS(d->GetScope(2), s2);
		TS_ASSERT_EQUALS(d->GetScope(0)->GetParent(), &mScope);
		TS_ASSERT_EQUALS(d->GetScope(1)->GetParent(), &mScope);
		TS_ASSERT_EQUALS(d->GetScope(2)->GetParent(), &mScope);

		Scope* s4 = new Scope();
		mScope.Adopt(*s4, "adios", 0);
		d = mScope.Find("adios");
		TS_ASSERT_EQUALS(mScope[4], *d);
		TS_ASSERT_EQUALS(d->Size(), 1);
		TS_ASSERT_EQUALS(d->GetScope(0), s4);
		TS_ASSERT_EQUALS(d->GetScope(0)->GetParent(), &mScope);

		Scope* s5 = new Scope();
		TS_ASSERT_THROWS_ANYTHING(mScope.Adopt(*s5, "hola", 0));
		delete s5;
	}

	void TestFindName(void)
	{
		std::string key = "hi";
		Scope& s = mScope.AppendScope(key);

		std::string foundName;
		bool found = mScope.FindName(s, foundName);
		TS_ASSERT_EQUALS(foundName, key);
		TS_ASSERT_EQUALS(found, true);

		Scope& s2 = mScope.AppendScope("bye");
		found = mScope.FindName(s2, foundName);
		TS_ASSERT_EQUALS(foundName, "bye");
		TS_ASSERT_EQUALS(found, true);

		Scope * s3 = new Scope();
		found = mScope.FindName(*s3, foundName);
		TS_ASSERT_EQUALS(found, false);
		delete s3;
	}

	void TestMakeOrphan(void)
	{
		std::string key = "hi";
		Scope& s = mScope.AppendScope(key);
		TS_ASSERT_EQUALS(s.GetParent(), &mScope);

		s.Orphan();
		TS_ASSERT_EQUALS(s.GetParent(), nullptr);

		Datum * d = mScope.Find(key);
		for (std::uint32_t i = 0; i < d->Size(); ++i)
		{
			TS_ASSERT_EQUALS(d->GetScope(i), nullptr);
		}

		delete &s;
	}

private:
	Scope mScope;

};