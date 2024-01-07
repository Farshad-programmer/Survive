#pragma once
#include <iostream>
#include "Database.h"

class Item
{
private:
	std::string m_name;
	EItemType m_itemType;

public:

	Item(const std::string& itemName, EItemType itemType);
	~Item() = default;

	void BeginPlay();


	//Getter and Setter
	std::string GetItemName()const { return m_name; }
	

};

