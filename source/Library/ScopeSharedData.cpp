#include "pch.h"
#include "ScopeSharedData.h"
#include "Attribute.h"

using namespace Library;

RTTI_DEFINITIONS(ScopeSharedData);

ScopeSharedData::ScopeSharedData(Scope* data):
mData(data), bIsClone(false), mWorld(nullptr)
{
}

ScopeSharedData::ScopeSharedData(Attribute* data) :
mWorld(data), bIsClone(false), mData(nullptr)
{
}

ScopeSharedData::~ScopeSharedData()
{
	if (bIsClone)
	{
		delete mData;
		mData = nullptr;
	}
}

XmlParseMaster::SharedData* ScopeSharedData::Clone()
{
	ScopeSharedData* clone = new ScopeSharedData(new Scope());
	clone->bIsClone = true;
	return clone;
}

void ScopeSharedData::Reset()
{
	XmlParseMaster::SharedData::Reset();
	if (mData)
	{
		mData->Clear();
	}
	bIsClone = false;
}

Scope* ScopeSharedData::GetScope()
{
	return mData;
}

Attribute* ScopeSharedData::GetWorld()
{
	return mWorld;
}

void ScopeSharedData::SetScope(Scope * data)
{
	mData = data;
}

void ScopeSharedData::SetWorld(Attribute * data)
{
	mWorld = data;
}