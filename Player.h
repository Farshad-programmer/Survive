#ifndef PLAYER_H_UNIQUE
#define PLAYER_H_UNIQUE

#include <array>
#include <vector>
#include "Item.h"
#include "Enemy.h"
#include <memory>
#include "CombatComponent.h"

class CombatComponent;

struct player_stats
{
public:

	int level = 1;
	int health = 50;
	int max_health = 100;
	int hungry = 40;
	int max_hungry = 100;
};

class Player 
{
private:
	bool m_bQuit{ false };
	std::vector<std::unique_ptr<Item>> m_inventoryItems;
	int m_inventorySize{ 0 };
	std::unique_ptr<Item> m_spawnedItem;
	std::shared_ptr<Enemy> m_spawnedEnemy;
	std::shared_ptr<CombatComponent> m_combatComp;
	
	std::string m_playerName;
	std::string m_playerSex;
	player_stats m_playerStats;
	int m_restCounter = 0;

	static constexpr std::size_t StorySize = 5000;
	
	std::string m_npc_name;
	bool m_bStory2Available{ true };
	bool m_bIsInAttack{ false };
	bool m_bIsNPCInteract{ false };
	bool m_bIsFromLoadGame{ false };

	// Private functions
	void BeginPlay();
	void Move();
	void Rest();
	void Search();
	bool CanRest();
	void MainDecision();
	void CombatDecision();
	int MakeRandomNumberInRange(int min, int max);
	void SpawnItem();
	void ItemAction();
	void CheckInventory();
	void InventoryAction();
	void NPCAction();
public:
	Player();
	~Player() = default;

	void Tick();
	void QuitGame();
	void InitializePlayerInformation();
	void ShowPlayerStats(bool isFromLoadGame = false);
	void ShowPlayerAndEnemyStats(std::shared_ptr<Enemy> enemy);
	void AddItem(std::unique_ptr<Item> newItem);
	void RemoveItem(Item& newItem);
	void UpdatePlayerStats(std::string propertyName, int value, bool add = true);
	void MainMenu();
	void PauseMenu();
	void AreYouSure();
	void SaveGame(const std::string& filename, const std::string& itemFilename);
	void LoadGame(const std::string& filename, const std::string& itemFilename);

	std::unique_ptr<Item> ReadItemFromFile(std::ifstream& ifs)
	{
		std::unique_ptr<Item> item = std::make_unique<Item>();
		ifs >> *item;
		return item;
	}

	// public variables

	std::array<char, StorySize> m_story {"In the heart of an untouched forest, full of mysteries and wonders, You woke up from your slumber. Opening your eyes, you found various silver lights shimmering in the darkness at the corners and edges of the forest. You moved towards these lights and entered a magical world you had never seen before..." };
	std::array<char, StorySize> m_story2 {"You reached an abandoned house nearby, where a faint fire was burning. A bit closer, there was a girl, an Elf by the fire, lying in a pool of blood. However, she was still alive. In a trembling voice, she said, I'm hungry." };
	std::array<char, StorySize> m_story3 {"She said , Thank you, you saved me. I think there's still hope left. Let's move on. I'm Rana. I can't stay here now; there's someone I need to find. Otherwise, darkness will soon engulf everything. I hope to see you again." };
	std::array<char, StorySize> m_story4{"An orc stands before you, poised to strike! Brace yourself, for the challenge of a close encounter awaits. The orc advances with an aggressive stance, wielding its blade in trembling hands. Confronting this formidable and unpredictable force, your combat skills are put to the test. Now is the time to employ wit and tactics to face this orc, making crucial decisions at the right moments. " };


	//Getter and Setter
	bool GetIsQuit()const { return m_bQuit; }
	bool IsInteractNPC()const { return m_bIsNPCInteract; }
	bool IsInAttack()const { return m_bIsInAttack; }
	bool IsFromLoadGame()const { return m_bIsFromLoadGame; }
	[[nodiscard]] std::string GetNPCName()const { return m_npc_name; }
	std::shared_ptr<Enemy> GetSpawnedEnemy()const { return m_spawnedEnemy; }
	void SetIsInteractNPC(bool interact) { m_bIsNPCInteract = interact; }
	void SetIsInAttack(bool isInAttack) { m_bIsInAttack = isInAttack; }
};

#endif // PLAYER_H_UNIQUE
