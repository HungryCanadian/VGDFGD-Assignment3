#include "Character.h"
#include "Inventory.h"


// Constructor implementation
Character::Character(const string& characterName, const Race& characterRace, const CharacterClass& characterClass, const abilityScores& scores)
    : mName(characterName), mRace(characterRace), mType(characterClass), mBaseScores(scores), mBonuses(0, 0, 0, 0, 0, 0) {
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
    int effectiveDamage = damage - totalDamageReduction; // totalDamageReduction is calculated based on equipped armor and if the player chose to defend or not.
    if (effectiveDamage < 0) effectiveDamage = 0; //prevent negative damage
    mHealth -= effectiveDamage;
    if (mHealth < 0) mHealth = 0;
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

void Character::addDamageReduction(int amount) {
    totalDamageReduction += amount;
}

void Character::removeDamageReduction(int amount) {
    totalDamageReduction -= amount;
    if (totalDamageReduction < 0) {
        totalDamageReduction = 0; // make sure you can't take extra damage anymore
    }
}

void Character::AddItemToInventory(const Item& item) {
    inventory->AddItem(item);
}

void Character::RemoveItemFromInventory(const std::string& itemName) {
    inventory->RemoveItem(itemName);
}

void Character::ListInventory() const {
    inventory->ListItems();
}

void Character::EquipGear(Gear& gear) {
    inventory->EquipGear(gear);
}

void Character::UnequipGear(Gear& gear) {
    inventory->UnequipGear(gear);
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
