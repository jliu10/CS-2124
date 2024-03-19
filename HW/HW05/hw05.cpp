/*
  hw05.cpp
  hw05: dynamic memory
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// Warrior class
class Warrior {
    friend ostream& operator<<(ostream& os, const Warrior& warrior);
public:
    Warrior(const string& iName, double iStrength) : 
    name(iName), strength(iStrength), isEmployed(false) {}

    // Return name
    const string& getName() const { return name; }

    // Return strength
    double getStrength() const { return strength; }

    // Set strength to newStrength
    void setStrength(double newStrength) { strength = newStrength; }

    // Return employment status
    bool getEmployed() const { return isEmployed; }

    // Set employment status
    void setEmployed(bool val) { isEmployed = val; }

private:
    string name;
    double strength;
    bool isEmployed;
};

ostream& operator<<(ostream& os, const Warrior& warrior) {
    os << warrior.name << ": " << warrior.strength << endl;
    return os;
}


// Noble class
class Noble {
     friend ostream& operator<<(ostream& os, const Noble& noble);
public:
     Noble(const string& name) : name(name), isAlive(true), strength(0) {}

     // Attempt to hire the specified warrior
     bool hire(Warrior& warrior) {
          if (warrior.getEmployed() || !isAlive) {
               cerr << name << " failed to hire " << 
               warrior.getName() << endl;
               return false;
          }
          warrior.setEmployed(true);
          army.push_back(&warrior);
          strength += warrior.getStrength();
          return true;
     }

     // Fire the specified warrior
     bool fire(Warrior& warrior) {
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
          if (i < army.size() ) {
               for (size_t j = i; j < army.size() - 1; j++) {
                    army[j] = army[j + 1];
               }
               army.pop_back();
          }        
          strength -= warrior.getStrength();
          warrior.setEmployed(false);
          cout << warrior.getName() << ", you don't work for me any more! -- " 
          << name << endl;
     }

     // Return army strength
     double getStrength() const { return strength; }

     // Return name
     const string& getName() const { return name; }

     // Scale army strength by factor (strength of each warrior)
     void scaleStrength(double factor) {
          for (Warrior* warrior : army) {
               warrior->setStrength( warrior->getStrength() * factor );
          }
          strength *= factor;
          if (factor == 0) {
               isAlive = false;
          }
     }

     // Battle with opponent
     void battle(Noble& opponent) {
          cout << name << " battles " << opponent.name << endl;
          if (strength == 0 && 
            opponent.getStrength() == 0) {
               cout << "Oh, NO! They're both dead! Yuck!" << endl;
          } else if (strength == 
            opponent.getStrength()) {
               this->scaleStrength(0);
               opponent.scaleStrength(0);
               cout << "Mutual Annihilation: " << this->name << " and " << 
               opponent.name << " die at each other's hands" << endl;
          } else if (strength == 0) {
               cout << "He's dead, " << opponent.name << endl;
          } else if (opponent.getStrength() == 0) {
               cout << "He's dead, " << name << endl;
          } else if (strength > 
            opponent.getStrength()) {
               scaleStrength( 1 - (opponent.getStrength() / strength) );
               opponent.scaleStrength(0);
               cout << name << " defeats " << opponent.name << endl;
          } else {
               opponent.scaleStrength(1 - (strength / opponent.getStrength()));
               this->scaleStrength(0);
               cout << opponent.name << " defeats " << name << endl;
          }
     }

private:
     string name;
     vector<Warrior*> army;
     bool isAlive;
     double strength;
};

ostream& operator<<(ostream& os, const Noble& noble) {
     os << noble.name << " has an army of " << noble.army.size()
     << endl;
     for (const Warrior* warrior : noble.army) {
          cout << "\t" << *warrior;
     }
     return os;
}

// PROTOTYPES HERE
void openFile(ifstream& ifs, const string& filename);
void readAndExecuteCommands(ifstream& ifs, vector<Warrior*>& warriors,  
    vector<Noble*>& nobles);
void addWarrior(const string& name, int strength, vector<Warrior*>& warriors);
void addNoble(const string& name, vector<Noble*>& nobles);
void status(const vector<Warrior*>& warriors, const vector<Noble*>& nobles);
Warrior* getWarrior(const string& name, const vector<Warrior*>& warriors);
Noble* getNoble(const string& name, const vector<Noble*>& nobles);
void clear(vector<Warrior*>& warriors, vector<Noble*>& nobles);

int main() {
    vector<Noble*> nobles;
    vector<Warrior*> warriors;

    ifstream ifs;
    openFile(ifs, "nobleWarriors.txt");
    readAndExecuteCommands(ifs, warriors, nobles);
    ifs.close();
	
    return 0;
}

/* Attempt to open file */
void openFile(ifstream& ifs, const string& filename) {
    ifs.open(filename);
    if (!ifs) {
        cerr << "Could not open: " << filename << endl;
        exit(1);
    }
}

/* Read and execute commands from file */
void readAndExecuteCommands(ifstream& ifs, vector<Warrior*>& warriors,  
    vector<Noble*>& nobles) {
    string cmd;
    string name1;
    string name2;
    int strength;
    while (ifs >> cmd) {
        if (cmd == "Noble") {
            ifs >> name1;
            if (getNoble(name1, nobles)) cerr << name1 << 
                " is already a noble!" << endl;
            else addNoble(name1, nobles);
        }
        else if (cmd == "Warrior") {
            ifs >> name1 >> strength;
            if (getWarrior(name1, warriors)) cerr << name1 << 
                " is already a warrior!" << endl;
            else addWarrior(name1, strength, warriors);
        }
        else if (cmd == "Hire") {
            ifs >> name1 >> name2;
            Noble* noble = getNoble(name1, nobles);
            Warrior* warrior = getWarrior(name2, warriors);
            if (!noble || !warrior) {
                cerr << "Attempting to hire using unknown ";
                if (!noble) cerr << "noble: " << name1 << endl;
                else cerr << "warrior: " << name2 << endl;
            }
            else noble->hire(*warrior);
        }
        else if (cmd == "Fire") {
            ifs >> name1 >> name2;
            Noble* noble = getNoble(name1, nobles);
            Warrior* warrior = getWarrior(name2, warriors);
            if (!noble) cerr << "Firing failed: noble " << 
                name1 << " doesn't exist!" << endl;
            else if (!warrior) cerr << "Firing failed: warrior " << 
                name2 << " doesn't exist!" << endl;
            else noble->fire(*warrior);
        }
        else if (cmd == "Battle") {
            ifs >> name1 >> name2;
            Noble* noble1 = getNoble(name1, nobles);
            Noble* noble2 = getNoble(name2, nobles);
            if (!noble1 || !noble2) {
                cerr << "Battle failed: either " << name1 << " or " << name2 <<
                    " doesn't exist" << endl;
            }
            else noble1->battle(*noble2);
        }
        else if (cmd == "Status") {
            status(warriors, nobles);
        }
        else if (cmd == "Clear") {
            clear(warriors, nobles);
        }
    }
}

/* Create and add new warrior to vector */
void addWarrior(const string& name, int strength, vector<Warrior*>& warriors) {
    warriors.push_back(new Warrior(name, strength));
}

/* Create and add new noble to vector */
void addNoble(const string& name, vector<Noble*>& nobles) {
    nobles.push_back(new Noble(name));
}

/* Display status */
void status(const vector<Warrior*>& warriors, const vector<Noble*>& nobles) {
    int count = 0;
    cout << "Status\n======\nNobles:\n";
    for (const Noble* noble : nobles) {
        cout << *noble;
        count++;
    }
    if (count == 0) cout << "NONE" << endl;

    count = 0;
    cout << endl << "Unemployed Warriors:\n";
    for (const Warrior* warrior : warriors) {
        if (!(warrior->getEmployed())) {
            cout << "\t" << *warrior;
            count++;
        }
    }
    if (count == 0) cout << "NONE" << endl;
    cout << endl;
}

/* Return pointer to first warrior with name, otherwise null */
Warrior* getWarrior(const string& name, const vector<Warrior*>& warriors) {
    for (size_t i = 0; i < warriors.size(); i++) {
        if (warriors[i]->getName() == name) {
            return warriors[i];
        }
    }
    return nullptr;
}

/* Return pointer to first noble with name, otherwise null */
Noble* getNoble(const string& name, const vector<Noble*>& nobles) {
    for (size_t i = 0; i < nobles.size(); i++) {
        if (nobles[i]->getName() == name) {
            return nobles[i];
        }
    }
    return nullptr;
}

/* Clear warrior and noble vectors */
void clear(vector<Warrior*>& warriors, vector<Noble*>& nobles) {
    for (size_t i = 0; i < nobles.size(); i++) {
        delete nobles[i];
    }
    nobles.clear();
    for (size_t i = 0; i < warriors.size(); i++) {
        delete warriors[i];
    }
    warriors.clear();
}