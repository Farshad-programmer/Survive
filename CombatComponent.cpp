#include "CombatComponent.h"
#include "MyLibrary.h"

CombatComponent::CombatComponent()
{

}


void CombatComponent::CombatDecision(std::shared_ptr<Enemy> enemy) 
{
	std::cout << "What do you do: \n";
	std::cout << "1 - Attack " << std::endl;
	std::cout << "2 - Run! " << std::endl;
	std::cout << "3 - Hide " << std::endl;
	std::cout << "4 - Nothing " << std::endl;
	std::string decision;
	std::cin >> decision;
	if (IsInputDigit(decision))
	{
		switch (int number = int(std::stod(decision)))
		{
		case 1:
			Attack(enemy);
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			CleanConsole();
			if(m_player)
			{
				m_player->SetIsInAttack(false);
			}
			break;
		default:
			CleanConsole();
			std::cout << "Please Type 1, 2, 3 or 4 for your Decision ! " << std::endl;
			break;
		}
	}
	else
	{
		CleanConsole();
		std::cout << "Please Type 1, 2, 3 or 4 for your Decision ! " << std::endl;
	}
}

void CombatComponent::Attack(std::shared_ptr<Enemy> enemy)
{
	CleanConsole();
	std::cout << "How do you plan to attack him: using physical strength or employing magical attacks?\n";
	std::cout << " strength / magic " << std::endl;

	std::string decision;
	std::cin >> decision;
	if (!IsInputDigit(decision))
	{
		if(decision == "strength")
		{
			CleanConsole();
			std::cout << "You attacked with strength to " + enemy->GetName() << std::endl;
		}
		else if(decision == "magic")
		{
			CleanConsole();
			std::cout << "You attacked with magic to " + enemy->GetName() << std::endl;
		}
		else
		{
			CleanConsole();
			std::cout << "Please Type correctly ! " << std::endl;
			Attack(enemy);
		}
	}
	else
	{
		CleanConsole();
		std::cout << "Please Type correctly ! " << std::endl;
		Attack(enemy);
	}
}
