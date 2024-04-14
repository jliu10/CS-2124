/*
  hw07_single.cpp
  hw07: cyclic association and separate compilation
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Warrior;

class Noble;

class Warrior {
    friend ostream& operator<<(ostream& os, const Warrior& warrior);
public:
    Warrior(const string& iName, double iStrength);

    // Return name
    const string& getName() const;

    // Return strength
    double getStrength() const;

    // Set strength to newStrength
    void setStrength(double newStrength);

    // Return employment status
    bool isHired() const;

    // Set employment status
    void setEmployed(bool val);

    // Set noble / employer
    void setNoble(Noble* noble);

    // Run away from noble
    bool runaway();

private:
    string name;
    double strength;
    bool hired;
    Noble* noble;
};

class Noble {
    friend ostream& operator<<(ostream& os, const Noble& noble);
public:
    Noble(const string& name);

    // Attempt to hire the specified warrior
    bool hire(Warrior& warrior);

    // Fire the specified warrior
    bool fire(Warrior& warrior);

    // Return army strength
    double getStrength() const;

    // Return name
    const string& getName() const;

    // Scale army strength by factor (strength of each warrior)
    void scaleStrength(double factor);

    // Battle with opponent
    void battle(Noble& opponent);

    // Acknowledge runaway warrior
    void acknowledgeRunaway(Warrior* warrior);

private:
    string name;
    vector<Warrior*> army;
    bool isAlive;
    double strength;
};

int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 4);
    Warrior sky("Leia", 6);
    Warrior wizard("Merlin", 9);
    Warrior jaffa("Teal'c", 9);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(jaffa);
    art.hire(cheetah);
    art.hire(wizard);
    art.hire(sky);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(nimoy);

    cout << "================ Initial Status ===============" << endl;
    cout << art << endl
	 << lance << endl
	 << jim << endl
	 << linus << endl
	 << billie << endl;
    cout << "===============================================\n\n";

    art.fire(cheetah);
    wizard.runaway();
    cout << endl << art << endl;

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "\n================ Final Status ===============" << endl;
    cout << art << endl
	 << lance << endl
	 << jim << endl
	 << linus << endl
	 << billie << endl;

    // Tarzan and Merlin should be unemployed
    cout << "Tarzan's Hire Status: " << boolalpha 
	 << cheetah.isHired() << endl;
    cout << "Merlin's Hire Status: " << boolalpha 
	 << wizard.isHired() << endl;
    cout << "===============================================\n\n";

}

/* *** Warrior definitions *** */
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

/* *** Noble definitions *** */
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