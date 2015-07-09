#include "pch.h"
#include "EntityParseHelper.h"
#include "ScopeSharedData.h"
#include "World.h"
#include "Sector.h"
#include "Entity.h"

using namespace Library;

#pragma region XMLStringTypes

const std::string EntityParseHelper::ScopeString = "Entity";
const std::string EntityParseHelper::NameString = "name";
const std::string EntityParseHelper::IndexString = "index";
const std::string EntityParseHelper::ClassString = "class";

#pragma endregion

typedef Datum::DatumType DatumType;

EntityParseHelper::EntityParseHelper() :
mDatumName(), bIsParsing(false), mIndex(0), mStringData()
{
}

void EntityParseHelper::Initialize()
{
	bIsParsing = false;
	mDatumName = std::string();
	mStringData = std::string();
	mIndex = 0;
}

bool EntityParseHelper::StartElementHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& name, Library::HashMap<std::string, std::string> hashmap)
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
					Sector * sector = data->GetWorld()->As<Sector>();
					if (sector)
					{
						auto classType = hashmap.Find(ClassString);
						if (classType != hashmap.end())
						{
							Entity* entity = sector->CreateEntity(classType->second, providedName->second);
							data->SetWorld(entity);
						}
						else
						{
							throw std::exception("You are not providing a class type");
						}
					}
					else
					{
						throw std::exception("You are not coming from a sector");
					}
				}
				else
				{
					throw std::exception("You are not providing a name for this sector");
				}
				return true;
			}
		}
	}
	return false;
}

bool EntityParseHelper::EndElementHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& name)
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
			Entity * entity = data->GetWorld()->As<Entity>();
			if (entity)
			{
				Sector* world = const_cast<Sector*>(entity->GetSector());
				data->SetWorld(world);
			}
			bIsParsing = false;
			return true;
		}
	}
	return false;
}

bool EntityParseHelper::CharDataHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& data, std::uint32_t length)
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

IXmlParseHelper* EntityParseHelper::Clone()
{
	return new EntityParseHelper();;
}

