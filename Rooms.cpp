#include "Rooms.h"
#include "character.h"

int sellItem(const string& input);
int purchaseItem(const string& input);
void displayShopInventory();
void displayPlayerInventory();
void runShop();
void combat(Character& player, Enemy& enemy);


// Create an instance of Character
//Character player("Hero", ("Human", 1, 1, 0, 0, 0, 0), ("Fighter", 10), (10, 10, 10, 10, 10, 10));


Room::Room(const string& roomName, const string& roomDesc, const vector<string>& roomExits, void (*roomAction)())
    : name(roomName), description(roomDesc), exits(roomExits), action(roomAction) {}

void visitGeneralStore() {
    cout << "\nWelcome to the General Store!\n";
    runShop(); // Allow purchasing or selling
}

void visitBlacksmith() {
    // code for blacksmith
}

void visitOutskirts() {
    // code for outskirts
    /*Enemy goblin("Goblin", 5, 30);
    combat(player, goblin);*/
}

// Room instances
Room generalStore("General Store", "\nYou see shelves filled with various supplies.", { "Blacksmith", "Town Square" }, visitGeneralStore);
Room blacksmith("Blacksmith", "\nYou smell hot metal and see tools everywhere.", { "General Store", "Town Square" }, visitBlacksmith);
Room outskirts("Outskirts", "\nThe town behind you and long flowing grassland in front of you..", { "Town Square" }, visitOutskirts);
Room townSquare("Town Square", "\nThe bustling center of the town, with paths leading to various shops.", { "Outskirts", "General Store", "Blacksmith" }, nullptr);

// Room collection
vector<Room> rooms = { generalStore, blacksmith, townSquare, outskirts };
