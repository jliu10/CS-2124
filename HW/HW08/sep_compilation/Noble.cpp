#include "Protector.h"
#include "Noble.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

namespace WarriorCraft {
    /* *** Noble definitions *** */
    Noble::Noble(const string& name, double strength) : name(name),
    alive(true), strength(strength) {}

    // Return name
    const string& Noble::getName() const { return name; }

    // Return alive
    bool Noble::getAlive() const { return alive; }

    // Set alive
    void Noble::setAlive(bool val) { alive = val; }

    // Scale strength
    void Noble::scaleStrength(double factor) {
        strength *= factor;
        if (factor == 0) {
            setAlive(false);
        }
    }

    double Noble::getStrength() const { return strength; }

    void Noble::setStrength(double newStrength) { strength = newStrength; }

    // Battle with opponent
    void Noble::battle(Noble& opponent) {
        cout << name << " battles " << opponent.name << endl;
        if (strength == 0 && 
        opponent.strength == 0) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        } else if (strength == 
        opponent.strength) {
            battleCry();
            opponent.battleCry();
            scaleStrength(0);
            opponent.scaleStrength(0);
            cout << "Mutual Annihilation: " << name << " and " << 
            opponent.name << " die at each other's hands" << endl;
        } else if (!alive) {
            opponent.battleCry();
            cout << "He's dead " << opponent.name << endl;
        } else if (!opponent.alive) {
            battleCry();
            cout << "He's dead " << name << endl;
        } else if (strength > 
        opponent.strength) {
            battleCry();
            opponent.battleCry();
            scaleStrength( 1 - (opponent.strength / strength) );
            opponent.scaleStrength(0);
            cout << name << " defeats " << opponent.name << endl;
        } else {
            battleCry();
            opponent.battleCry();
            opponent.scaleStrength(1 - (strength / opponent.strength));
            scaleStrength(0);
            cout << opponent.name << " defeats " << name << endl;
        }
    }

    /* *** Lord definitions *** */
    // Attempt to hire the specified warrior
    bool Lord::hires(Protector& prot) {
        if (prot.isHired() || !getAlive()) {
            cerr << getName() << " failed to hire " << 
            prot.getName() << endl;
            return false;
        }
        prot.setLord(this);
        army.push_back(&prot);
        setStrength(getStrength() + prot.getStrength());
        return true;
    }

    // Fire the specified warrior
    bool Lord::fires(Protector& prot) {
        if (!getAlive()) {
            cerr << getName() << " failed to fire " << 
            prot.getName() << endl;
            return false;
        }
        size_t i = 0;
        while (i < army.size()) { 
            if ( army[i] == &prot ) {
                break;
            }
            i++;
        }
        // Warrior not in army
        if (i >= army.size()) {
            cerr << getName() << " failed to fire " << 
            prot.getName() << endl;
            return false;
        }
        army.erase(army.begin() + i);

        setStrength(getStrength() - prot.getStrength());    
        prot.setLord(nullptr);
        cout << prot.getName() << ", you don't work for me anymore! -- " 
        << getName() << "." << endl;
        return true;
    }

    // Scale army strength by factor (strength of each warrior)
    void Lord::scaleStrength(double factor) {
        // cout << "Invoking Lord::scaleStrength(" << factor << ")\n";
        for (Protector* prot : army) {
            prot->setStrength( prot->getStrength() * factor );
        }
        Noble::scaleStrength(factor);
    }

    // Acknowledge runaway warrior
    void Lord::acknowledgeRunaway(Protector* prot) {
        for (size_t i = 0; i < army.size(); i++) {
            if (army[i] == prot) {
                setStrength(getStrength() - prot->getStrength());
                // army[i] = army[army.size() - 1];
                // army.pop_back();
                army.erase(army.begin() + i);
                break;
            }
        }
    }

    // Battle cry
    void Lord::battleCry() const {
        for (Protector* prot : army) {
            prot->battleCry();
        }
    }

    // Display
    void Lord::display() const {
        cout << getName() << " has an army of size: " << army.size()
        << endl;
        for (const Protector* prot : army) {
            cout << "\t" << *prot;
        }
    }

    /* *** PersonWithStrengthToFight definitions *** */
    // Battle cry
    void PersonWithStrengthToFight::battleCry() const {
        cout << "Ugh!" << endl;
    }

    // Display
    void PersonWithStrengthToFight::display() const {
        cout << getName() << " has strength: " << getStrength() << endl;
    }

    ostream& operator<<(ostream& os, const Noble& noble) {
        noble.display();
        return os;
    }
}