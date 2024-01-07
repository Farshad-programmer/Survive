#pragma once
#include <string>
#include <array>

struct player_stats
{
public:

	int health = 100;
	int level = 1;
};


class Player
{
private:

	void BeginPlay();

	std::string m_playerName;
	std::string m_playerSex;
	player_stats m_playerStats;

	static constexpr std::size_t StorySize = 1000; 

	std::array<char , StorySize> m_story {"In the heart of an untouched forest, full of mysteries and wonders, You woke up from your slumber. Opening your eyes, you found various silver lights shimmering in the darkness at the corners and edges of the forest. You moved towards these lights and entered a magical world you had never seen before..." };

public:
	Player();
	~Player() = default;

	
	void Tick();

	void InitializePlayerInformation();
	void ShowPlayerStats();
	void Story();
};
