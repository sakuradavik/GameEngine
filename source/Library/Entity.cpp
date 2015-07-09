#include "pch.h"
#include "Entity.h"
#include "Sector.h"
#include "Action.h"

using namespace Library;

RTTI_DEFINITIONS(Entity);

Entity::Entity(Sector* sector) :
mName(), mSector(sector)
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
	InternalSignature("Actions", Datum::DatumType::Table, &scope, 1);
	Populate();
}

const std::string& Entity::Name() const
{
	return mName;
}

const Sector* Entity::GetSector() const
{
	return mSector;
}

void Entity::SetSector(Sector* sector)
{
	mSector = sector;
}

Scope* Entity::Actions()
{
	Datum *datum = Find("Actions");
	if (datum)
	{
		return datum->GetScope();
	}
	return nullptr;
}

Action* Entity::CreateAction(const std::string& EntityName, const std::string& instanceName)
{
	Action* action = Factory<Action>::Create(EntityName);
	if (action)
	{
		Actions()->Adopt(*action, instanceName, Actions()->Size());
		action->SetName(instanceName);
		action->SetEntity(this);
		return action;
	}
	else
	{
		throw std::exception("This Entity factory does not exist");
	}
}

void Entity::Update(WorldState& worldState)
{
	Scope* scope = Actions();
	if (scope)
	{
		for (std::uint32_t i = 0; i < scope->Size(); ++i)
		{
			Scope* action = (*scope)[i].GetScope();
			if (action)
			{
				Action* concreteAction = action->As<Action>();
				if (concreteAction)
				{
					worldState.mAction = concreteAction;
					concreteAction->Update(worldState);
				}
			}
		}
	}
}