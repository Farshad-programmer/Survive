#pragma once
#include "MasterAI.h"

class NPC : public MasterAI
{
private:


public:
	NPC(std::string name,int level = 1, int health = 100, int max_health = 100);
	~NPC() = default;

	virtual void Beginplay()override;
	virtual void Tick()override;
};

