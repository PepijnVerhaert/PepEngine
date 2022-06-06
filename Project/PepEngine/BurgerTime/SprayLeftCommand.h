#pragma once
#include "BaseCommand.h"

class SprayLeftCommand final : public pep::BaseCommand
{
public:
	explicit SprayLeftCommand(pep::Object* pObject);
	~SprayLeftCommand() = default;
	void Execute() override;
private:
};