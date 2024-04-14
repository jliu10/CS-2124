#include "Warrior.h"
#include "Noble.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace WarriorCraft {
    Noble::Noble(const string& name) : name(name), isAlive(true), strength(0) {}

    // Attempt to hire the specified warrior
    bool Noble::hire(Warrior& warrior) {
        if (warrior.isHired() || !isAlive) {
            cerr << name << " failed to hire " << 
            warrior.getName() << endl;
            return false;
        }
        warrior.setEmployed(true);
        warrior.setNoble(this);
        army.push_back(&warrior);
        strength += warrior.getStrength();
        return true;
    }

    // Fire the specified warrior
    bool Noble::fire(Warrior& warrior) {
        if (!isAlive) {
            cerr << name << " failed to fire " << 
            warrior.getName() << endl;
            return false;
        }
        size_t i = 0;
        while (i < army.size()) { 
            if ( army[i] == &warrior ) {
                break;
            }
            i++;
        }
        // Warrior not in army
        if (i >= army.size()) {
            cerr << name << " failed to fire " << 
            warrior.getName() << endl;
            return false;
        }

        // Now this must be a valid request
        // Remove the warrior from the army
        for (size_t j = i; j < army.size() - 1; j++) {
            army[j] = army[j + 1];
        }
        army.pop_back();
            
        strength -= warrior.getStrength();
        warrior.setNoble(nullptr);
        warrior.setEmployed(false);
        cout << warrior.getName() << ", you don't work for me anymore! -- " 
        << name << "." << endl;
        return true;
    }

    // Return army strength
    double Noble::getStrength() const { return strength; }

    // Return name
    const string& Noble::getName() const { return name; }

    // Scale army strength by factor (strength of each warrior)
    void Noble::scaleStrength(double factor) {
        for (Warrior* warrior : army) {
            warrior->setStrength( warrior->getStrength() * factor );
        }
        strength *= factor;
        if (factor == 0) {
            isAlive = false;
        }
    }

    // Battle with opponent
    void Noble::battle(Noble& opponent) {
        cout << name << " battles " << opponent.name << endl;
        if (strength == 0 && 
        opponent.strength == 0) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        } else if (strength == 
        opponent.strength) {
            this->scaleStrength(0);
            opponent.scaleStrength(0);
            cout << "Mutual Annihilation: " << this->name << " and " << 
            opponent.name << " die at each other's hands" << endl;
        } else if (strength == 0) {
            cout << "He's dead, " << opponent.name << endl;
        } else if (opponent.strength == 0) {
            cout << "He's dead, " << name << endl;
        } else if (strength > 
        opponent.strength) {
            scaleStrength( 1 - (opponent.strength / strength) );
            opponent.scaleStrength(0);
            cout << name << " defeats " << opponent.name << endl;
        } else {
            opponent.scaleStrength(1 - (strength / opponent.strength));
            this->scaleStrength(0);
            cout << opponent.name << " defeats " << name << endl;
        }
    }

    // Acknowledge runaway warrior
    void Noble::acknowledgeRunaway(Warrior* warrior) {
        for (size_t i = 0; i < army.size(); i++) {
            if (army[i] == warrior) {
                strength -= warrior->getStrength();
                army[i] = army[army.size() - 1];
                army.pop_back();
            }
        }
    }

    ostream& operator<<(ostream& os, const Noble& noble) {
        os << noble.name << " has an army of " << noble.army.size()
        << endl;
        for (const Warrior* warrior : noble.army) {
            cout << "\t" << *warrior;
        }
        return os;
    }
}