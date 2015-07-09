#include <cxxtest/TestSuite.h>
#include "Action.h"
#include "Entity.h"
#include "Sector.h"
#include "World.h"
#include "ActionList.h"
#include "ConcreteAction.h"
#include "ActionCreateAction.h"
#include "ActionDestroyAction.h"
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
using namespace Unit_Tests;
ConcreteFactory(Action, ConcreteAction);
ConcreteFactory(Action, ActionList);
ConcreteFactory(Action, ActionCreateAction);
ConcreteFactory(Action, ActionDestroyAction);

class ActionTestSuite : public CxxTest::TestSuite
{
public:
	void setUp()
	{
		mWorld = new World();
		mConcreteActionFactory = new ConcreteActionFactory();
		mEntityFactory = new EntityFactory();
		mActionListFactory = new ActionListFactory();
		mActionCreateFactory = new ActionCreateActionFactory();
		mActionDestroyFactory = new ActionDestroyActionFactory();

		mScopeSharedData = new ScopeSharedData(mWorld);
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
		delete mWorld;
		delete mConcreteActionFactory;
		delete mEntityFactory;
		delete mActionListFactory;
		delete mActionCreateFactory;
		delete mActionDestroyFactory;

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
	}

	void TestInitialization()
	{
		mWorld->SetName("World1");
		TS_ASSERT_EQUALS(mWorld->Name(), "World1");

		WorldState worldState = mWorld->GetWorldState();
		TS_ASSERT_EQUALS(worldState.mWorld, mWorld);

		//Creating Sector 1
		Sector* sector = mWorld->CreateSector("Sector1");
		TS_ASSERT_DIFFERS(sector, nullptr);
		TS_ASSERT_EQUALS(sector->Name(), "Sector1");

		//Adding Paul to Sector 1
		Entity* entity = sector->CreateEntity("Entity", "Paul");
		Scope* sectors = mWorld->Sectors();
		TS_ASSERT_EQUALS(entity->Name(), "Paul");

		//Finding sector in sectors
		Datum * sector1 = sectors->Search("Sector1");
		TS_ASSERT_DIFFERS(sector1, nullptr);

		if (sector1)
		{
			TS_ASSERT_EQUALS(sector1->GetScope(), sector);
		}
		else
		{
			TS_ASSERT(false);
		}

		//Getting entities in Sector 1
		Scope* entities = sector->Entities();
		TS_ASSERT_EQUALS(entities->Size(), 1);

		//Searching for Paul in Sector 1's Entities
		Datum * paul = entities->Find("Paul");
		TS_ASSERT_DIFFERS(sector1, nullptr);

		if (paul)
		{
			TS_ASSERT_EQUALS(paul->GetScope(), entity);
		}
		else
		{
			TS_ASSERT(false);
		}

		Entity* paulEntity = paul->GetScope()->As<Entity>();
		if (paulEntity)
		{
			Action* action = paulEntity->CreateAction("ConcreteAction", "Grading");
			TS_ASSERT_EQUALS(action->Name(), "Grading");
			TS_ASSERT_EQUALS(action->GetEntity(), entity);
		}
		else
		{
			TS_ASSERT(false);
		}

		TS_ASSERT_EQUALS(sector->GetWorld(), mWorld);
		TS_ASSERT_EQUALS(entity->GetSector(), sector);
	}

	void TestUpdate()
	{

		//Creating Sector 1
		WorldState worldState = WorldState();
		worldState.mWorld = mWorld;
		Sector* sector = mWorld->CreateSector("Sector1");
		Scope* entity = sector->CreateEntity("Entity", "Paul");
		Entity* paulEntity = entity->As<Entity>();

		if (paulEntity)
		{
			Scope* scope = paulEntity->CreateAction("ConcreteAction", "Grading");
			ConcreteAction* action = scope->As<ConcreteAction>();
			if (action)
			{
				mWorld->Update(worldState);
				TS_ASSERT_EQUALS(action->bUpdateHasBeenCalled, true);
				TS_ASSERT_EQUALS(action->mWorldState.mAction, action);
				TS_ASSERT_EQUALS(action->mWorldState.mEntity, entity);
				TS_ASSERT_EQUALS(action->mWorldState.mSector, sector);
				TS_ASSERT_EQUALS(action->mWorldState.mWorld, mWorld);
			}
			else
			{
				TS_ASSERT(false);
			}
		}
		else
		{
			TS_ASSERT(false);
		}
	}

	void TestUpdateActionList()
	{
		ConcreteAction concreteAction;
		WorldState worldState = WorldState();
		worldState.mWorld = mWorld;
		Sector* sector = mWorld->CreateSector("Sector1");
		Scope* entity = sector->CreateEntity("Entity", "Paul");
		Entity* paulEntity = entity->As<Entity>();
		if (paulEntity)
		{
			ActionList* actionList = paulEntity->CreateAction("ActionList", "Grading")->As<ActionList>();
			Scope* action = &concreteAction;
			actionList->Adopt(*action, "Grading", 0);
			paulEntity->Update(worldState);
			ConcreteAction* concreteAction2 = action->As<ConcreteAction>();
			if (concreteAction2)
			{
				TS_ASSERT_EQUALS(concreteAction2->bUpdateHasBeenCalled, true);
				TS_ASSERT_EQUALS(concreteAction2->mWorldState.mAction, action);
				TS_ASSERT_EQUALS(concreteAction2->mWorldState.mWorld, mWorld);
			}
			else
			{
				TS_ASSERT(false);
			}
		}
		else
		{
			TS_ASSERT(false);
		}
	}

	void TestXmlCreate()
	{
		std::string fileName = "Action.xml";
		mParseMaster->ParseFromFile(fileName);
		WorldState worldState;
		mWorld->Update(worldState);
		Action * action = worldState.mAction;
		ConcreteAction* actionCreate = action->As<ConcreteAction>();
		TS_ASSERT_EQUALS(actionCreate->Name(), "ActionAssignment");
		TS_ASSERT_EQUALS(actionCreate->bUpdateHasBeenCalled, true);

		Scope* scope = worldState.mEntity->Actions();
		if (scope)
		{
			Datum* datum = scope->Find("Assignments");
			if (datum)
			{
				ActionCreateAction* entity = datum->GetScope()->As<ActionCreateAction>();
				TS_ASSERT_EQUALS(entity->Name(), "Assignments");
			}
			else
			{
				TS_ASSERT(false);
			}
		}
		else
		{
			TS_ASSERT(false);
		}
	}

	void TestXmlDestroy()
	{
		std::string fileName = "Action2.xml";
		mParseMaster->ParseFromFile(fileName);
		WorldState worldState;
		mWorld->Update(worldState);
		worldState.mEntity->CreateAction("ConcreteAction", "ActionAssignment");
		Datum * datum = worldState.mEntity->Actions()->Find("ActionAssignment");
		if (datum)
		{
			Scope* scope = datum->GetScope();
			if (scope)
			{
				ConcreteAction* concrete = scope->As<ConcreteAction>();
				if (concrete)
				{
					TS_ASSERT_EQUALS(concrete->Name(), "ActionAssignment");
				}
				else
				{
					TS_ASSERT(false);
				}
			}
			else
			{
				TS_ASSERT(false);
			}
		}
		mWorld->Update(worldState);

		datum = worldState.mEntity->Actions()->Find("ActionAssignment");
		if (datum)
		{
			Scope* scope = datum->GetScope();
			if (!scope)
			{
				TS_ASSERT(true);

			}
			else
			{
				TS_ASSERT(false);
			}
		}

	}

private:
	World* mWorld;
	ConcreteActionFactory* mConcreteActionFactory;
	ActionListFactory* mActionListFactory;
	EntityFactory* mEntityFactory;
	ActionCreateActionFactory* mActionCreateFactory;
	ActionDestroyActionFactory* mActionDestroyFactory;

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
};

