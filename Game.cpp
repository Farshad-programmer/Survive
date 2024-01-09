#include "Game.h"
#include "Color.h"

Game::Game()
	:m_player(std::make_unique<Player>())
{
	
}

void Game::BeginPlay()
{
	SetConsoleFont(30);
	m_player->InitializePlayerInformation();
	m_player->Story(m_player->m_story);
	m_player->CleanConsole();
	m_bUpdate = true;
}

void Game::Tick()
{
	if(m_player)
	{
		while (m_bUpdate && !m_player->GetIsQuit())
		{
			m_player->ShowPlayerStats();
			m_player->Tick();
		}
	}
	
}
