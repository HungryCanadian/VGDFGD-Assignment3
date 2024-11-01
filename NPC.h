#pragma once
#include "Rooms.h"



class NPC {
public:
    NPC(const string& name, const string& dialogue);

    // Method for interacting with the NPC
    void Talk() const;
    string getName();

private:
    string mName;     // Name of the NPC
    string mDialogue; // Dialogue for the NPC
    
};
