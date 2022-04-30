#pragma once

namespace pep
{
	class Object;
	class BaseCommand
	{
	public:
		explicit BaseCommand(Object* pObject);
		virtual ~BaseCommand() = default;
		virtual void Execute() = 0;
	protected:
		Object* GetActor() const;
	private:
		Object* m_pObject;
	};
}