#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Character.h"
#include "Item.h"
#include "Equipment.h"


using std::vector;
using std::string;

class Inventory {
public:
    void AddItem(const Item& item);
    void RemoveItem(const string& itemName);
    void ListItems() const;
    void EquipGear(Gear& gear);
    void UnequipGear(Gear& gear);

private:
    vector<Item> items;
    vector<Gear> equippedGear; // specifically for gear that is equipped
};