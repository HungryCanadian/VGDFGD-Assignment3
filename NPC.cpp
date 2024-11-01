#include "NPC.h"

// Constructor implementation
NPC::NPC(const string& name, const string& dialogue)
    : mName(name), mDialogue(dialogue) {}

// Method implementation for talking to the NPC
void NPC::Talk() const {
    cout << mName << " says: " << mDialogue << "\n";
}

string NPC::getName() {
    return mName;
}