#include <cxxtest/TestSuite.h>
#include "ScopeSharedData.h"
#include "IntegerXmlParseHelper.h"
#include "MatrixXmlParseHelper.h"
#include "FloatXmlParseHelper.h"
#include "VectorXmlParseHelper.h"
#include "StringXmlParseHelper.h"
#include "ScopeXmlParseHelper.h"
#include "XmlParseMaster.h"

using namespace Library;

class ScopeParseTestSuite : public CxxTest::TestSuite
{
public:
	void setUp()
	{
		mScope = new Scope();
		mScopeSharedData = new ScopeSharedData(mScope);
		mIntegerXmlParseHelper = new IntegerXmlParseHelper();
		mFloatXmlParseHelper = new FloatXmlParseHelper();
		mVectorXmlParseHelper = new VectorXmlParseHelper();
		mMatrixXmlParseHelper = new MatrixXmlParseHelper();
		mStringXmlParseHelper = new StringXmlParseHelper();
		mScopeXmlParseHelper = new ScopeXmlParseHelper();
		mParseMaster = new XmlParseMaster(mScopeSharedData);

		mParseMaster->AddHelper(*mIntegerXmlParseHelper);
		mParseMaster->AddHelper(*mFloatXmlParseHelper);
		mParseMaster->AddHelper(*mVectorXmlParseHelper);
		mParseMaster->AddHelper(*mMatrixXmlParseHelper);
		mParseMaster->AddHelper(*mStringXmlParseHelper);
		mParseMaster->AddHelper(*mScopeXmlParseHelper);

		mFileName = "ScopeSample.xml";
		mParseMaster->ParseFromFile(mFileName);
	}

	void tearDown()
	{
		mParseMaster->RemoveHelper(*mIntegerXmlParseHelper);
		mParseMaster->RemoveHelper(*mFloatXmlParseHelper);
		mParseMaster->RemoveHelper(*mVectorXmlParseHelper);
		mParseMaster->RemoveHelper(*mMatrixXmlParseHelper);
		mParseMaster->RemoveHelper(*mStringXmlParseHelper);
		mParseMaster->RemoveHelper(*mScopeXmlParseHelper);

		delete mIntegerXmlParseHelper;
		delete mFloatXmlParseHelper;
		delete mVectorXmlParseHelper;
		delete mMatrixXmlParseHelper;
		delete mStringXmlParseHelper;
		delete mScopeXmlParseHelper;
		delete mParseMaster;
		delete mScopeSharedData;
		delete mScope;
	}

	void TestIntegerHelper(void)
	{
		Datum * datum = mScopeSharedData->GetScope()->Find("PowerLevel");
		if (datum)
		{
			TS_ASSERT_EQUALS(datum->GetInteger(0), 7);
			TS_ASSERT_EQUALS(datum->GetInteger(1), 9);
			TS_ASSERT_EQUALS(datum->Size(), 2);
		}
	}

	void TestFloatHelper(void)
	{
		Datum * datum = mScopeSharedData->GetScope()->Find("MagicLevel");
		if (datum)
		{
			TS_ASSERT_EQUALS(datum->GetFloat(0), 13.0f);
			TS_ASSERT_EQUALS(datum->GetFloat(1), 9.0f);
			TS_ASSERT_EQUALS(datum->Size(), 2);
		}
	}

	void TestVectorHelper(void)
	{
		Datum * datum = mScopeSharedData->GetScope()->Find("Location");
		if (datum)
		{
			TS_ASSERT_EQUALS(datum->GetVector(0), glm::vec4(7.0, 3.0, 11.0, 98.0));
			TS_ASSERT_EQUALS(datum->GetVector(1), glm::vec4(9.0, 32.0, 25.0, 65.0));
			TS_ASSERT_EQUALS(datum->Size(), 2);
		}
	}

	void TestMatrixHelper(void)
	{
		Datum * datum = mScopeSharedData->GetScope()->Find("Transform");
		if (datum)
		{
			TS_ASSERT_EQUALS(datum->GetMatrix(0), glm::mat4(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.3, 13.2, 14.9, 15.26, 16.256));
			TS_ASSERT_EQUALS(datum->GetMatrix(1), glm::mat4(4.0, 6.0, 8.0, 4.0, 1.0, 44.0, 73.0, 58.0, 29.0, 150.0, 511.0, 172.3, 613.2, 14.9, 15.26, 16.256));
			TS_ASSERT_EQUALS(datum->Size(), 2);
		}
	}

	void TestStringHelper(void)
	{
		Datum * datum = mScopeSharedData->GetScope()->Find("Name");
		if (datum)
		{
			TS_ASSERT_EQUALS(datum->GetString(0), "Hi");
			TS_ASSERT_EQUALS(datum->GetString(1), "Hello");
			TS_ASSERT_EQUALS(datum->GetString(2), "Bye");
			TS_ASSERT_EQUALS(datum->Size(), 3);
		}
	}

	void TestNestedScopeHelper(void)
	{
		Datum * datum = mScopeSharedData->GetScope()->Find("Grandpa");
		if (datum)
		{
			TS_ASSERT_EQUALS(datum->GetType(), Datum::DatumType::Table);

			Datum * datum2 = datum->GetScope()->Find("Age");
			TS_ASSERT_EQUALS(datum2->GetType(), Datum::DatumType::Integer);
			TS_ASSERT_EQUALS(datum2->GetInteger(), 65);
			TS_ASSERT_EQUALS(datum2->Size(), 1);

			//Nested Scope
			Datum * datum3 = datum->GetScope()->Find("YoungGrandpa");

			Datum *datum4 = datum3->GetScope()->Find("Memories");
			TS_ASSERT_EQUALS(datum4->GetType(), Datum::DatumType::String);
			TS_ASSERT_EQUALS(datum4->GetString(), "Fishing");
			TS_ASSERT_EQUALS(datum4->Size(), 1);

			Datum *datum5 = datum3->GetScope()->Find("Age");
			TS_ASSERT_EQUALS(datum5->GetType(), Datum::DatumType::Integer);
			TS_ASSERT_EQUALS(datum5->GetInteger(), 15);
			TS_ASSERT_EQUALS(datum5->Size(), 1);
		}
	}

	void TestingBadFileFormat(void)
	{
		std::string xmlString = "<scope>"\
			"<integer name=\"Health\">\n"\
			"<value>10</value>\n"\
			"</scope>\n"\
			"</integer>\n";
		TS_ASSERT_THROWS_ANYTHING(mParseMaster->Parse(xmlString.c_str(), xmlString.length(), true, true));

		xmlString = "<scope>"\
			"<integer>\n"\
			"<value>10</value>\n"\
			"</scope>\n"\
			"</integer>\n";
		TS_ASSERT_THROWS_ANYTHING(mParseMaster->Parse(xmlString.c_str(), xmlString.length(), true, true));
	}

	void TestClone(void)
	{
		XmlParseMaster* parseMaster = mParseMaster->Clone();
		parseMaster->ParseFromFile(mFileName);

		ScopeSharedData* sharedData = parseMaster->GetSharedData()->As<ScopeSharedData>();

		if (sharedData)
		{
			Datum * datum = mScopeSharedData->GetScope()->Find("PowerLevel");
			if (datum)
			{
				TS_ASSERT_EQUALS(datum->GetInteger(0), 7);
				TS_ASSERT_EQUALS(datum->GetInteger(1), 9);
				TS_ASSERT_EQUALS(datum->Size(), 2);
			}

			datum = mScopeSharedData->GetScope()->Find("Grandpa");
			if (datum)
			{
				TS_ASSERT_EQUALS(datum->GetType(), Datum::DatumType::Table);

				Datum * datum2 = datum->GetScope()->Find("Age");
				TS_ASSERT_EQUALS(datum2->GetType(), Datum::DatumType::Integer);
				TS_ASSERT_EQUALS(datum2->GetInteger(), 65);
				TS_ASSERT_EQUALS(datum2->Size(), 1);

				//Nested Scope
				Datum * datum3 = datum->GetScope()->Find("YoungGrandpa");

				Datum *datum4 = datum3->GetScope()->Find("Memories");
				TS_ASSERT_EQUALS(datum4->GetType(), Datum::DatumType::String);
				TS_ASSERT_EQUALS(datum4->GetString(), "Fishing");
				TS_ASSERT_EQUALS(datum4->Size(), 1);

				Datum *datum5 = datum3->GetScope()->Find("Age");
				TS_ASSERT_EQUALS(datum5->GetType(), Datum::DatumType::Integer);
				TS_ASSERT_EQUALS(datum5->GetInteger(), 15);
				TS_ASSERT_EQUALS(datum5->Size(), 1);
			}
		}

		delete parseMaster;
	}

private:
	XmlParseMaster *mParseMaster;
	IntegerXmlParseHelper *mIntegerXmlParseHelper;
	FloatXmlParseHelper *mFloatXmlParseHelper;
	VectorXmlParseHelper *mVectorXmlParseHelper;
	MatrixXmlParseHelper *mMatrixXmlParseHelper;
	StringXmlParseHelper *mStringXmlParseHelper;
	ScopeXmlParseHelper *mScopeXmlParseHelper;
	ScopeSharedData* mScopeSharedData;
	Scope* mScope;
	std::string mFileName;
};