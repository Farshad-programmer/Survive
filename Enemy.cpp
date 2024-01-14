#include "Enemy.h"
#include "Color.h"

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
	PlaySound(TEXT("sounds/Sword_Hit_Flesh_2.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
