#pragma once


#include <iostream>
#include <string>
#include "AbilityScores.h" // Include your AbilityScores struct

using std::string;

struct Race {
    string name;
    abilityScores abilityIncrease;

    // Constructor
    Race(const string& raceName, int strBonus, int dexBonus, int conBonus, int intlBonus, int wisBonus, int chaBonus);
};


