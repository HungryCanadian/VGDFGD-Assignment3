#pragma once

#include <iostream>
#include <string>

using std::string;

struct Class {
    string name;
    int defaultHealth;


    // Constructor
    Class(const string& className, int health);
};


