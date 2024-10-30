#include "Item.h"

Item::Item(const string& name, const Effect& effect, int quantity, int value, bool consumable, ItemType type)
	: mName(name), mEffect(effect), mQuantity(quantity), mValue(value), mConsumable(consumable), mType(type) {}

void Item::use() {
	if (mQuantity > 0) {
		cout << "Using " << mName << "!\n";

		if (mEffect.healing > 0) {
			cout << "You heal for " << mEffect.healing << " health.\n";
		}

		if (mEffect.damage > 0) {
			cout << "You deal " << mEffect.damage << " damage.\n";
		}

		if (mConsumable) {
			mQuantity--;
			cout << "Remaining amount: " << mQuantity << "\n";
		}
	}
	else {
		cout << mName << "Can't be used or you have none left!\n";
	}
}

bool Item::isUsable() const {
	return (mEffect.healing > 0 || mEffect.damage > 0); //item should be classified as usable if it has a healing or damage component
}

string Item::getName() const {
	return mName;
}

int Item::getQuantity() const {
	return mQuantity;
}

int Item::getValue() const {
	return mValue;
}

Effect Item::getEffect() const {
	return mEffect;
}

ItemType Item::getType() const {
	return mType;
}

void Item::decreaseQuantity(int howMany) {
	if (howMany > 0 && mQuantity >= howMany) {
		mQuantity -= howMany;
	}
	else {
		cout << "Invalid amount or not enough quantity!\n";
	}
}

void Item::increaseQuantity(int amount) {
		mQuantity += amount;
	}
