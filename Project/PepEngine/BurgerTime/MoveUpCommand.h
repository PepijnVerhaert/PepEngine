#pragma once
#include "BaseCommand.h"

class MovementComponent;
class MoveUpCommand final : public pep::BaseCommand
{
public:
	explicit MoveUpCommand(pep::Object* pObject, MovementComponent* pMovement);
	~MoveUpCommand() = default;
	void Execute() override;
private:
	MovementComponent* m_pMovement;
};