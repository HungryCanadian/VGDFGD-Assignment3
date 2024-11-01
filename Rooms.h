#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Character.h"

using std::string;
using std::vector;
using std::cout;
class Inventory;

class Room {
public:
	Room(string name = "Empty Room", string description = "This is an empty room.", bool mFirstVisit = true, float = 0.0);
	void AddExit(Room* roomToAdd);
	vector<Room*> GetExits();
	int GetNumberOfExits();
	void ListExits();
	void HandlePlayerAction(Room* room,Character& player, Inventory& inventory);
	void handleRoomEvents(Room* currentRoom, Character& player, Inventory inventory);
	void DisplayRoom(Character& player, Inventory& inventory);
	string GetName();
	bool IsFirstVisit();
	Room* ChooseExit();
	Room* createTown();
	void HandleAttack(Character& player, Inventory& inventory);

	//AddEntity(Entity* entity);
	//vector<Entity*> GetEntities();
	//void ListEntities();

private:
	string mName;
	string mDescription;
	//TODO
	//add a vector of entitities that will store any/all entities (NPCs/Enemies) that are in this room.
	vector<Room*> mExits;
	float mAttackChance;


	//Extra detail --> impliment if time allows, but not REQUIRED
	bool mFirstVisit;

};



//vector of Entities
//Vector of Doors/exits
//some kind of lock (boolean)