#ifndef NOBLE_H
#define NOBLE_H

#include <iostream>
#include <string>
#include <vector>

namespace WarriorCraft {
    class Warrior;

    class Noble {
        friend std::ostream& operator<<(std::ostream& os, const Noble& noble);
    public:
        Noble(const std::string& name);
        // Attempt to hire the specified warrior
        bool hire(Warrior& warrior);
        // Fire the specified warrior
        bool fire(Warrior& warrior);
        // Return army strength
        double getStrength() const;
        // Return name
        const std::string& getName() const;
        // Scale army strength by factor (strength of each warrior)
        void scaleStrength(double factor);
        // Battle with opponent
        void battle(Noble& opponent);
        // Acknowledge runaway warrior
        void acknowledgeRunaway(Warrior* warrior);
    private:
        std::string name;
        std::vector<Warrior*> army;
        bool isAlive;
        double strength;
    };
}

#endif