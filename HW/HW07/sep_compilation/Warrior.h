#ifndef WARRIOR_H
#define WARRIOR_H

#include <iostream>
#include <string>

namespace WarriorCraft {
    class Noble;

    class Warrior {
        friend std::ostream& operator<<(std::ostream& os, 
        const Warrior& warrior);
    public:
        Warrior(const std::string& iName, double iStrength);
        // Return name
        const std::string& getName() const;
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
        std::string name;
        double strength;
        bool hired;
        Noble* noble;
    };
}

#endif