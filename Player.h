#pragma once
#include <array>
#include <vector>
#include "Item.h"

struct player_stats
{
public:

	int level = 1;
	int health = 50;
	int hungry = 40;
};


class Player
{
private:

	void BeginPlay();

	std::vector<std::unique_ptr<Item>> m_inventory;
	std::unique_ptr<Item> m_spawnedItem;
	
	std::string m_playerName;
	std::string m_playerSex;
	player_stats m_playerStats;
	int m_restCounter = 0;

	static constexpr std::size_t StorySize = 1000; 

	std::array<char , StorySize> m_story {"In the heart of an untouched forest, full of mysteries and wonders, You woke up from your slumber. Opening your eyes, you found various silver lights shimmering in the darkness at the corners and edges of the forest. You moved towards these lights and entered a magical world you had never seen before..." };

public:
	Player();
	~Player() = default;

	
	void Tick();

	void InitializePlayerInformation();
	void ShowPlayerStats();
	void Story();
	void MainDecision();
	void ItemAction();
	void Move();
	void Rest();
	bool CanRest();
	void CleanConsole();
	void SpawnItem();
	void AddItem(std::unique_ptr<Item> newItem);
};

