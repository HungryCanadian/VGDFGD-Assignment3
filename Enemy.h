#pragma once

#include <string>
#include <iostream>
using namespace std;

class Enemy {
protected:
    string mName;
    int mDamage;
    int mHealth;

public:
    Enemy(const string& name, int damage = 1, int health = 10);

    void Attack() const;
    void Taunt() const;
    void takeDamage(int damage);
    bool isAlive() const;

    // Getter for the enemy's name
    string getName() const;

    // Getter for the enemy's health
    int getHealth() const;

    // Getter for the enemy's attack damage
    int getAttack() const;
};