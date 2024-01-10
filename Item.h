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
	int m_hungerIncrease;
	void Eat(Player* player);
	int MakeRandomNumberInRange(int min, int max);

public:

	Item(const std::string& itemName, EItemType itemType, int itemQuantity = 1, bool IsStackable = true);
	~Item() = default;

	void BeginPlay();
	void ItemAction(Player* player);
	void IncreaseQuantity();
	void DecreaseQuantity();
	//Getter and Setter
	std::string GetItemName()const { return m_name; }
	int GetItemQuantity()const { return m_itemQuantity; }
	bool IsItemStackable()const { return m_bIsStackable; }
	

};

