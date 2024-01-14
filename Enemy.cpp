#include "Enemy.h"

Enemy::Enemy(std::string name,int level, int health, int max_health, bool hasStory)
	:MasterAI(name,level,health,max_health,hasStory)
{

}

Enemy::~Enemy()
{

}


void Enemy::ReceiveDamage(int damage)
{
	m_health -= damage;
}

bool Enemy::IsDeath() const
{
	if(m_health <= 0)
	{
		return true;
	}
	return false;
}

void Enemy::EnemyAttackPlayer(Player& player)
{
	const unsigned damage = m_level * 20;
	player.ReceiveDamage(static_cast<int>(damage));
}
