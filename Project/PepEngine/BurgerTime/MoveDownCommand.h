#pragma once
#include "BaseCommand.h"

class MovementComponent;
class MoveDownCommand final : public pep::BaseCommand
{
public:
	explicit MoveDownCommand(pep::Object* pObject, MovementComponent* pMovement);
	~MoveDownCommand() = default;
	void Execute() override;
private:
	MovementComponent* m_pMovement;
};