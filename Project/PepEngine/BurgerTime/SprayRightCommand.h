#pragma once
#include "BaseCommand.h"

class SprayRightCommand final : public pep::BaseCommand
{
public:
	explicit SprayRightCommand(pep::Object* pObject);
	~SprayRightCommand() = default;
	void Execute() override;
private:
};