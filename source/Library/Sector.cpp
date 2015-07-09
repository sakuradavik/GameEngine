#include "pch.h"
#include "Sector.h"
#include "Factory.h"
#include "Entity.h"

using namespace Library;
RTTI_DEFINITIONS(Sector);

Sector::Sector(World* world):
mName(), Attribute(), mWorld(world)
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
	InternalSignature("Entities", Datum::DatumType::Table, &scope, 1);
	Populate();
}

const std::string& Sector::Name() const
{
	return mName;
}

Scope* Sector::Entities()
{
	Datum *datum = Find("Entities");
	if (datum)
	{
		return datum->GetScope();
	}
	return nullptr;
}

Entity* Sector::CreateEntity(const std::string& entityName, const std::string& instanceName)
{	
	Entity* entity = Factory<Entity>::Create(entityName);
	if (entity)
	{
		Entities()->Adopt(*entity, instanceName, Entities()->Size());
		entity->mName = instanceName;
		entity->SetSector(this);
		return entity;
	}
	else
	{
		throw std::exception("This entity factory does not exist");
	}
}

void Sector::SetWorld(World* world)
{
	mWorld = world;
}

const World* Sector::GetWorld() const
{
	return mWorld;
}

void Sector::Update(WorldState& worldState)
{
	Scope* entities = Entities();
	if (entities)
	{
		for (std::uint32_t i = 0; i < entities->Size(); ++i)
		{
			Scope* scope = (*entities)[i].GetScope();
			if (scope)
			{
				Entity* entity = scope->As<Entity>();
				if (entity)
				{
					worldState.mEntity = entity;
					entity->Update(worldState);
				}
			}
		}
	}
}
