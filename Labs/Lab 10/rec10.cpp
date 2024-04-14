/*
  rec10_start.cpp
  Starting code 23S
 */

#include <iostream>
#include <vector>
using namespace std;

class Instrument {
    friend ostream& operator<<(ostream& os, const Instrument& ins) {
        ins.display();
        return os;
    }
public:
    virtual void makeSound() const = 0;
    virtual void display() const = 0;
    virtual void play() const = 0;
};

void Instrument::makeSound() const {
    cout << "To make a sound... ";
}

class Brass : public Instrument {
public:
    Brass(unsigned size) : size(size) {}
    
    void makeSound() const {
        Instrument::makeSound();
        cout << "blow on a mouthpiece of size " << size << endl;
    }

    void display() const {
        cout << ": " << size;
    }
private:
    unsigned size;
};

class String : public Instrument {
public:
    String(unsigned pitch) : pitch(pitch) {}

    void makeSound() const {
        Instrument::makeSound();
        cout << "bow a string with pitch " << pitch << endl;
    }

    void display() const {
        cout << ": " << pitch;
    }
private:
    unsigned pitch;
};

class Percussion : public Instrument {
public:
    void makeSound() const {
        Instrument::makeSound();
        cout << "hit me!" << endl;
    }
};

class Trumpet : public Brass {
public:
    using Brass::Brass;

    void display() const { 
        cout << "Trumpet";
        Brass::display();
    }

    void play() const { cout << "Toot"; }
};

class Trombone : public Brass {
public:
    using Brass::Brass;

    void display() const {
        cout << "Trombone";
        Brass::display();
    }

    void play() const { cout << "Blat"; }
};

class Violin : public String {
public:
    using String::String;

    void display() const {
        cout << "Violin";
        String::display();
    }

    void play() const { cout << "Screech"; }
};

class Cello : public String {
public:
    using String::String;

    void display() const {
        cout << "Cello";
        String::display();
    }

    void play() const { cout << "Squawk"; }
};

class Drum : public Percussion {
public:
    using Percussion::Percussion;

    void display() const { cout << "Drum"; }

    void play() const { cout << "Boom"; }
};

class Cymbal : public Percussion {
public:
    using Percussion::Percussion;

    void display() const { cout << "Cymbal"; }

    void play() const { cout << "Crash"; }
};

class MILL {
    friend ostream& operator<<(ostream& os, const MILL& mill) {
        os << "The MILL has the following instruments: ";
        if (!mill.size) os << "None" << endl;
        else {
            for (const Instrument* ins : mill.instruments) {
                if (ins != nullptr) os << "\t" << *ins << endl;
            }
        }
        return os;
    }
public:
    MILL() : size(0) {}

    void receiveInstr(Instrument& ins) {
        ins.makeSound();
        bool placed = false;
        for (size_t i = 0; i < instruments.size(); i++) {
            if (instruments[i] == nullptr) {
                instruments[i] = &ins;
                placed = true;
                break;
            }
        }
        if (!placed) instruments.push_back(&ins);
        size++;
    }

    void dailyTestPlay() const {
        for (const Instrument* ins : instruments) {
            if (ins != nullptr) ins->makeSound();
        }
    }

    Instrument* loanOut() {
        for (size_t i = 0; i < instruments.size(); i++) {
            if (instruments[i] != nullptr) {
                Instrument* ip = instruments[i];
                instruments[i] = nullptr;
                size--;
                return ip;
            }
        }
        return nullptr;
    }
private:
    vector<Instrument*> instruments;
    unsigned int size;
};

// 
// Musician class as provided to the students. Requires an Instrument class.
// 

class Musician {
public:
    Musician(const string& name) : instr(nullptr), name(name) {}

    // acceptInstr takes in an instrument for the Musician to later play.
    //  "loses" any instrument that it used to have.
    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    // giveBackInstr: gives the instrument that the Musicial was holding "back"
    Instrument* giveBackInstr() { 
        Instrument* result(instr); 
        instr = nullptr;
        return result;
    }

    // testPlay: testing out my instrument
    void testPlay() const {
        if (instr) instr->makeSound(); 
        else cerr << name << " has no instr\n";
    }

    // play: play the instrument

    //   Not making it const so that Instrument::play method does not
    //   need to be const. Allows the instrument to be modifed in the
    //   process of being played.
    void play() {
        if (instr) instr->play();
        // Don't do anything if we don't have an instrument.
    }
private:
    Instrument* instr;
    string name;
};

class Orch {
public:
    void addPlayer(Musician& musc) {
        roster.push_back(&musc);
    }

    void play() const {
        for (Musician* musc : roster) musc->play();
        cout << endl;
    }
private:
    vector<Musician*> roster;
};

int main() {

    //
    // PART ONE
    //
    cout << "P A R T  O N E\n";

    cout << "Define some instruments ---------------------------------------\n";
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12) ;
    Violin violin(567) ;
  
    cout << "Define the MILL -----------------------------------------------\n";
    MILL mill;
    cout << "The MILL before adding instruments:\n" << mill << "\n\n";

    cout << "Put the instruments into the MILL -----------------------------\n";
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);
    cout << "\nThe MILL after adding some instruments:\n" << mill << "\n\n";
  
    cout << "Daily test ----------------------------------------------------\n"
	 << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    cout << "Define some Musicians------------------------------------------\n";
    Musician harpo("Harpo");
    Musician groucho("Groucho");
  	
    cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
    groucho.testPlay();	 // Groucho doesn't have an instrument yet.

    groucho.acceptInstr(mill.loanOut());
    groucho.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    groucho.testPlay();	
    mill.receiveInstr(*groucho.giveBackInstr());
    harpo.acceptInstr(mill.loanOut());
    groucho.acceptInstr(mill.loanOut());
    groucho.testPlay();
    harpo.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();

    cout << "\nThe MILL after giving out some instruments:\n";
    cout << mill << "\n\n";

    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
    mill.receiveInstr(*groucho.giveBackInstr());

    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());
    cout << endl;

    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
  
    cout << "\nThe MILL at the end of Part One:\n";
    cout << mill << endl;

    //
    // PART TWO
    //
    cout << "\nP A R T  T W O\n";
    
    Musician bob("Bob");
    Musician sue("Sue");
    Musician mary("Mary");
    Musician ralph("Ralph");
    Musician jody("Judy");
    Musician morgan("Morgan");

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
	
    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    cout << endl << mill << endl;
}