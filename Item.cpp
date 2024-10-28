#include "Item.h"

Item::Item(const string& name, const Effect& effect, int quantity, bool consumable)
	:name(name), effect(effect), quantity(quantity), consumable(consumable) { }

void Item::use() {
	if (quantity > 0) {
		cout << "Using " << name << "!\n";

		if (effect.healing > 0) {
			cout << "You heal for " << effect.healing << " health.\n";
		}

		if (effect.damage > 0) {
			cout << "You deal " << effect.damage << " damage.\n";
		}

		if (consumable) {
			quantity--;
			cout << "Remaining amount: " << quantity << "\n";
		}
	}
	else {
		cout << name << "Can't be used or you have none left!\n";
	}
}

bool Item::isUsable() const {
	return (effect.healing > 0 || effect.damage > 0); //item should be classified as usable if it has a healing or damage component
}

string Item::getName() const {
	return name;
}

int Item::getQuantity() const {
	return quantity;
}
