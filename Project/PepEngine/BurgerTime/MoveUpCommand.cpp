#include "MoveUpCommand.h"
#include "Object.h"
#include "MovementComponent.h"

MoveUpCommand::MoveUpCommand(pep::Object* pObject, MovementComponent* pMovement)
	:pep::BaseCommand(pObject)
	,m_pMovement{pMovement}
{
}

void MoveUpCommand::Execute()
{
	m_pMovement->MoveUp();
}
