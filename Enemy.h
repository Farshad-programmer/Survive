#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "MasterAI.h"
#include "Player.h"


class Enemy :public MasterAI
{

public:
	Enemy(std::string name,int level = 1, int health = 100, int max_health = 100, bool hasStory = false);
	~Enemy();

	void ReceiveDamage(int damage);
	bool IsDeath() const;

	void EnemyAttackPlayer(Player& player);




protected:


private:


public:
};

#endif // ENEMY_H
