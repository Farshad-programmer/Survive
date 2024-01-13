#include "CombatComponent.h"

CombatComponent::CombatComponent()
{

}

CombatComponent::~CombatComponent()
{
	delete m_player;
	m_player = nullptr;
}
