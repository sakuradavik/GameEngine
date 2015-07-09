#include "pch.h"
#include "ReactionAttributed.h"
#include "Event.h"
#include "EventMessageAttributed.h"
#include "World.h"

using namespace Library;

RTTI_DEFINITIONS(ReactionAttributed);

const std::string ReactionAttributed::SubtypeName = "Subtype";

ReactionAttributed::ReactionAttributed()
{
	Event<EventMessageAttributed>::Subscribe(*this);

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
	InternalSignature(SubtypeName, Datum::DatumType::String, &subtype, 1);
	Populate();
}

ReactionAttributed::~ReactionAttributed()
{
	Event<EventMessageAttributed>::Unsubscribe(*this);
}

void ReactionAttributed::Notify(const EventPublisher& eventPublisher)
{
	Event<EventMessageAttributed> * event = eventPublisher.As<Event<EventMessageAttributed>>();
	if (event)
	{
		EventMessageAttributed* message = event->Message().As<EventMessageAttributed>();
		if (message)
		{
			for (std::uint32_t i = message->AuxiliaryBegin(); i < message->GetOrderVector().Size(); ++i)
			{
				auto& entry = message->GetOrderVector()[i];
				Datum& datum = AppendAuxiliaryAttribute(entry->first);
				datum = entry->second;
			}

			if (message->GetSubtype() == GetSubtype())
			{
				WorldState  worldState = message->GetWorld()->GetWorldState();
				ActionList::Update(worldState);
			}
		}
	}
}

void ReactionAttributed::SetSubtype(const std::string& subtype)
{
	Datum * d = Find("Subtype");
	if (d)
	{
		*d = subtype;
	}
}

std::string ReactionAttributed::GetSubtype() const
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


ReactionAttributed::ReactionAttributed(const ReactionAttributed& rhs)
{
	Attribute::Attribute(rhs);
}


ReactionAttributed& ReactionAttributed::operator=(const ReactionAttributed& rhs)
{
	if (this != &rhs)
	{
		Attribute::operator=(rhs);
	}
	return *this;
}