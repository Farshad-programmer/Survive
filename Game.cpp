#include "Game.h"

Game::Game()
	:m_player(std::make_unique<Player>())
{
	
}

void Game::BeginPlay()
{
	m_player->InitializePlayerInformation();
	m_player->Story();
	m_bUpdate = true;
}

void Game::Tick()
{
	while (m_bUpdate)
	{
		m_player->ShowPlayerStats();
		m_player->Tick();
	}
}
