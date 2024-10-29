#pragma once

#include "Character.h"
#include "Enemy.h"
#include "Item.h"
#include <vector>
#include <iostream>

using std::cout;
using std::cin;
using std::vector;

class Combat {
public:
	Combat(Character& player, Enemy& enemy, vector<Item>& inventory);
	void start();

private:
	Character& player;
	Enemy& enemy;
	vector<Item> inventory;

	//void handlePlayerAction(int choice); // does the player want to heal or attack?
	void enemyTurn(); // runs the enemies turn
	void useItem(); //handles all items being used.
};