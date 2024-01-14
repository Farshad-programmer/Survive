#include "NPC.h"

NPC::NPC(std::string name,int level, int health, int max_health, bool hasStory)
	:MasterAI(name,level,health,max_health, hasStory)
{

}

NPC::~NPC()
{

}
