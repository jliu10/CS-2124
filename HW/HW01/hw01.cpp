/**
 * hw01.cpp
 * Justin Liu
 * Demonstrate understanding of vectors, strings and functions in C++
**/

#include <iostream>
using namespace std;
#include <fstream>

char decryptChar(char ch, const int dist);
void decryptString(string &str, const int dist);
int mod(int n, const int x);

int main() {
    ifstream inn("encrypted.txt");
    if (!inn) {
        cerr << "Failed to open encrypted.txt";
        exit(1);
    }

    vector<string> lines;
    string line;

    // Get encryption rotation distance
    int dist;
    inn >> dist;

    // Avoid taking in the extra '\n'
    string garbage;
    getline(inn, garbage);

    // Read file lines into vector
    while (getline(inn, line)) {
        lines.push_back(line);
    }
    inn.close();

    // Decrypt each line in the reversed order of lines
    for (size_t i = lines.size(); i > 0; i--) {
        line = lines[i - 1];
        decryptString(line, dist);
        cout << line << endl;
    }

    return 0;
}

/**
 * Compute the modulus of integers n and x, including when n < 0
 **/
int mod(const int n, const int x) {
    if (n >= 0) return n % x;
    else {
        return x - (-n % x);
    }
}

/**
 * First, write a function that takes an encrypted character and the rotation
 * distance, and returns the corresponding decrypted character. Note that only
 * UPPERcase characters will result in a change. For all other characters, this
 * function will return the input value. (Note that the function's return type
 * will need to be char.)
 **/
char decryptChar(char ch, const int dist) {
    if (ch < 65 or ch > 90) return ch;
    else {
        ch = mod((ch - 65 - dist), 26) + 65;
        return ch;
    }
}

/**
 * Second, write a function that takes a string and the rotation distance. It
 * will modify the string that is passed in, using the above function, changing
 * the character in the string into its unencrypted form. Note that unlike in
 * some languages strings in C++ are mutable, meaning that we can directly
 * change their contents. This function is passed the string to be modified
 * along with the rotation distance and changes the string in place. It does
 * not return anything, i.e. it has a void return type.
 **/
void decryptString(string &str, const int dist) {
    for (size_t i = 0; i < str.size(); i++) {
        str[i] = decryptChar(str[i], dist);
    }
}