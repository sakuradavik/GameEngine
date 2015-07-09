#include "pch.h"
#include "ActionEvent.h"
#include "EventMessageAttributed.h"
#include <memory>
#include "World.h"
#include "Event.h"


using namespace Library;

RTTI_DEFINITIONS(ActionEvent);

ActionEvent::ActionEvent()
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

	std::int32_t delay = 0;
	std::string subtype = std::string();
	InternalSignature("Delay", Datum::DatumType::Integer, &delay, 1);
	InternalSignature("Subtype", Datum::DatumType::String, &subtype, 1);
	Populate();
}

std::string& ActionEvent::GetSubtype() const
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

void ActionEvent::SetSubtype(std::string& subtype)
{
	Datum * d = Find("Subtype");
	if (d)
	{
		*d = subtype;
	}
}

void ActionEvent::Update(WorldState& worldState)
{
	EventMessageAttributed eventMessage = EventMessageAttributed(worldState.mWorld);
	eventMessage.SetSubtype(GetSubtype());


	for (std::uint32_t i = AuxiliaryBegin(); i < GetOrderVector().Size(); ++i)
	{
		Datum& datum = eventMessage.AppendAuxiliaryAttribute(GetOrderVector()[i]->first);
		datum = GetOrderVector()[i]->second;
	}

	std::shared_ptr<EventPublisher> eventPublisher = std::make_shared<Event<EventMessageAttributed>>(eventMessage);
	worldState.mWorld->GetEventQueue().Enqueue(eventPublisher, worldState.GetGameTime().ElapsedGameTime(), GetDelay());
}

std::int32_t ActionEvent::GetDelay() const
{
	Datum * d = Find("Delay");
	if (d)
	{
		return d->GetInteger();
	}
	else
	{
		throw std::exception("No delay was added");
	}
}

void ActionEvent::SetDelay(std::int32_t delay)
{
	Datum * d = Find("Delay");
	if (d)
	{
		*d = delay;
	}
}