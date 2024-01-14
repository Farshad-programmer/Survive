#include "MasterAI.h"
#include "Story.h"

MasterAI::MasterAI(std::string name,int level, int health , int max_health,bool hasStory )
	:m_name(name),m_level(level),m_health(health),m_maxHealth(max_health),m_bHasStory(hasStory)
{
	if(hasStory)
	{
		if(m_name == "Orc")
		{
			m_AIafterDeathStory = orcDeathStory;
		}
	}
}

MasterAI::~MasterAI()
{

}

