#ifndef NOBLE_H
#define NOBLE_H

#include <string>
#include <vector>
#include <iostream>

namespace WarriorCraft {
    class Protector;

    class Noble {
        friend std::ostream& operator<<(std::ostream& os, const Noble& noble);
    public:
        Noble(const std::string& name, double strength = 0);
        // Battle with opponent
        void battle(Noble& opponent);
        virtual void display() const = 0;
        // Return name
        const std::string& getName() const;
        bool getAlive() const;
        void setAlive(bool val);
        virtual void scaleStrength(double factor);
        double getStrength() const;
        void setStrength(double newStrength);
        virtual void battleCry() const = 0;
    private:
        std::string name;
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
        std::vector<Protector*> army;
    };

    class PersonWithStrengthToFight : public Noble {
    public:
        using Noble::Noble;
        // Display to output;
        void display() const;
        // Battle cry
        void battleCry() const;
    };
}

#endif