#include "Player.h"
#include <chrono> // for miliseconds
#include <conio.h> // for _getch() and _kbhit()
#include <string>
#include <cstdlib> // for clean console cmd


Player::Player() :
	m_playerName("Player"), m_playerSex("Male"),m_spawnedItem(nullptr)
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
	std::cout << "Set Your Name: ";
	std::cin >> m_playerName;
	std::cout << "\n";
    bool gender_Correct = false;

    while(!gender_Correct) {
        std::cout << "Set Your Sex: " << std::endl;
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
			system("cls");
			std::cout << "Please Type 1 or 2 for your Sex ! " << std::endl;
        }
    }
}

void Player::ShowPlayerStats()
{
	std::cout << "\n";
	std::cout << "\n";

	std::cout << m_playerName << std::endl;
	std::cout << "------------------------" << std::endl;
	std::cout << "Level: " << m_playerStats.level<< std::endl;
	std::cout << "Health: " << m_playerStats.health << std::endl;
	std::cout << "Hungry: " << m_playerStats.hungry << std::endl;
	std::cout << "------------------------" << std::endl;
}


void Player::Story()
{
	std::cout << "\nPress Enter to skip...\n";

	long long type_writer_speed = 100LL;

	for (auto element : m_story)
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
}

void Player::MainDecision()
{
	std::cout << "What do you do: \n";
	std::cout << "1 - Move " << std::endl;
	std::cout << "2 - Rest " << std::endl;
	std::cout << "3 - Search " << std::endl;
	std::cout << "4 - Check Inventory " << std::endl;
	int decision;
	std::cin >> decision;
	switch (decision)
	{
	case 1:
		Move();
		break;
	case 2:
		Rest();
		break;
	case 3:
		SpawnItem();
		break;
	case 4:

		break;
	}
}

void Player::ItemAction()
{
	std::cout << "What do you do: " << std::endl;
	std::cout << "1 - Add item to Inventory " << std::endl;
	std::cout << "2 - Do nothing " << std::endl;

	int action;
	std::cin >> action;
	switch (action)
	{
	case 1:
		AddItem(std::move(m_spawnedItem));
		break;
	case 2:
		break;
	}
}

void Player::Move()
{
	CleanConsole();
	if(m_playerStats.hungry < 15)
	{
		std::cout << "I am so hungry , I can not walk more." << std::endl;
	}
	else if(m_playerStats.health < 15)
	{
		std::cout << "I am sick , I can not walk more." << std::endl;
	}
	else
	{
		size_t kilometer = 2;
		std::cout << "You walked for about " << kilometer << " kilometers" << std::endl;
		m_playerStats.hungry -= 5;
	}
}

void Player::Rest()
{
	CleanConsole();
	
	if(CanRest())
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

bool Player::CanRest()
{
	if(m_restCounter <= 6)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Player::CleanConsole()
{
	system("cls");
}

void Player::SpawnItem()
{
	m_spawnedItem = std::make_unique<Item>("apple",EItemType::food);
	std::cout << " You found an " << m_spawnedItem->GetItemName() << std::endl;
	ItemAction();
}

void Player::AddItem(std::unique_ptr<Item> newItem)
{
	CleanConsole();
	if(newItem != nullptr)
	{
		std::cout << newItem->GetItemName() << " added to inventory." << std::endl;
		m_inventory.push_back(std::move(newItem));
		m_spawnedItem = nullptr;
	}
}
