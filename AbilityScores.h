#pragma once

struct abilityScores {
    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;


    // Constructor
    abilityScores(int str, int dex, int con, int intl, int wis, int cha);

    // Method to apply racial bonuses
    void applyRaceBonuses(const abilityScores& raceBonus);
};


