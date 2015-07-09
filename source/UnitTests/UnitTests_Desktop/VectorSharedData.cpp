#include "VectorSharedData.h"

using namespace Unit_Tests;
using namespace Library;

RTTI_DEFINITIONS(VectorSharedData);

VectorSharedData::VectorSharedData(Vector<glm::vec4> data) :
mData(data), mState(SharedDataState::Invalid)
{
}

XmlParseMaster::SharedData* VectorSharedData::Clone()
{
	VectorSharedData * vectorSharedData = new VectorSharedData();
	return vectorSharedData;
}

void VectorSharedData::Reset()
{
	SharedData::Reset();
	mData.Clear();
	mState = SharedDataState::Invalid;
}