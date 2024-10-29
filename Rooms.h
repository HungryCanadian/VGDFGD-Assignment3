#pragma once
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::cout;

class Room {
public:
	Room(string name = "Empty Room", string description = "This is an empty room.", bool locked = false);
	void AddExit(Room* roomToAdd);
	vector<Room*> GetExits();
	int GetNumberOfExits();
	void ListExits();

	void DisplayRoom();
	string GetName();
	bool IsFirstVisit();

	//AddEntity(Entity* entity);
	//vector<Entity*> GetEntities();
	//void ListEntities();

private:
	string mName;
	string mDescription;
	//TODO
	//add a vector of entitities that will store any/all entities (NPCs/Enemies) that are in this room.
	vector<Room*> mExits;


	//Extra detail --> impliment if time allows, but not REQUIRED
	bool mLocked;
	bool mFirstVisit;

};



//vector of Entities
//Vector of Doors/exits
//some kind of lock (boolean)