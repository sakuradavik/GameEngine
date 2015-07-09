#include "IntegerSharedData.h"

using namespace Unit_Tests;
using namespace Library;

RTTI_DEFINITIONS(IntegerSharedData);

IntegerSharedData::IntegerSharedData() :
mData(), mState(SharedDataState::Invalid), mStringData()
{
}

XmlParseMaster::SharedData* IntegerSharedData::Clone()
{
	IntegerSharedData * integerSharedData = new IntegerSharedData();
	return integerSharedData;
}

void IntegerSharedData::Reset()
{
	SharedData::Reset();
	mData.Clear();
	mStringData = std::string();
	mState = SharedDataState::Invalid;
}