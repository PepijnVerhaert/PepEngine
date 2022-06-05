#pragma once
#include "BaseCommand.h"

class MovementComponent;
class MoveRightCommand final : public pep::BaseCommand
{
public:
	explicit MoveRightCommand(pep::Object* pObject, MovementComponent* pMovement);
	~MoveRightCommand() = default;
	void Execute() override;
private:
	MovementComponent* m_pMovement;
};