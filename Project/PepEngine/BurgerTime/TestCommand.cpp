#include "TestCommand.h"
#include "Object.h"
#include "TestComponent.h"

TestCommand::TestCommand(pep::Object* pObject)
	:pep::BaseCommand(pObject)
{
}

void TestCommand::Execute()
{
	GetActor()->GetComponent<TestComponent>()->Test();
}
