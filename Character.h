#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "AbilityScores.h" 
#include "Race.h"         
#include "Class.h"  

using std::cout;
using std::cin;



class Character {
public:
    string mName;
    Race mRace;
    Class mType;
    abilityScores mBaseScores;
    abilityScores mBonuses;
    int mHealth;
    int mDamage;

    // Parameterized constructor
    Character(const string& characterName, const Race& characterRace, const Class& characterClass, const abilityScores& scores);

    void calculateBonuses();
    void calculateHealth();
    void takeDamage(int damage);
    bool isAlive() const;
    int attack() const;
    string getName() const;
    int getHealth();
    int getAttack() const;
    void displayStats() const;

private:
    int calculateBonus(int score) const; // Declaration of the private method
};