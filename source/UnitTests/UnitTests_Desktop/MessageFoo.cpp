#include "MessageFoo.h"

using namespace Unit_Tests;
using namespace Library;

RTTI_DEFINITIONS(MessageFoo);

int MessageFoo::mTestInt = 0;

MessageFoo::MessageFoo() :
bMessageHabeenPassed(false), mNumberOfCalls(0)
{
}


