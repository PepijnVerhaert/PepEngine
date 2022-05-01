#include "PepEnginePCH.h"
#include "BaseCommand.h"

using namespace pep;

BaseCommand::BaseCommand(Object* pObject)
    :m_pObject{ pObject }
{
}

Object* BaseCommand::GetActor() const
{
    return m_pObject;
}
