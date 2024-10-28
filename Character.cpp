#include "Character.h"


// Constructor implementation
Character::Character(const string& characterName, const Race& characterRace, const Class& characterClass, const abilityScores& scores)
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
}

void Character::takeDamage(int damage) {
    mHealth -= damage;
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

int Character::getAttack() const {
    return mDamage;
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
