#ifndef COMBAT_COMPONENT_H
#define COMBAT_COMPONENT_H


#include <memory>
#include "Player.h"
#include "Enemy.h"

class Enemy;
class CombatComponent 
{

public:
	CombatComponent();
	~CombatComponent() = default;
	friend Player;

	Player* m_player {nullptr};


private:

	void CombatDecision(std::shared_ptr<Enemy>& enemy) ;
	void Attack(std::shared_ptr<Enemy>& enemy,bool cleanConsole = true);
	void StrengthAttack(std::shared_ptr<Enemy>& enemy);
	void ApplyDamageToEnemy(unsigned damage ,std::shared_ptr<Enemy>& enemy);
	void ChangeTurn(const std::shared_ptr<Enemy>& enemy);
};



#endif // COMBAT_COMPONENT_H
