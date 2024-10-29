#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "AbilityScores.h" 
#include "Race.h"         
#include "CharacterClass.h"
#include "Item.h"
#include "Equipment.h"


class Inventory;


using std::cout;
using std::cin;



class Character {
public:

    abilityScores mBaseScores;
    abilityScores mBonuses;


    // Parameterized constructor
    Character(const string& characterName, const Race& characterRace, const CharacterClass& characterClass, const abilityScores& scores);

    void calculateBonuses();
    void calculateHealth();
    void takeDamage(int damage);
    bool isAlive() const;
    int attack() const;
    string getName() const;
    int getHealth();
    int getMaxHealth();
    int heal(int amount);
    int getAttack() const;
    void displayStats() const;
    void EquipGear(Gear& gear); // To equip armor
    void UnequipGear(Gear& gear); // To unequip armor
    void addDamageReduction(int amount); // To add to damage reduction
    void removeDamageReduction(int amount); // To remove from damage reduction
    void AddItemToInventory(const Item& item); // Method to add an item
    void RemoveItemFromInventory(const std::string& itemName); // Method to remove an item
    void ListInventory() const; // Method to list items in inventory


private:
    Inventory* inventory;
    int totalDamageReduction = 0;
    int calculateBonus(int score) const;
    int mHealth;
    int mDamage;
    int mMaxHealth;
    string mName;
    Race mRace;
    CharacterClass mType;
};