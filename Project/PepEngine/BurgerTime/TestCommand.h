#pragma once
#include "BaseCommand.h"

class TestCommand final : public pep::BaseCommand
{
public:
	explicit TestCommand(pep::Object* pObject);
	~TestCommand() = default;
	void Execute() override;
};

