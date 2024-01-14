#pragma once
#include "MasterAI.h"

class NPC : public MasterAI
{

public:
	NPC(std::string name,int level = 1, int health = 100, int max_health = 100, bool hasStory = false);
	~NPC();


protected:

};

