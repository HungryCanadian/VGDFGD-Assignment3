
#include "Equipment.h"
#include "Globals.h"


extern Character player;

Gear::Gear()
    : Item("Default Gear", Effect(), 1, 0, false, ItemType::Gear), // Initialize base Item
    totalDamageReduction(0), // Default total damage reduction
    equipped(false) // Default not equipped
{
}

Gear::Gear(const string& name, const Effect& effect, int quantity, int value, bool consumable, ItemType type, bool equipped)
    : Item(name, effect, quantity, value, consumable, type), equipped(equipped) { }

int Gear::addDamageReduction(int amount) {
    totalDamageReduction += amount; // Update total damage reduction
    return totalDamageReduction; // Return the new total
}

int Gear::removeDamageReduction(int amount) {
	totalDamageReduction -= amount; // Update total damage reduction
	if (totalDamageReduction < 0) {
		totalDamageReduction = 0; // make sure you can't take extra damage anymore
	}
	return totalDamageReduction; // Return the new total
}

int Gear::getTotalDamageReduction() const {
    int totalReduction = 0;

    // Assuming this method is called on a Gear object that may be part of equipped items
    if (isEquipped()) {
        totalReduction += getEffect().damageReduction; // Add this gear's damage reduction
    }

    return totalReduction; // Return the total damage reduction from this gear
}

void Gear::equip() {
    if (!equipped && getQuantity() > 0) {
        equipped = true;
        int reductionAmount = getEffect().damageReduction;
        
        // Add this gear's damage reduction to the player's total
        player.addDamageReduction(reductionAmount);

        cout << "Equipped " << getName() << "!\n";
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