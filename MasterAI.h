
#ifndef MASTER_AI_H
#define MASTER_AI_H

#include <string>
#include <array>

class MasterAI
{

public:
	
	MasterAI(std::string name = "no name",int level = 1 ,int health = 100, int max_health = 100,bool hasStory = false);
	virtual ~MasterAI();

	static constexpr std::size_t StorySize = 5000;


protected:
	std::string m_name;
	int m_level = 1;
	int m_health = 50;
	int m_maxHealth = 100;
	bool m_bHasStory{ false };
	std::array<char, StorySize> m_AIstory{"An orc stands before you, poised to strike! Brace yourself, for the challenge of a close encounter awaits. The orc advances with an aggressive stance, wielding its blade in trembling hands. Confronting this formidable and unpredictable force, your combat skills are put to the test. Now is the time to employ wit and tactics to face this orc, making crucial decisions at the right moments. " };
	std::array<char, StorySize> m_AIafterDeathStory{""};
private:

public:


	// Getter and setter
	[[nodiscard]] std::string GetName()const { return m_name; }
	[[nodiscard]] int GetLevel()const { return m_level; }
	[[nodiscard]] int GetHealth()const { return m_health; }
	[[nodiscard]] int GetMaxHealth()const { return m_maxHealth; }
	[[nodiscard]] bool GetIsHasStory() const { return m_bHasStory; }
	std::array<char, StorySize> GetAIStory()const { return m_AIstory; }
	std::array<char, StorySize> GetAIAfterDeathStory()const { return m_AIafterDeathStory; }
};

#endif // MASTER_AI_H