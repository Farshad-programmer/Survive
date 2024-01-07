#include "Player.h"
#include <iostream>
#include <chrono> // for miliseconds
#include <conio.h> // for _getch() and _kbhit()
#include <string>
#include <cstdlib> // for clean console cmd


Player::Player() :
	m_playerName("Player"), m_playerSex("Male")
{

}

void Player::BeginPlay()
{

}

void Player::Tick()
{

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
	std::cout << "Health: " << m_playerStats.health << std::endl;
	std::cout << "Level: " << m_playerStats.level<< std::endl;
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
