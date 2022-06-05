#include "MoveRightCommand.h"
#include "Object.h"
#include "MovementComponent.h"

MoveRightCommand::MoveRightCommand(pep::Object* pObject, MovementComponent* pMovement)
	:pep::BaseCommand(pObject)
	, m_pMovement{ pMovement }
{
}

void MoveRightCommand::Execute()
{
	m_pMovement->MoveRight();
}
