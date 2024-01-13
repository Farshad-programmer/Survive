#pragma once
#include "MasterAI.h"


class Enemy :public MasterAI
{

public:
	Enemy(std::string name,int level = 1, int health = 100, int max_health = 100);
	~Enemy() override = default;

	virtual void Beginplay()override;
	virtual void Tick()override;

protected:

};

