#include "MoveLeftCommand.h"
#include "Object.h"
#include "MovementComponent.h"

MoveLeftCommand::MoveLeftCommand(pep::Object* pObject, MovementComponent* pMovement)
	:pep::BaseCommand(pObject)
	, m_pMovement{ pMovement }
{
}

void MoveLeftCommand::Execute()
{
	m_pMovement->MoveLeft();
}
