#pragma once
#include <memory>
#include "Player.h"



class Game
{
private:

	bool m_bUpdate{false};
	std::unique_ptr<Player> m_player;

public:
	Game();
	~Game() = default;


	void BeginPlay();
	void Tick();




};

