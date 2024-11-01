#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Item.h"
#include <algorithm> // For std::any_of
#include "Equipment.h"
#include "Character.h"


class Item;
class Gear;

using std::vector;
using std::string;
using std::cin;



class Inventory {
public:
    void AddItem(Gear& gear);
    void RemoveItem(Gear& gear);
    void ListGearItems() const;
    void decreaseQuantity(const string& itemName, int howMany);
    void increaseQuantity(const string& itemName, int howMany);
    vector<Item>& getItems();
    vector<Item>& getInv();
    vector<Gear> getGearItems();
    vector<Gear> getEquippedGear();
    vector<Gear> getEquipment();
    void EquipGear(Gear& gear, Character& player);
    void UnequipGear(Gear& gear, Character& player);
	void openInventory(Character& player); //function to open the inventory  
    void ListEquippedItems(Character& player);
    Gear* GetGearByIndex(int index); //get gear by index
    int getGearCount() const; //return the number of gear 
	void displayShopInventory(Character& player); //display the shop inventory   
	void displayBlacksmithInventory(Character& player); //display the blacksmith inventory
	void displayPlayerInventory(); //display the player inventory   
	int getGoldQuantity() const; //get the gold quantity  
	void increaseGold(Character& player,int amount); //increase the gold quantity   
	void decreaseGold(Character& player,int amount); //decrease the gold quantity   
    int sellEquipItem(Character& player,int index); //sell the equipment items
	void runBlacksmith(Character& player); //run the blacksmith
	void runGeneralStore(Character& player); //run the general store 
	int sellGeneralItem(Character& player,int index); //sell the general items  
	int purchaseEquipItem(Character& player,int index); //purchase the equipment items 
	int purchaseGeneralItem(Character& player,int index); //purchase the general items    

private:
 //   vector<Item> items; // specifically for items that are not gear
 //   vector<Gear> gearItems; // specifically for gear that is not equipped
 //   vector<Gear> equippedGear; // specifically for gear that is equipped
 //   vector<Item> inv; //vector to hold the inventory
	//vector<Gear> equipment; //vector to hold the equipment
};