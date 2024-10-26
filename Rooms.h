#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "Enemy.h" // Include if Enemy class is in a separate file

using namespace std;

struct Room {
    string name;
    string description;
    vector<string> exits; // Names of rooms that can be accessed
    void (*action)(); // Pointer to function for room-specific actions

    Room(const string& roomName, const string& roomDesc, const vector<string>& roomExits, void (*roomAction)());
};

// Function prototypes
void exploreTown();
void visitGeneralStore();
void visitBlacksmith();
void visitOutskirts();

// Room instances
extern Room generalStore;
extern Room blacksmith;
extern Room outskirts;
extern Room townSquare;

// Room collection
extern vector<Room> rooms;

