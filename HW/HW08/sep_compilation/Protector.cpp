#include "Protector.h"
#include "Noble.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

namespace WarriorCraft {
    /* *** Protector definitions *** */
    Protector::Protector(const string& name, double strength) : 
        name(name), strength(strength), lord(nullptr) {}

    // Return name
    const string& Protector::getName() const { return name; }

    // Return strength
    double Protector::getStrength() const { return strength; }

    // Set strength to newStrength
    void Protector::setStrength(double newStrength) { strength = newStrength; }

    // Return employment status
    bool Protector::isHired() const { return (lord) ? true : false; }

    // Set noble / employer
    void Protector::setLord(Lord* employer) {
        lord = employer;
    }

    // Run away from noble
    bool Protector::runaway() {
        if (!lord) return false;

        lord->acknowledgeRunaway(this);
        cout << name << " flees in terror, abandoning his lord, "
        << lord->getName() << endl;

        lord = nullptr;
        return true;
    }

    const string& Protector::getLordName() const { return lord->getName(); }

    ostream& operator<<(ostream& os, const Protector& Protector) {
        os << Protector.name << " has strength " << Protector.strength << endl;
        return os;
    }

    /* *** Wizard definitions *** */
    // Battle cry
    void Wizard::battleCry() const {
        cout << "POOF!" << endl;
    }

    /* *** Warrior definitions *** */
    // Battle cry
    void Warrior::battleCry() const {
        cout << getName() << " says: Take that in the name of my lord, "
        << getLordName() << endl;
    }

    /* *** Archer definitions *** */
    void Archer::battleCry() const {
        cout << "TWANG!  ";
        Warrior::battleCry();
    }

    /* *** Swordsman definitions *** */
    void Swordsman::battleCry() const {
        cout << "CLANG!  ";
        Warrior::battleCry();
    }
}