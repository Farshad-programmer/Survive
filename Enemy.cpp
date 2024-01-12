#include "Enemy.h"

Enemy::Enemy(std::string name,int level, int health, int max_health)
	:MasterAI(name,level,health,max_health)
{

}

void Enemy::Beginplay()
{
	MasterAI::Beginplay();

}

void Enemy::Tick()
{
	MasterAI::Tick();

}
