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

string characterName;
string input = "";

//void handleRoomEvents(Room* currentRoom, Character& player);


Inventory inventory;

bool skipDelays = false; // Global variable to track delay preference





// Races


void delay(int milliseconds) {
    if (!skipDelays) {
        clock_t goal = milliseconds + clock();
        while (goal > clock());

    }
}
Room room;

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    Room* currentRoom = room.createTown();
    
    system("cls");
    cout << " __      __            .__       .___         _____  _________                       .__               \n";
    cout << "/  \\    /  \\___________|  |    __| _/   _____/ ____\\ \\_   ___ \\_____    ____________ |__|___________   \n";
    cout << "\\   \\/\\/   /  _ \\_  __ \\  |   / __ |   /  _ \\   __\\  /    \\  \\/\\__  \\  /  ___/\\____ \\|  \\_  __ \\__  \\  \n";
    cout << " \\        (  <_> )  | \\/  |__/ /_/ |  (  <_> )  |    \\     \\____/ __ \\_\\___ \\ |  |_> >  ||  | \\/ / __ \\_ \n";
    cout << "  \\__\\/  / \\____/|__|  |____/\\____ |   \\____/|__|     \\______  (____  /____  >|   __/|__||__|  (____  / \n";
    cout << "       \\/                         \\/                         \\/     \\/     \\/ |__|                   \\/  \n";
    cout << " -----------------------------------------------------------------------------------------------------\n";

    cout << "                              The Vanishing Vessels of Caspira!                                        \n";
    cout << "Would you like to skip the story? (y/n): ";
    char skipChoice;
    cin >> skipChoice;
    skipDelays = (skipChoice == 'y' || skipChoice == 'Y');
    system("cls");
    cout << " __      __            .__       .___         _____  _________                       .__               \n";
    cout << "/  \\    /  \\___________|  |    __| _/   _____/ ____\\ \\_   ___ \\_____    ____________ |__|___________   \n";
    cout << "\\   \\/\\/   /  _ \\_  __ \\  |   / __ |   /  _ \\   __\\  /    \\  \\/\\__  \\  /  ___/\\____ \\|  \\_  __ \\__  \\  \n";
    cout << " \\        (  <_> )  | \\/  |__/ /_/ |  (  <_> )  |    \\     \\____/ __ \\_\\___ \\ |  |_> >  ||  | \\/ / __ \\_ \n";
    cout << "  \\__\\/  / \\____/|__|  |____/\\____ |   \\____/|__|     \\______  (____  /____  >|   __/|__||__|  (____  / \n";
    cout << "       \\/                         \\/                         \\/     \\/     \\/ |__|                   \\/  \n";
    cout << " -----------------------------------------------------------------------------------------------------\n";

    cout << "                              The Vanishing Vessels of Caspira!                                        \n\n\n";
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


	Character player = player.createCharacter();


    cout << "Now " << player.getName() << ", let's start your adventure!\n\n";
    while (true) {
        currentRoom->HandlePlayerAction(currentRoom,player, inventory); // Handle player actions
    }
    


        cout << "'Have a good day!'";
        /*inventory.runGeneralStore();
		inventory.runBlacksmith();
        inventory.openInventory(player);*/
        
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
        auto inv = inventory.getInv();
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





//void handleRoomEvents(Room* currentRoom,Character& player) {
//    if (currentRoom->IsFirstVisit()) { // Check if it's the first visit
//        if (currentRoom->GetName() == "Tavern") {
//            cout << "You wake up in your cozy bed at the tavern, the smell of breakfast wafting through the air.\n";
//            delay(3 * 1000);
//            cout << "You can hear the chatter of patrons and the clinking of mugs, but your head is pounding.\n";
//            delay(3 * 1000);
//            cout << "As you sit up, a wave of nausea hits you, and you remember last night's revelry.\n";
//            delay(3 * 1000);
//            cout << "You feel dehydrated and your mouth is dry, you crave water.\n";
//            delay(3 * 1000);
//            cout << "A faint light coming through the window only intensifies your headache.\n";
//            delay(3 * 1000);
//            cout << "You get up slowly and gather your things.\n";
//            delay(1 * 1000);
//            inventory.displayPlayerInventory();
//            delay(5 * 1000);
//            cout << "You meander your way out of the room and down the stairs to the tavern.\n\n";
//            delay(2 * 1000);
//            cout << "'Rough night eh? Well, I would have a hangover too if I drank " << std::rand() % 50 + 1 << " bottles of rum as well.'\n\n";
//            delay(2 * 1000);
//		}
//        else if (currentRoom->GetName() == "Town Center") {
//            char tutorial;
//            cout << "Hang on! before you leave! You may need a bit of information.\nDo you know how to fight in these lands? (y/n): ";
//            cin >> tutorial;
//            if (tutorial == 'n' || tutorial == 'N') {
//                cout << "Well then! Hi there, my name is Ryder. \nI will be the friendly voice in your head that helps you out!\n";
//                delay(3 * 1000);
//                cout << "Don't look around like that, people are going to think you're weird\ndon't bother trying to talk either, you will just look like you are talking to yourself.\n";
//                delay(3 * 1000);
//                cout << "Let me teach you some things about how combat works in the world of caspira.\n";
//                delay(3 * 1000);
//
//                cout << "\nChoose an action:\n";
//                cout << "[1] Attack\n";
//                cout << "[2] Defend\n";
//                cout << "[3] Use Item\n";
//                cout << "[4] Run\n\n";
//                delay(3 * 1000);
//
//                cout << "This is what you will see when you enter combat, \nYou don't need to choose anything right now i am just giving you an example!\n";
//                delay(3 * 1000);
//                cout << "Now, [1] Attack, should be self explanatory, \nyou will attack with whatever weapon you have equipped currently.\n";
//                delay(3 * 1000);
//                cout << "Next, [2] Defend, you will raise your weapon or shield into a defensive position, \nyou will reduce any incoming damage to '1 damage' for that round.\n";
//                delay(3 * 1000);
//                cout << "Next, [3] Use Item, this will open your inventory and let you choose from a list of useable items, such as potions, \nyou then give up your turn to use that item.\n";
//                delay(3 * 1000);
//                cout << "Finally, [4] Run, you will try to run away from the fight. \nit is only a percentage chance you will run away and if you fail the enemy will get a free attack on you.\n";
//                delay(3 * 1000);
//                cout << "Now that we have gone over the basics of the system, let's get you some hands on experience!\n\n";
//                delay(2 * 1000);
//                cout << "A Random Goblin appears in front of you! \nIt looks angry and hungry.\n";
//                delay(4 * 1000);
//            }
//
//            else {
//                cout << "\nWatch out!\n";
//                cout << "Ambush!\nYou were ambushed the moment you exited the town!\n";
//            }
//            Enemy enemy("Goblin", 2, 10);
//            auto inv = inventory.getInv();
//            Combat combat(player, enemy, inv);
//            combat.start();
//            if (player.isAlive() == false) {
//                cout << "Game over man! Game over!\n\n";
//                exit(0);
//            }
//            else {
//                cout << "Congratulation on your first victory!";
//            }
//            return;
//        }
//        }
//        // Add more room-specific logic as needed
//    }

