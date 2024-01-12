#pragma once
#include <string>

class MasterAI
{
private:
	std::string m_name;
	int m_level = 1;
	int m_health = 50;
	int m_maxHealth = 100;

public:
	
	MasterAI(std::string name = "no name",int level = 1 ,int health = 100, int max_health = 100);
	~MasterAI() = default;

	virtual void Beginplay();
	virtual void Tick();



	// Getter and setter
	[[nodiscard]] std::string GetName()const { return m_name; }
	[[nodiscard]] int GetLevel()const { return m_level; }
	[[nodiscard]] int GetHealth()const { return m_health; }
	[[nodiscard]] int GetMaxHealth()const { return m_maxHealth; }
};

