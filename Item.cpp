#include "Item.h"
#include "Player.h"


Item::Item(const std::string& itemName, EItemType itemType, int itemQuantity, bool IsStackable)
	:m_name(itemName),m_itemType(itemType),m_itemQuantity(itemQuantity),m_bIsStackable(IsStackable)
{

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

	player->UpdatePlayerStats("hungry", 10);
	player->RemoveItem(*this);
}
