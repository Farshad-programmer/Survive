#pragma once
#include <iostream>
#include "Database.h"
#include <string>

class Player;

class Item
{
private:
	std::string m_name;
	EItemType m_itemType;
	int m_itemQuantity;
	bool m_bIsStackable;
	void Eat(Player* player);

public:

	Item(const std::string& itemName, EItemType itemType, int itemQuantity = 1, bool IsStackable = true);
	~Item() = default;

	void BeginPlay();
	bool IsInputDigit(const std::string str);
	void ItemAction(Player* player);

	//Getter and Setter
	std::string GetItemName()const { return m_name; }
	int GetItemQuantity()const { return m_itemQuantity; }
	

};

