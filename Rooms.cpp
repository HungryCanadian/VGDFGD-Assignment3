#include "Rooms.h"
#include "character.h"
#include "Inventory.h"

Room::Room(string name, string description, bool locked)
	: mName(name), mDescription(description), mLocked(locked), mFirstVisit(true) { }

void Room::AddExit(Room* room) {
	mExits.push_back(room);
}

vector<Room*> Room::GetExits() {
	return mExits;
}

int Room::GetNumberOfExits() {
	return mExits.size();
}

void Room::ListExits() {
	//Check and make sure we actually have exits
	if (mExits.size() > 0) {
		//if we do
			//loop through those exits and display their names
		cout << "You see the following exits: \n";
		for (int i = 0; i < mExits.size(); i++)
			cout << i + 1 << ". " << mExits[i]->GetName() << "\n";
	}
	else {
		//else
			//display "There are no exits!"
		cout << "There is no escape!\n";
	}
	//Generates a blank line 
	cout << "\n";


}

string Room::GetName() {
	return mName;
}

void Room::DisplayRoom() {
	cout << mName << "\n";
	cout << "-----------------------\n";
	cout << mDescription << "\n";

	//List the number of exits
	ListExits();



	//TODO
	//List any/all Entities in the room
	//List whether or not the room is locked.
}

bool Room::IsFirstVisit() {
	if (mFirstVisit) {
		mFirstVisit = false; // Set to false after first visit
		return true; // Indicate this is the first visit
	}
	return false; // Indicate this is not the first visit
}

void Room::HandlePlayerAction() {
	Inventory inventory; // Create an inventory object	
	while (true) {
		cout << "\nWhat would you like to do?\n";
		cout << "[1] Open Inventory\n";
		cout << "[2] Move to another room\n"; // Placeholder for moving
		cout << "[3] Check room description\n";
		cout << "[4] Exit room\n"; // For breaking the loop

		int choice;
		cin >> choice;

		switch (choice) {
		case 1: // Open inventory
			inventory.openInventory(); // Call the inventory function
			break;
		case 2:
			ListExits();
			// Logic to move to another room can go here
			break;
		case 3:
			DisplayRoom(); // Show room description
			break;
		case 4:
			return; // Exit the action loop
		default:
			cout << "Invalid choice. Please try again.\n";
			break;
		}
	}
}