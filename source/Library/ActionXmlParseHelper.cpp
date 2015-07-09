#include "pch.h"
#include "ActionXmlParseHelper.h"
#include "ScopeSharedData.h"
#include "World.h"
#include "Sector.h"
#include "Action.h"
#include "Entity.h"
#include "ActionCreateAction.h"
#include "ActionDestroyAction.h"
#include "ActionEvent.h"
#include "ReactionAttributed.h"

using namespace Library;

#pragma region XMLStringTypes

const std::string ActionParseHelper::CreateString = "ActionCreateAction";
const std::string ActionParseHelper::DestroyString = "ActionDestroyAction";
const std::string ActionParseHelper::ActionString = "Action";
const std::string ActionParseHelper::NameString = "name";
const std::string ActionParseHelper::InstanceString = "instanceName";
const std::string ActionParseHelper::ClassString = "class";
const std::string ActionParseHelper::Subtype = "subtype";

#pragma endregion

typedef Datum::DatumType DatumType;

ActionParseHelper::ActionParseHelper() :
mDatumName(), bIsParsing(false), mIndex(0), mStringData()
{
}

void ActionParseHelper::Initialize()
{
	bIsParsing = false;
	mDatumName = std::string();
	mStringData = std::string();
	mIndex = 0;
}

bool ActionParseHelper::StartElementHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& name, Library::HashMap<std::string, std::string> hashmap)
{
	if (!sharedData)
	{
		return false;
	}

	ScopeSharedData * data = sharedData->As<ScopeSharedData>();
	if (data)
	{
		mStringData = std::string();
		if (name == CreateString)
		{
			if (!bIsParsing)
			{
				bIsParsing = true;
				auto providedName = hashmap.Find(NameString);
				if (providedName != hashmap.end())
				{
					Entity * entity = data->GetWorld()->As<Entity>();
					if (entity)
					{
						auto classType = hashmap.Find(ClassString);
						if (classType != hashmap.end())
						{
							Action* action = entity->CreateAction(name, providedName->second);
							ActionCreateAction* actionCreate = action->As<ActionCreateAction>();
							auto instanceName = hashmap.Find(InstanceString);
							if (instanceName != hashmap.end())
							{
								if (actionCreate)
								{
									actionCreate->SetClassName(classType->second);
									actionCreate->SetInstanceName(instanceName->second);
									data->SetWorld(action);
								}
							}
						}
						else
						{
							throw std::exception("You are not providing a class type");
						}
					}
					else
					{
						throw std::exception("You are not coming from a entity");
					}
				}
				else
				{
					throw std::exception("You are not providing a name for this entity");
				}
				return true;
			}
		}
		else if (name == DestroyString)
		{
			bIsParsing = true;
			auto providedName = hashmap.Find(NameString);
			if (providedName != hashmap.end())
			{
				Entity * entity = data->GetWorld()->As<Entity>();
				if (entity)
				{
					Action* action = entity->CreateAction(name, providedName->second);
					ActionDestroyAction* actionDestroy = action->As<ActionDestroyAction>();
					auto instanceName = hashmap.Find(InstanceString);
					if (instanceName != hashmap.end())
					{
						if (actionDestroy)
						{
							actionDestroy->SetInstanceName(instanceName->second);
							data->SetWorld(action);
						}

					}
					else
					{
						throw std::exception("You are not providing a class type");
					}
				}
				else
				{
					throw std::exception("You are not coming from a entity");
				}
			}
			else
			{
				throw std::exception("You are not providing a name for this entity");
			}
			return true;
		}
		else if (name == ActionString)
		{
			if (!bIsParsing)
			{
				bIsParsing = true;
				auto providedName = hashmap.Find(NameString);
				if (providedName != hashmap.end())
				{
					Entity * entity = data->GetWorld()->As<Entity>();
					if (entity)
					{
						auto classType = hashmap.Find(ClassString);
						if (classType != hashmap.end())
						{
							Action* action = entity->CreateAction(classType->second, providedName->second);
							auto instanceName = hashmap.Find(InstanceString);
							if (instanceName != hashmap.end())
							{
								if (action)
								{
									ActionEvent* actionEvent = action->As <ActionEvent>();
									ReactionAttributed* reactionAttributed = action->As<ReactionAttributed>();
									if (actionEvent)
									{
										auto subtypeType = hashmap.Find(Subtype);
										if (subtypeType != hashmap.end())
										{
											actionEvent->SetSubtype(subtypeType->second);
										}
									}

									if (reactionAttributed)
									{
										auto subtypeType = hashmap.Find(Subtype);
										if (subtypeType != hashmap.end())
										{
											reactionAttributed->SetSubtype(subtypeType->second);
										}
									}

									data->SetWorld(action);
								}
							}
						}
						else
						{
							throw std::exception("You are not providing a class type");
						}
					}
					else
					{
						throw std::exception("You are not coming from a entity");
					}
				}
				else
				{
					throw std::exception("You are not providing a name for this entity");
				}
				return true;
			}
		}
	}
	return false;
}

bool ActionParseHelper::EndElementHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& name)
{
	if (!sharedData)
	{
		return false;
	}

	ScopeSharedData * data = sharedData->As<ScopeSharedData>();
	if (data)
	{
		if (name == CreateString && bIsParsing)
		{
			ActionCreateAction * action = data->GetWorld()->As<ActionCreateAction>();
			if (action)
			{
				Entity* world = const_cast<Entity*>(action->GetEntity());
				data->SetWorld(world);
			}
			bIsParsing = false;
			return true;
		}

		if (name == DestroyString && bIsParsing)
		{
			ActionDestroyAction * action = data->GetWorld()->As<ActionDestroyAction>();
			if (action)
			{
				Entity* world = const_cast<Entity*>(action->GetEntity());
				data->SetWorld(world);
			}
			bIsParsing = false;
			return true;
		}

		if (name == ActionString && bIsParsing)
		{
			Action * action = data->GetWorld()->As<Action>();
			if (action)
			{
				Entity* world = const_cast<Entity*>(action->GetEntity());
				data->SetWorld(world);
			}
			bIsParsing = false;
			return true;
		}
	}
	return false;
}

bool ActionParseHelper::CharDataHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& data, std::uint32_t length)
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

IXmlParseHelper* ActionParseHelper::Clone()
{
	return new ActionParseHelper();;
}

