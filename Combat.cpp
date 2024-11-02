#include "Combat.h"
#include "Character.h"



Combat::Combat(Character& player, Enemy& enemy, vector<Item>& inventory)
	: player(player), enemy(enemy), inventory2(inventory) { }

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
		case 1:
		{
			cout << "\nChoose an attack:\n";
			cout << "[1] Regular Attack\n";
			cout << "[2] Heavy Attack\n";
			cout << "[3] Special Move\n";
			cout << "[4] Class Ability\n";

			int choice2;
			cin >> choice2;

			switch (choice2) {
			case 1:
			{
				cout << player.getName() << " uses a regular attack!\n";
				int damageToEnemy = player.getAttack();
				cout << player.getName() << " attacks " << enemy.getName() << " for " << damageToEnemy << " damage!\n";
				enemy.takeDamage(damageToEnemy);
				if (!enemy.isAlive()) {
					cout << enemy.getName() << " has been defeated!\n";
					inCombat = false; // should exit combat loop
				}
				break; // Missing break statement added
			}
			case 2:
			{
				cout << player.getName() << " uses a heavy attack!\n";
				int damageToEnemy = player.getAttack() + 3; // add 3 to the damage
				cout << player.getName() << " attacks " << enemy.getName() << " for " << damageToEnemy << " damage!\n";
				enemy.takeDamage(damageToEnemy);
				if (!enemy.isAlive()) {
					cout << enemy.getName() << " has been defeated!\n";
					inCombat = false; // should exit combat loop
				}
				break; // Missing break statement added
			}
			case 3:
				SpecialMove();
				break;
			case 4:
				cout << player.getName() << " uses a class ability!\n";
				break;
			default:
				cout << "Invalid choice!\n";
				continue;
			}
			break; // Added break to outer switch case
		}
		case 2: // defend
			cout << player.getName() << " defends this turn!\n";
			continue;
		case 3: // use items
			useItem();
			break;
		case 4: // run away
			cout << "You try to run away!\n";
			if (rand() % 100 == 0) {
				cout << "You successfully got away!\n";
				inCombat = false; // ends combat
			}
			else {
				cout << "You tried, but " << enemy.getName() << " was faster!\n";
			}
			break;
		default:
			cout << "This is not a valid choice! Please try again!\n";
			continue;
		}

		// If combat continues, it's the enemy's turn
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
	int index = 1;
	for (auto& item : inventory2) {
		if (item.isUsable() && item.getQuantity() > 0) {
			consumableItems.push_back(&item); // add consumable item to a list
			cout << "["<< index << "]" << item.getName() << " (x " << item.getQuantity() << ")\n";
			index++;
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


void Combat::SpecialMove() {
	if (player.getClass().getName() == "Fighter") {
		cout << player.getName() << " uses a special move!\n";
		cout << "Fighter's special move: Whirlwind!\n";
		cout << player.getName() << " spins around, hitting all enemies for 10 damage!\n";
		enemy.takeDamage(10);
	}
	else if (player.getClass().getName() == "Paladin") {
		cout << player.getName() << " uses a special move!\n";
		cout << "Paladin's special move: Smite!\n";
		cout << player.getName() << " Smites " << enemy.getName() <<" for 10 damage!\n";
		enemy.takeDamage(10);
	}
	else if (player.getClass().getName() == "Druid") {
		cout << player.getName() << " uses a special move!\n";
		cout << "Druid's's special move: Thorny Grasp!\n";
		cout << player.getName() << " casts Thorny Grasp at " << enemy.getName() << " and binds them for 10 damage!\n";
		enemy.takeDamage(15);
	}
	else if (player.getClass().getName() == "Warlock") {
		cout << player.getName() << " uses a special move!\n";
		cout << "Warlock's special move: Life Siphon!\n";
		cout << player.getName() << " siphons 10 health from " << enemy.getName() << "!\n";
		enemy.takeDamage(10);
		player.heal(10);
	}
	else if (player.getClass().getName() == "Sorceror") {
		cout << player.getName() << " uses a special move!\n";
		cout << "Sorceror's special move: Arcane Blast!\n";
		cout << player.getName() << " unleashes a powerful blast of arcane energy at " << enemy.getName() << " for 15 damage!\n";
		enemy.takeDamage(15);
	}
	else if (player.getClass().getName() == "Wizard") {
		cout << player.getName() << " uses a special move!\n";
		cout << "Wizard's special move: Fireball!\n";
		cout << player.getName() << " casts a fireball at the " << enemy.getName() << " for 10 damage!\n";
		enemy.takeDamage(10);
	}
	else if (player.getClass().getName() == "Ranger") {
		cout << player.getName() << " uses a special move!\n";
		cout << "Ranger's special move: Piercing Shot!\n";
		cout << player.getName() << " unleashes a precise shot that pierces through " << enemy.getName() << "’s defenses.\n";
		enemy.takeDamage(15);
	}
	else {
		cout << "Invalid class!\n";
	}
	//not yet implemented
}

void Combat::ClassAbility() {
	//not yet implemented
	if (player.getClass().getName() == "Fighter") {
		cout << player.getName() << " uses an ultimate move!\n";
		cout << "Fighter's Ultimate move: Overpower!\n";
		cout << player.getName() << " cleaves through " << enemy.getName() << " for 10 damage!\n";
		enemy.takeDamage(30);
	}
	else if (player.getClass().getName() == "Paladin") {
		cout << player.getName() << " uses a ultimate move!\n";
		cout << "Paladin's ultimate move: Lay on hands!\n";
		cout << player.getName() << " casts lay on hands! they are fully healed by their diety!\n";
		player.heal(300);
	}
	else if (player.getClass().getName() == "Druid") {
		cout << player.getName() << " uses a Ultimate move!\n";
		cout << "Druid's's Ultimate move: Nature's Wrath!\n";
		cout << player.getName() << " calls upon the spirits of the forest, dealing 30 damage to " << enemy.getName() << "!\n";
		enemy.takeDamage(15);
	}
	else if (player.getClass().getName() == "Warlock") {
		cout << player.getName() << " uses their ultimate move!\n";
		cout << "Warlock's ultimate move: Dark Pact!\n";
		cout << player.getName() << " sacrifices some health to deal 40 damage to " << enemy.getName() << "!\n";
		enemy.takeDamage(40);
		player.takeDamage(10);
	}
	else if (player.getClass().getName() == "Sorceror") {
		cout << player.getName() << " uses their ultimate move!\n";
		cout << "Sorceror's ultimate move: Elemental Onslaught!\n";
		cout << player.getName() << " unleashes a storm of elemental energy, dealing 45 damage to " << enemy.getName() << "!\n";
		enemy.takeDamage(45);
	}
	else if (player.getClass().getName() == "Wizard") {
		cout << player.getName() << " uses their ultimate move!\n";
		cout << "Wizard's ultimate move: Meteor Shower!\n";
		cout << player.getName() << " rains fire from the sky, striking " << enemy.getName() << " for 50 damage!\n";
		enemy.takeDamage(50);
	}
	else if (player.getClass().getName() == "Ranger") {
		cout << player.getName() << " uses their ultimate move!\n";
		cout << "Ranger's ultimate move: Rapid Fire!\n";
		cout << player.getName() << " unleashes a flurry of arrows, dealing 30 damage to " << enemy.getName() << "!\n";
		enemy.takeDamage(30);
	}
	else {
		cout << "Invalid class!\n";
	}
	//not yet implemented
}
