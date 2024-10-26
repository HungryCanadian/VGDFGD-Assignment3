#pragma once



#include <string>
#include "AbilityScores.h" // Include your AbilityScores struct

struct Race {
    std::string name;
    abilityScores abilityIncrease;

    // Constructor
    Race(const std::string& raceName, int strBonus, int dexBonus, int conBonus, int intlBonus, int wisBonus, int chaBonus);
};


