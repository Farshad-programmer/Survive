#include "Item.h"
#include "Player.h"
#include <random> 

Item::Item(const std::string& itemName, EItemType itemType, int itemQuantity, bool IsStackable)
	:m_name(itemName),m_itemType(itemType),m_itemQuantity(itemQuantity),m_bIsStackable(IsStackable)
{
	m_hungerIncrease = MakeRandomNumberInRange(5, 25);
}

void Item::BeginPlay()
{

}

bool Item::IsInputDigit(const std::string str)
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

void Item::ItemAction(Player* player)
{
	if(player == nullptr) return;

	player->CleanConsole();

	std::cout << "Item to action : " << m_name << std::endl;
	if(m_itemType == food)
	{
		std::cout << "What do you do: " << std::endl;
		std::cout << "1 - Eat it " << std::endl;
		std::cout << "2 - Throw it away " << std::endl;
		std::cout << "3 - Do nothing " << std::endl;
		if(player->m_bIsNPCInteract)
		{
			std::cout << "4 - Give it to " << player->GetNPCName() << std::endl;
		}

		std::string action;
		std::cin >> action;

		if (IsInputDigit(action))
		{
			switch (const int number = static_cast<int>(std::stod(action)))
			{
			case 1:
				player->CleanConsole("You used an item!");
				Eat(player);
				break;
			case 2:
				player->CleanConsole("You removed an item from your inventory!");
				player->RemoveItem(*this);
				break;
			case 3:
				player->CleanConsole();
				break;

			case 4:
				if (player->m_bIsNPCInteract)
				{
					player->CleanConsole();
					player->RemoveItem(*this);
					player->Story(player->m_story3);
					player->m_bIsNPCInteract = false;
				}
				else
				{
					player->CleanConsole();
					std::cout << "Please Type 1 , 2 or 3 for your action ! " << std::endl;
				}
				break;
			default:
				std::cout << "Please Type 1 , 2 or 3 for your action ! " << std::endl;
				ItemAction(player);
			}
		}
		else
		{
			player->CleanConsole();
			std::cout << "Please Type 1 , 2 or 3 for your action ! " << std::endl;
			ItemAction(player);
		}
	}

}

void Item::IncreaseQuantity()
{
	m_itemQuantity++;
}

void Item::DecreaseQuantity()
{
	m_itemQuantity--;
}

void Item::Eat(Player* player)
{
	if(player == nullptr) return;

	player->UpdatePlayerStats("hungry", m_hungerIncrease);
	player->RemoveItem(*this);
}

int Item::MakeRandomNumberInRange(int min, int max)
{
	std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<> distribution(min, max);// make a distribution

	return distribution(gen);
}
