#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Item.h"
#include "Equipment.h"
class Item;

using std::vector;
using std::string;
using std::cin;

class Inventory {
public:
    void AddItem(const Item& item);
    void RemoveItem(const string& itemName);
    void ListItems() const;
    void EquipGear(Gear& gear);
    void UnequipGear(Gear& gear);
	void openInventory(); //function to open the inventory  
	vector<Gear> gearItems; //vector to store gear items

    Gear* GetGearByIndex(int index); //get gear by index
    int getGearCount() const; //return the number of gear items

private:
    vector<Item> items;
    vector<Gear> equippedGear; // specifically for gear that is equipped
};