#include "Rooms.h"
#include "Character.h"
#include "Inventory.h"
#include "Enemy.h"
#include "combat.h"   

Room::Room(string name, string description, bool locked, float attackChance)
    : mName(name), mDescription(description), mFirstVisit(true), mAttackChance(attackChance) { }


void Room::AddExit(Room* room) {
    mExits.push_back(room);
}

vector<Room*> Room::GetExits() {
    return mExits;
}

int Room::GetNumberOfExits() {
    return mExits.size();
}

void Room::ListExits() {
    if (mExits.empty()) {
        cout << "There is no escape!\n";
    }
    else {
        cout << "You see the following exits: \n";
        for (size_t i = 0; i < mExits.size(); i++) {
            cout << i + 1 << ". " << mExits[i]->GetName() << "\n";
        }
    }
    cout << "\n"; // Blank line for readability
}

string Room::GetName() {
    return mName;
}

void Room::DisplayRoom() {
    cout << mName << "\n";
    cout << "-----------------------\n";
    cout << mDescription << "\n";

    if (mLocked) {
        cout << "The room is locked.\n";
    }

    ListExits(); // Show exits
}

bool Room::IsFirstVisit() {
    if (mFirstVisit) {
        mFirstVisit = false; // Set to false after first visit
        return true; // Indicate this is the first visit
    }
    return false; // Indicate this is not the first visit
}

void Room::HandleAttack(Character& player) {
    cout << "An enemy appears!\n";
    Enemy enemies[] = {
        Enemy("Goblin", 2, 10, 3, 25),
        Enemy("Orc", 4, 15, 6, 50),
        Enemy("Troll", 3, 20, 25, 100),
        Enemy("Skeleton", 1, 5, 1, 50),
        Enemy("Werewolf", 4, 40, 100, 250)
    };

    // Generate a random index between 0 and 4 (inclusive)
    int randomIndex = rand() % 5;

    // Select a random enemy
    Inventory inventory;
    auto inv = inventory.getInv();
    Enemy selectedEnemy = enemies[randomIndex];
	cout << "You have encountered a " << selectedEnemy.getName() << "!" << "\n";
    Combat combat(player, selectedEnemy, inv);
    combat.start();
    if (!player.isAlive()) {
        cout << "Game over, man! Game over!\n\n";
        exit(0); // Exit the game if the player is dead
    }
    else {
        cout << "You have defeated the " << selectedEnemy.getName() << "!\n";
        cout << "You have gained " << selectedEnemy.getExp() << " experience points!\n";
        player.addExp(selectedEnemy.getExp());
        cout << "You now have " << player.getExp() << " experience points!\n";
        cout << "You have gained " << selectedEnemy.getGold() << " gold!\n";
        player.addGold(selectedEnemy.getGold());
        cout << "You now have " << player.getGold() << " gold!\n";
    }
}

void Room::HandlePlayerAction(Character& player) {
	Inventory inventory;
    // Check for specific room interactions first
    if (GetName() == "General Store") {
        inventory.runGeneralStore();
        return; // Exit this method after handling store logic
    }
    if (GetName() == "Blacksmith") {
        inventory.runBlacksmith();
        return; // Exit this method after handling store logic
    }

    // Check for attack chance immediately upon entering the room
    if (static_cast<float>(rand()) / RAND_MAX < mAttackChance) {
        cout << "You have been attacked!\n";
        HandleAttack(player); // Call combat here
        
    }

    // Prompt the player for their action
    while (true) {
        cout << "\nWhat would you like to do?\n";
        cout << "[1] Open Inventory\n";
        cout << "[2] Move to another room\n";
        cout << "[3] Check room description\n";
        cout << "[4] Investigate your Surroundings\n";
        cout << "[0] Exit\n";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: // Open inventory
            inventory.openInventory(player); // Call the inventory function
            break;
        case 2: {
            Room* nextRoom = ChooseExit(); // Get the next room from ChooseExit
            if (nextRoom) { // If the next room is valid
                nextRoom->HandlePlayerAction(player); // Pass inventory to the next room
            }
            break;
        }
        case 3:
            DisplayRoom(); // Show room description
            break;
        case 4:
            // Implement the logic for investigating surroundings
            cout << "You look around carefully...\n";
            // Add any findings or interactions here
            break;
        case 0: // Exit the loop
            return;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
}


Room* Room::ChooseExit() {
    ListExits(); // List the exits for the current room

    int choice = 0;
    cout << "Choose an exit (enter the number): ";
    cin >> choice;

    // Validate input
    if (choice < 1 || choice > GetNumberOfExits()) {
        cout << "Invalid choice. Please try again.\n";
        return nullptr; // Return null if invalid choice
    }

    return mExits[choice - 1]; // Return the chosen room
}

Room* Room::createTown() {
    Room* tavern = new Room("Tavern", "A lively tavern filled with sounds of laughter and music.", false, 0.0f);
    Room* townCenter = new Room("Town Center", "The bustling center of town, with shops and stalls.", false, 0.05f);
    Room* generalStore = new Room("General Store", "A shop filled with various supplies and goods.", false, 0.0f); // No attack chance
    Room* blacksmith = new Room("Blacksmith", "The forge is hot, and the blacksmith is hard at work.", false, 0.0f);
    Room* docks = new Room("Caspiran Docks", "A bustling waterfront where ships come and go, carrying the rich scents of salt and adventure. \nYou are surrounded by the sounds of seagulls and the chatter of merchants.", false, 0.0f);
    Room* heartwood = new Room("Heartwood Grove", "A serene, enchanted forest filled with ancient trees whose vibrant leaves whisper secrets, \ninviting wanderers to explore its hidden paths.", false, 0.0f);
    Room* crypt = new Room("Hall of Ancestors", "Once a majestic structure, the Hall of Ancestors now stands in decay. \nThe crumbling stone walls and overgrown vines, its faded carvings barely visible. \nIt quietly bears witness to the forgotten memories of those it once honored.", false, 0.5f);

    // Create roads
    Room* roadEast = new Room("East Road", "A dusty road leading east out of town.", false, 0.25f);
    Room* roadWest = new Room("West Road", "A quiet road leading west towards the forest.", false, 0.25f);
    Room* roadNorth = new Room("North Road", "A path leading north towards the mountains.", false, 0.25f);
    Room* roadEast2 = new Room("Docks Outskirts", "A bustling area where the docks meet the land, filled with the sounds of waves and the cries of seagulls.", false, 0.25f);
    Room* roadWest2 = new Room("Graveyard", "A solemn place shrouded in mist, with weathered tombstones and the faint sound of rustling leaves.", false, 0.25f);
    Room* roadNorth2 = new Room("Lumberyard", "A rugged path lined with stacks of timber, echoing with the sounds of axes and saws as workers tend to their trade.", false, 0.25f);

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

    roadNorth2->AddExit(roadNorth);
    roadNorth->AddExit(roadNorth2);

    roadEast2->AddExit(roadEast);
    roadEast->AddExit(roadEast2);

    roadWest2->AddExit(roadWest);
    roadWest->AddExit(roadWest2);

    roadNorth2->AddExit(heartwood);
    heartwood->AddExit(roadNorth2);

    roadWest2->AddExit(crypt);
    crypt->AddExit(roadWest2);

    roadEast2->AddExit(docks);
    docks->AddExit(roadEast2);


    return tavern; // Start in the tavern
}