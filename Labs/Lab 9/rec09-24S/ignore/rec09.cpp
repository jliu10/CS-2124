#include <iostream>
using namespace std;

class PrintedMaterial {
    // friend ostream& operator<<(ostream& os, const PrintedMaterial& pm) {
    //     os << pm.numberOfPages;
    //     return os;
    // }
public:
    PrintedMaterial(unsigned numberOfPages = 0) : numberOfPages(numberOfPages) {}

    // virtual void displayNumPages() const { cout << numberOfPages; }
    virtual void displayNumPages() const = 0;

    unsigned getNumberOfPages() const { return numberOfPages; }
private:
    unsigned numberOfPages;
};

class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned numberOfPages = 0) : PrintedMaterial(numberOfPages) {}

    void displayNumPages() const { cout << getNumberOfPages(); }
private:
};

class Book : public PrintedMaterial {
public:
    Book(unsigned numberOfPages = 0) : PrintedMaterial(numberOfPages) {}

    void displayNumPages() const { cout << getNumberOfPages(); }
private:
};

class TextBook : public Book {
public:
    TextBook(unsigned numberOfPages = 0, unsigned numOfIndexPages = 0) : Book(numberOfPages), numOfIndexPages(numOfIndexPages) {}

    void displayNumPages() const {
        cout << "TextBook display: ";
        cout << getNumberOfPages() << " " << numOfIndexPages;
    }
private:
    unsigned numOfIndexPages;
};

class Novel : public Book {
public:
    Novel(unsigned numberOfPages = 0) : Book(numberOfPages) {}

    void displayNumPages() const { cout << getNumberOfPages(); }
private:
};

void displayNumberOfPages(PrintedMaterial& pm) {
    pm.displayNumPages();
}

// tester/modeler code
int main() {
    TextBook text;
    Novel novel;
    Magazine mag;

    text.displayNumPages();
    // cout << text;
    cout << endl;
    novel.displayNumPages();
    // cout << novel;
    cout << endl;

    // PrintedMaterial pm = text; // kind of like copying text into a vector of PrintedMaterials
    // pm.displayNumPages();
    // cout << endl;

    PrintedMaterial* pmPtr;
    pmPtr = &text;
    // instead of putting an actual PrintedMaterial
    // object into the vector, we put the address of
    // a PrintedMaterial object (text) into a vector
    // of pointers-to-PrintedMaterial
    // (that is, pointers to the Base class)
    // we'll be "managing" our objects by using
    // pointers to PrintedMaterial values.

    pmPtr->displayNumPages();
    cout << endl;

    displayNumberOfPages(text);
    cout << endl;
    displayNumberOfPages(novel);
    cout << endl;

    cout << "TASK 15" << endl;

    vector<PrintedMaterial*> vec;
    vec.push_back(&text);
    vec.push_back(&novel);
    vec.push_back(&mag);
    for (const PrintedMaterial* pm : vec) {
        pm->displayNumPages();
        cout << endl;
    }
}
