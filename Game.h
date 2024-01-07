#pragma once
#include <memory>
#include <iostream>
#include "Player.h"



class Game
{
private:

	

	std::unique_ptr<Player> m_player;

public:
	Game();
	~Game() = default;


	void BeginPlay();
	void Tick();




};

