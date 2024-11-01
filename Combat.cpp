#include "Combat.h"
#include "Character.h"


Combat::Combat(Character& player, Enemy& enemy, vector<Item>& inventory)
	:player(player), enemy(enemy), inventory2(inventory) { }

void Combat::start() {
	bool inCombat = true;
	cout << enemy.getName() << " charges at you!\n";

	while (inCombat && player.isAlive() && enemy.isAlive()) {
		cout << "\nChoose an action:\n";
		cout << "[1] Attack\n";
		cout << "[2] Defend\n";
		cout << "[3] Use Item\n";
		cout << "[4] Run\n";

		int choice;
		cin >> choice;

		switch (choice) {
		case 1: //Attack
		{
			int damageToEnemy = player.getAttack();
			cout << player.getName() << " attacks " << enemy.getName() << " for " << damageToEnemy << " damage!\n";
			enemy.takeDamage(damageToEnemy);
			if (!enemy.isAlive()) {
				cout << enemy.getName() << " has been defeated!\n";
				inCombat = false; //should exit combat loop
			}
			break;
		}
		case 2: //defend
		{
			cout << player.getName() << " defends this turn!\n";
			//add defense code (reduce all incoming damage to 1 for this turn only)
			continue;
		}
		case 3: //use items!
		{
			useItem();
			break;
		}
		case 4: //run away!
		{
			cout << "You try to run away!\n";
			if (rand() % 100 == 0) {
				cout << "You succesfully got away!\n";
				inCombat = false; // ends combat
			}
			else {
				cout << "You tried, but " << enemy.getName() << " was faster!\n";
			}
			break;
		}
		default:
			cout << "this is not a valid choice! Please try again!\n";
			continue;
		}
		//If combat continues, it's the enemy's turn
		if (inCombat && enemy.isAlive()) {
			enemyTurn();
		}
		
	}
}

void Combat::enemyTurn() {
    // Calculate damage to the player
    int damageReduction = player.getTotalDamageReduction();
    int damageToPlayer = enemy.getAttack() - damageReduction;

    // Ensure damage is not negative
    if (damageToPlayer < 0) {
        damageToPlayer = 0; // No damage if reduction exceeds attack
    }
	// Output the attack message
	cout << enemy.getName() << " attacks you for " << enemy.getAttack() << " damage!\n";
    // Apply damage to the player
    player.takeDamage(damageToPlayer);    

    if (!player.isAlive()) {
        cout << player.getName() << " has been defeated!\n";
		exit(0);
    }
}

void Combat::useItem() {
	//not yet implemented
	cout << "Choose an item to use:\n";

	vector<Item*> consumableItems;
	for (auto& item : inventory2) {
		if (item.isUsable() && item.getQuantity() > 0) {
			consumableItems.push_back(&item); // add consumable item to a list
			cout << " - " << item.getName() << " ( x " << item.getQuantity() << ")\n";
		}
	}
	if (consumableItems.empty()) {
		cout << "You have no consumable items!\n";
		return;
	}

	int choice;
	cout << "Enter the number of the item you want to use: ";
	cin >> choice;

	if (choice > 0 && choice <= consumableItems.size()) {
		Item* selectedItem = consumableItems[choice - 1];
		selectedItem->use(); // should use the selected item

		Effect itemEffect = selectedItem->getEffect();
		if (itemEffect.healing > 0) {
			player.heal(itemEffect.healing);
			cout << "you heal for " << itemEffect.healing << " health!\n";
		}
		if (itemEffect.damage > 0) {
			enemy.takeDamage(itemEffect.damage); //set the enemy on fire(or something)
			cout << enemy.getName() << " takes " << itemEffect.damage << " damage!\n";
		}

		selectedItem->decreaseQuantity(1);

		if (selectedItem->getQuantity() <= 0) {
			//remove item from inventory
			for (auto it = inventory2.begin(); it != inventory2.end(); ++it) {
				if (it->getName() == selectedItem->getName()) {
					inventory2.erase(it);
					cout << "You have no more: " << selectedItem->getName() << "\n";
					break;
				}
			}

		}

	}
	else {
		cout << "Invalid choice!\n";
	}
}
