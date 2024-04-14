#ifndef PROTECTOR_H
#define PROTECTOR_H

#include <string>
#include <vector>
#include <iostream>

namespace WarriorCraft {
    class Lord;

    class Protector {
        friend std::ostream& operator<<(std::ostream& os, const Protector& prot);
    public:
        Protector(const std::string& name, double strength);
        // Return name
        const std::string& getName() const;
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
        const std::string& getLordName() const;
    private:
        std::string name;
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
}

#endif