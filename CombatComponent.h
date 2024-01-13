#ifndef COMBAT_COMPONENT_H
#define COMBAT_COMPONENT_H


#include <memory>
#include "Player.h"


class CombatComponent 
{

public:
	CombatComponent();
	~CombatComponent();
	friend Player;

	Player* m_player {nullptr};



private:


};

#endif // COMBAT_COMPONENT_H
