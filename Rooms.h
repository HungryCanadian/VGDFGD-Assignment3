#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Character.h"


using std::string;
using std::vector;
using std::cout;
class Inventory;
class NPC;	

class Room {
public:
	Room(string name = "Empty Room", string description = "This is an empty room.", bool mFirstVisit = true, float = 0.0);
	
	
	void AddExit(Room* roomToAdd);
	void AddNPC(NPC* npc);
	vector<Room*> GetExits();
	int GetNumberOfExits();
	void ListExits();
	void HandlePlayerAction(Room* room, Character& player, Inventory& inventory);
	void DisplayRoom(Character& player, Inventory& inventory);
	string GetName();
	bool IsFirstVisit();
	Room* ChooseExit();
	Room* createTown();
	void InteractWithNPCs();
	vector<NPC*> GetNPCs();
	void HandleAttack(Character& player, Inventory& inventory);


private:
	string mName;
	string mDescription;
	vector<Room*> mExits;
	float mAttackChance;
	vector<NPC*> mNPCs;
	bool mFirstVisit;

};



//vector of Entities
//Vector of Doors/exits
//some kind of lock (boolean)