#include "pch.h"
#include "WorldParseHelper.h"
#include "ScopeSharedData.h"
#include "World.h"

using namespace Library;

#pragma region XMLStringTypes

const std::string WorldParseHelper::ScopeString = "World";
const std::string WorldParseHelper::NameString = "name";
const std::string WorldParseHelper::IndexString = "index";

#pragma endregion

typedef Datum::DatumType DatumType;

WorldParseHelper::WorldParseHelper() :
mDatumName(), bIsParsing(false), mIndex(0), mStringData()
{
}

void WorldParseHelper::Initialize()
{
	bIsParsing = false;
	mDatumName = std::string();
	mStringData = std::string();
	mIndex = 0;
}

bool WorldParseHelper::StartElementHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& name, Library::HashMap<std::string, std::string> hashmap)
{
	if (!sharedData)
	{
		return false;
	}

	ScopeSharedData * data = sharedData->As<ScopeSharedData>();
	if (data)
	{
		mStringData = std::string();
		if (name == ScopeString)
		{
			if (!bIsParsing)
			{
				bIsParsing = true;
				auto providedName = hashmap.Find(NameString);
				if (providedName != hashmap.end())
				{
					World * world = data->GetWorld()->As<World>();
					if (world)
					{
						world->SetName(providedName->second);
					}
					else
					{
						throw std::exception("You are not starting with a world");
					}
				}
				return true;
			}
		}
	}
	return false;
}

bool WorldParseHelper::EndElementHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& name)
{
	if (!sharedData)
	{
		return false;
	}

	ScopeSharedData * data = sharedData->As<ScopeSharedData>();
	if (data)
	{
		if (name == ScopeString && bIsParsing)
		{
			bIsParsing = false;
			return true;
		}
	}
	return false;
}

bool WorldParseHelper::CharDataHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& data, std::uint32_t length)
{
	if (!sharedData)
	{
		return false;
	}

	ScopeSharedData * sharedScopeData = sharedData->As<ScopeSharedData>();
	if (sharedScopeData)
	{
		if (bIsParsing)
		{
			return true;
		}
	}
	return false;
}

IXmlParseHelper* WorldParseHelper::Clone()
{
	return new WorldParseHelper();;
}

