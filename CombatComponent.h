#ifndef COMBAT_COMPONENT_H
#define COMBAT_COMPONENT_H


#include <memory>
#include "Player.h"
#include "Enemy.h"
#include "Item.h"

class Enemy;
class Item;


class CombatComponent
{

public:
	CombatComponent();
	~CombatComponent() = default;
	friend Player;

	Player* m_player {nullptr};
	std::unique_ptr<Item>m_spawnedLootItem;


private:

	void CombatDecision(std::shared_ptr<Enemy>& enemy) ;
	void Attack(std::shared_ptr<Enemy>& enemy,bool cleanConsole = true);
	void StrengthAttack(std::shared_ptr<Enemy>& enemy);
	void ApplyDamageToEnemy(unsigned damage ,std::shared_ptr<Enemy>& enemy);
	void ChangeTurn(const std::shared_ptr<Enemy>& enemy);
	void ObtainItem();
};



#endif // COMBAT_COMPONENT_H
