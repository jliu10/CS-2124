/**
 * Justin Liu
 * rec04.cpp
 */

#include <iostream>
using namespace std;

class Colour {  
public:       
    Colour(const string& name, unsigned r, unsigned g, unsigned b)       
        : name(name), r(r), g(g), b(b) {}       
    void display() const { 
        cout << name << " (RBG: " << r << "," << g<< "," << b << ")"; 
    }   
private:       
    string name;      // what we call this colour       
    unsigned r, g, b; // red/green/blue values for displaying  
};

int main() {
    int x;
    x = 10;
    cout << "x = " << x << endl;

    int* p;
    p = &x;
    // p = 0x000000016fdff268;
    cout << "p = " << p << endl;

    cout << "p points to where " << *p << " is stored\n";
    cout << "*p contains " << *p << endl;

    *p = -2763;  
    cout << "p points to where " << *p << " is stored\n";  
    cout << "*p now contains " << *p << endl;  
    cout << "x now contains " << x << endl;

    int y(13);      
    cout << "y contains " << y << endl;      
    p = &y;      
    cout << "p now points to where " << *p << " is stored\n";      
    cout << "*p now contains " << *p << endl;      
    *p = 980;      
    cout << "p points to where " << *p << " is stored\n";      
    cout << "*p now contains " << *p << endl;      
    cout << "y now contains " << y << endl;

    int* q;      
    q = p;      
    cout << "q points to where " << *q << " is stored\n";      
    cout << "*q contains " << *q << endl;

    double d(33.44);      
    double* pD(&d);      
    *pD = *p;      
    *pD = 73.2343;      
    *p  = *pD;      
    *q  = *p;      
    // pD  = p;
    // p   = pD;

    int joe = 24;  
    const int sal = 19;    
    int*  pI;  
    pI = &joe;  
    *pI = 234;  
    // pI = &sal;  // pI points to an int, so it cannot point to a const int
    // *pI = 7623;    

    // const int* pcI;
    // pcI = &joe;  
    // *pcI = 234;  // pcI is points to a const int, so it makes the value that it has a const int, which is 24. Thus we cannot change the value
    // pcI = &sal;  
    // *pcI = 7623; // Same as above.   

    // int* const cpI; // This is a const pointer to an int, and all const varables must be initialized as declaration
    // int* const cpI(&joe);
    // int* const cpI(&sal); // We declared the type to be a const pointer to a regular int, while sal is a const int
    // cpI = &joe;  // cpI is a constant variable, so we cannot reassign it after initialization
    // *cpI = 234;  
    // cpI = &sal;  // Same as above
    // *cpI = 7623;    

    // const int* const cpcI; // Again this is a const pointer, so it must be initialized at declaration
    // const int* const cpcI(&joe);
    // const int* const cpcI(&sal);
    // cpcI = &joe; // cpcI is a const pointer, so it cannot be reassigned
    // *cpcI = 234; // cpcI points to a const int, so the value cannot be reassigned
    // cpcI = &sal; // Same as 2 lines above
    // *cpcI = 7623; // Same as 2 lines above

    struct Complex {
        double real;
        double img;
    };
    Complex c = {11.23,45.67};      
    Complex* pC(&c);
    cout << "real: " << (*pC).real << "\nimaginary: " << (*pC).img << endl;
    cout << "real: " << pC->real << "\nimaginary: " << pC->img << endl;

    class PlainOldClass {
    public:
        PlainOldClass() : x(-72) {}
        int getX() const { return x; }
        void setX( int x )  { this->x = x; }
    private:
        int x;
    };

    PlainOldClass poc;
    PlainOldClass* ppoc( &poc );
    cout << ppoc->getX() << endl;
    ppoc->setX( 2837 );
    cout << ppoc->getX() << endl;

    int* pDyn = new int(3); // p points to an int initialized to 3 on the heap      
    *pDyn = 17;
    int* pDyn2 = pDyn;

    cout << "The " << *pDyn
     << " is stored at address " << pDyn
     << " which is in the heap\n";

    cout << pDyn << endl;  
    delete pDyn;  
    pDyn = nullptr;
    cout << pDyn << endl;

    cout << "The 17 might STILL be stored at address " << pDyn2<< " even though we deleted pDyn\n";  
cout << "But can we dereference pDyn?  We can try.  This might crash... " << *pDyn2 << ".  Still here?\n";

    double* pDouble = nullptr;

    // cout << "Can we dereference nullptr?  " << *pDyn << endl;      
    // cout << "Can we dereference nullptr?  " << *pDouble << endl;

    double* pTest = new double(12);      
    delete pTest;      
    pTest = nullptr;      
    // delete pTest; // safe

    short* pShrt = new short(5);      
    delete pShrt;      
    // delete pShrt;

    long jumper = 12238743;      
    // delete jumper;
    long* ptrTolong = &jumper;      
    // delete ptrTolong;  // What happens here?      
    Complex cmplx;      
    // delete cmplx;      // What happens here?

    vector<Complex*> complV; // can hold pointers to Complex objects
    Complex* tmpPCmplx;      // space for a Complex pointer
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        tmpPCmplx = new Complex; // create a new Complex object on the heap
        tmpPCmplx->real = ndx;   // set real and img to be the
        tmpPCmplx->img  = ndx;   // value of the current ndx
        complV.push_back(tmpPCmplx); // store the ADDRESS of the object in a vector or pointer to Complex
    }      
    // display the objects using the pointers stored in the vector
    for (size_t ndx = 0; ndx < 3; ++ndx) {         
        cout << complV[ ndx ]->real << endl;         
        cout << complV[ ndx ]->img  << endl;      
    }      
    // release the heap space pointed at by the pointers in the vector      
    for (size_t ndx = 0; ndx < 3; ++ndx) {         
        delete complV[ndx];
    }      
    // clear the vector      
    complV.clear();

    vector<Colour*> colours;         
    string inputName;       
    unsigned inputR, inputG, inputB;

    // fill vector with Colours from the file       
    // this could be from an actual file but here we are using the keyboard instead of a file
    // (so we don't have to create an actual file)
    // Do you remember the keystroke combination to indicate "end of file" at the keyboard?
    // somehow the while's test has to fail - from keyboard input
    while (cin >> inputName >> inputR >> inputG >> inputB) {
        colours.push_back(new Colour(inputName, inputR, inputG, inputB));       
    }         

    // display all the Colours in the vector:       
    for (size_t ndx = 0; ndx < colours.size(); ++ndx) {            
        colours[ndx]->display();            
        cout << endl;       
    }


    class SpeakerSystem {
       public:
       void vibrateSpeakerCones(unsigned signal) const {
          cout << "Playing: " << signal << "Hz sound..." << endl;
          cout << "Buzz, buzzy, buzzer, bzap!!!\n";
       }
    };

    class Amplifier {
    public:
      void attachSpeakers(const SpeakerSystem& spkrs)
       {
          if(attachedSpeakers) {
             cout << "already have speakers attached!\n";
          } else {
            attachedSpeakers = &spkrs;
          }
       }
      
       void detachSpeakers() { // should there be an "error" message if not attached?
          attachedSpeakers = nullptr; 
       } 
      
       void playMusic( ) const {
          if (attachedSpeakers) {
             attachedSpeakers -> vibrateSpeakerCones(440); 
          } else {
             cout << "No speakers attached\n";
          } 
       }
    private:
       const SpeakerSystem* attachedSpeakers = nullptr;
    };


    class Person {  
    public:       
        Person(const string& name) : name(name) {}
        void movesInWith(Person& newRoomate) {
            if (!newRoomate.roomie && &newRoomate != this) // Check if newRoomate already has a roomie and is not myself
            roomie = &newRoomate;        // now I have a new roomie            
            newRoomate.roomie = this;    // and now they do too       
        }       
        const string& getName() const { return name; }
        // Don't need to use getName() below, just there for you to use in debugging.
        const string& getRoomiesName() const { return roomie->getName(); }  
    private:
        Person* roomie = nullptr;       
        string name;  
    };           

    // write code to model two people in this world       
    Person joeBob("Joe Bob"), billyJane("Billy Jane");         

    // now model these two becoming roommates       
    joeBob.movesInWith(billyJane);         

    // did this work out?       
    cout << joeBob.getName() << " lives with " << joeBob.getRoomiesName() << endl;
    cout << billyJane.getName() << " lives with " << billyJane.getRoomiesName() << endl;


    return 0;
}