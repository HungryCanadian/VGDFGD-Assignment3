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

Gear* Inventory::GetGearByIndex(int index) {
	if (index >= 0 && index < gearItems.size()) {
		return &gearItems[index]; // Return pointer to Gear
	}
	return nullptr; // Return nullptr if index is out of bounds
}

int Inventory::getGearCount() const {
	return items.size(); // Return the number of items
}

void Inventory::openInventory() {
	while (true) {
		cout << "\nYour Inventory:\n";
		ListItems(); // List all items
		cout << "[Enter the number of the gear to equip, or '0' to exit]\n";

		// List available gear for equipping
		int index = 1;
		for (const auto& gear : gearItems) {
			cout << "[" << index++ << "] " << gear.getName() << " (x" << gear.getQuantity() << ")\n";
		}

		int choice;
		cin >> choice;

		if (choice == 0) {
			break; // Exit the inventory
		}

		if (choice > 0 && choice <= gearItems.size()) {
			Gear& selectedGear = gearItems[choice - 1];
			selectedGear.equip(); // Equip the selected gear
		}
		else {
			cout << "Invalid choice! Please try again.\n";
		}
	}
}