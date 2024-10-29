#include "Character.h"
#include "Equipment.h"
#include "Globals.h"

extern Character player;

Gear::Gear(const string& name, const Effect& effect, int quantity, int value, bool consumable, ItemType type, bool equipped)
	: Item(name, effect, quantity, value, consumable, type), equipped(equipped) { }

void Gear::equip() {
	if (!equipped && getQuantity() > 0) {
		equipped = true;
		//Armor damage reduction would go here
		player.addDamageReduction(getEffect().damageReduction);
		cout << "Equipped " << getName() << "!\n";
	}
	else if (equipped) {
		cout << getName() << " is already equipped!\n";
		}
	else {
		cout << "Cannot equip " << getName() << ". You have none left!\n";
	}
}

void Gear::unequip() {
	if (equipped) {
		equipped = false;
		player.removeDamageReduction(getEffect().damageReduction);
		cout << "Unequipped " << getName() << "!\n";
	}
	else {
		cout << getName() << " is not equipped!\n";
	}
}

bool Gear::isEquipped() const {
	return equipped;
}