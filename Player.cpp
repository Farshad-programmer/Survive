#include "Player.h"
#include <chrono> // for miliseconds
#include <conio.h> // for _getch() and _kbhit()
#include <string>
#include <random> 
#include <fstream>
#include "Color.h"
#include "MyLibrary.h"

Player::Player() :
	m_playerName("Player"), m_playerSex("Male"), m_spawnedItem(nullptr)
{

}

void Player::BeginPlay()
{

}

void Player::Tick()
{
	MainDecision();
}

void Player::InitializePlayerInformation()
{
	std::cout << "What is your name? ";
	std::string yourName;
	std::cin >> yourName;
	if (!IsNonNumeric(yourName))
	{
		CleanConsole("Please Type a correct name !");
		InitializePlayerInformation();
	}
	else
	{
		m_playerName = yourName;
		std::cout << "\n";
		bool gender_Correct = false;

		while (!gender_Correct)
		{
			std::cout << "What is your gender? " << std::endl;
			std::cout << "1 - Male " << std::endl;
			std::cout << "2 - Female " << std::endl;
			std::string gender;
			std::cin >> gender;

			if (gender == "1")
			{
				m_playerSex = "Male";
				gender_Correct = true;
			}
			else if (gender == "2")
			{
				m_playerSex = "Female";
				gender_Correct = true;
			}
			else
			{
				CleanConsole();
				std::cout << "Please Type 1 or 2 for your Sex ! " << std::endl;
			}
		}
	}

}

void Player::ShowPlayerStats(bool isFromLoadGame)
{
	if(!isFromLoadGame)
	{
		std::cout << "------------------------" << std::endl;
		std::cout << YELLOW_TEXT << m_playerName << RESET_COLOR << std::endl;
		std::cout << "------------------------" << std::endl;
		std::cout << "Level: " << m_playerStats.level << std::endl;
		std::cout << "Health: " << m_playerStats.health << " / " << m_playerStats.max_health << std::endl;
		std::cout << "Hungry: " << m_playerStats.hungry << " / " << m_playerStats.max_hungry << std::endl;
		std::cout << "------------------------" << std::endl;
	}
	else
	{
		//Data loaded from save file!
	}

}


void Player::Story(std::array<char, StorySize> story)
{
	std::cout << "\nPress Enter to skip...\n";

	long long type_writer_speed = 100LL;

	for (const auto element : story)
	{
		if (_kbhit()) {
			if (_getch() == '\r')
			{
				type_writer_speed = static_cast<long long>(0.1);
			}
		}
		std::cout << element;
		std::this_thread::sleep_for(std::chrono::milliseconds(type_writer_speed));
	}

	std::cout << "\n";
	std::cout << "\n";
}

void Player::QuitGame()
{
	//exit(0); // not safe
	CleanConsole();
	std::cout << "****************** END GAME ******************* " << std::endl;
	m_bQuit = true;
}

void Player::MainDecision()
{
	std::cout << "What do you do: \n";
	std::cout << "1 - Move " << std::endl;
	std::cout << "2 - Rest " << std::endl;
	std::cout << "3 - Search " << std::endl;
	std::cout << "4 - Check Inventory " << std::endl;
	std::cout << "5 - Menu " << std::endl;
	std::string decision;
	std::cin >> decision;

	if (IsInputDigit(decision))
	{
		switch (int number = int(std::stod(decision)))
		{
		case 1:
			Move();
			break;
		case 2:
			Rest();
			break;
		case 3:
			Search();
			break;
		case 4:
			CheckInventory();
			break;
		case 5:
			PauseMenu();
			break;
		default:
			CleanConsole();
			std::cout << "Please Type 1, 2, 3, 4 or 5 for your Decision ! " << std::endl;
			break;
		}
	}
	else
	{
		CleanConsole();
		std::cout << "Please Type 1, 2, 3, 4 or 5 for your Decision ! " << std::endl;
	}

}

void Player::ItemAction()
{
	std::cout << "What do you do: " << std::endl;
	std::cout << "1 - Add item to Inventory " << std::endl;
	std::cout << "2 - Do nothing " << std::endl;
	if(m_spawnedItem->GetItemType() == EItemType::food)
	{
		std::cout << "3 - Eat it " << std::endl;
	}

	std::string action;
	std::cin >> action;

	if (IsInputDigit(action))
	{
		switch (int number = static_cast<int>(std::stod(action)))
		{
		case 1:
			AddItem(std::move(m_spawnedItem));
			break;
		case 2:
			CleanConsole();
			break;
		case 3:
			CleanConsole("You ate an : " + m_spawnedItem->GetItemName());
			m_spawnedItem->Eat(this,false);
			break;
		default:
			CleanConsole();
			std::cout << "Please Type 1 or 2 for your action ! " << std::endl;
			ItemAction();
		}
	}
	else
	{
		CleanConsole();
		std::cout << "Please Type 1 or 2 for your action ! " << std::endl;
		ItemAction();
	}

}

void Player::Move()
{
	CleanConsole();
	if (m_playerStats.hungry < 15)
	{
		std::cout << "I am so hungry , I can not walk more." << std::endl;
	}
	else if (m_playerStats.health < 15)
	{
		std::cout << "I am sick , I can not walk more." << std::endl;
	}
	else
	{
		const int randNumber = MakeRandomNumberInRange(1, 6);
		if (randNumber == 6 && m_bStory2Available)
		{
			m_bStory2Available = false;
			Story(m_story2);
			m_npc_name = "stranger";
			NPCAction();
		}
		else
		{
			size_t kilometer = 2;
			std::cout << "You walked for about " << kilometer << " kilometers" << std::endl;
			m_playerStats.hungry -= 5;
		}

	}
}

void Player::Rest()
{
	CleanConsole();

	if (CanRest())
	{
		m_restCounter += 3;
		std::cout << "You rested for a while." << std::endl;
		m_playerStats.hungry -= 5;
		m_playerStats.health += 10;
		if (m_playerStats.health > 100)
		{
			m_playerStats.health = 100;
		}
	}
	else
	{
		m_restCounter--;
		std::cout << "I've rested enough, I can't stay here for too long. It's dangerous." << std::endl;
	}
}

void Player::Search()
{
	CleanConsole();
	const int randNumber = MakeRandomNumberInRange(1, 3);
	if (randNumber == 1)
	{
		SpawnItem();
	}
	else
	{
		CleanConsole();
		std::cout << "No special findings were discovered! " << std::endl;
	}
	m_playerStats.hungry -= 2;
}

bool Player::CanRest()
{
	if (m_restCounter <= 6)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Player::SpawnItem()
{
	switch (const int randNum = MakeRandomNumberInRange(1, 5))
	{
	case 1:
		m_spawnedItem = std::make_unique<Item>("apple", EItemType::food);
		break;
	case 2:
		m_spawnedItem = std::make_unique<Item>("banana", EItemType::food);
		break;
	case 3:
		m_spawnedItem = std::make_unique<Item>("corn", EItemType::food);
		break;
	case 4:
		m_spawnedItem = std::make_unique<Item>("soup", EItemType::food, 1, false);
		break;
	case 5:
		m_spawnedItem = std::make_unique<Item>("meat", EItemType::food);
		break;
	default:
		m_spawnedItem = std::make_unique<Item>("apple", EItemType::food);
		break;
	}


	std::cout << " You found an " << m_spawnedItem->GetItemName() << std::endl;
	ItemAction();
}

void Player::AddItem(std::unique_ptr<Item> newItem)
{
	if (newItem == nullptr) return;

	CleanConsole();
	bool itemFound = false;
	if (newItem->IsItemStackable())
	{
		for (size_t i = 0; i < m_inventoryItems.size(); i++)
		{
			if (newItem->GetItemName() == m_inventoryItems[i]->GetItemName())
			{
				std::cout << newItem->GetItemName() << " added to inventory." << std::endl;
				m_inventoryItems[i]->IncreaseQuantity();
				m_spawnedItem = nullptr;
				itemFound = true;
				break;
			}
		}
		if (!itemFound)
		{
			std::cout << newItem->GetItemName() << " added to inventory." << std::endl;
			m_inventoryItems.push_back(std::move(newItem));
			m_spawnedItem = nullptr;
		}
	}
	else
	{
		std::cout << newItem->GetItemName() << " added to inventory." << std::endl;
		m_inventoryItems.push_back(std::move(newItem));
		m_spawnedItem = nullptr;
	}
}

void Player::RemoveItem(Item& newItem)
{
	if (!m_inventoryItems.empty())
	{
		if (newItem.IsItemStackable() && newItem.GetItemQuantity() > 1)
		{
			newItem.DecreaseQuantity();
		}
		else
		{
			for (int i = 0; i < m_inventoryItems.size(); ++i)
			{
				if (m_inventoryItems[i]->GetItemName() == newItem.GetItemName())
				{
					m_inventoryItems.erase(m_inventoryItems.begin() + i);
					break;
				}
			}
		}
	}
	else
	{
		std::cout << "Inventory is already empty." << std::endl;
	}
}

void Player::CheckInventory()
{
	CleanConsole();
	int index = 0;
	std::cout << " You can select your items ..." << std::endl;
	for (const auto& item : m_inventoryItems)
	{
		if (item->GetItemQuantity() > 1)
		{
			std::cout << index + 1 << "-" << item->GetItemName() << "(" << item->GetItemQuantity() << ")" << std::endl;
		}
		else
		{
			std::cout << index + 1 << "-" << item->GetItemName() << std::endl;
		}

		index++;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "-----------------" << std::endl;
	std::cout << "0-Close Inventory" << std::endl;
	std::cout << "-----------------" << std::endl;
	m_inventorySize = index;
	if (m_inventorySize < 1)
	{
		std::cout << " Your inventory is empty" << std::endl;
		if (m_bIsNPCInteract)
		{
			// todo : need a separate class for NPCs later
			NPCAction();
		}
	}
	else
	{
		InventoryAction();
	}
}

void Player::InventoryAction()
{
	std::string action;
	std::cin >> action;
	int number = static_cast<int>(std::stod(action));

	if (number != 0)
	{
		if (number <= m_inventorySize)
		{
			number--;
			const std::unique_ptr<Item>& selectedItem = m_inventoryItems[number];
			if (selectedItem)
			{
				selectedItem->ItemAction(this);
			}
		}
		else
		{
			std::cout << " Invalid Input!" << std::endl;
			CheckInventory();
		}
	}
	else
	{
		CleanConsole();
	}

}

void Player::NPCAction()
{
	m_bIsNPCInteract = true;
	std::cout << "What do you do? " << std::endl;
	std::cout << GREEN_TEXT << "1 - Check Your Inventory for Food " << RESET_COLOR << std::endl;
	std::cout << RED_TEXT << "2 - Do nothing " << RESET_COLOR << std::endl;

	std::string action;
	std::cin >> action;

	if (IsInputDigit(action))
	{
		switch (int number = static_cast<int>(std::stod(action)))
		{
		case 1:
			CheckInventory();
			break;
		case 2:
			m_bIsNPCInteract = false;
			CleanConsole("You left her unattended!");
			break;
		default:
			CleanConsole();
			std::cout << "Please Type 1 or 2 for your action ! " << std::endl;
			ItemAction();
		}
	}
}

int Player::MakeRandomNumberInRange(int min, int max)
{
	std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<> distribution(min, max);// make a distribution

	return distribution(gen);
}

void Player::UpdatePlayerStats(std::string propertyName, int value, bool add)
{
	if (propertyName == "health")
	{
		if (add)
		{
			m_playerStats.health += value;
			if (m_playerStats.health >= m_playerStats.max_health)
			{
				m_playerStats.health = m_playerStats.max_health;
			}

		}
		else
		{
			m_playerStats.health -= value;
			if (m_playerStats.health < 0)
			{
				m_playerStats.health = 0;
			}
		}

	}
	else if (propertyName == "hungry")
	{
		if (add)
		{
			m_playerStats.hungry += value;
			if (m_playerStats.hungry >= m_playerStats.max_hungry)
			{
				m_playerStats.hungry = m_playerStats.max_hungry;
			}
		}
		else
		{
			m_playerStats.hungry -= value;
			if (m_playerStats.hungry < 0)
			{
				m_playerStats.hungry = 0;
			}
		}
	}
}

void Player::MainMenu()
{
	SetConsoleFont(20);
	std::cout << "1 - NEW GAME " << std::endl;
	std::cout << "2 - CONTINUE " << std::endl;
	std::cout << "3 - QUIT " << std::endl;

	std::string action;
	std::cin >> action;

	if (IsInputDigit(action))
	{
		switch (int number = int(std::stod(action)))
		{
		case 1:
			CleanConsole();
			InitializePlayerInformation();
			CleanConsole();
			break;
		case 2:
			LoadGame("save/base_save.txt", "save/item_save.txt");
			break;
		case 3:
			QuitGame();
			break;
		default:
			MainMenu();
			std::cout << "Please Type 1, 2 or 3 ! " << std::endl;
			break;
		}
	}
	else
	{
		MainMenu();
		std::cout << "Please Type 1, 2 or 3 ! " << std::endl;
	}
}

void Player::PauseMenu()
{
	CleanConsole("PAUSE GAME !");
	std::cout << "1 - RESUME " << std::endl;
	std::cout << "2 - SAVE " << std::endl;
	std::cout << "3 - QUIT " << std::endl;

	std::string action;
	std::cin >> action;

	if (IsInputDigit(action))
	{
		switch (int number = int(std::stod(action)))
		{
		case 1:
			CleanConsole();
			break;
		case 2:
			SaveGame("save/base_save.txt", "save/item_save.txt");
			break;
		case 3:
			CleanConsole();
			AreYouSure();
			break;
		default:
			PauseMenu();
			std::cout << "Please Type 1, 2 or 3 ! " << std::endl;
			break;
		}
	}
	else
	{
		PauseMenu();
		std::cout << "Please Type 1, 2 or 3 ! " << std::endl;
	}
}

void Player::AreYouSure()
{
	CleanConsole("Are you sure? ");
	std::cout << "1 - No " << std::endl;
	std::cout << "2 - Yes " << std::endl;

	std::string action;
	std::cin >> action;

	if (IsInputDigit(action))
	{
		switch (int number = int(std::stod(action)))
		{
		case 1:
			CleanConsole();
			PauseMenu();
			break;
		case 2:
			CleanConsole();
			QuitGame();
			break;

		default:
			PauseMenu();
			std::cout << "Please Type 1, 2 ! " << std::endl;
			break;
		}
	}
	else
	{
		PauseMenu();
		std::cout << "Please Type 1, or 2 ! " << std::endl;
	}
}

void Player::SaveGame(const std::string& filename, const std::string& itemFilename)
{
	CleanConsole();

	// to save item class
	std::ofstream ofs("save/item_save.txt", std::ios::out | std::ios::trunc);
	if (!ofs.is_open()) {
		std::cerr << "Error opening file for writing!" << std::endl;
		return;
	}
	for (const auto& itemPtr : m_inventoryItems)
	{
		ofs << *itemPtr;
	}
	ofs.close();

	// to save player stats
	std::fstream file(filename);
	if (file.is_open())
	{
		file << "Player Name: " << m_playerName << std::endl;
		file << "Level: " << m_playerStats.level << std::endl;
		file << "Health: " << m_playerStats.health << std::endl;
		file << "Hungry: " << m_playerStats.hungry << std::endl;
		file.close();
		std::cout << CYAN_TEXT << "GAME SAVED !" << RESET_COLOR << std::endl;
	}
	else
	{
		std::cerr << "Unable to open the file for saving." << std::endl;
	}
}




void Player::LoadGame(const std::string& filename, const std::string& itemFilename)
{

	std::ifstream ifs("save/item_save.txt");

	if (!ifs.is_open()) {
		std::cerr << "Error opening file for reading!" << std::endl;
		return;
	}

	std::unique_ptr<Item> currentItem;

	while (!ifs.eof()) {
		currentItem = ReadItemFromFile(ifs);
		if (currentItem != nullptr && currentItem->GetItemName() != "") {
			AddItem(std::move(currentItem));
		}
	}
	
	std::fstream file(filename);
	if(file.is_open())
	{
		std::string line;
		while (std::getline(file,line))
		{
			size_t delimiterPos = line.find(":");
			if(delimiterPos != std::string::npos)
			{
				std::string key = line.substr(0, delimiterPos);
				std::string value = line.substr(delimiterPos + 2); // it start from : and one space after that
				if (key == "Health") {
					m_playerStats.health = std::stoi(value);
				}
				else if (key == "Hungry") {
					m_playerStats.hungry = std::stoi(value);
				}
				else if(key == "Level")
				{
					m_playerStats.level = std::stoi(value);
				}
				else if(key == "Player Name")
				{
					m_playerName = value;
				}
			}
		}
		file.close();

		CleanConsole("Data loaded successfully.");
		ShowPlayerStats(true);
	}
	else
	{
		CleanConsole("Unable to open the file for loading.");
	}
}


