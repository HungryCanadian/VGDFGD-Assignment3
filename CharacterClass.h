#pragma once

#include <iostream>
#include <string>

using std::string;

struct CharacterClass {
    string name;
    int defaultHealth;


    // Constructor
    CharacterClass(const string& className, int health);
};


