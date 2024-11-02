#include "Inventory.h"


class Character;

static vector<Item> items = {
    { "healing potion", Effect(5,0,0), 5, 5, true, ItemType::Consumable },
    { "rations", Effect(2,0,0), 30, 1, true, ItemType::Consumable },
    { "mess kit", Effect(0,0,0), 1, 1, false, ItemType::Item },
    { "tinderbox", Effect(0,0,0), 1, 1, false, ItemType::Item },
    { "torch", Effect(0,0,0), 10, 1, false, ItemType::Item },
    { "waterskin", Effect(0,0,0), 1, 1, false, ItemType::Item },
    { "rope", Effect(0,0,0), 1, 2, false, ItemType::Item }

};

static vector<Item> inv = {
    { "backpack", Effect(0,0,0), 1, 1, false, ItemType::Item },
    { "gold pouch", Effect(0,0,0), 1, 1, false, ItemType::Item },
    { "mess kit", Effect(0,0,0), 1, 1, false, ItemType::Item },
    { "tinderbox", Effect(0,0,0), 1, 1, false, ItemType::Item },
    { "torch", Effect(0,0,0), 10, 1, false, ItemType::Item },
    { "rations", Effect(2,0,0), 5, 1, true, ItemType::Consumable },
    { "waterskin", Effect(0,0,0), 1, 1, false, ItemType::Item },
    { "rope", Effect(0,0,0), 1, 2, false, ItemType::Item }

};

static vector<Gear> equipment = {
    { "sword", Effect(0,3,0), 1, 15, false, ItemType::Weapon, false },
    { "shield", Effect(0,0,0,1), 1, 25, false, ItemType::Gear, false },
    { "crossbow", Effect(0,2,0), 1, 20, false, ItemType::Weapon, false },
	{ "armor", Effect(0,0,0,2), 1, 100, false, ItemType::Gear, false },
	/*{ "helmet", Effect(0,0,0,1), 1, 10, false, ItemType::Gear, false }, //more gear for later implementation *needs a check to make sure you dont become a tank*
	{ "boots", Effect(0,0,0,1), 1, 10, false, ItemType::Gear, false },
	{ "gloves", Effect(0,0,0,1), 1, 10, false, ItemType::Gear, false },
	{ "ring", Effect(0,0,0,1), 1, 10, false, ItemType::Gear, false },
	{ "amulet", Effect(0,0,0,1), 1, 10, false, ItemType::Gear, false },
	{ "belt", Effect(0,0,0,1), 1, 10, false, ItemType::Gear, false },
	{ "cloak", Effect(0,0,0,1), 1, 10, false, ItemType::Gear, false },
	{ "bracers", Effect(0,0,0,1), 1, 10, false, ItemType::Gear, false },
	{ "pants", Effect(0,0,0,1), 1, 10, false, ItemType::Gear, false },
	{ "shirt", Effect(0,0,0,1), 1, 10, false, ItemType::Gear, false },
	{ "robe", Effect(0,0,0,1), 1, 10, false, ItemType::Gear, false },
	{ "staff", Effect(0,2,0), 1, 10, false, ItemType::Weapon, false },
	{ "wand", Effect(0,1,0), 1, 10, false, ItemType::Weapon, false },
	{ "orb", Effect(0,1,0), 1, 10, false, ItemType::Weapon, false },
	{ "scroll", Effect(0,0,0), 1, 10, false, ItemType::Gear, false },
	{ "book", Effect(0,0,0), 1, 10, false, ItemType::Gear, false },*/


};

static vector<Gear> gearItems = {


};

static vector<Gear> equippedGear = {


};

void Inventory::AddItem(Gear& gear) {
	items.push_back(gear);
}

void Inventory::RemoveItem(Gear& gear) {
	//trying to remove item by name
	for (auto it = gearItems.begin(); it != gearItems.end(); ++it) {
		if (it->getName() == gear.getName()) {
			gearItems.erase(it);
			break;
		}
	}
}

void Inventory::decreaseQuantity(const string& itemName, int howMany) {
    for (auto& item : items) {
        if (item.getName() == itemName) {
            item.decreaseQuantity(howMany);
            break; // Exit once the item is found and quantity is decreased
        }
    }
}


void Inventory::increaseQuantity(const string& itemName, int howMany) {
    for (auto& item : items) {
        if (item.getName() == itemName) {
            item.increaseQuantity(howMany);
            break; // Exit once the item is found and quantity is increased
        }
    }
}

vector<Item>& Inventory::getItems() {
    return items;
}

vector<Item>& Inventory::getInv() {
    return inv;
}

vector<Gear> Inventory::getGearItems() {
    return gearItems;
}

vector<Gear> Inventory::getEquippedGear() {
	return equippedGear;
}

vector<Gear> Inventory::getEquipment() {
	return equipment;
}   

void Inventory::ListGearItems() const {
	cout << "Gear:\n";
    int index = 1;
	for (const auto& gear : gearItems) {
		
		cout << "[" << index++ << "] " << gear.getName() << "\n";
	}
}

void Inventory::ListEquippedItems(Character& player) {
    cout << "Equipped Gear Items:\n";
    const auto& equippedItems = player.getGearItems();

    int totalDamageReduction = 0;
    int totalDamage = 0;

    for (size_t i = 0; i < equippedItems.size(); ++i) {
        cout << "[" << (i + 1) << "] " << equippedItems[i].getName() << "\n";
        totalDamageReduction += equippedItems[i].getTotalDamageReduction();
        totalDamage += equippedItems[i].getTotalDamage(); // Sum up damage bonuses in the same loop
    }

    // Display total damage reduction and damage
    cout << "Total Damage Reduction from Equipped Items: " << totalDamageReduction << "\n";
    cout << "Total Damage from Equipped Items: " << totalDamage << "\n";
}

void Inventory::EquipGear(Gear& gear,Character& player) {
	gear.equip(player); // gear.equip() should handle the player's damage reduction
	equippedGear.push_back(gear);
}

void Inventory::UnequipGear(Gear& gear, Character& player) {
    gear.unequip(player); // Call the unequip method on the gear

    // Find the gear in the equippedGear list and remove it
    auto it = std::find(equippedGear.begin(), equippedGear.end(), gear);
    if (it != equippedGear.end()) {
        equippedGear.erase(it); // Remove the gear from equippedGear
        cout << gear.getName();
    }
    else {
        cout << "Error: Gear not found in equipped items.\n";
    }
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

void Inventory::openInventory(Character& player) {
    while (true) {
        cout << "\nChoose an inventory to open:\n";
        cout << "[1] Unequipped Gear\n";
        cout << "[2] Equipped Gear\n";
        cout << "[3] General Inventory\n";
        cout << "[4] Exit\n";

        int choice;
        cin >> choice;

        if (choice == 4) {
            break; // Exit the inventory menu
        }

        switch (choice) {
        case 1: { // Open Gear Inventory
            ListGearItems(); // List gear items
            cout << "\n---------------------------------\n";
            cout << "[Enter the number of the gear to equip, or '0' to exit]\n";

            int choice;
            cin >> choice;

            // Exit inventory
            if (choice == 0) {
                break;
            }

            // Validate choice and equip gear
            if (choice > 0 && choice <= gearItems.size()) {
                Gear& selectedGear = gearItems[choice - 1];

                // Equip the gear
                player.EquipGear(selectedGear, player);

                // Remove the gear from the gearItems inventory after equipping
                gearItems.erase(gearItems.begin() + (choice - 1));
            }
            else {
                cout << "Invalid choice! Please try again.\n";
            }
        }
              break;

        case 2: { // Open Equipped Gear Inventory
            ListEquippedItems(player); // List equipped gear items
            cout << "\n---------------------------------\n";
            cout << "[Enter the number of the gear to unequip, or '0' to exit]\n";

            int choice;
            cin >> choice;

            // Exit inventory
            if (choice == 0) {
                break;
            }

            // Validate choice and unequip gear
            if (choice > 0 && choice <= player.getGearItems().size()) { // Assume equippedGearItems is a list of currently equipped items
                Gear selectedGear = player.getGearItems()[choice - 1];

				// add it to old gear list then remove it from equipped gear
                gearItems.push_back(selectedGear);
                player.RemoveItemFromInventory(choice - 1);

                cout << selectedGear.getName() << " has been unequipped.\n";


            }
            else {
                cout << "Invalid choice! Please try again.\n";
            }
        }
              break;

        case 3: { // Open General Inventory
            displayPlayerInventory(); // Display general inventory
            cout << "[Enter the number of the Item you wish to interact with, or '0' to exit]\n";

            int choice;
            cin >> choice;

            // Exit inventory
            if (choice == 0) {
                break;
            }

            // Validate choice within bounds and interact with gear
            if (choice > 0 && choice <= static_cast<int>(inv.size())) { // Cast to ensure types match
                Item& selectedItem = inv[choice - 1];

                // Check if the selected item is consumable
                if (selectedItem.getType() == ItemType::Consumable) {
                    cout << "You have consumed: " << selectedItem.getName() << "\n";
                    selectedItem.use(); // Use the item if it's consumable
                }
                else {
                    cout << "You selected a non-consumable item: " << selectedItem.getName() << "\n";
                    cout << "You feel like Ryder is judging you...";
                }
            }
            else {
                cout << "Invalid choice! Please try again.\n";
            }
        }

        default:
            cout << "Invalid choice! Please try again.\n";
            break;
        }
    }
}


void Inventory::displayShopInventory(Character& player) {
    cout << "\nMerchant items: \n\n";
    cout << "You have: " << player.getGold() << " gold pieces!\n\n";

    // Loop through the items to display them
    for (size_t i = 0; i < items.size(); ++i) {
        const Item& item = items[i]; // Get the item at index i
        cout << "[" << i + 1 << "] " << item.getName() << " x "
            << item.getQuantity() << " - " << item.getValue() << " gold each\n";
    }
}

void Inventory::displayBlacksmithInventory(Character& player) {
    cout << "\nBlacksmith items: \n\n";
    cout << "You have: " << player.getGold() << " gold pieces!\n\n";

    for (size_t i = 0; i < equipment.size(); ++i) {
        const Gear& gear = equipment[i]; // Get the gear at index i
        cout << "[" << i + 1 << "] " << gear.getName() << " x "
            << gear.getQuantity() << " - " << gear.getValue() << " gold each\n";
    }
}

// Display player items
void Inventory::displayPlayerInventory() {
    cout << "\nYour items: \n";
    for (size_t i = 0; i < inv.size(); ++i) {
        const auto& item = inv[i];
        cout << "[" << i + 1 << "] " << item.getName() << " x " << item.getQuantity() << "\n";
    }
}

int Inventory::getGoldQuantity() const {
    for (const auto& item : inv) {
        if (item.getName() == "gold") {
            return item.getQuantity(); // Return the quantity of gold
        }
    }
    return 0; // Return 0 if gold is not found
}

void Inventory::increaseGold(Character& player,int amount) {
    
    if (amount <= 0) {
        cout << "Amount to increase must be positive!\n";
        return; // Exit if the amount is not positive
    }

    // Increase the player's gold using the Character class's method
    player.addGold(amount);

    cout << "Gold increased by " << amount << ". New total: " << player.getGold() << " gold pieces.\n";
}

void Inventory::decreaseGold(Character& player,int amount) {
    
    if (amount <= 0) {
        cout << "Amount to decrease must be positive!\n";
        return; // Exit if the amount is not positive
    }

    // Check if the player has enough gold
    if (player.getGold() < amount) {
        cout << "Not enough gold \m";
        return; // Exit if there's not enough gold
    }

    // Decrease the player's gold using the Character class's method
    player.subtractGold(amount);

    cout << "Gold decreased by " << amount << ". New total: " << player.getGold() << " gold pieces.\n";
}

int Inventory::sellEquipItem(Character& player,int index) { // Sell items to the blacksmith by index
    while (true) {
        if (index < 1 || index > gearItems.size()) {
            cout << "Invalid selection! Please enter a valid index.\n";
            return 0; // Exit if the index is out of bounds
        }

        // Adjust for zero-based indexing
        int itemIndex = index - 1;
        Gear& item = gearItems[itemIndex]; // Get the item based on the index

        cout << "How many " << item.getName() << " would you like to sell?\n";
        int howMany;
        cin >> howMany;

        // Validate quantity
        if (howMany <= 0) {
            cout << "Please enter a positive number!\n";
            continue; // Loop back for valid input
        }

        if (item.getQuantity() >= howMany) {
            int totalSaleValue = item.getValue() * howMany;

            // Use the inventory functions to handle gold and quantity
            player.addGold(totalSaleValue); // Add gold from the sale
            item.decreaseQuantity(howMany); // Decrease the item quantity

            // If quantity drops to 0, remove the item from inventory
            if (item.getQuantity() == 0) {
                gearItems.erase(gearItems.begin() + itemIndex); // Remove item by index
            }

            cout << "You have successfully sold " << howMany << " " << item.getName() << "s!\n";

            // Ask if they want to sell more
            string again;
            cout << "Would you like to sell anything else? (yes/no)\n";
            cin >> again;

            system("cls");

            if (again == "yes") {
                cout << "Enter the number of the item you would like to sell:\n";
                int newIndex;
                cin >> newIndex; // Get new index for the next sell
                return sellEquipItem(player,newIndex); // Recursive call to continue selling
            }
            else {
                return 1; // Exit the sell loop
            }
        }
        else {
            cout << "You don't have enough " << item.getName() << ". You have " << item.getQuantity() << " available.\n";
            system("pause");
            return 0; // Exit if not enough quantity
        }
    }
}

void Inventory::runBlacksmith(Character& player) {
    while (true) {
        cout << player.getGold() << " Gold remaining\n\n";
        
        cout << "Welcome to the Hooves and Steel! What can I do for you today?\n[1]Buy \n[2]Sell \n[3]Leave \n\n";
        cout << "What would you like to do?: ";
        int intent;
        cin >> intent;

        if (intent == 3) {
            break; // Exit the loop if user wants to quit
        }

        if (intent == 1) {
            system("cls");
            cout << "What would you like to purchase?\n";
            displayBlacksmithInventory(player);
            int input;
            cout << "which item would you like to buy: ";
            cin >> input;
            purchaseEquipItem(player,input);
            system("pause");
            system("cls");
        }
        else if (intent == 2) {
            system("cls");
            cout << "What would you like to sell?\n";
            displayPlayerInventory();
            int input;
            cout << "Which item would you like to sell: ";
            cin >> input;
            sellEquipItem(player,input);
            system("pause");
            system("cls");
        }
        else {
            cout << "Invalid option! Please enter 1, 2, or 3.\n";
        }
    }
}

void Inventory::runGeneralStore(Character& player) {
    while (true) {
        cout << player.getGold() << " Gold remaining\n\n";
        cout << "Welcome to the Caspiran general store! What can I do for you today?\n[1]Buy \n[2]Sell \n[3]Leave \n\n";
        cout << "What would you like to do: ";
        int intent;
        cin >> intent;

        if (intent == 3) {
            break; // Exit the loop if user wants to quit
        }

        if (intent == 1) {
            system("cls");
            cout << "What would you like to purchase?\n";
            displayShopInventory(player);
            int input;
            cout << "What would you like to do: ";
            cin >> input;
            purchaseGeneralItem(player,input);
            system("pause");
            system("cls");
        }
        else if (intent == 2) {
            system("cls");
            cout << "What would you like to sell?\n";
            displayPlayerInventory();
            int input;
            cout << "what would you like to do: ";
            cin >> input;
            sellGeneralItem(player,input);
            system("pause");
            system("cls");
        }
        else {
            cout << "Invalid option! Please enter a shown number!\n";
        }
    }
}

int Inventory::sellGeneralItem(Character& player,int index) { // Selling items to the general store
    while (true) {
        if (index < 1 || index > inv.size()) {
            cout << "Invalid number! Please try again.\n";
            return 0; // Exit if the index is invalid
        }

        auto& item = inv[index - 1]; // Get the item from the inventory at the provided index

        cout << "How many would you like to sell?\n";
        int howMany;
        cin >> howMany;

        // Validate quantity
        if (howMany <= 0) {
            cout << "Please enter a positive number!\n";
            return 0;
        }

        if (item.getQuantity() < howMany) {
            cout << "You don't have enough " << item.getName() << " to sell!\n";
            return 0;
        }

        // Adjust gold and inventory
        player.addGold(item.getValue() * howMany);
        decreaseQuantity(item.getName(), howMany);

        // Check if the item is also available in the shop to increase stock
        auto shopIter = std::find_if(items.begin(), items.end(), [&](const Item& shopItem) {
            return shopItem.getName() == item.getName(); // Check against the correct item
            });

        if (shopIter != items.end()) {
            shopIter->increaseQuantity(howMany); // Ensure this is not const
        }

        // If quantity drops to 0, remove the item from inventory
        if (item.getQuantity() == 0) {
            inv.erase(inv.begin() + (index - 1)); // Remove from inventory
            // Note: Be careful with erasing while using the index
        }

        cout << "You have successfully sold " << howMany << " " << item.getName() << "s!\n";

        // Ask if they want to sell more
        string again;
        cout << "Would you like to sell anything else? (yes/no)\n";
        cin >> again;

        system("cls");

        if (again == "yes") {
            cout << "What would you like to sell: ";
            displayPlayerInventory(); // Display available items again
            cin >> index; // Get new index input
            continue; // Loop back to sell
        }
        else {
            return 1; // Exit the selling loop
        }
    }
}

int Inventory::purchaseEquipItem(Character& player,int index) { // Purchase items from the blacksmith by index
    while (true) {
        // Check if the index is valid
        if (index < 1 || index > equipment.size()) {
            cout << "Invalid selection! Please enter a valid number.\n";
            return 0; // Exit if the index is out of bounds
        }

        // Adjust for zero-based indexing
        int itemIndex = index - 1;
        Item& item = equipment[itemIndex]; // Get the item based on the index

        cout << "How many " << item.getName() << " would you like to purchase?\n";
        int howMany;
        cin >> howMany;

        // Validate quantity input
        while (true) {
            if (cin.fail() || howMany <= 0) {
                cin.clear(); // Clear the error flag
                cin.ignore(10000, '\n'); // Discard invalid input
                cout << "Please enter a positive number!\n";
                cin >> howMany;
            }
            else {
                break; // Valid input; exit the loop
            }
        }

        int totalCost = item.getValue() * howMany;

        // Check if the player has enough gold
        if (player.getGold() < totalCost) {
            cout << "Not enough gold!\n";
            return 0;
        }

        // Check if there is enough stock available
        if (item.getQuantity() < howMany) {
            cout << "Not enough stock available!\n";
            return 0;
        }

        // Process the purchase
        player.subtractGold(totalCost);
        item.decreaseQuantity(howMany);

        // Check if the item already exists in gearItems
        auto invIter = std::find_if(gearItems.begin(), gearItems.end(), [&](const Item& invItem) {
            return invItem.getName() == item.getName();
            });

        if (invIter != gearItems.end()) {
            invIter->increaseQuantity(howMany);
        }
        else {
            gearItems.push_back(Gear(item.getName(), item.getEffect(), howMany, item.getValue(), item.isUsable(), item.getType(), false)); // Add new item to inventory
        }

        cout << "You have purchased " << howMany << " " << item.getName() << "s!\n";

        // Ask if the player wants to purchase anything else
        char again;
        cout << "Would you like to purchase anything else? (y/n)\n";
        cin >> again;

        // Validate the input for 'again'
        while (again != 'y' && again != 'n') {
            cout << "Please enter 'y' for yes or 'n' for no.\n";
            cin >> again;
        }

        if (again == 'n') {
            return 0; // Exit the purchase loop
        }

        // Display the inventory and prompt for a new purchase
        system("cls"); // Clear the screen
        displayBlacksmithInventory(player);
        cout << "What would you like to purchase? (Enter the item number)\n";

        // Get a valid item index
        while (true) {
            cin >> index;

            // Validate the input
            if (cin.fail() || index < 1 || index > equipment.size()) {
                cin.clear();
                cin.ignore(10000, '\n'); // Discard invalid input
                cout << "Invalid selection! Please enter a valid number.\n";
            }
            else {
                break; // Valid input; exit the loop
            }
        }
    }
}

int Inventory::purchaseGeneralItem(Character& player,int index) { // Purchase items from the general store
    while (true) {
        if (index < 1 || index > items.size()) {
            cout << "Invalid number! Please try again.\n";
            return 0; // Exit if the index is invalid
        }

        auto& item = items[index - 1]; // Get the item at the provided index (adjust for 0-based indexing)

        cout << "How many would you like to purchase?\n";
        int howMany;
        cin >> howMany;

        // Validate quantity
        if (howMany <= 0) {
            cout << "Please enter a positive number!\n";
            continue; // Loop back for valid input
        }

        int totalCost = item.getValue() * howMany;

        if (player.getGold() < totalCost) {
            cout << "Not enough gold!\n";
            return 0;
        }

        if (item.getQuantity() < howMany) {
            cout << "Not enough stock available!\n";
            return 0;
        }

        // Use the Inventory functions for decreasing gold and item quantity
        player.subtractGold(totalCost);
        decreaseQuantity(item.getName(), howMany);

        // Check if the item already exists in the inventory
        auto invIter = std::find_if(inv.begin(), inv.end(), [&](const Item& invItem) {
            return invItem.getName() == item.getName();
        });

        if (invIter != inv.end()) {
            invIter->increaseQuantity(howMany);
        } else {
            inv.push_back(Item(item.getName(), item.getEffect(), howMany, item.getValue(), item.isUsable(), item.getType())); // Add new item to inventory
        }

        cout << "You have purchased " << howMany << " " << item.getName() << "s!\n";

        // Ask if they want to purchase more
        char again;
        cout << "Would you like to purchase anything else? (y/n)\n";
        cin >> again;

        system("cls");

        if (again == 'y') {
            displayShopInventory(player); // Display available items again
            cout << "What else would you like to purchase: ";
            int newIndex;
            cin >> newIndex;
            return purchaseGeneralItem(player,newIndex); // Loop back to purchase
        } else {
            return 1;  // Exit the purchase loop
        }
    }
}
