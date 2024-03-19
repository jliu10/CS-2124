/**
 * hw03.cpp
 * Justin Liu
 * Demonstrate understanding of data hiding, encapsulation, delegation,
 * and overloading the output operator.
**/

#include <fstream>
#include <iostream>
using namespace std;

// Warrior class
class Warrior {
    friend ostream& operator<<(ostream& os, const Warrior& warrior);
private:
    // Weapon class
    class Weapon {
        friend ostream& operator<<(ostream& os, const Weapon& weapon);
    public:
        Weapon(const string& iName, int iStrength) : name(iName),
        strength(iStrength) {}

        // Return strength
        int getStrength() const { return strength; }

        // Set strength to newStrength
        void setStrength(int newStrength) { strength =  newStrength; }
    private:
        string name;
        int strength;
    };
    friend ostream& operator<<(ostream& os, const Warrior::Weapon& weapon);
public:
    Warrior(const string& iName, const string& weaponName, int strength) : 
    name(iName), weapon(weaponName, strength) {}

    // Return name
    const string& getName() const { return name; }

    // Return weapon strength
    int getWeaponStrength() const { return weapon.getStrength(); }

    // Set weapon strength to newStrength
    void setWeaponStrength(int newStrength) { weapon.setStrength(newStrength); }

    // Battle the two warriors if possible
    void battle(const string& name, vector<Warrior>& warriors) {
        // Try to find first warrior
        size_t i1 = 0;
        while (i1 < warriors.size()) {
            if (warriors[i1].getName() == this->name) {
                break;
            }
            i1++;
        }
        // Try to find second warrior
        size_t i2 = 0;
        while (i2 < warriors.size()) {
            if (warriors[i2].getName() == name) {
                break;
            }
            i2++;
        }

        if (i1 >= warriors.size() || i2 >= warriors.size()) {
            cerr << "Battle failed because one or both warriors don't exist!" 
            << endl;
        } else {
            cout << this->name << " battles " << name << endl;
            Warrior& warrior1 = warriors[i1];
            Warrior& warrior2 = warriors[i2];
            if (warrior1.getWeaponStrength() == 0 && 
            warrior2.getWeaponStrength() == 0) {
                cout << "Oh, NO! They're both dead! Yuck!" << endl;
            } else if (warrior1.getWeaponStrength() == 
            warrior2.getWeaponStrength()) {
                warrior1.setWeaponStrength(0);
                warrior2.setWeaponStrength(0);
                cout << "Mutual Annihilation: " << this->name << " and " << 
                name << " die at each other's hands" << endl;
            } else if (warrior1.getWeaponStrength() == 0) {
                cout << "He's dead, " << name << endl;
            } else if (warrior2.getWeaponStrength() == 0) {
                cout << "He's dead, " << this->name << endl;
            } else if (warrior1.getWeaponStrength() > 
            warrior2.getWeaponStrength()) {
                warrior1.setWeaponStrength(warrior1.getWeaponStrength() - 
                warrior2.getWeaponStrength());
                warrior2.setWeaponStrength(0);
                cout << this->name << " defeats " << name << endl;
            } else {
                warrior2.setWeaponStrength(warrior2.getWeaponStrength() - 
                warrior1.getWeaponStrength());
                warrior1.setWeaponStrength(0);
                cout << name << " defeats " << this->name << endl;
            }
        }
    }

private:
    string name;
    Weapon weapon;
};

ostream& operator<<(ostream& os, const Warrior& warrior) {
    os << "Warrior: " << warrior.name << ", " << warrior.weapon;
    return os;
}

ostream& operator<<(ostream& os, const Warrior::Weapon& weapon) {
    os << "weapon: " << weapon.name << ", " << weapon.strength;
    return os;
}

// PROTOTYPES HERE
void openFile(ifstream& ifs, const string& filename);
void readAndExecuteCommands(ifstream& ifs, vector<Warrior>& warriors);
void addWarrior(const string& name, const string& weaponName, int strength, 
vector<Warrior>& warriors);
void status(const vector<Warrior>& warriors);
size_t getWarrior(const string& name, const vector<Warrior>& warriors);

int main() {
    ifstream ifs;
    const string filename = "warriors.txt";
    vector<Warrior> warriors;
    openFile(ifs, filename);
    readAndExecuteCommands(ifs, warriors);
    ifs.close();
}

// Open file
void openFile(ifstream& ifs, const string& filename) {
    ifs.open(filename);
    if (!ifs) {
        cerr << "Could not open: " << filename << endl;
    }
}

// Read and execute commands from file
void readAndExecuteCommands(ifstream& ifs, vector<Warrior>& warriors) {
    string cmd;
    string name1;
    string name2;
    string weaponName;
    int strength;
    while (ifs >> cmd) {
        if (cmd == "Warrior") {
            ifs >> name1 >> weaponName >> strength;
            addWarrior(name1, weaponName, strength, warriors);
        } else if (cmd == "Battle") {
            ifs >> name1 >> name2;
            size_t index = getWarrior(name1, warriors);
            warriors[index].battle(name2, warriors);
        } else if (cmd == "Status") {
            status(warriors);
        }
    }
}

// Get index of warrior if in list, else return size of list
size_t getWarrior(const string& name, const vector<Warrior>& warriors) {
    for (size_t i = 0; i < warriors.size(); i++) {
        if (warriors[i].getName() == name) {
            return i;
        }
    }
    return warriors.size();
}

// Add new warrior to warriors if there isn't already one with the same name
void addWarrior(const string& name, const string& weaponName, int strength, 
vector<Warrior>& warriors) {
    const size_t i = getWarrior(name, warriors);
    if (i < warriors.size()) {
        cerr << name << " already exists!" << endl;
    } else {
        warriors.emplace_back(name, weaponName, strength);
    }
}

// Display status of current warriors
void status(const vector<Warrior>& warriors) {
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for (const Warrior& warrior : warriors) {
        cout << warrior << endl;
    }
}