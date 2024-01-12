#include "NPC.h"

NPC::NPC(std::string name,int level, int health, int max_health)
	:MasterAI(name,level,health,max_health)
{

}

void NPC::Beginplay()
{
	MasterAI::Beginplay();
}

void NPC::Tick()
{
	MasterAI::Tick();
}
