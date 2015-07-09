#include "pch.h"
#include "WorldSharedData.h"

using namespace Library;

RTTI_DEFINITIONS(WorldSharedData);

WorldSharedData::WorldSharedData(Attribute* data) :
mData(data), bIsClone(false)
{
}

WorldSharedData::~WorldSharedData()
{
	if (bIsClone)
	{
		delete mData;
		mData = nullptr;
	}
}

XmlParseMaster::SharedData* WorldSharedData::Clone()
{
	WorldSharedData* clone = new WorldSharedData(new Attribute());
	clone->bIsClone = true;
	return clone;
}

void WorldSharedData::Reset()
{
	XmlParseMaster::SharedData::Reset();
	mData->Clear();
	bIsClone = false;
}

Scope* WorldSharedData::GetScope()
{
	return mData;
}

void WorldSharedData::SetScope(Attribute * data)
{
	mData = data;
}