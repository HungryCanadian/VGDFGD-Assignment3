#include "CharacterClass.h"

// Constructor implementation
CharacterClass::CharacterClass(const std::string& className, int health)
    : name(className), defaultHealth(health) {}

string CharacterClass::getName() {
    return name;
}