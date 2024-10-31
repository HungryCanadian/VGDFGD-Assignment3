#include "Character.h"
#include "Inventory.h"


vector<Gear> equippedGear{
}; // Initialize the equipped gear vector

// Constructor implementation
Character::Character(const string& characterName, const Race& characterRace, const CharacterClass& characterClass,
    const abilityScores& scores, int level, int experience, int expToLevel, int gold) :
    mName(characterName),
    mRace(characterRace),
    mType(characterClass),
    mBaseScores(scores),
    mBonuses(0, 0, 0, 0, 0, 0),
    mHealth(0),
    mMaxHealth(0),
    mLevel(level),
    mExperience(experience),
    mExpToLevel(expToLevel > 0 ? expToLevel : 100), // Set a default value if 0
    mGold(gold)
{
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

int Character::attack() const {
    return rand() % 3 + (mBonuses.strength + 1); // Example attack damage calculation
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
    return mHealth;
}

int Character::getAttack() const {
    return mDamage;
}


void Character::AddItemToInventory(Gear& gear) {
    inventory->AddItem(gear);
}

void Character::RemoveItemFromInventory(Gear& gear) {
    inventory->RemoveItem(gear);
}

void Character::ListInventory() const {
    inventory->ListGearItems();
}

void Character::EquipGear(Gear& gear) {
    // Check if the gear is already equipped
    if (gear.isEquipped()) {
        cout << gear.getName() << " is already equipped!\n";
        return;
    }

    // Equip the gear
    gear.equip(); // Call the gear's equip method

    // After successfully equipping, add it to the equippedGear vector
    equippedGear.push_back(gear); // Copy the gear into the vector
    cout << gear.getName() << " has been added to your equipped gear.\n";
}


void Character::UnequipGear(Gear& gear) {
    // Find the gear in the equippedGear vector
    for (auto it = equippedGear.begin(); it != equippedGear.end(); ++it) {
        if (it->getName() == gear.getName() && it->isEquipped()) {
            it->unequip(); // Call the unequip method on the gear
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
    mHealth = mMaxHealth;
    mDamage += 1;
    cout << "You have leveled up! You are now level " << mLevel << "!\n";
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
    mGold += amount;
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
    cout << "Character: " << mName << "\n";
    cout << "Race: " << mRace.name << "\n";
    cout << "Class: " << mType.name << "\n";
    cout << "Hitpoints: " << mHealth << "\n";
    cout << "Ability Scores:\n";
    cout << "Strength: " << mBaseScores.strength << " (+" << mBonuses.strength << ")\n";
    cout << "Dexterity: " << mBaseScores.dexterity << " (+" << mBonuses.dexterity << ")\n";
    cout << "Constitution: " << mBaseScores.constitution << " (+" << mBonuses.constitution << ")\n";
    cout << "Intelligence: " << mBaseScores.intelligence << " (+" << mBonuses.intelligence << ")\n";
    cout << "Wisdom: " << mBaseScores.wisdom << " (+" << mBonuses.wisdom << ")\n";
    cout << "Charisma: " << mBaseScores.charisma << " (+" << mBonuses.charisma << ")\n";
}
