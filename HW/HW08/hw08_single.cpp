/*
  CS2124 hw08.cpp
 */

#include <string>
#include <vector>
#include <iostream>
#include <cassert>
using namespace std;

class Protector;
class Wizard;
class Warrior;
class Archer;
class Swordsman;

class Noble;
class Lord;
class PersonWithStrengthToFight;

class Protector {
    friend ostream& operator<<(ostream& os, const Protector& prot);
public:
    Protector(const string& name, double strength);
    // Return name
    const string& getName() const;
    // Return strength
    double getStrength() const;
    // Set strength to newStrength
    void setStrength(double newStrength);
    // Return employment status
    bool isHired() const;
    // Set noble / employer
    void setLord(Lord* lord);
    // Run away from noble
    bool runaway();
    // Battle cry
    virtual void battleCry() const = 0;
    // Get name of lord
    const string& getLordName() const;
private:
    string name;
    double strength;
    Lord* lord;
};

class Wizard : public Protector {
public:
    using Protector::Protector;
    void battleCry() const;
};

class Warrior : public Protector {
public:
    using Protector::Protector;
    void battleCry() const;
};

class Archer : public Warrior {
public:
    using Warrior::Warrior;
    void battleCry() const;
};

class Swordsman : public Warrior {
public:
    using Warrior::Warrior;
    void battleCry() const;
};

class Noble {
    friend ostream& operator<<(ostream& os, const Noble& noble);
public:
    Noble(const string& name, double strength = 0);
    // Battle with opponent
    void battle(Noble& opponent);
    virtual void display() const = 0;
    // Return name
    const string& getName() const;
    bool getAlive() const;
    void setAlive(bool val);
    virtual void scaleStrength(double factor);
    double getStrength() const;
    void setStrength(double newStrength);
    virtual void battleCry() const = 0;
private:
    string name;
    double strength;
    bool alive;
};

class Lord : public Noble {
public:
    using Noble::Noble;
    // Display to output
    void display() const;
    // Attempt to hire the specified protector
    bool hires(Protector& prot);
    // Fire the specified protector
    bool fires(Protector& prot);
    // Scale army strength by factor (strength of each warrior)
    void scaleStrength(double factor);
    // Acknowledge runaway warrior
    void acknowledgeRunaway(Protector* prot);
    // Battle cry
    void battleCry() const;
private:
    vector<Protector*> army;
};

class PersonWithStrengthToFight : public Noble {
public:
    using Noble::Noble;
    // Display to output;
    void display() const;
    // Battle cry
    void battleCry() const;
};

//
// Test Code
//
int main() {
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250); 	
    Lord janet("Janet");	
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);	
    janet.hires(stout);	
    janet.hires(samantha);     // fails because samantha works for sam.
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);	
    cout << "\n==========\nNobles: \n"
	 << sam << endl
	 << randy << endl
	 << janet << endl
	 << barclay << endl
	 << joe << endl
	 << "\n==========\n";
    joe.battle(randy);	            // joe has no army and dies.
    joe.battle(sam);	            // joe is dead
    janet.battle(barclay);          // barclay wins
    Archer pethora("Pethora", 50);	
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);          // janet is dead, so can't hire
    sam.hires(thora);              // sam brings in reinforcements
    sam.hires(pethora);
    sam.hires(merlin);
    janet.battle(barclay);	   // Silly janet
    sam.battle(barclay);           // Go Sam!
    samantha.runaway();            // Samantha has had enough
    sam.fires(thora);              // These layoffs! Sam fires thora.
    joe.battle(barclay);           // They're both dead already

    cout << "\n==========\nNobles: \n"
	 << sam << endl
	 << randy << endl
	 << janet << endl
	 << barclay << endl
	 << joe << endl
	 << "==========\n";
} // main

////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////

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