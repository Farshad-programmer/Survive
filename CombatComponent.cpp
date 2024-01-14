#include "CombatComponent.h"
#include "MyLibrary.h"

CombatComponent::CombatComponent()
{

}


void CombatComponent::CombatDecision(std::shared_ptr<Enemy>& enemy)
{
	if (enemy == nullptr || m_player == nullptr) return;

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
			m_player->SetCanBackCombatDecision(false);
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

void CombatComponent::Attack(std::shared_ptr<Enemy>& enemy, bool cleanConsole)
{
	if (enemy == nullptr) return;

	if(cleanConsole)
		CleanConsole();

	std::cout << "How do you plan to attack him: using physical strength or employing magical attacks?\n";
	std::cout << "[S]trength" << std::endl;
	std::cout << "[M]agic" << std::endl;


	std::string decision;
	std::cin >> decision;
	if (!IsInputDigit(decision))
	{
		if(decision == "s" || decision == "S")
		{
			CleanConsole();
			StrengthAttack(enemy);
		}
		else if(decision == "m" || decision == "M")
		{
			CleanConsole();
			std::cout << "You attacked with magic to " + enemy->GetName() << std::endl;
		}
		else
		{
			CleanConsole();
			std::cout << "Please Type correctly , example : 's' " << std::endl;
			Attack(enemy);
		}
	}
	else
	{
		CleanConsole();
		std::cout << "Please Type correctly , example : 's' " << std::endl;
		Attack(enemy);
	}
}

void CombatComponent::StrengthAttack(std::shared_ptr<Enemy>& enemy)
{
	if(enemy == nullptr || m_player == nullptr) return;

	if(m_player->GetPlayerStats().health > enemy->GetHealth())
	{
		const unsigned damage = m_player->GetPlayerStats().level * 30;
		ApplyDamageToEnemy(damage,enemy);
	}
}

void CombatComponent::ApplyDamageToEnemy(unsigned damage, std::shared_ptr<Enemy>& enemy)
{
	if (enemy == nullptr || m_player == nullptr) return;
	enemy->ReceiveDamage(static_cast<int>(damage)); // later I need to decide do I want to use int or unsigned
	std::cout << "You attacked with strength to " << RED_TEXT << enemy->GetName() << RESET_COLOR  << std::endl;
	std::cout << "You dealt " << damage << " damage to " << RED_TEXT << enemy->GetName() << RESET_COLOR  << std::endl;

	bool bIsDead = enemy->IsDeath();
	if(!bIsDead)
	{
		ChangeTurn(enemy);
	}
	else
	{
		if(!enemy->GetIsHasStory())
		{
			PlaySound(TEXT("sounds/Battle_Roar_death_1.wav"), NULL, SND_FILENAME | SND_ASYNC);
			std::cout << "You Killed him! " << std::endl;
			ObtainItem();
			m_player->SetCanBackCombatDecision(true);
			m_player->SetIsInAttack(false);
			const int randNumber = MakeRandomNumberInRange(1, 1);
			if(randNumber == 1)
			{
				// todo : spawn an item and add it to the player inventory
			}
			if (enemy.use_count() == 1)
			{
				enemy.reset();
			}
		}
		else
		{
			Story(enemy->GetAIAfterDeathStory());
			m_player->SetCanBackCombatDecision(true);
			m_player->SetIsInAttack(false);
			PlaySound(TEXT("sounds/Battle_Roar_death_1.wav"), NULL, SND_FILENAME | SND_ASYNC);
			std::cout << "You Killed him! " << std::endl;
			ObtainItem();
			if (enemy.use_count() == 1)
			{
				enemy.reset();
			}
		}
	}
}

void CombatComponent::ChangeTurn(const std::shared_ptr<Enemy>& enemy)
{
	std::cout << "The combat continue , now its turn " << RED_TEXT << enemy->GetName() << RESET_COLOR << " to attack you !" << std::endl;
	m_player->ShowPlayerAndEnemyStats(enemy, false);
	std::cout << "[T]urn ----> to observe the enemy's turn.  " << std::endl;

	std::string decision;
	std::cin >> decision;
	if (decision == "t" || decision == "T")
	{
		CleanConsole();
		enemy->EnemyAttackPlayer(*m_player);
	}
	else
	{
		CleanConsole();
		ChangeTurn(enemy);
	}

}

void CombatComponent::ObtainItem()
{
	switch (const int randNum = MakeRandomNumberInRange(1, 5))
	{
	case 1:
		m_spawnedLootItem = std::make_unique<Item>("apple", EItemType::food);
		break;
	case 2:
		m_spawnedLootItem = std::make_unique<Item>("banana", EItemType::food);
		break;
	case 3:
		m_spawnedLootItem = std::make_unique<Item>("corn", EItemType::food);
		break;
	case 4:
		m_spawnedLootItem = std::make_unique<Item>("soup", EItemType::food, 1, false);
		break;
	case 5:
		m_spawnedLootItem = std::make_unique<Item>("meat", EItemType::food);
		break;
	default:
		m_spawnedLootItem = std::make_unique<Item>("apple", EItemType::food);
		break;
	}


	std::cout << "You obtained an " << m_spawnedLootItem->GetItemName() << std::endl;
	m_player->AddItem(std::move(m_spawnedLootItem),false);
}


