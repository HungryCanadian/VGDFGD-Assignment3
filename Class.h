#pragma once


#include <string>

struct Class {
    std::string name;
    int defaultHealth;

    // Constructor
    Class(const std::string& className, int health);
};


