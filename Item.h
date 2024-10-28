#pragma once

#include <string>
#include <iostream>
#include "VGDFGDAssignment3.cpp"
#include "Effect.h"

class Item {
public:
	Item(const string& name, const Effect& effect, int quantity, bool consumable);

	void use(); //Use function to use the item or potion
	bool isUsable() const; //function to check if the item is declared as usable, potions/swords etc etc

	string getName() const; //get the name of the item(s)
	int getQuantity() const; //How many items are there? make sure they have at least 1

private:
	string name;
	Effect effect;
	int quantity;
	bool consumable;

};

