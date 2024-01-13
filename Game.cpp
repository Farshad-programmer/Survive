#include "Game.h"
#include "Color.h"
#include "MyLibrary.h"

Game::Game()
	:m_player(std::make_unique<Player>())
{
	
}

void Game::BeginPlay()
{
	if(m_player == nullptr) return;
	GameTitle();
	m_player->MainMenu();
	if(!m_player->GetIsQuit())
	{
		if(!m_player->IsFromLoadGame())
		{
			Story(m_player->m_story);
		}
		m_bUpdate = true;
	}
	
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




