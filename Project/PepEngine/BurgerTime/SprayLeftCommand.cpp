#include "SprayLeftCommand.h"
#include "Object.h"
#include "SprayPepperComponent.h"

SprayLeftCommand::SprayLeftCommand(pep::Object* pObject)
	:BaseCommand(pObject)
{
}

void SprayLeftCommand::Execute()
{
	GetActor()->GetComponent<SprayPepperComponent>()->SprayLeft();
}
