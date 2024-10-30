// Textbased RPG test
// By Jonathon Cannon

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib> 
#include <limits>
#include <ctime>


#include "Rooms.h"
#include "AbilityScores.h"
#include "Character.h"
#include "CharacterClass.h"
#include "Enemy.h"
#include "Race.h"
#include "Item.h"
#include "Equipment.h"
#include "Effect.h"
#include "Combat.h"
#include "Globals.h"
#include "Inventory.h"

using std::cout;
using std::cin;
using std::string;
using std::vector;

using std::endl;
using std::numeric_limits;
using std::streamsize;


int chosenRace;
int chosenClass;
int calculateBonus(int score) {
    if (score >= 8 && score <= 12) return 0;
    else if (score >= 13 && score <= 14) return 1;
    else if (score >= 15 && score <= 16) return 2;
    else if (score >= 17 && score <= 18) return 3;
    else if (score >= 19 && score <= 20) return 4;
    return 0; // For scores below 8 or above 18
}

int gold = 150;
string characterName;
string input = "";

vector<Item> items = {
    { "healing potion", Effect(5,0,0), 3, 5, true, ItemType::Consumable },
    { "rations", Effect(2,0,0), 30, 1, true, ItemType::Consumable },
    { "mess kit", Effect(0,0,0), 1, 1, false, ItemType::Item },
	{ "tinderbox", Effect(0,0,0), 1, 1, false, ItemType::Item },
	{ "torch", Effect(0,0,0), 10, 1, false, ItemType::Item },
	{ "waterskin", Effect(0,0,0), 1, 1, false, ItemType::Item },
	{ "rope", Effect(0,0,0), 1, 2, false, ItemType::Item }

};

vector<Item> inv = {
    { "backpack", Effect(0,0,0), 1, 1, false, ItemType::Item },
    { "gold pouch", Effect(0,0,0), 1, 1, false, ItemType::Item },
    { "mess kit", Effect(0,0,0), 1, 1, false, ItemType::Item },
    { "tinderbox", Effect(0,0,0), 1, 1, false, ItemType::Item },
    { "torch", Effect(0,0,0), 10, 1, false, ItemType::Item },
    { "rations", Effect(2,0,0), 30, 1, true, ItemType::Consumable },
    { "waterskin", Effect(0,0,0), 1, 1, false, ItemType::Item },
    { "rope", Effect(0,0,0), 1, 2, false, ItemType::Item }

};

vector<Gear> equipment = {
    { "sword", Effect(0,3,0), 1, 15, false, ItemType::Weapon, false },
    { "shield", Effect(0,0,0,1), 1, 25, false, ItemType::Gear, false },
    { "crossbow", Effect(0,2,0), 1, 20, false, ItemType::Weapon, false },
    { "armor", Effect(0,0,0,2), 1, 100, false, ItemType::Gear, false }

};

int sellGeneralItem(int index);
int sellEquipItem(int index);
int purchaseGeneralItem(int index);
int purchaseEquipItem(int index);
void displayShopInventory();
void displayPlayerInventory();
Room* createTown();
void handleRoomEvents(Room* currentRoom);
void runGeneralStore();
void runBlacksmith();
void ChooseExit(Room*& currentRoom);



bool skipDelays = false; // Global variable to track delay preference

abilityScores generateRandomScores() {
    return abilityScores(
        std::rand() % 11 + 8,  // Strength
        std::rand() % 11 + 8,  // Dexterity
        std::rand() % 11 + 8,  // Constitution
        std::rand() % 11 + 8,  // Intelligence
        std::rand() % 11 + 8,  // Wisdom
        std::rand() % 11 + 8   // Charisma
    );
}

Character createCharacter();

// Races
vector<Race> races = {
    { "Dwarf", 0, 0, 2, 0, 0, 0},
    { "Elf", 0, 2, 0, 0, 0, 0},
    { "Halfling",0, 2, 0, 0, 0, 0},
    { "Human", 0, 0, 1, 0, 2, 0},
    { "Gnome", 0, 0, 0, 2, 0, 0},
    { "Tiefling", 0, 0, 0, 1, 0, 2}
};

vector<string> raceFlavorText = {
"Dwarves are stout and hardy. +2 con\n",
"Elves are graceful and agile. +2 Dex\n",
"Halflings are cheerful and nimble. +2 Dex\n",
"Humans are versatile and adaptable. +2 Wis +1 Con\n",
"Gnomes are curious and inventive. +2 Int\n",
"Tieflings carry the legacy of fiendish ancestry. +2 Cha +1 Int\n"
};

vector<string> classFlavorText = {
"Fighters are warriors who have trained extensively in the art of combat.\n",
"Paladins are holy warriors dedicated to upholding justice and righteousness.\n",
"Druids are guardians of nature, able to harness its power and shape-shift into animals.\n",
"Warlocks forge pacts with powerful entities to gain magical abilities.\n",
"Sorcerers possess innate magical talent, drawing on their bloodline to unleash powerful spells.\n",
"Wizards are scholars of the arcane, dedicating their lives to studying ancient tomes and mastering complex spells.\n",
"Rangers are skilled hunters and trackers, adept at surviving in the wild.\n"
};

vector<CharacterClass> charClass = {
    { "Fighter", 10 },
    { "Paladin", 12 },
    { "Druid", 8 },
    { "Warlock", 6 },
    { "Sorcerer", 6 },
    { "Wizard", 6 },
    { "Ranger", 10 }
};

void delay(int milliseconds) {
    if (!skipDelays) {
        clock_t goal = milliseconds + clock();
        while (goal > clock());

    }
}


int main()
{
	Inventory inventory;

    Room* currentRoom = createTown();

    system("cls");
    cout << "The Vanishing Vessels of Caspira!\n";
    cout << "Would you like to skip the story? (y/n): ";
    char skipChoice;
    cin >> skipChoice;
    skipDelays = (skipChoice == 'y' || skipChoice == 'Y');
    delay(3 * 1000);
    cout << "In the shimmering waters of the Caspiran archipelago,\n";
    delay(3 * 1000);
    cout << "The islands, known for their lush forests and masterful shipbuilders,\n";
    delay(3 * 1000);
    cout << "thrived on exports of fine lumber and swift sailing ships.\n";
    delay(3 * 1000);
    cout << "Yet, a dark cloud loomed over the vibrant trade routes;\n";
    delay(3 * 1000);
    cout << "vessels laden with precious cargo had begun to vanish without a trace.\n\n";
    delay(3 * 1000);
    delay(3 * 1000);
    cout << "The people of Caspira grew anxious.\n";
    delay(3 * 1000);
    cout << "Whispers of curses and sea spirits filled the air as merchants and sailors traded tales of the lost ships.\n";
    delay(3 * 1000);
    cout << "One night, as the village gathered by the flickering lanterns,\n";
    delay(3 * 1000);
    cout << "an elderly sailor recounted a haunting legend a specter known as the Wraith of the Waves,\n";
    delay(3 * 1000);
    cout << "said to haunt the waters, claiming ships that dared to leave with timber from the sacred Heartwood Grove.\n\n";
    delay(3 * 1000);
    delay(3 * 1000);
    cout << "Amidst the crowd, a newcomer emerged. With eyes like stormy seas and a unyielding spirit,\n";
    delay(3 * 1000);
    cout << "they had journeyed to Caspira seeking adventure. Hearing the villagers' plight,\n";
    delay(3 * 1000);
    cout << "they felt a calling to uncover the truth behind the disappearances.\n";
    delay(3 * 1000);
    cout << "they gathered there courage, determined to face whatever lay beneath the waves.\n";
    delay(3 * 1000);
    cout << "\nLet's get a bit more information on our Hero!\n\n";

    Character player(createCharacter());


    cout << "Now " << player.getName() << ", let's start your adventure!\n\n";

    while (true) {
        handleRoomEvents(currentRoom);
        currentRoom->DisplayRoom();

        // Handle navigation based on exits
        Room* nextRoom = nullptr;
        ChooseExit(currentRoom);
        // Cleanup
    


        cout << "'Have a good day!'";
        runGeneralStore();
		runBlacksmith();
        inventory.openInventory();
        
        char tutorial;
        cout << "Hang on! before you head out there you may need a bit of information.\nDo you know how to fight in these lands? (y/n): ";
        cin >> tutorial;
        if (tutorial == 'n' || tutorial == 'N') {
            cout << "Hi there, my name is Ryder and i will be the friendly voice in your head that helps you out!\n";
            delay(2 * 1000);
            cout << "Let me teach you some things about how combat works in the world of caspira.\n";
            delay(2 * 1000);

            cout << "\nChoose an action:\n";
            cout << "[1] Attack\n";
            cout << "[2] Defend\n";
            cout << "[3] Use Item\n";
            cout << "[4] Run\n\n";
            delay(2 * 1000);

            cout << "This is what you will see when you enter combat, \nYou don't need to choose anything right now i am just giving you an example!\n";
            delay(3 * 1000);
            cout << "Now, [1] Attack, should be self explanatory, \nyou will attack with whatever weapon you have equipped currently.\n";
            delay(3 * 1000);
            cout << "Next, [2] Defend, you will raise your weapon or shield into a defensive position, \nyou will reduce any incoming damage to '1 damage' for that round.\n";
            delay(3 * 1000);
            cout << "Next, [3] Use Item, this will open your inventory and let you choose from a list of useable items, such as potions, \nyou then give up your turn to use that item.\n";
            delay(3 * 1000);
            cout << "Finally, [4] Run, you will try to run away from the fight. \nit is only a percentage chance you will run away and if you fail the enemy will get a free attack on you.\n";
            delay(3 * 1000);
            cout << "Now that we have gone over the basics of the system, let's get you some hands on experience!\n\n";
            delay(2 * 1000);
            cout << "A Random Goblin appears in front of you! \nIt looks angry and hungry.\n";
            delay(4 * 1000);
        }

        else {
            cout << "\nWatch out!\n";
            cout << "Ambush!\nYou were ambushed the moment you exited the town!\n";
        }
        Enemy enemy("Goblin", 2, 10);
        Combat combat(player, enemy, inv);
        combat.start();
        if (player.isAlive() == false) {
            cout << "Game over man! Game over!\n\n";
            exit(0);
        }
        else {
            cout << "Congratulation on your first victory!";
        }
        return 0;
    }
}

// Display merchant items
void displayShopInventory() {
    cout << "\nMerchant items: \n\n";
    cout << "You have: " << gold << " gold pieces!\n\n";

    for (size_t i = 0; i < items.size(); ++i) {
        const Item& item = items[i]; // Get the item at index i
        cout << "[" << i + 1 << "] " << item.getName() << " x "
            << item.getQuantity() << " - " << item.getValue() << " gold each\n";
    }
}

void displayBlacksmithInventory() {
    cout << "\nBlacksmith items: \n\n";
    cout << "You have: " << gold << " gold pieces!\n\n";

    for (size_t i = 0; i < equipment.size(); ++i) {
        const Item& item = equipment[i]; // Get the item at index i
        cout << "[" << i + 1 << "] " << item.getName() << " x "
            << item.getQuantity() << " - " << item.getValue() << " gold each\n";
    }
}

// Display player items
void displayPlayerInventory() {
    cout << "\nYour items: \n";
    for (const auto& item : inv) {
        cout << item.getQuantity() << " x " << item.getName() << endl;
    }
}

int purchaseGeneralItem(int index) { // purchase items from the general store
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
            return 0;
        }

        int totalCost = item.getValue() * howMany;

        if (gold < totalCost) {
            cout << "Not enough gold!\n";
            return 0;
        }

        if (item.getQuantity() < howMany) {
            cout << "Not enough stock available!\n";
            return 0;
        }

        gold -= totalCost;
        item.decreaseQuantity(howMany);

        // Check if the item already exists in the inventory
        auto invIter = std::find_if(inv.begin(), inv.end(), [&](const Item& invItem) {
            return invItem.getName() == item.getName();
            });

        if (invIter != inv.end()) {
            invIter->increaseQuantity(howMany);
        }
        else {
            inv.push_back(Item(item.getName(), item.getEffect(), howMany, item.getValue(), item.isUsable(), item.getType())); // Add new item to inventory
        }

        cout << "You have purchased " << howMany << " " << item.getName() << "s!\n";

        // Ask if they want to purchase more
        char again;
        cout << "Would you like to purchase anything else? (y/n)\n";
        cin >> again;

        system("cls");

        if (again == 'y') {
            displayShopInventory(); // Display available items again
            cout << "What else would you like to purchase: ";
            int newIndex;
            cin >> newIndex;
            return purchaseGeneralItem(newIndex); // Loop back to purchase
        }
        else {
            return 1;  // Exit the purchase loop
        }
    }
}

int purchaseEquipItem(int index) { // Purchase items from the blacksmith by index
    while (true) {
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

        // Validate quantity
        if (howMany <= 0) {
            cout << "Please enter a positive number!\n";
            return 0;
        }

        int totalCost = item.getValue() * howMany;

        if (gold < totalCost) {
            cout << "Not enough gold!\n";
            return 0;
        }

        if (item.getQuantity() < howMany) {
            cout << "Not enough stock available!\n";
            return 0;
        }

        gold -= totalCost;
        item.decreaseQuantity(howMany);

        // Check if the item already exists in the inventory
        auto invIter = std::find_if(inv.begin(), inv.end(), [&](const Item& invItem) {
            return invItem.getName() == item.getName();
            });

        if (invIter != inv.end()) {
            invIter->increaseQuantity(howMany);
        }
        else {
            inv.push_back(Item(item.getName(), item.getEffect(), howMany, item.getValue(), item.isUsable(), item.getType())); // Add new item to inventory
        }

        cout << "You have purchased " << howMany << " " << item.getName() << "s!\n";

        // Ask if they want to purchase more
        string again;
        cout << "Would you like to purchase anything else? (yes/no)\n";
        cin >> again;

        system("cls");
        displayBlacksmithInventory();
        if (again == "yes") {
            cout << "What else would you like to purchase:\n";
            int newIndex;
            cin >> newIndex;
            return purchaseEquipItem(newIndex); // Recursive call to start over
        }
        else {
            return 1; // Exit the purchase loop
        }
    }
}

int sellGeneralItem(int index) { // Selling items to the general store
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
        gold += item.getValue() * howMany;
        item.decreaseQuantity(howMany);

        // Check if the item is also available in the shop to increase stock
        auto shopIter = std::find_if(items.begin(), items.end(), [&](const Item& shopItem) {
            return shopItem.getName() == item.getName();
            });

        if (shopIter != items.end()) {
            shopIter->increaseQuantity(howMany);
        }

        // If quantity drops to 0, remove the item from inventory
        if (item.getQuantity() == 0) {
            inv.erase(inv.begin() + (index - 1)); // Remove from inventory
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


int sellEquipItem(int index) { // Sell items to the blacksmith by index
    while (true) {
        if (index < 1 || index > inv.size()) {
            cout << "Invalid selection! Please enter a valid index.\n";
            return 0; // Exit if the index is out of bounds
        }

        // Adjust for zero-based indexing
        int itemIndex = index - 1;
        Item& item = inv[itemIndex]; // Get the item based on the index

        cout << "How many " << item.getName() << " would you like to sell?\n";
        int howMany;
        cin >> howMany;

        // Validate quantity
        if (howMany <= 0) {
            cout << "Please enter a positive number!\n";
            return 0;
        }

        if (item.getQuantity() >= howMany) {
            gold += item.getValue() * howMany;
            item.decreaseQuantity(howMany);

            // Find the corresponding item in the equipment for selling
            auto shopIter = std::find_if(equipment.begin(), equipment.end(), [&](const Gear& shopItem) {
                return shopItem.getName() == item.getName();
                });

            if (shopIter != equipment.end()) {
                shopIter->increaseQuantity(howMany);
            }

            // If quantity drops to 0, remove the item from inventory
            if (item.getQuantity() == 0) {
                inv.erase(inv.begin() + itemIndex); // Remove item by index
            }

            cout << "You have successfully sold " << howMany << " " << item.getName() << "s!\n";

            // Ask if they want to sell more
            string again;
            cout << "Would you like to sell anything else? (yes/no)\n";
            cin >> again;

            system("cls");

            if (again == "yes") {
                cout << "Enter the index of the item you would like to sell:\n";
                int newIndex;
                cin >> newIndex; // Get new index for the next sell
                return sellEquipItem(newIndex); // Recursive call to continue selling
            }
            else {
                return 1; // Exit the sell loop
            }
        }
        else {
            cout << "You don't have enough " << item.getName() << "\n";
            system("pause");
            return 0; // Exit if not enough quantity
        }
    }
}

void runGeneralStore() {
    while (true) {
        cout << gold << " Gold remaining\n\n";
        cout << "Welcome to the Caspiran general store! What can I do for you today?\n[1]Buy \n[2]Sell \n[3]Inventory \n[4]Quit \n\n";
        cout << "What would you like to do: ";
		int intent;  
        cin >> intent;

        if (intent == 4) {
            break; // Exit the loop if user wants to quit
        }
        if (intent == 3) {
            system("cls");
            displayPlayerInventory();
            continue; // Go back to the start of the loop
        }

        if (intent == 1) {
            system("cls");
            cout << "What would you like to purchase?\n";
            displayShopInventory();
            int input;
            cout << "What would you like to do: ";
            cin >> input;
            purchaseGeneralItem(input);
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
            sellGeneralItem(input);
            system("pause");
            system("cls");
        }
        else {
            cout << "Invalid option! Please enter a shown number!\n";
        }
    }
}

void runBlacksmith() {
    while (true) {
        cout << gold << " Gold remaining\n\n";
        cout << "Welcome to the Hooves and Steel! What can I do for you today?\n[1]Buy \n[2]Sell \n[3]Inventory \n[4]Quit \n\n";
        cout << "What would you like to do?: ";
        int intent;
        cin >> intent;

        if (intent == 4) {
            break; // Exit the loop if user wants to quit
        }
        if (intent == 3) {
            system("cls");
            displayPlayerInventory();
            continue; // Go back to the start of the loop
        }

        if (intent == 1) {
            system("cls");
            cout << "What would you like to purchase?\n";
            displayBlacksmithInventory();
            int input;
            cout << "which item would you like to buy: ";
            cin >> input;
            purchaseEquipItem(input);
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
            sellEquipItem(input);
            system("pause");
            system("cls");
        }
        else {
            cout << "Invalid option! Please enter 'buy', 'sell', 'inventory', or 'quit'.\n";
        }
    }
}

Character createCharacter() {
    string characterName;
    int chosenRace;
    int chosenClass;

    // Get character name
    while (true) {
        cout << "Enter your character's name (1-10 characters): ";
        cin >> characterName;

        if (characterName.empty() || characterName.length() > 10) {
            cout << "Invalid name. Name must be between 1 and 10 characters.\n";
        }
        else {
            break; // Valid name
        }
    }

    cout << characterName << ", pleased to meet you! Now, what are you?\n\n";

    // Choose a race
    while (true) {
        cout << "Races:\n[1] Dwarf\n[2] Elf\n[3] Halfling\n[4] Human\n[5] Gnome\n[6] Tiefling\n\n";
        cout << "Please choose a Race (1-" << races.size() << "): ";
        cin >> chosenRace;

        if (chosenRace < 1 || chosenRace > races.size()) {
            cout << "Invalid choice. Please try again.\n";
        }
        else {
            chosenRace--; // Adjust for zero-based index
            cout << "\n" << raceFlavorText[chosenRace] << "\n"; // Display flavor text
            break; // Valid choice
        }
    }

    // Choose a class
    while (true) {
        cout << "Classes:\n[1] Fighter\n[2] Paladin\n[3] Druid\n[4] Warlock\n[5] Sorcerer\n[6] Wizard\n[7] Ranger\n\n";
        cout << "Please choose a Class (1-" << charClass.size() << "): ";
        cin >> chosenClass;

        if (chosenClass < 1 || chosenClass > charClass.size()) {
            cout << "Invalid choice. Please try again.\n";
        }
        else {
            chosenClass--; // Adjust for zero-based index
            cout << "\n" << classFlavorText[chosenClass] << "\n"; // Display flavor text
            break; // Valid choice
        }
    }

    // Generate ability scores
    abilityScores playerScores = generateRandomScores();

    // Create character
    Character player(characterName, races[chosenRace], charClass[chosenClass], playerScores);

    cout << "\n";
    player.displayStats();

    // Ask if they want to create another character
    cout << "\nAre you happy with this Hero? (y/n): ";
    char continueChoice;
    cin >> continueChoice;

    if (continueChoice != 'n' && continueChoice != 'N') {
        return player; // Return the created character
    }
    else {
        // Create a new character without recursion
        return createCharacter(); // Call the function again to create a new character
    }
}

Room* createTown() {
    // Create rooms
    Room* tavern = new Room("Tavern", "A lively tavern filled with the sounds of laughter and music.");
    Room* townCenter = new Room("Town Center", "The bustling center of town, with shops and stalls.");
    Room* generalStore = new Room("General Store", "A shop filled with various supplies and goods.");
    Room* blacksmith = new Room("Blacksmith", "The forge is hot, and the blacksmith is hard at work.");

    // Create roads
    Room* roadEast = new Room("East Road", "A dusty road leading east out of town.");
    Room* roadWest = new Room("West Road", "A quiet road leading west towards the forest.");
    Room* roadNorth = new Room("North Road", "A path leading north towards the mountains.");

    // Set connections
    tavern->AddExit(townCenter);
    townCenter->AddExit(tavern);

    townCenter->AddExit(generalStore);
    generalStore->AddExit(townCenter);

    townCenter->AddExit(blacksmith);
    blacksmith->AddExit(townCenter);

    townCenter->AddExit(roadEast);
    roadEast->AddExit(townCenter);

    townCenter->AddExit(roadWest);
    roadWest->AddExit(townCenter);

    townCenter->AddExit(roadNorth);
    roadNorth->AddExit(townCenter);

    return tavern; // Start in the tavern
}

void handleRoomEvents(Room* currentRoom) {
    if (currentRoom->IsFirstVisit()) { // Check if it's the first visit
        if (currentRoom->GetName() == "Tavern") {
            cout << "You wake up in your cozy bed at the tavern, the smell of breakfast wafting through the air.\n";
            delay(3 * 1000);
            cout << "You can hear the chatter of patrons and the clinking of mugs, but your head is pounding.\n";
            delay(3 * 1000);
            cout << "As you sit up, a wave of nausea hits you, and you remember last night's revelry.\n";
            delay(3 * 1000);
            cout << "You feel dehydrated and your mouth is dry, you crave water.\n";
            delay(3 * 1000);
            cout << "A faint light coming through the window only intensifies your headache.\n";
            delay(3 * 1000);
            cout << "You get up slowly and gather your things.\n";
            delay(1 * 1000);
            displayPlayerInventory();
            delay(5 * 1000);
            cout << "You meander your way out of the room and down the stairs to the tavern.\n\n";
            delay(2 * 1000);
            cout << "'Rough night eh? Well, I would have a hangover too if I drank " << std::rand() % 50 + 1 << " bottles of rum as well.'\n\n";
            delay(2 * 1000);
        }
        else if (currentRoom->GetName() == "General Store") { // Handle General Store
            cout << "The general store is bustling with customers looking for supplies.\n";
            // Add general store-specific interactions here
			runGeneralStore();  
        }
        else if (currentRoom->GetName() == "Blacksmith") { // Handle Blacksmith
            cout << "You see the blacksmith hammering away at a piece of glowing metal.\n";
            // Add blacksmith-specific interactions here
			runBlacksmith();
        }
        // Add more room-specific logic as needed
    }
}

void ChooseExit(Room*& currentRoom) {
    currentRoom->ListExits();

    int choice = 0;
    cout << "Choose an exit (enter the number): ";
    cin >> choice;

    // Validate input
    if (choice < 1 || choice > currentRoom->GetNumberOfExits()) {
        cout << "Invalid choice. Please try again.\n";
        return;
    }

    Room* nextRoom = currentRoom->GetExits()[choice - 1];
    currentRoom = nextRoom;
    cout << "You move to: " << currentRoom->GetName() << "\n";
}

