#include "IntegerParseHelper.h"
#include "XmlParseMaster.h"
#include "IntegerSharedData.h"

using namespace Unit_Tests;
using namespace Library;

IntegerParseHelper::IntegerParseHelper() :
mMaxDepth(0), mStartElementCalled(0), mEndElementCalled(0), mCharElementCalled(0)
{

}

void IntegerParseHelper::Initialize()
{
	mMaxDepth = 0;
	mStartElementCalled = 0;
	mEndElementCalled = 0;
	mCharElementCalled = 0;
}

bool IntegerParseHelper::StartElementHandler(XmlParseMaster::SharedData * sharedData, std::string& name, HashMap<std::string, std::string> hashmap)
{
	++mStartElementCalled;
	IntegerSharedData * data = sharedData->As<IntegerSharedData>();
	if (data)
	{
		data->mStringData = std::string();
		if (name.compare("Integer") == 0)
		{
			data->mState = IntegerSharedData::SharedDataState::StartElement;
			if (data->Depth() > mMaxDepth)
			{
				mMaxDepth = data->Depth();
			}

			for (auto it : hashmap)
			{
				if (it.first.compare("value") == 0)
				{
					data->mStringData += it.second;
				}
			}

			return true;
		}
	}
	return false;

}

bool IntegerParseHelper::EndElementHandler(XmlParseMaster::SharedData * sharedData, std::string& name)
{
	++mEndElementCalled;
	IntegerSharedData * data = sharedData->As<IntegerSharedData>();
	if (data)
	{
		if (name.compare("Integer") == 0)
		{
			data->mState = IntegerSharedData::SharedDataState::EndElement;
			data->mData.PushBack(std::atoi(data->mStringData.c_str()));
			return true;
		}
	}
	return false;
}

bool IntegerParseHelper::CharDataHandler(XmlParseMaster::SharedData * sharedData, std::string& name, std::uint32_t length)
{
	++mCharElementCalled;
	IntegerSharedData * data = sharedData->As<IntegerSharedData>();
	if (data)
	{
		if (data->mState == IntegerSharedData::SharedDataState::StartElement)
		{
			data->mState = IntegerSharedData::SharedDataState::CharElement;
		}

		if (data->mState == IntegerSharedData::SharedDataState::CharElement)
		{
			data->mStringData += name;
			return true;
		}
	}
	return false;
}

IXmlParseHelper* IntegerParseHelper::Clone()
{
	return new IntegerParseHelper();
}
