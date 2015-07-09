#include "pch.h"
#include "EventMessageAttributed.h"
#include "World.h"

using namespace Library;

RTTI_DEFINITIONS(EventMessageAttributed);

EventMessageAttributed::EventMessageAttributed(World* world) :
mWorld(world)
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

	std::string subtype = std::string();
	InternalSignature("Subtype", Datum::DatumType::String, &subtype, 1);
	Populate();
}

World* EventMessageAttributed::GetWorld() const
{
	return mWorld;
}

void EventMessageAttributed::SetWorld(World* world)
{
	mWorld = world;
}

std::string& EventMessageAttributed::GetSubtype() const
{
	Datum * d = Find("Subtype");
	if (d)
	{
		return d->GetString();
	}
	else
	{
		throw std::exception("No Subtype was added");
	}
}

void EventMessageAttributed::SetSubtype(std::string& subtype)
{
	Datum * d = Find("Subtype");
	if (d)
	{
		*d = subtype;
	}
}
