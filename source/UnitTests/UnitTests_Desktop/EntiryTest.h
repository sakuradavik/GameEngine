#include <cxxtest/TestSuite.h>
#include "Entity.h"
#include "Sector.h"
#include "World.h"
#include "WorldState.h"
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

using namespace Library;

class EntityTestSuite : public CxxTest::TestSuite
{
public:
	void setUp()
	{
		mWorld = new World();
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

		mEntityFactory = new EntityFactory();
		mFileName = "World.xml";
		mParseMaster->ParseFromFile(mFileName);
	}

	void tearDown()
	{
		mParseMaster->RemoveHelper(*mIntegerXmlParseHelper);
		mParseMaster->RemoveHelper(*mFloatXmlParseHelper);
		mParseMaster->RemoveHelper(*mVectorXmlParseHelper);
		mParseMaster->RemoveHelper(*mMatrixXmlParseHelper);
		mParseMaster->RemoveHelper(*mStringXmlParseHelper);
		mParseMaster->RemoveHelper(*mScopeXmlParseHelper);
		mParseMaster->RemoveHelper(*mWorldParseHelper);
		mParseMaster->RemoveHelper(*mSectorParseHelper);
		mParseMaster->RemoveHelper(*mEntityParseHelper);

		delete mIntegerXmlParseHelper;
		delete mFloatXmlParseHelper;
		delete mVectorXmlParseHelper;
		delete mMatrixXmlParseHelper;
		delete mStringXmlParseHelper;
		delete mWorldParseHelper;
		delete mSectorParseHelper;
		delete mEntityParseHelper;
		delete mScopeXmlParseHelper;
		delete mParseMaster;
		delete mScopeSharedData;
		delete mWorld;
		delete mEntityFactory;
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

		//Adding Tom to Sector 1
		Entity* entity2 = sector->CreateEntity("Entity", "Tom");
		entities = sector->Entities();
		TS_ASSERT_EQUALS(entities->Size(), 2);
		TS_ASSERT_EQUALS(entity2->Name(), "Tom");
		
		//Searching for Tom in Sector1's Entities
		Datum * tom = entities->Search("Tom");
		TS_ASSERT_DIFFERS(sector1, nullptr);

		if (tom)
		{
			TS_ASSERT_EQUALS(tom->GetScope(), entity2);
		}

		TS_ASSERT_EQUALS(sector->GetWorld(), mWorld);
		TS_ASSERT_EQUALS(entity->GetSector(), sector);
		TS_ASSERT_EQUALS(entity2->GetSector(), sector);

	}

	void TestWorldParser()
	{
		Attribute* scope = mScopeSharedData->GetWorld();
		if (scope)
		{
			World * world = scope->As<World>();
			if (world)
			{
				TS_ASSERT_EQUALS(world->Name(), "FIEA");
				Scope* sectors = world->Sectors();
				Datum * sector1 = sectors->Search("ProgrammingII");
				if (sector1)
				{
					Sector* sector = sector1->GetScope()->As<Sector>();
					if (sector)
					{
						TS_ASSERT_EQUALS(sector->Name(), "ProgrammingII");
						Scope* entities = sector->Entities();
						Datum * paul = entities->Find("Paul");
						if (paul)
						{
							Entity* entity = paul->GetScope()->As<Entity>();
							TS_ASSERT_EQUALS(entity->Name(),"Paul");
							if (entity->Find("PowerLevel"))
							{
								TS_ASSERT_EQUALS(entity->Find("PowerLevel")->GetInteger(), 10);
							}
						}
					}
				}

				sectors = world->Sectors();
				Datum * sector2 = sectors->Search("ProgrammingI");
				if (sector2)
				{
					Sector* sector = sector2->GetScope()->As<Sector>();
					if (sector)
					{
						TS_ASSERT_EQUALS(sector->Name(), "ProgrammingI");
						Scope* entities = sector->Entities();
						Datum * paul = entities->Find("Tom");
						if (paul)
						{
							Entity* entity = paul->GetScope()->As<Entity>();
							TS_ASSERT_EQUALS(entity->Name(), "Tom");
						}
					}
				}
			}
		}

	}

private:
	EntityFactory* mEntityFactory;
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
	ScopeSharedData* mScopeSharedData;
	World* mWorld;
	std::string mFileName;
};