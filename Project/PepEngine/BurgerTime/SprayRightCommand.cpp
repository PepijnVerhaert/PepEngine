#include "SprayRightCommand.h"
#include "Object.h"
#include "SprayPepperComponent.h"

SprayRightCommand::SprayRightCommand(pep::Object* pObject)
	:BaseCommand(pObject)
{
}

void SprayRightCommand::Execute()
{
	GetActor()->GetComponent<SprayPepperComponent>()->SprayRight();
}
