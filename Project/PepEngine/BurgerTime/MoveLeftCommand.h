#pragma once
#include "BaseCommand.h"

class MovementComponent;
class MoveLeftCommand final : public pep::BaseCommand
{
public:
	explicit MoveLeftCommand(pep::Object* pObject, MovementComponent* pMovement);
	~MoveLeftCommand() = default;
	void Execute() override;
private:
	MovementComponent* m_pMovement;
};