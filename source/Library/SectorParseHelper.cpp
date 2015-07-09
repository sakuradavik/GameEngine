#include "pch.h"
#include "SectorParseHelper.h"
#include "ScopeSharedData.h"
#include "World.h"
#include "Sector.h"

using namespace Library;

#pragma region XMLStringTypes

const std::string SectorParseHelper::ScopeString = "Sector";
const std::string SectorParseHelper::NameString = "name";
const std::string SectorParseHelper::IndexString = "index";

#pragma endregion

typedef Datum::DatumType DatumType;

SectorParseHelper::SectorParseHelper() :
mDatumName(), bIsParsing(false), mIndex(0), mStringData()
{
}

void SectorParseHelper::Initialize()
{
	bIsParsing = false;
	mDatumName = std::string();
	mStringData = std::string();
	mIndex = 0;
}

bool SectorParseHelper::StartElementHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& name, Library::HashMap<std::string, std::string> hashmap)
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
						Sector* sector = world->CreateSector(providedName->second);
						data->SetWorld(sector);
					}
					else
					{
						throw std::exception("You are not coming from a world");
					}
				}
				return true;
			}
		}
	}
	return false;
}

bool SectorParseHelper::EndElementHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& name)
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
			Sector * sector = data->GetWorld()->As<Sector>();
			if (sector)
			{
				World* world = const_cast<World*>(sector->GetWorld());
				data->SetWorld(world);
			}
			bIsParsing = false;
			return true;
		}
	}
	return false;
}

bool SectorParseHelper::CharDataHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& data, std::uint32_t length)
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

IXmlParseHelper* SectorParseHelper::Clone()
{
	return new SectorParseHelper();;
}

