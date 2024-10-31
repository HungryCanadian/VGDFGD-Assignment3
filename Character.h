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
class Gear;


using std::cout;
using std::cin;
using std::vector;



class Character {
public:

    abilityScores mBaseScores;
    abilityScores mBonuses;
    //make a default constructor
    Character() : mBaseScores(0, 0, 0, 0, 0, 0), mBonuses(0, 0, 0, 0, 0, 0), mHealth(0), mDamage(0), mMaxHealth(0), mName(""), mRace("", 0, 0, 0, 0, 0, 0), mType("", 0), inventory(nullptr) {}
    // Parameterized constructor
    Character(const string& characterName, const Race& characterRace,
        const CharacterClass& characterClass, const abilityScores& scores,
        int level = 1, int experience = 0, int expToLevel = 100, int gold = 150);

    void calculateBonuses();
    void calculateHealth();
    void takeDamage(int damage);
    bool isAlive() const;
    int attack() const;
    string getName() const;
    int getHealth();
    int getMaxHealth();
	int getExp();
	void addDamageReduction(int amount);
    void removeDamageReduction(int amount);
	int getGold();
	int addGold(int amount);
	int subtractGold(int amount);
    int heal(int amount);
    //void toggleEquip(Gear& gear);
    int getAttack() const;
    void displayStats() const;
    void Levelup();
    void EquipGear(Gear& gear); // To equip armor
    void UnequipGear(Gear& gear); // To unequip armor
    void AddItemToInventory(Gear& gear); // Method to add an item
    void RemoveItemFromInventory(Gear& gear); // Method to remove an item
    void ListInventory() const; // Method to list items in inventory
	int getTotalDamageReduction() const; // Method to get total damage reduction
    const vector<Gear>& getGearItems() const;
    int addExp(int amount);
  


private:
    Inventory* inventory;
    int calculateBonus(int score) const;
    int totalDamageReduction;
    int mHealth;
    int mDamage;
    int mMaxHealth;
    int mGold = 150;
	int mExperience = 0;
	int mExpToLevel = 100;
    int mLevel = 1;
    string mName;
    Race mRace;
    CharacterClass mType;
	vector<Gear> equippedGear;
};