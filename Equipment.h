#pragma once
#include <string>
#include "Item.h"
#include "Character.h"




using std::string;

class Gear : public Item {
public:
	Gear(); // Default constructor
	Gear(const string& name, const Effect& effect, int quantity, int value, bool consumable, ItemType type, bool equipped);
	int totalDamageReduction = 0;
	void equip(); //function to donn the gear
	void unequip(); //function to doff the gear
	int addDamageReduction(int amount);
	int removeDamageReduction(int amount);
	int getTotalDamageReduction() const;
	int getTotalDamage() const;
	bool isEquipped() const;


private:
	//int totalDamageReduction;
	bool equipped;
};
