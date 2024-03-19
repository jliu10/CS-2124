/**
 * hw02.cpp
 * Justin Liu
 * Demonstrate understanding of functions, structs, vectors and file I/O.
 * We will model a game of medieval times. Our world is filled with warriors.
 * Naturally what warriors like to do is fight. To the death. So we happily let
 * them.
**/

#include <fstream>
#include <iostream>
using namespace std;

struct Warrior {
    string name;
    int strength;
};

// PROTOTYPES HERE
void openFile(ifstream& ifs, const string& filename);
void readAndExecuteCommands(ifstream& ifs, vector<Warrior>& warriors);
void addWarrior(const string& name, int strength, vector<Warrior>& warriors);
void battle(const string& name1, const string& name2, vector<Warrior>& warriors);
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

/**
 * Open file
 **/
void openFile(ifstream& ifs, const string& filename) {
    ifs.open(filename);
    if (!ifs) {
        cerr << "Could not open: " << filename << endl;
    }
}

/**
 * Read and execute commands from file
 **/
void readAndExecuteCommands(ifstream& ifs, vector<Warrior>& warriors) {
    string cmd;
    string name1;
    string name2;
    int strength;
    while (ifs >> cmd) {
        if (cmd == "Warrior") {
            ifs >> name1 >> strength;
            addWarrior(name1, strength, warriors);
        } else if (cmd == "Battle") {
            ifs >> name1 >> name2;
            battle(name1, name2, warriors);
        } else if (cmd == "Status") {
            status(warriors);
        }
    }
}

/**
 * Get index of warrior if in list, else return size of list
 **/
size_t getWarrior(const string& name, const vector<Warrior>& warriors) {
    for (size_t i = 0; i < warriors.size(); i++) {
        if (warriors[i].name == name) {
            return i;
        }
    }
    return warriors.size();
}

/**
 * Add new warrior to warriors if there isn't already one with the same name
 **/
void addWarrior(const string& name, int strength, vector<Warrior>& warriors) {
    const size_t i = getWarrior(name, warriors);
    if (i < warriors.size()) {
        cerr << name << " already exists!" << endl;
    } else {
        const Warrior warrior = {name, strength};
        warriors.push_back(warrior);
    }
}

/**
 * Battle the two warriors if possible
 **/
void battle(const string& name1, const string& name2, vector<Warrior>& warriors) {
    const size_t i1 = getWarrior(name1, warriors);
    const size_t i2 = getWarrior(name2, warriors);
    if (i1 >= warriors.size() || i2 >= warriors.size()) {
        cerr << "Battle failed because one or both warriors don't exist!" << endl;
    } else {
        cout << name1 << " battles " << name2 << endl;
        Warrior& warrior1 = warriors[i1];
        Warrior& warrior2 = warriors[i2];
        if (warrior1.strength == 0 && warrior2.strength == 0) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        } else if (warrior1.strength == warrior2.strength) {
            warrior1.strength = 0;
            warrior2.strength = 0;
            cout << "Mutual Annihilation: " << name1 << " and " << name2 << " die at each other's hands" << endl;
        } else if (warrior1.strength == 0) {
            cout << "He's dead, " << name2 << endl;
        } else if (warrior2.strength == 0) {
            cout << "He's dead, " << name1 << endl;
        } else if (warrior1.strength > warrior2.strength) {
            warrior1.strength -= warrior2.strength;
            warrior2.strength = 0;
            cout << name1 << " defeats " << name2 << endl;
        } else {
            warrior2.strength -= warrior1.strength;
            warrior1.strength = 0;
            cout << name2 << " defeats " << name1 << endl;
        }
    }
}

/**
 * Display status of current warriors
 **/
void status(const vector<Warrior>& warriors) {
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for (const Warrior& warrior : warriors) {
        cout << "Warrior: " << warrior.name << ", strength: " << warrior.strength << endl;
    }
}