#include "Character.h"
#include "Inventory.h"


vector<Gear> equippedGear{
}; // Initialize the equipped gear vector

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

// Constructor implementation
Character::Character(const string& characterName, const Race& characterRace,
    const CharacterClass& characterClass, const abilityScores& scores,
    int level, int experience, int expToLevel, int gold)
    : mName(characterName), mRace(characterRace), mType(characterClass),
    mBaseScores(scores), mLevel(level), mExperience(experience),
    mExpToLevel(expToLevel), mGold(gold) {
    mBaseScores.applyRaceBonuses(mRace.abilityIncrease);
    calculateBonuses();
    calculateHealth();
}


void Character::calculateBonuses() {
    mBonuses.strength = calculateBonus(mBaseScores.strength);
    mBonuses.dexterity = calculateBonus(mBaseScores.dexterity);
    mBonuses.constitution = calculateBonus(mBaseScores.constitution);
    mBonuses.intelligence = calculateBonus(mBaseScores.intelligence);
    mBonuses.wisdom = calculateBonus(mBaseScores.wisdom);
    mBonuses.charisma = calculateBonus(mBaseScores.charisma);
}

void Character::calculateHealth() {
    int constitutionModifier = mBonuses.constitution;
    mHealth = mType.defaultHealth + constitutionModifier; // Set health based on class default
    mMaxHealth = mHealth;
}

void Character::takeDamage(int damage) {
    int effectiveDamage = damage;
    if (effectiveDamage < 0) effectiveDamage = 0; // Prevent negative damage

    mHealth -= effectiveDamage;
    cout << "Your armor reduced it to " << effectiveDamage << " damage!\n"; // "Your armor reduced it to x damage!"

    if (mHealth < 0) mHealth = 0;
    cout << getName() << "'s remaining health: " << mHealth << "\n"; // Debugging output for remaining health
    cout << " ______   ______   ______   ______   ______   ______ \n";
	cout << "/_____/  /_____/  /_____/  /_____/  /_____/  /_____/ \n";

}

bool Character::isAlive() const {
    return mHealth > 0;
}

string Character::getName() const {
    return mName;
}

int Character::getHealth() {
    return mHealth;
}

int Character::getMaxHealth() {
    return mMaxHealth;
}
int Character::heal(int amount) {
    mHealth += amount;
    if (mHealth > mMaxHealth) {
        mHealth = mMaxHealth;
    }
	cout << "You are now at " << mHealth << " health!\n";
    return mHealth;
}
void Character::setHealth(int health) {
	mHealth = health;
}

int Character::getAttack() const {
    int baseDamage = mDamage + mBonuses.strength + 1; // Base damage calculation
    int damageFromGear = 0;

    // Iterate through equipped gear to find damage increases
    for (const auto& gear : equippedGear) {
        if (gear.isEquipped()) {
            damageFromGear += gear.getEffect().damage; // Add gear's damage increase
        }
    }

    return baseDamage + damageFromGear; // Return total damage
}


void Character::AddItemToInventory(Gear& gear) {
    inventory->AddItem(gear);
}

void Character::RemoveItemFromInventory(int index) {
    // Check if the index is within the valid range
    if (index >= 0 && index < equippedGear.size()) {
        // Erase the item at the specified index
        equippedGear.erase(equippedGear.begin() + index);
        cout << "Item at index " << index << " has been removed from equipped gear.\n";
    }
    else {
        cout << "Invalid index! Unable to remove item from equipped gear.\n";
    }
}

void Character::ListInventory() const {
    inventory->ListGearItems();
}

void Character::EquipGear(Gear& gear, Character& player) {
    // Check if the gear is already equipped
    if (gear.isEquipped()) {
        cout << gear.getName() << " is already equipped!\n";
        return;
    }

    // Equip the gear
    gear.equip(player); // Call the gear's equip method

    // After successfully equipping, add it to the equippedGear vector
    equippedGear.push_back(gear); // Copy the gear into the vector
    cout << gear.getName() << " has been added to your equipped gear.\n";
}

void Character::displayVictoryScreen() {
    cout << "\n\n";
    cout << "|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n";
    cout << "|              VICTORY!                |\n";
    cout << "|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n";
    cout << "\n";
    cout << "Congratulations, " << getName() << "!\n";
    cout << "You've defeated Barbossa and claimed victory!\n";
    cout << "\n";
    system("pause");
    exit(0);
    

}

void Character::UnequipGear(Gear& gear, Character& player) {
    // Find the gear in the equippedGear vector
    for (auto it = equippedGear.begin(); it != equippedGear.end(); ++it) {
        if (it->getName() == gear.getName() && it->isEquipped()) {
            it->unequip(player); // Call the unequip method on the gear
            equippedGear.erase(it); // Remove it from the equipped gear vector
            return;
        }
    }
    cout << gear.getName() << " is not equipped!\n";
}

int Character::getTotalDamageReduction() const {
    int totalReduction = 0;
    for (const auto& gear : equippedGear) {
        if (gear.isEquipped()) {
            totalReduction += gear.getTotalDamageReduction();
        }
    }
    return totalReduction;
}
void Character::Levelup() {
    mLevel++;
    mExperience = 0;
    mExpToLevel *= 2;
    mMaxHealth += mType.defaultHealth;
    mDamage += 1;
	cout << "\n\n";
    cout << "  |~~~~~~~~~~~~~~~~~~~~| " <<"\n";
    cout << "  |     LEVEL UP!      | " << "\n";
    cout << "  |~~~~~~~~~~~~~~~~~~~~| " << "\n";
	cout << "\n\n You are now Level " << mLevel << "!\n\n";
	cout << "You have gained 1 damage!\nYour max health has increased to " << mMaxHealth << "!\n\n";
}

int Character::addExp(int exp) {
    mExperience += exp;
    if (mExperience >= mExpToLevel) {
        Levelup();
    }
    return mExperience;
}

int Character::getExp() {
    return mExperience;
}

int Character::getGold() {
    return mGold;
}

int Character::addGold(int amount) {
    cout << "Adding gold: " << amount << "\n";
    mGold += amount;
    cout << "New gold amount: " << mGold << "\n";
    return mGold;
}

const vector<Gear>& Character::getGearItems() const {
    return equippedGear;
}


int Character::subtractGold(int amount) {
    mGold -= amount;
    return mGold;

}


void Character::removeDamageReduction(int amount) {
    totalDamageReduction -= amount;
    if (totalDamageReduction < 0) {
        totalDamageReduction = 0; // make sure you can't take extra damage anymore
    }
}

void Character::addDamageReduction(int amount) {
    totalDamageReduction += amount;
}




// Calculate the bonus based on the score (Member function)
int Character::calculateBonus(int score) const {
    if (score >= 8 && score <= 12) return 0;
    else if (score >= 13 && score <= 14) return 1;
    else if (score >= 15 && score <= 16) return 2;
    else if (score >= 17 && score <= 18) return 3;
    else if (score >= 19 && score <= 20) return 4;
    return 0; // For scores below 8 or above 20
}

void Character::displayStats() const {
    cout << "|~~~~~~~~~~~~~~~~~|\n";
    cout << "| Character:      |--" << mName << "\n";
    cout << "| Race:           |--" << mRace.name << "\n";
    cout << "| Class:          |--" << mType.name << "\n";
    cout << "| Hitpoints:      |--" << mHealth << "/" << mMaxHealth << "\n";
    cout << "|~~~~~~~~~~~~~~~~~|\n";
    cout << "| Ability Scores: |\n";
    cout << "| Strength:       |--" << mBaseScores.strength << " (+" << mBonuses.strength << ")\n";
    cout << "| Dexterity:      |--" << mBaseScores.dexterity << " (+" << mBonuses.dexterity << ")\n";
    cout << "| Constitution:   |--" << mBaseScores.constitution << " (+" << mBonuses.constitution << ")\n";
    cout << "| Intelligence:   |--" << mBaseScores.intelligence << " (+" << mBonuses.intelligence << ")\n";
    cout << "| Wisdom:         |--" << mBaseScores.wisdom << " (+" << mBonuses.wisdom << ")\n";
    cout << "| Charisma:       |--" << mBaseScores.charisma << " (+" << mBonuses.charisma << ")\n";
    cout << "|~~~~~~~~~~~~~~~~~|\n";
}

Character Character::createCharacter() {
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
    // Give the player some starting gold  

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

abilityScores Character::generateRandomScores() {
    return abilityScores(
        std::rand() % 11 + 8,  // Strength
        std::rand() % 11 + 8,  // Dexterity
        std::rand() % 11 + 8,  // Constitution
        std::rand() % 11 + 8,  // Intelligence
        std::rand() % 11 + 8,  // Wisdom
        std::rand() % 11 + 8   // Charisma
    );
}
