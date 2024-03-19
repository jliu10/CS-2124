/*
  rec06_begin.cpp
  CS2124
 
  Focus: Dynamic arrays and copy control
 */

#include <string>
#include <iostream>
using namespace std;

// 
// Position class
// 
class Position {
    friend ostream& operator<<(ostream& os, const Position& rhs)
    {
        os << '[' << rhs.title << ',' << rhs.salary << ']';
        return os;
    } // Position op<<
public:
    Position(const string& aTitle, double aSalary)
        : title(aTitle), salary(aSalary) {}
    const string& getTitle() const { return title; }
    double getSalary() const { return salary; }
    void changeSalaryTo(double d) { salary = d; }
private:
    string title;
    double salary;
}; // class Position


// 
// Directory class
// 
class Directory {
    // 
    // nested Entry class
    // 
    class Entry {
	friend ostream& operator<<(ostream& os, const Entry& rhs)
        {
	    os << rhs.name << ' ' << rhs.room
	       << ' ' << rhs.phone << ", " << *rhs.pos;
	    return os;
	} // Entry op<<
    public:
	Entry(const string& name, unsigned room, unsigned phone, Position& position)
	    : name(name), room(room), phone(phone), pos(&position) {
	}
	const string& getName() const { return name; }
	unsigned getPhone() const { return phone; }
    private:
	string name;
	unsigned room;
	unsigned phone;
	Position* pos;
    }; // class Entry


    // Overload Directory's output operator
    friend ostream& operator<<(ostream& os, const Directory& dir) {
        os << "Directory: " << dir.company << endl;
        for (size_t i = 0; i < dir.size; i++) {
            os << *(dir.entries[i]) << endl;
        }
        return os;
    }


public:
    // Of course the first function you need to write for this (or
    // any) class is...
    Directory(const string& name) : company(name), size(0), capacity(0), entries(new Entry*[0]) {}
    
    ~Directory() {
        cout << "DESTRUCTOR ACTIVATED!!!!" << endl;
        for (size_t i = 0; i < size; i++) {
            delete entries[i];
        }
        delete [] entries;
    }

    Directory(const Directory& dir) : company(dir.company){
        cout << "COPY CONSTRUCTOR ACTIVATED!!!!" << endl;
        entries = new Entry*[ dir.capacity ];
        capacity = dir.capacity;
        size = dir.size;
        for (size_t i = 0; i < dir.size; i++) {
            entries[i] = new Entry( *(dir.entries[i]) );
        }
    }

    Directory& operator=(const Directory& dir) {
        cout << "OPERATOR= ACTIVATED!!!!" << endl;
        if (this != &dir) {
            for (size_t i = 0; i < size; i++) {
                delete entries[i];
            }
            delete [] entries;
            entries = new Entry* [ dir.capacity ];
            size = dir.size;
            company = dir.company;
            capacity = dir.capacity;
            for (size_t i = 0; i < dir.size; i++) {
                entries[i] = new Entry( *(dir.entries[i]) );
            }
        }
        return *this;
    }

    unsigned operator[](const string& name) const {
        for (size_t i = 0; i < size; i++) {
            if (entries[i]->getName() == name) { 
                return entries[i]->getPhone(); 
            }
        }
        // cerr << "Error: could not find " << name << "'s phone" << endl;
        return 999999999;
    }
    
    // We'll get you started with the add method, but obviously you
    // have a lot of work to do here.
    void add(const string& name, unsigned room, unsigned ph, Position& pos) {
        if (size == capacity)	{
            if (size == 0) {
                delete [] entries;
                entries = new Entry*[1];
                capacity = 1;
            }
            else {
                const int new_capacity = capacity * 2;
                Entry** new_entries = new Entry*[new_capacity];
                for (size_t i = 0; i < size; i++) {
                    new_entries[i] = entries[i];
                }
                delete [] entries;
                entries = new_entries;
                capacity = new_capacity;
            }
        } // if
        entries[size] = new Entry(name, room, ph, pos);
        ++size;
    } // add

    //
    // === Copy Control ===
    //
    // (get checked out on everything else before starting this)
    

private:	
    Entry** entries; // Notice the type!!! Pointer to Entry pointers.
    size_t size;
    size_t capacity;
    string company;
}; // class Directory


void doNothing(Directory dir)
{ 
    // You need to overload the Directory output operator before
    // uncommenting the next line.

    cout << dir << endl;
} // doNothing

int main()
{
	
    // Note that the Postion objects are NOT on the heap.
    Position boss("Boss", 3141.59);
    Position pointyHair("Pointy Hair", 271.83);
    Position techie("Techie", 14142.13);
    Position peon("Peonissimo", 34.79);
	
    // Create a Directory
    Directory d("HAL");
    // Add someone
    d.add("Marilyn", 123, 4567, boss);
    // print the directory
    cout << d << endl;
    // Use the square bracket operator, aka the Index operator,
    // to access someone's phone extension.
    cout << "d[\"Marilyn\"]: " << d["Marilyn"] << endl;
    cout << "======\n\n";

    // Everything working so far? Get checked out!!!

    Directory d2 = d;	// What function is being used??
    d2.add("Gallagher", 111, 2222, techie);
    d2.add("Carmack", 314, 1592, techie);
    cout << "Directory d:\n" << d << endl;
    cout << "Directory d2:\n" << d2 << endl;

    cout << "Calling doNothing\n";
    doNothing(d2);
    cout << "Back from doNothing\n";

    // Should display 1592
    cout << d2["Carmack"] << endl;

    Directory d3("IBM");
    d3.add("Torvalds", 628, 3185, techie);
    d3.add("Ritchie", 123, 5813, techie);
    

    d2 = d3;
    // Should display 5813
    cout << d2["Ritchie"] << endl;

    cout << d2 << endl;
} // main
