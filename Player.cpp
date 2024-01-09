#include "Player.h"
#include <chrono> // for miliseconds
#include <conio.h> // for _getch() and _kbhit()
#include <string>
#include <cstdlib> // for clean console cmd
#include <random> 



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
	std::cout << "------------------------" << std::endl;
	std::cout << m_playerName << std::endl;
	std::cout << "------------------------" << std::endl;
	std::cout << "Level: " << m_playerStats.level<< std::endl;
	std::cout << "Health: " << m_playerStats.health << " / "<< m_playerStats.max_health << std::endl;
	std::cout << "Hungry: " << m_playerStats.hungry << " / " << m_playerStats.max_hungry << std::endl;
	std::cout << "------------------------" << std::endl;
}


void Player::Story()
{
	std::cout << "\nPress Enter to skip...\n";

	long long type_writer_speed = 100LL;

	for (const auto element : m_story)
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

bool Player::IsInputDigit(const std::string str)
{
	for (char c : str)
	{
		if (!isdigit(c))
		{
			return false;
		}
	}
	return true;
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
	std::cout << "5 - Quit " << std::endl;
	std::string decision;
	std::cin >> decision;

	if(IsInputDigit(decision))
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
			QuitGame();
			break;
		default:
			CleanConsole();
			std::cout << "Please Type 1, 2, 3 or 5 for your Decision ! " << std::endl;
			break;
		}
	}
	else
	{
		CleanConsole();
		std::cout << "Please Type 1, 2, 3 or 5 for your Decision ! " << std::endl;
	}

}

void Player::ItemAction()
{
	std::cout << "What do you do: " << std::endl;
	std::cout << "1 - Add item to Inventory " << std::endl;
	std::cout << "2 - Do nothing " << std::endl;

	std::string action;
	std::cin >> action;

	if(IsInputDigit(action))
	{
		switch (int number = static_cast<int>(std::stod(action)))
		{
		case 1:
			AddItem(std::move(m_spawnedItem));
			break;
		case 2:
			CleanConsole();
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
	if(m_restCounter <= 6)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Player::CleanConsole(std::string message)
{
	system("cls");
	if(message != "none")
	{
		std::cout << message << std::endl;
	}
}

void Player::SpawnItem()
{
	m_spawnedItem = std::make_unique<Item>("apple",EItemType::food);
	std::cout << " You found an " << m_spawnedItem->GetItemName() << std::endl;
	ItemAction();
}

void Player::AddItem(std::unique_ptr<Item> newItem)
{
	if (newItem == nullptr) return;

	CleanConsole();
	bool itemFound = false;
	if(newItem->IsItemStackable())
	{
		for (size_t i = 0 ; i < m_inventoryItems.size() ; i++)
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
		if(!itemFound)
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

void Player::RemoveItem(const std::string itemName)
{
	if(!m_inventoryItems.empty())
	{
	for (int i = 0; i < m_inventoryItems.size(); ++i)
	{
		if(m_inventoryItems[i]->GetItemName() == itemName)
		{
			m_inventoryItems.erase(m_inventoryItems.begin() + i);
			break;
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
	std::cout <<" You have opened your inventory ..." << std::endl;
	for(const auto& item : m_inventoryItems)
	{
		std::cout << index + 1 << "-" << item->GetItemName() << "(" << item->GetItemQuantity()<<")"<< std::endl;
		index++;
	}
	m_inventorySize = index;
	if(m_inventorySize < 1)
	{
		std::cout << " Your inventory is empty" << std::endl;
	}
	else
	{
		std::cout << " You can select your items ..." << std::endl;
		InventoryAction();
	}
}

void Player::InventoryAction()
{
	std::string action;
	std::cin >> action;
	int number = static_cast<int>(std::stod(action));

	if(number != 0)
	{
		if (number <= m_inventorySize)
		{
			number--;
			const std::unique_ptr<Item>& selectedItem = m_inventoryItems[number];
			if(selectedItem)
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
		std::cout << " Invalid Input!" << std::endl;
		CheckInventory();
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
	if(propertyName == "health")
	{
		if(add)
		{
			m_playerStats.health += value;
			if(m_playerStats.health >= m_playerStats.max_health)
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
	else if(propertyName == "hungry")
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
