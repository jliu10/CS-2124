#include "Warrior.h"
#include "Noble.h"
#include <iostream>
#include <string>
using namespace std;

namespace WarriorCraft {
    Warrior::Warrior(const string& iName, double iStrength) : 
    name(iName), strength(iStrength), hired(false), noble(nullptr) {}

    // Return name
    const string& Warrior::getName() const { return name; }

    // Return strength
    double Warrior::getStrength() const { return strength; }

    // Set strength to newStrength
    void Warrior::setStrength(double newStrength) { strength = newStrength; }

    // Return employment status
    bool Warrior::isHired() const { return hired; }

    // Set employment status
    void Warrior::setEmployed(bool val) { hired = val; }

    // Set noble / employer
    void Warrior::setNoble(Noble* employer) {
        noble = employer;
    }

    // Run away from noble
    bool Warrior::runaway() {
        if (!noble) return false;

        noble->acknowledgeRunaway(this);
        cout << name << " flees in terror, abandoning his lord, "
        << noble->getName() << endl;

        hired = false;
        noble = nullptr;
        return true;
    }

    ostream& operator<<(ostream& os, const Warrior& warrior) {
        os << warrior.name << ": " << warrior.strength << endl;
        return os;
    }
}