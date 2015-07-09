#include <cxxtest/TestSuite.h>
#include "Event.h"
#include "EventPublisher.h"
#include "EventSubscriber.h"
#include "Reaction.h"
#include "ActionEvent.h"
#include "EventMessageAttributed.h"
#include "World.h"
#include "Entity.h"
#include "Sector.h"
#include "ReactionAttributed.h"
#include "ScopeSharedData.h"
#include "IntegerXmlParseHelper.h"
#include "MatrixXmlParseHelper.h"
#include "FloatXmlParseHelper.h"
#include "VectorXmlParseHelper.h"
#include "StringXmlParseHelper.h"
#include "ScopeXmlParseHelper.h"
#include "XmlParseMaster.h"
#include "WorldParseHelper.h"
#include "SectorParseHelper.h"
#include "EntityParseHelper.h"
#include "ActionXmlParseHelper.h"

using namespace Library;

class ReactionTestSuite : public CxxTest::TestSuite
{
public:
	void setUp()
	{
		world = new World();

		mActionEventFactory = new ActionEventFactory();
		mReactionAttributedFactory = new ReactionAttributedFactory();
		mEntityFactory = new EntityFactory();

		mScopeSharedData = new ScopeSharedData(world);
		mIntegerXmlParseHelper = new IntegerXmlParseHelper();
		mFloatXmlParseHelper = new FloatXmlParseHelper();
		mVectorXmlParseHelper = new VectorXmlParseHelper();
		mMatrixXmlParseHelper = new MatrixXmlParseHelper();
		mStringXmlParseHelper = new StringXmlParseHelper();
		mScopeXmlParseHelper = new ScopeXmlParseHelper();
		mWorldParseHelper = new WorldParseHelper();
		mSectorParseHelper = new SectorParseHelper();
		mEntityParseHelper = new EntityParseHelper();
		mActionParseHelper = new ActionParseHelper();
		mParseMaster = new XmlParseMaster(mScopeSharedData);

		mParseMaster->AddHelper(*mIntegerXmlParseHelper);
		mParseMaster->AddHelper(*mFloatXmlParseHelper);
		mParseMaster->AddHelper(*mVectorXmlParseHelper);
		mParseMaster->AddHelper(*mMatrixXmlParseHelper);
		mParseMaster->AddHelper(*mStringXmlParseHelper);
		mParseMaster->AddHelper(*mScopeXmlParseHelper);
		mParseMaster->AddHelper(*mWorldParseHelper);
		mParseMaster->AddHelper(*mSectorParseHelper);
		mParseMaster->AddHelper(*mEntityParseHelper);
		mParseMaster->AddHelper(*mActionParseHelper);
	}

	void tearDown()
	{
		delete world;
		mParseMaster->RemoveHelper(*mIntegerXmlParseHelper);
		mParseMaster->RemoveHelper(*mFloatXmlParseHelper);
		mParseMaster->RemoveHelper(*mVectorXmlParseHelper);
		mParseMaster->RemoveHelper(*mMatrixXmlParseHelper);
		mParseMaster->RemoveHelper(*mStringXmlParseHelper);
		mParseMaster->RemoveHelper(*mScopeXmlParseHelper);
		mParseMaster->RemoveHelper(*mWorldParseHelper);
		mParseMaster->RemoveHelper(*mSectorParseHelper);
		mParseMaster->RemoveHelper(*mEntityParseHelper);
		mParseMaster->RemoveHelper(*mActionParseHelper);

		delete mIntegerXmlParseHelper;
		delete mFloatXmlParseHelper;
		delete mVectorXmlParseHelper;
		delete mMatrixXmlParseHelper;
		delete mStringXmlParseHelper;
		delete mWorldParseHelper;
		delete mSectorParseHelper;
		delete mEntityParseHelper;
		delete mActionParseHelper;
		delete mScopeXmlParseHelper;
		delete mParseMaster;
		delete mScopeSharedData;

		delete mActionEventFactory;
		delete mReactionAttributedFactory;
		delete mEntityFactory;

	}

	void TestActionEvent()
	{
		ActionEventFactory actionEventFactory;

		ReactionAttributed reactionAttribute;
		reactionAttribute.SetSubtype("ReactionType");

		ActionEvent* actionEvent = actionEventFactory.Create();
		std::string str = "ActionEvent";
		actionEvent->SetSubtype(str);
		actionEvent->SetDelay(7);

		Datum& anotherAttribute = actionEvent->AppendAuxiliaryAttribute("Matrix");
		Datum& anotherAttribute2 = actionEvent->AppendAuxiliaryAttribute("Float");
		anotherAttribute.SetType(Datum::DatumType::Matrix);
		anotherAttribute2.SetType(Datum::DatumType::Float);
		anotherAttribute = glm::mat4(7);
		anotherAttribute2 = 8.0f;

		Datum* subtype = actionEvent->Find("Subtype");
		if (subtype)
		{
			TS_ASSERT_EQUALS(subtype->GetString(), str);
		}
		else
		{
			TS_ASSERT(false);
		}

		Datum* delay = actionEvent->Find("Delay");
		if (delay)
		{
			TS_ASSERT_EQUALS(delay->GetInteger(), 7);
		}
		else
		{
			TS_ASSERT(false);
		}

		actionEvent->Update((world->GetWorldState()));
		TS_ASSERT_EQUALS(world->GetEventQueue().Count(), 1);

		world->GetEventQueue().Update(8);
		TS_ASSERT_EQUALS(world->GetEventQueue().Count(), 0);

		Datum* reactionAttribute2 = reactionAttribute.Find("Matrix");
		if (reactionAttribute2)
		{
			TS_ASSERT_EQUALS(reactionAttribute2->GetMatrix(), glm::mat4(7));
		}

		Datum* reactionAttribute3 = reactionAttribute.Find("Float");
		if (reactionAttribute3)
		{
			TS_ASSERT_EQUALS(reactionAttribute3->GetFloat(), 8.0f);
		}
		delete actionEvent;
	}
	void TestXml()
	{
		ActionEvent* actionEvent = nullptr;
		ReactionAttributed* reaction = nullptr;

		std::string fileName = "Reaction.xml";
		mParseMaster->ParseFromFile(fileName);
		
		Scope* sectors = world->Sectors();
		Datum * sector1 = sectors->Search("ProgrammingII");
		if (sector1)
		{
			Sector* sector = sector1->GetScope()->As<Sector>();
			Scope* entities = sector->Entities();
			Datum * paul = entities->Find("Paul");
			if (paul)
			{
				Entity* entity = paul->GetScope()->As<Entity>();
				if (entity)
				{
					Scope* actions = entity->Actions();
					Datum * datum = actions->Find("Assignments");
					if (datum)
					{
						actionEvent = datum->GetScope()->As<ActionEvent>();
						if (actionEvent)
						{
							TS_ASSERT_EQUALS(actionEvent->GetSubtype(), "WaitingToGrade");
						}
					}
					datum = actions->Find("Assignments2");
					if (datum)
					{
						reaction = datum->GetScope()->As<ReactionAttributed>();
						if (reaction)
						{
							TS_ASSERT_EQUALS(reaction->GetSubtype(), "ReactionAttributed");
						}
					}
				}
			}
		}
		actionEvent->SetDelay(7);

		Datum& anotherAttribute = actionEvent->AppendAuxiliaryAttribute("Matrix");
		Datum& anotherAttribute2 = actionEvent->AppendAuxiliaryAttribute("Float");
		anotherAttribute.SetType(Datum::DatumType::Matrix);
		anotherAttribute2.SetType(Datum::DatumType::Float);
		anotherAttribute = glm::mat4(7);
		anotherAttribute2 = 8.0f;

		Datum* delay = actionEvent->Find("Delay");
		if (delay)
		{
			TS_ASSERT_EQUALS(delay->GetInteger(), 7);
		}
		else
		{
			TS_ASSERT(false);
		}

		actionEvent->Update((world->GetWorldState()));
		TS_ASSERT_EQUALS(world->GetEventQueue().Count(), 1);

		world->GetEventQueue().Update(8);
		TS_ASSERT_EQUALS(world->GetEventQueue().Count(), 0);

		Datum* reactionAttribute2 = reaction->Find("Matrix");
		if (reactionAttribute2)
		{
			TS_ASSERT_EQUALS(reactionAttribute2->GetMatrix(), glm::mat4(7));
		}

		Datum* reactionAttribute3 = reaction->Find("Float");
		if (reactionAttribute3)
		{
			TS_ASSERT_EQUALS(reactionAttribute3->GetFloat(), 8.0f);
		}

	}


private:
	World* world;
	XmlParseMaster *mParseMaster;
	IntegerXmlParseHelper *mIntegerXmlParseHelper;
	FloatXmlParseHelper *mFloatXmlParseHelper;
	VectorXmlParseHelper *mVectorXmlParseHelper;
	MatrixXmlParseHelper *mMatrixXmlParseHelper;
	StringXmlParseHelper *mStringXmlParseHelper;
	ScopeXmlParseHelper *mScopeXmlParseHelper;
	WorldParseHelper *mWorldParseHelper;
	SectorParseHelper *mSectorParseHelper;
	EntityParseHelper *mEntityParseHelper;
	ActionParseHelper *mActionParseHelper;
	ScopeSharedData* mScopeSharedData;

	ActionEventFactory* mActionEventFactory;
	ReactionAttributedFactory* mReactionAttributedFactory;
	EntityFactory* mEntityFactory;
};