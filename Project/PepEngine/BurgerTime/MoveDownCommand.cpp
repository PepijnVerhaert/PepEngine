#include "MoveDownCommand.h"
#include "Object.h"
#include "MovementComponent.h"

MoveDownCommand::MoveDownCommand(pep::Object* pObject, MovementComponent* pMovement)
	:pep::BaseCommand(pObject)
	, m_pMovement{ pMovement }
{
}

void MoveDownCommand::Execute()
{
	m_pMovement->MoveDown();
}
