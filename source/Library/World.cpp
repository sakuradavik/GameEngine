#include "pch.h"
#include "World.h"
#include "Sector.h"

using namespace Library;

RTTI_DEFINITIONS(World);

World::World() :
mName(), mWorldState(this), Attribute()
{
	bool inserted;
	Vector<Signature> mVector;
	auto& signatureVector = mSignatures.Insert(TypeIdClass(), mVector, inserted)->second;

	if (!inserted)
	{
		std::uint32_t size = signatureVector.Size();
		signatureVector.Clear();
		signatureVector.Reserve(size);
	}

	Scope* scope = nullptr;
	ExternalSignature("Name", Datum::DatumType::String, &mName, 1);
	InternalSignature("Sectors", Datum::DatumType::Table, &scope, 1);
	Populate();
}

const std::string& World::Name() const
{
	return mName;
}

void World::SetName(const std::string& name)
{
	mName = name;
}

Scope* World::Sectors()
{
	Datum& datum = Append("Sectors", Datum::DatumType::Table);
	Scope* scope = datum.GetScope();
	return scope;
}

Sector* World::CreateSector(const std::string& name)
{
	Sector* sector = new Sector(this);
	sector->mName = name;
	Sectors()->Adopt(*sector, name, Sectors()->Size());
	return sector;
}

void World::Update(WorldState& worldState)
{
	Scope* sectors = Sectors();
	if (sectors)
	{
		for (std::uint32_t i = 0; i < sectors->Size(); ++i)
		{
			Scope* scope = (*sectors)[i].GetScope();
			if (scope)
			{
				Sector* sector = scope->As<Sector>();
				if (sector)
				{
					worldState.mSector = sector;
					sector->Update(worldState);
				}
			}
		}
	}
}

WorldState& World::GetWorldState()
{
	return mWorldState;
}

EventQueue& World::GetEventQueue()
{
	return mEventQueue;
}