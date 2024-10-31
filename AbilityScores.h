#pragma once

struct abilityScores {
    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;


    // Default constructor initializing all scores to 10
    abilityScores()
        : strength(10), dexterity(10), constitution(10),
        intelligence(10), wisdom(10), charisma(10) {}

    // Parameterized constructor
    abilityScores(int str, int dex, int con, int intl, int wis, int cha);
 
    // Method to apply racial bonuses
    void applyRaceBonuses(const abilityScores& raceBonus);
};


