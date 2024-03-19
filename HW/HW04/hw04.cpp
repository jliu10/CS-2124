/*
  hw04.cpp
  Association: Noble - Warrior
  Test code for hw04
 */

#include <iostream>
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
               // if ( army[i]->getName() == warrior.getName() ) {
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
          cout << name << " battles " << opponent.getName() << endl;
          if (strength == 0 && 
            opponent.getStrength() == 0) {
               cout << "Oh, NO! They're both dead! Yuck!" << endl;
          } else if (strength == 
            opponent.getStrength()) {
               this->scaleStrength(0);
               opponent.scaleStrength(0);
               cout << "Mutual Annihilation: " << this->name << " and " << 
               opponent.getName() << " die at each other's hands" << endl;
          } else if (strength == 0) {
               cout << "He's dead, " << opponent.getName() << endl;
          } else if (opponent.getStrength() == 0) {
               cout << "He's dead, " << name << endl;
          } else if (strength > 
            opponent.getStrength()) {
               scaleStrength( 1 - (opponent.getStrength() / strength) );
               opponent.scaleStrength(0);
               cout << name << " defeats " << opponent.getName() << endl;
          } else {
               opponent.scaleStrength(1 - (strength / opponent.getStrength()));
               this->scaleStrength(0);
               cout << opponent.getName() << " defeats " << name << endl;
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

int main() {
	
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");
	
    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);
	
    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
    art.hire(nimoy);
	
    cout << "==========\n\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n\n";
	
    art.fire(cheetah);
    cout << art << endl;

    lance.fire(nimoy);
    cout << lance << endl;
    cout << "==========\n\n";

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";
	
}
