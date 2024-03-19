#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <vector>

/*
  rec01_start.cpp
  spring 2024
*/


//
// Function prototypes for tasks 15-17
//

// Task 15. Function to display a vector of ints
void displayVector(const vector<int>& v);


// Task 16. Function to modify the vector, using indices
void doubleValues(vector<int>& v);


// Task 17. Function to modify the vector, using a ranged for
void doubleValues2(vector<int>& v);



//
// main
//
int main() { // Yes, it has to have an int for the return type
    //
    // Output
    //

    // Task 1. Printing hello ...  No use of "using namespace"
    std::cout << "Hello world!\n";


    // Task 2  Printing hello ...  Using "using namespace"
    cout << "Hello world!\n";


    //
    // Types and variables
    //

    // Task 3  Displaying uninitialized variable
    int x;
    cout << "x: " << x << "\n";

    
    // Task 4 Use the sizeof function to see the size in bytes of
    //        different types on your machine.
    int y = 17;
    int z = 2000000017;
    double pie = 3.14159;
    cout << "sizeof(y): " << sizeof(y) << endl;
    cout << "sizeof(z): " << sizeof(z) << endl;
    cout << "sizeof(pie): " << sizeof(pie) << endl;

    
    // Task 5  Attempt to assign the wrong type of thing to a variable
//    x = "felix";
    // Compilation error?


    //
    // Conditions
    //

    // Task 6  Testing for a range
    if (y >= 10 && y <= 20) {
        cout << "y is in [10, 20]" << endl;
    } else {
        cout << "y is not in [10, 20]" << endl;
    }
    

    //
    // Loops and files
    //

    // Task 7  Looping, printing values 10 to 20 inclusive

    // First with a for loop
    for (size_t i = 10; i <= 20; i++) {
        cout << i << endl;
    }

    // Then with a while loop
    {
        int n = 10;
        while (n <= 20) {
            cout << n << endl;
            n++;
        }
    }

    // Finally with a do-while loop
    {
        int n = 10;
        do {
            cout << n << endl;
            n++;
        } while (n <= 20);
    }


    // Task 8  Looping to successfully open a file, asking user for the name
    string filename;
    ifstream ifs;
    do {
        cout << "Provide input filename: " << endl;
        cin >> filename;
        cout << "Attempting to open: " << filename << endl;
        ifs.open(filename);
    } while (!ifs);
    

    // Task 9  Looping, reading file word by "word".
    string token;
    while (ifs >> token) {
        cout << token << endl;
    }
    ifs.close();


    // Task 10 Open a file of integers, read it in, and display the sum.
    ifs.open("integers.txt");
    if (!ifs) {
        cerr << "Failed to open integers.txt";
        exit(1);
    }
    int num;
    int sum = 0;
    while (ifs >> num) {
        sum += num;
    }
    cout << "sum: " << sum << endl;
    ifs.close();


    // Taks 11 Open and read a file of integers and words. Display the sum.
    ifs.open("mixed.txt");
    if (!ifs) {
        cerr << "Failed to open integers.txt";
    }
    int num2;
    int sum2 = 0;
    while (ifs >> num2) {
        sum2 += num2;
    }
    cout << "mixed sum: " << sum2 << endl;
    ifs.close();

    //
    // Vectors
    //

    // Task 12 Filling a vector of ints
    vector<int> ints;
    for (int n = 10; n <= 100; n += 2) {
        ints.push_back(n);
    }

    
    // Task 13 Displaying the vector THREE times
    //         a) using the indices,
    for (size_t i = 0; i < ints.size(); i++) {
        cout << ints[i] << endl;
    }

    //         b) using a "ranged for"
    for (int n : ints) {
        cout << n << endl;
    }

    //         c) using indices again but backwards
    for (size_t i = ints.size(); i > 0; i--) {
        cout << ints[i - 1] << endl;
    }
    

    // Task 14. Initialize a vector with the primes less than 20.
    vector<int> primes{2, 3, 5, 7, 11, 13, 17};
    for (int prime : primes) {
        cout << prime << endl;
    }

    //
    // Function calls
    //
    
    // Task 15  Function to print a vector
    displayVector(primes);
    
    // Task 16  Function to double the values in a vector
    doubleValues(primes);
    displayVector(primes);

    // Task 17  Function to double the values in a vector, using a ranged for
    doubleValues2(primes);
    displayVector(primes);

    // return 0;
}

//
// Function definitions for tasks 15-17
//

// Task 15. Function to display a vector of ints
void displayVector(const vector<int>& v) {
    for (int n : v) {
        cout << n << " ";
    }
    cout << endl;
}


// Task 16. Function to modify the vector, using indices
void doubleValues(vector<int>& v) {
    for (size_t i = 0; i < v.size(); i++) {
        v[i] *= 2;
    }
}


// Task 17. Function to modify the vector, using a ranged for
void doubleValues2(vector<int>& v) {
    for (int &n : v) {
        n = n * 2;
    }
}
