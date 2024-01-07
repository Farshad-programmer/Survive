#include "Game.h"

Game::Game()
	:m_player(std::make_unique<Player>())
{
	
}

void Game::BeginPlay()
{
	m_player->InitializePlayerInformation();
	m_player->Story();
	m_player->ShowPlayerStats();
	
}

void Game::Tick()
{

}
