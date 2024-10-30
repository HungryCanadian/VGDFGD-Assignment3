#pragma once
#include <string>
#include "Item.h"

using std::string;

class Gear : public Item {
public:
	Gear(const string& name, const Effect& effect, int quantity, int value, bool consumable, ItemType type, bool equipped = false);

	void equip(); //function to donn the gear
	void unequip(); //function to doff the gear
	bool isEquipped() const; //checking if the gear is equipped or not

private:
	bool equipped;
};

