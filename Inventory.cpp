#include "Inventory.h"

void Inventory::AddItem(const Item& item) {
	items.push_back(item);
}

void Inventory::RemoveItem(const string& itemName) {
	//trying to remove item by name
	for (auto it = items.begin(); it != items.end(); ++it) {
		if (it->getName() == itemName) {
			items.erase(it);
			break;
		}
	}
}

void Inventory::ListItems() const {
	cout << "Inventory:\n";
	for (const auto& item : items) {
		cout << item.getName() << " (x" << item.getQuantity() << ")\n";
	}
}

void Inventory::EquipGear(Gear& gear) {
	gear.equip(); // gear.equip() should handle the player's damage reduction
	equippedGear.push_back(gear);
}

void Inventory::UnequipGear(Gear& gear) {
	gear.unequip();
	// add code to remove gear from equippedGear vector
}