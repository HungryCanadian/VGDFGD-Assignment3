#include "Enemy.h"

// Constructor
Enemy::Enemy(const string& name, int damage, int health, int gold, int experience)
    : mName(name), mDamage(damage), mHealth(health), mGold(gold), mExperience(experience) {}

// Attack method
int Enemy::Attack() const {
    cout << "Attack inflicts " << mDamage << " damage." << endl;
    return mDamage;
}

// Taunt method
void Enemy::Taunt() const {
    cout << "The enemy taunts, making you target them!\n";
}

// Method to take damage
void Enemy::takeDamage(int damage) {
    mHealth -= damage;
    if (mHealth < 0) {
        mHealth = 0; // Ensure health does not go below zero
    }
    cout << mName << " takes " << damage << " damage! Remaining health: " << mHealth << endl;
}

// Check if enemy is alive
bool Enemy::isAlive() const {
    return mHealth > 0;
}

int Enemy::getGold() const {
	return mGold;
}

int Enemy::getExp() const {
	return mExperience;
}

// Getter for the enemy's name
string Enemy::getName() const {
    return mName;
}

// Getter for the enemy's health
int Enemy::getHealth() const {
    return mHealth;
}

// Getter for the enemy's attack damage
int Enemy::getAttack() const {
    return mDamage;
}
