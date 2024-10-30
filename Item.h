#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "Effect.h"



using std::string;
using std::cout;


enum class ItemType {
	Gear,
	Consumable,
	Weapon,
	Item,
	// Add other types as needed
};

class Item {
public:
	Item(const string& name, const Effect& effect, int quantity, int value, bool consumable, ItemType type);

	void use(); //Use function to use the item or potion
	bool isUsable() const; //function to check if the item is declared as usable, potions/swords etc etc
	ItemType getType() const; //get the type of the item(s)
	string getName() const; //get the name of the item(s)
	int getQuantity() const; //How many items are there? make sure they have at least 1
	int getValue() const; //How much is this item worth for a shopkeep
	Effect getEffect() const;

	void decreaseQuantity(int value);
	void increaseQuantity(int amount);

private:
	ItemType mType;
	string mName;
	Effect mEffect;
	int mQuantity;
	int mValue;
	bool mConsumable;

};

