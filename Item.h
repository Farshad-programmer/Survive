#pragma once
#include <iostream>
#include "Database.h"
#include <string>
#include <fstream>


class Player;

class Item
{
private:

	// private variables
	std::string m_name;
	EItemType m_itemType;
	int m_itemQuantity;
	bool m_bIsStackable;
	int m_hungerIncrease;

	int MakeRandomNumberInRange(int min, int max);

public:

	Item(const std::string& itemName = "no name", EItemType itemType = EItemType::food, int itemQuantity = 1, bool IsStackable = true);
	~Item() = default;

	void BeginPlay();
	void ItemAction(Player* player);
	void IncreaseQuantity();
	void DecreaseQuantity();
	void Eat(Player* player, bool removeFromInventory = true);


	friend std::ostream& operator<<(std::ostream& os,const Item& item)
	{
		os << item.m_name << '\n';
		os << item.m_bIsStackable << '\n';
		os << static_cast<int>(item.m_itemType) << '\n';
		os << item.m_itemQuantity << '\n';
		os << item.m_hungerIncrease << '\n';
		return os;
	}

	friend std::istream& operator>>(std::istream& is, Item& item)
	{
		std::getline(is, item.m_name);
		is >> item.m_bIsStackable;
		is.ignore();
		int itemTypeValue;
		is >> itemTypeValue;
		item.m_itemType = static_cast<EItemType>(itemTypeValue);
		is.ignore();
		is >> item.m_itemQuantity;
		is.ignore(); 
		is >> item.m_hungerIncrease;
		is.ignore(); 

		return is;
	}



	//Getter and Setter
	std::string GetItemName()const { return m_name; }
	int GetItemQuantity()const { return m_itemQuantity; }
	bool IsItemStackable()const { return m_bIsStackable; }
	EItemType GetItemType()const { return m_itemType; }



	

};

