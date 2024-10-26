#include "AbilityScores.h"

// Constructor implementation
abilityScores::abilityScores(int str, int dex, int con, int intl, int wis, int cha)
    : strength(str), dexterity(dex), constitution(con), intelligence(intl), wisdom(wis), charisma(cha) {}

// Method implementation to apply racial bonuses
void abilityScores::applyRaceBonuses(const abilityScores& raceBonus) {
    strength += raceBonus.strength;
    dexterity += raceBonus.dexterity;
    constitution += raceBonus.constitution;
    intelligence += raceBonus.intelligence;
    wisdom += raceBonus.wisdom;
    charisma += raceBonus.charisma;
}
