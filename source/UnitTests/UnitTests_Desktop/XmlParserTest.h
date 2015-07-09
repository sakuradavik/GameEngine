#include <cxxtest/TestSuite.h>
#include "IntegerParseHelper.h"
#include "IntegerSharedData.h"
#include "VectorSharedData.h"
#include "VectorParseHelper.h"
#include "XmlParseMaster.h"

using namespace Unit_Tests;
using namespace Library;

class FooXmlParseTestSuite : public CxxTest::TestSuite
{
public:
	void setUp()
	{
		mIntegerSharedData = new IntegerSharedData();
		mVectorSharedData = new VectorSharedData();
		mParseMaster = new XmlParseMaster(mIntegerSharedData);
		mIntegerParseHelper = new IntegerParseHelper();
		mVectorParseHelper = new VectorParseHelper();
		mParseMaster->AddHelper(*mIntegerParseHelper);
		mParseMaster->AddHelper(*mVectorParseHelper);
	}

	void tearDown()
	{
		mParseMaster->RemoveHelper(*mIntegerParseHelper);
		mParseMaster->RemoveHelper(*mVectorParseHelper);
		delete mIntegerSharedData;
		delete mParseMaster;
		delete mIntegerParseHelper;
		delete mVectorParseHelper;
		delete mVectorSharedData;
	}

	void TestIntegerParser(void)
	{
		std::string data = "<Integer> 10 </Integer>";
		mParseMaster->Parse(data.c_str(), data.length(), true, true);
		TS_ASSERT_EQUALS(mIntegerSharedData->mData[0], 10);
		TS_ASSERT_EQUALS(mIntegerParseHelper->mMaxDepth, 1);
		TS_ASSERT_EQUALS(mIntegerParseHelper->mStartElementCalled, 1);
		TS_ASSERT_EQUALS(mIntegerParseHelper->mEndElementCalled, 1);
		TS_ASSERT_EQUALS(mIntegerParseHelper->mCharElementCalled, 1);

		data = "<XML><Integer> 10 </Integer><Integer> 125 </Integer><Integer> 7 </Integer></XML>";
		mParseMaster->Parse(data.c_str(), data.length(), true, true);
		TS_ASSERT_EQUALS(mIntegerSharedData->mData.Size(), 3);
		TS_ASSERT_EQUALS(mIntegerParseHelper->mMaxDepth, 2);
		TS_ASSERT_EQUALS(mIntegerSharedData->mData[0], 10);
		TS_ASSERT_EQUALS(mIntegerSharedData->mData[1], 125);
		TS_ASSERT_EQUALS(mIntegerSharedData->mData[2], 7);
		TS_ASSERT_EQUALS(mIntegerParseHelper->mStartElementCalled, 4);
		TS_ASSERT_EQUALS(mIntegerParseHelper->mEndElementCalled, 4);
		TS_ASSERT_EQUALS(mIntegerParseHelper->mCharElementCalled, 3);
	}

	void TestExceptions(void)
	{
		std::string data = "< Integer>10 < / Integer > < Integer>20 < / Integer >";
		TS_ASSERT_THROWS_ANYTHING(mParseMaster->Parse(data.c_str(), data.length(), true, true));

		std::string filename = "";
		TS_ASSERT_THROWS_ANYTHING(mParseMaster->ParseFromFile(filename));

		filename = "invalid.xml";
		TS_ASSERT_THROWS_ANYTHING(mParseMaster->ParseFromFile(filename));


	}

	void TestIntegerClone(void)
	{
		XmlParseMaster* parseMaster = mParseMaster->Clone();
		std::string data = "<Integer> 10 </Integer>";
		parseMaster->Parse(data.c_str(), data.length(), true, true);

		IntegerSharedData* sharedData = parseMaster->GetSharedData()->As<IntegerSharedData>();
		if (sharedData)
		{
			TS_ASSERT_EQUALS(sharedData->mData[0], 10);
			TS_ASSERT_EQUALS(sharedData->Depth(), 0);
		}
		delete parseMaster;
	}

	void TestIntegerReadFromFile(void)
	{
		std::string fileName = "Integer.xml";
		mParseMaster->ParseFromFile(fileName);
		TS_ASSERT_EQUALS(mIntegerSharedData->mData.Size(), 3);
		TS_ASSERT_EQUALS(mIntegerParseHelper->mMaxDepth, 2);
		TS_ASSERT_EQUALS(mIntegerSharedData->mData[0], 10);
		TS_ASSERT_EQUALS(mIntegerSharedData->mData[1], 125);
		TS_ASSERT_EQUALS(mIntegerSharedData->mData[2], 7);
		TS_ASSERT_EQUALS(mIntegerParseHelper->mStartElementCalled, 4);
		TS_ASSERT_EQUALS(mIntegerParseHelper->mEndElementCalled, 4);
		TS_ASSERT_EQUALS(mIntegerParseHelper->mCharElementCalled, 10);
	}

	void TestIntegerReadFromAttributes(void)
	{
		std::string data = "<Integer value = '10'></Integer>";
		mParseMaster->Parse(data.c_str(), data.length(), true, true);
		TS_ASSERT_EQUALS(mIntegerSharedData->mData[0], 10);
		TS_ASSERT_EQUALS(mIntegerParseHelper->mMaxDepth, 1);
		TS_ASSERT_EQUALS(mIntegerParseHelper->mStartElementCalled, 1);
		TS_ASSERT_EQUALS(mIntegerParseHelper->mEndElementCalled, 1);
		TS_ASSERT_EQUALS(mIntegerParseHelper->mCharElementCalled, 0);

	}

	void TestVectorParser(void)
	{
		std::string data = "<Vector> <X>10</X> <Y>20</Y> <Z>30</Z> <W>40</W> </Vector>";
		mParseMaster->SetSharedData(mVectorSharedData);
		mParseMaster->Parse(data.c_str(), data.length(), true, true);
		TS_ASSERT_EQUALS(mVectorSharedData->mData[0], glm::vec4(10.0f, 20.0f, 30.0f, 40.0f));
		TS_ASSERT_EQUALS(mVectorParseHelper->mMaxDepth, 2);
		TS_ASSERT_EQUALS(mVectorParseHelper->mStartElementCalled, 5);
		TS_ASSERT_EQUALS(mVectorParseHelper->mEndElementCalled, 5);
		TS_ASSERT_EQUALS(mVectorParseHelper->mCharElementCalled, 9);

	}

	void TestVectorReadFromFile(void)
	{
		std::string fileName = "Vector.xml";
		mParseMaster->SetSharedData(mVectorSharedData);
		mParseMaster->ParseFromFile(fileName);
		TS_ASSERT_EQUALS(mVectorSharedData->mData[0], glm::vec4(10.0f, 20.0f, 30.0f, 40.0f));
		TS_ASSERT_EQUALS(mVectorSharedData->mData[1], glm::vec4(0.0f, 1.0f, 3.0f, 4.0f));
		TS_ASSERT_EQUALS(mVectorParseHelper->mMaxDepth, 3);
		TS_ASSERT_EQUALS(mVectorParseHelper->mStartElementCalled, 11);
		TS_ASSERT_EQUALS(mVectorParseHelper->mEndElementCalled, 11);
		TS_ASSERT_EQUALS(mVectorParseHelper->mCharElementCalled, 43);
	}

	void TestVectorClone(void)
	{
		mParseMaster->SetSharedData(mVectorSharedData);
		XmlParseMaster* parseMaster = mParseMaster->Clone();
		std::string data = "<Vector> <X>10</X> <Y>20</Y> <Z>30</Z> <W>40</W> </Vector>";
		parseMaster->Parse(data.c_str(), data.length(), true, true);

		VectorSharedData* sharedData = parseMaster->GetSharedData()->As<VectorSharedData>();
		if (sharedData)
		{
			TS_ASSERT_EQUALS(sharedData->mData[0], glm::vec4(10.0f, 20.0f, 30.0f, 40.0f));
		}
		delete parseMaster;
	}

	void TestVectorReadFromAttributes(void)
	{
		std::string data = "<Vector X = '10' Y = '20' Z = '30' W = '40'></Vector>";
		mParseMaster->SetSharedData(mVectorSharedData);
		mParseMaster->Parse(data.c_str(), data.length(), true, true);
		TS_ASSERT_EQUALS(mVectorSharedData->mData[0], glm::vec4(10.0f, 20.0f, 30.0f, 40.0f));
		TS_ASSERT_EQUALS(mIntegerParseHelper->mMaxDepth, 0);
		TS_ASSERT_EQUALS(mIntegerParseHelper->mStartElementCalled, 1);
		TS_ASSERT_EQUALS(mIntegerParseHelper->mEndElementCalled, 1);
		TS_ASSERT_EQUALS(mIntegerParseHelper->mCharElementCalled, 0);

	}

private:
	XmlParseMaster *mParseMaster;
	IntegerParseHelper *mIntegerParseHelper;
	IntegerSharedData *mIntegerSharedData;
	VectorSharedData *mVectorSharedData;
	VectorParseHelper *mVectorParseHelper;
};
