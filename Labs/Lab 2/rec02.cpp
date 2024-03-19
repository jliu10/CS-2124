#include <iostream>
using namespace std;
#include <fstream>
#include <utility>

struct formula {
    int numC;
    int numH;
    vector<string> names;
};

void openStream(ifstream& ifs);
void fillFormulas(ifstream& ifs, vector<formula>& formulas);
void displayVector(const vector<formula>& formulas);
void sortVector(vector<formula>& formulas);
void insertInfo(const string& name, int cNum, int hNum, vector<formula>& formulas);
const size_t findFormula(int cNum, int hNum, const vector<formula>& formulas);
void printFormula(const formula& f);

int main() {
    ifstream ifs;
    string filename;
    vector<formula> formulas;

    openStream(ifs);
    fillFormulas(ifs, formulas);

    cout << "Unsorted:" << endl;
    displayVector(formulas);
    cout << "\nSorted:" << endl;
    sortVector(formulas);
    displayVector(formulas);

    ifs.close();

    return 0;
}

void openStream(ifstream& ifs) {
    string filename;
     do {
        cout << "Enter new filename to open:" << endl;
        cin >> filename;
        ifs.open(filename);
    } while (!ifs);
}

const size_t findFormula(int cNum, int hNum, const vector<formula>& formulas) {
    for (size_t i = 0; i < formulas.size(); i++) {
        formula f = formulas[i];
        if (f.numC == cNum && f.numH == hNum) {
            return i;
        }
    }
    return formulas.size();
}

void insertInfo(const string& name, int cNum, int hNum, vector<formula>& formulas) {
    size_t i = findFormula(cNum, hNum, formulas);
    if (i < formulas.size()) {
        formulas[i].names.push_back(name);
    } else {
        // formula f{cNum, hNum};
        formula f;
        f.numC = cNum;
        f.numH = hNum;
        f.names.push_back(name);
        formulas.push_back(f);
    }
}

void fillFormulas(ifstream& ifs, vector<formula>& formulas) {
    char c;
    char h;
    int numC;
    int numH;
    string chemName;
    while(ifs >> chemName >> c >> numC >> h >> numH) {
        insertInfo(chemName, numC, numH, formulas);
        //  cout << "Inserted an entry" << endl;
    }
}

void printFormula(const formula& f) {
    // string names;
    cout << 'C' << f.numC << 'H' << f.numH << ' ';
    for (const string& name : f.names) {
        cout << name << " ";
    }
    cout << endl;
}

void displayVector(const vector<formula>& formulas) {
    for (const formula& f : formulas) {
        // cout << "Printing formula" << endl;
        printFormula(f);
    }
}

void sortVector(vector<formula>& formulas) {
    for (size_t i = 0; i < formulas.size(); i++) {
        for (size_t j = 0; j < formulas.size() - 1; j++) {
            if ((formulas[j].numC > formulas[j + 1].numC) || (formulas[j].numH > formulas[j + 1].numH)) {
                swap(formulas[j], formulas[j + 1]);
            }
        }
    }
}

/*
def bubble_sort(seq):
    """Sort the sequence in place using bubble sort"""
    for i in range(len(seq)):
# Bubble up
        for j in range(len(seq)-1):
            if (seq[j] > seq[j+1]):
                seq[j], seq[j+1] = seq[j+1], seq[j] # swap
*/