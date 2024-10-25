// Textbased RPG test
// By Jonathon Cannon

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib> 
#include <limits>
#include <ctime>

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
string intent = "";
string input = "";
string newItem = "";

struct Item {
    string name;
    int price;
    int quantity;
};

vector<Item> items = {
    { "sword", 15, 1 },
    { "shield", 25, 1 },
    { "potion", 5, 3 },
    { "crossbow", 20, 1 },
    { "Rations", 1, 30 },
    { "armor", 100, 1 }
};

vector<Item> inventory = {
    { "Backpack", 0, 1 },
    { "Gold pouch", 0, 1 },
    { "Mess kit", 3, 1 },
    { "Tinderbox", 5, 1 },
    { "Torch", 1, 10 },
    { "Rations", 1, 10 },
    { "Waterskin", 2, 1 },
    { "Rope", 2, 1 },

};

int sellItem(const string& input);
int purchaseItem(const string& input);
void displayShopInventory();
void displayPlayerInventory();
void runShop();

void SetColor(int textColor)
{
    cout << "\033[" << textColor << "m";
}

void ResetColor() { cout << "\033[0m"; }

// Struct for races
struct abilityScores {
    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;

    abilityScores(int str, int dex, int con, int intl, int wis, int cha)
        : strength(str), dexterity(dex), constitution(con), intelligence(intl), wisdom(wis), charisma(cha) {}

    // Method to apply racial bonuses
    void applyRaceBonuses(const abilityScores& raceBonus) {
        strength += raceBonus.strength;
        dexterity += raceBonus.dexterity;
        constitution += raceBonus.constitution;
        intelligence += raceBonus.intelligence;
        wisdom += raceBonus.wisdom;
        charisma += raceBonus.charisma;
    }

};
struct Class {
    string name;
    int defaultHealth; // New property for default health

    Class(const string& className, int health)
        : name(className), defaultHealth(health) {}
};
struct Race {
    string name;
    abilityScores abilityIncrease;

    Race(const string& raceName, int strBonus, int dexBonus, int conBonus, int intlBonus, int wisBonus, int chaBonus)
        : name(raceName), abilityIncrease(strBonus, dexBonus, conBonus, intlBonus, wisBonus, chaBonus) {}
};
class Character {
public:
    string name;
    Race race;
    Class type;
    abilityScores baseScores;
    abilityScores bonuses; 
    int health;

    // Constructor
    Character(const string& characterName, const Race& characterRace, const Class& characterClass, const abilityScores& scores)
        : name(characterName), race(characterRace), type(characterClass), baseScores(scores), bonuses(0, 0, 0, 0, 0, 0) {
        baseScores.applyRaceBonuses(race.abilityIncrease);
        calculateBonuses(); // Calculate bonuses after applying racial bonuses
        calculateHealth(); // Calculate health after bonuses
    }

    void calculateBonuses() {
        bonuses.strength = calculateBonus(baseScores.strength);
        bonuses.dexterity = calculateBonus(baseScores.dexterity);
        bonuses.constitution = calculateBonus(baseScores.constitution);
        bonuses.intelligence = calculateBonus(baseScores.intelligence);
        bonuses.wisdom = calculateBonus(baseScores.wisdom);
        bonuses.charisma = calculateBonus(baseScores.charisma);
    }
    void calculateHealth() {
        int constitutionModifier = bonuses.constitution;
        health = type.defaultHealth + constitutionModifier; // Set health based on class default
    }

    void displayStats() const {
        cout << "Character: " << name << "\n";
        cout << "Race: " << race.name << "\n";
        cout << "Class: " << type.name << "\n";
        cout << "Hitpoints: " << health << "\n";
        cout << "Ability Scores:\n";
        cout << "Strength: " << baseScores.strength << " (+" << bonuses.strength << ")\n";
        cout << "Dexterity: " << baseScores.dexterity << " (+" << bonuses.dexterity << ")\n";
        cout << "Constitution: " << baseScores.constitution << " (+" << bonuses.constitution << ")\n";
        cout << "Intelligence: " << baseScores.intelligence << " (+" << bonuses.intelligence << ")\n";
        cout << "Wisdom: " << baseScores.wisdom << " (+" << bonuses.wisdom << ")\n";
        cout << "Charisma: " << baseScores.charisma << " (+" << bonuses.charisma << ")\n";
    }
};

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
void createCharacter();

// Races
vector<Race> races = {
    { "Dwarf", 0, 0, 2, 0, 0, 0},
    { "Elf", 0, 2, 0, 0, 0, 0},
    { "Halfling",0, 2, 0, 0, 0, 0},
    { "Human", 0, 0, 1, 0, 2, 0},
    { "Gnome", 0, 0, 0, 2, 0, 0},
    { "Tiefling", 0, 0, 0, 1, 0, 2}
};

Character playerCharacter("", Race("", 0, 0, 0, 0, 0, 0), Class("", 0), abilityScores(0, 0, 0, 0, 0, 0));


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

vector<Class> charClass = {
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

        createCharacter(); // Call the character creation function



  
    cout << "Now " << characterName << ", let's start your adventure!\n\n";
    
    cout << "You awake slowly and groggily, how much did you drink last night?\n\nYou look around the tiny room you had acquired for the night and see all your belongings are still there\n";
    delay(2 * 1000);
    cout << "You get up slowly and gather your things\n";
    delay(1 * 1000);
    displayPlayerInventory();
    delay(5 * 1000);
    cout << "You meander your way out of the room and down the stairs to the inn.\n\n";
    delay(2 * 1000);
    SetColor(31);
    cout << "'rough night eh? well i would have a hangover too if i drank " << std::rand() % 50 + 1 << " bottles of rum as well.'\n";
    delay(2 * 1000);
    cout << "'I have a friend who sell's some things if you would like to take a look at his wares before you head out? \n(y/n): ";
    ResetColor();
    char shopping;
    cin >> shopping;
    if (shopping == 'y' || shopping == 'Y')
        runShop();
    else
        SetColor(31);
        cout << "'Fair enough! Hope that hangover treats you well then.'\n";
    SetColor(31);
    cout << "'Have a good day!'";
    ResetColor();

    return 0;
}

// Display merchant items
void displayShopInventory() {
    cout << "\nMerchant items: \n\n";
    cout << "You have: " << gold << " gold pieces!\n\n";

    for (const auto& item : items) {
        cout << item.quantity << " x " << item.name << " - " << item.price << " gold each\n";
    }
}

// Display player items
void displayPlayerInventory() {
    cout << "\nYour items: \n";
    for (const auto& item : inventory) {
        cout << item.quantity << " x " << item.name << endl;
    }
}

// Handle purchasing items
int purchaseItem(const string& input) {
    while (true) {
        bool found = false;
        for (auto& item : items) {
            if (input == item.name) {
                found = true;
                cout << "How many would you like to purchase?\n";
                int quantity;
                cin >> quantity;

                // Validate quantity
                if (quantity <= 0) {
                    cout << "Please enter a positive number!\n";
                    return 0;
                }

                int totalCost = item.price * quantity;

                if (gold < totalCost) {
                    cout << "Not enough gold!\n";
                    return 0;
                }

                if (item.quantity < quantity) {
                    cout << "Not enough stock available!\n";
                    return 0;
                }

                gold -= totalCost;
                item.quantity -= quantity;

                // Check if the item already exists in the inventory
                auto invIter = std::find_if(inventory.begin(), inventory.end(), [&](const Item& invItem) {
                    return invItem.name == item.name;
                    });

                if (invIter != inventory.end()) {
                    invIter->quantity += quantity;
                }
                else {
                    inventory.push_back({ item.name, item.price, quantity }); // Add new item to inventory
                }

                cout << "You have purchased " << quantity << " " << item.name << "s!\n";

                // Ask if they want to purchase more
                string again;
                string newItem;
                cout << "Would you like to purchase anything else? (yes/no)\n";
                cin >> again;

                system("cls");

                if (again == "yes") {
                    cout << "What would you like to purchase?\n";
                    displayShopInventory();
                    cin >> newItem;
                    return purchaseItem(newItem); // this should hopefully allow for a proper return to the start of the loop
                }
                else {
                    return 1;  // Exit the purchase loop
                }

                break;  // Exit the inner loop if we found a match
            }
        }
        if (!found) {
            cout << input << " is not a valid option!\n";
            return 0;  // If item was not found, exit the function
        }
    }
}

// Handle selling items
int sellItem(const string& input) {
    while (true) {
        bool found = false;
        for (const auto& item : items) {
            if (input == item.name) {
                found = true;
                cout << "How many would you like to sell?\n";
                int quantity;
                cin >> quantity;

                // Validate quantity
                if (quantity <= 0) {
                    cout << "Please enter a positive number!\n";
                    return 0;
                }

                auto invIter = std::find_if(inventory.begin(), inventory.end(), [&](const Item& invItem) {
                    return invItem.name == item.name;
                    });

                if (invIter != inventory.end() && invIter->quantity >= quantity) {
                    gold += item.price * quantity;
                    invIter->quantity -= quantity;

                    auto shopIter = std::find_if(items.begin(), items.end(), [&](const Item& shopItem) {
                        return shopItem.name == item.name;
                        });

                    if (shopIter != items.end()) {
                        shopIter->quantity += quantity;
                    }

                    // If quantity drops to 0, remove the item from inventory
                    if (invIter->quantity == 0) {
                        inventory.erase(invIter);
                    }

                    cout << "You have successfully sold " << quantity << " " << item.name << "s!\n";

                    // Ask if they want to sell more
                    string again;
                    string newItem;
                    cout << "Would you like to sell anything else? (yes/no)\n";
                    cin >> again;

                    system("cls");

                    if (again == "yes") {
                        cout << "What would you like to sell?\n";
                        displayPlayerInventory();
                        cin >> newItem; // Get new input for the next sell
                    }
                    else {
                        return 1;
                    }

                    break;
                }
                else {
                    cout << "You don't have enough " << item.name << "\n";
                    system("pause");
                    return 0;
                }
            }
        }
        if (!found) {
            cout << input << " is not a valid option!\n";
            system("pause");
            return 0;
        }
    }
}
void runShop() {
    while (true) {
        cout << gold << " Gold remaining\n\n";
        cout << "Welcome to the Caspiran general store! What can I do for you today?\n buy \n sell \n inventory \n quit \n\n";
        cout << "Type the whole word: ";
        cin >> intent;

        if (intent == "quit") {
            break; // Exit the loop if user wants to quit
        }
        if (intent == "inventory") {
            system("cls");
            displayPlayerInventory();
            continue; // Go back to the start of the loop
        }

        if (intent == "buy") {
            system("cls");
            cout << "What would you like to purchase?\n";
            displayShopInventory();
            string input;
            cout << "Type the whole word: ";
            cin >> input;
            purchaseItem(input);
            system("pause");
            system("cls");
        }
        else if (intent == "sell") {
            system("cls");
            cout << "What would you like to sell?\n";
            displayPlayerInventory();
            string input;
            cout << "Type the whole word: ";
            cin >> input;
            sellItem(input);
            system("pause");
            system("cls");
        }
        else {
            cout << "Invalid option! Please enter 'buy', 'sell', 'inventory', or 'quit'.\n";
        }
    }
}

void createCharacter() {
    while (true) {
        cout << "Enter your character's name (1-10 characters): ";
        cin >> characterName;

        if (characterName.empty() || characterName.length() > 10) {
            cout << "Invalid name. Name must be between 1 and 10 characters.\n";
        }
        else {
            break; // Valid name, exit the loop
        }
    } 
    cout << characterName << " Pleased to meet you! now what are you?\n\n";

    // Choose a race
    while (true) {
        cout << "Races:\n[1]Dwarf\n[2]Elf\n[3]Halfling\n[4]Human\n[5]Gnome\n[6]Tiefling\n\n";
        cout << "Please choose a Race (1-" << races.size() << "): ";
        cin >> chosenRace;

        if (chosenRace < 1 || chosenRace > races.size()) {
            cout << "Invalid choice. Please try again.\n";
        }
        else {
            chosenRace--; // Adjust for zero being #1
            cout << "\n" << raceFlavorText[chosenRace] << "\n"; // Display flavor text
            break; // Valid choice, exit the loop
        }
    }

    // Choose a class
    while (true) {
        cout << "Classes:\n[1]Fighter\n[2]Paladin\n[3]Druid\n[4]Warlock\n[5]Sorcerer\n[6]Wizard\n[7]Ranger\n\n";
        cout << "Please choose a Class (1-" << charClass.size() << "): ";
        cin >> chosenClass;

        if (chosenClass < 1 || chosenClass > charClass.size()) {
            cout << "Invalid choice. Please try again.\n";
        }
        else {
            chosenClass--; // Adjust for zero
            cout << "\n" << classFlavorText[chosenClass] << "\n"; // Display flavor text
            break; // Valid choice, exit the loop
        }
    }

    std::srand(static_cast<unsigned int>(std::time(0)));
    abilityScores playerScores = generateRandomScores();

    // Create character
    Character playerCharacter(characterName, races[chosenRace], charClass[chosenClass], playerScores);

    cout << "\n";
    playerCharacter.displayStats();

    // Ask if they want to create another character
    cout << "\nAre you happy with this Hero? (y/n): ";
    char continueChoice;
    cin >> continueChoice;

    if (continueChoice != 'n' && continueChoice != 'N') {
        return; // Exit the function
    }
    else {
        createCharacter(); // Recursively call to create a new character
    }
}

