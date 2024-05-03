// rec13_start.cpp

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

/* Task 9 */
void iterPrint(const list<int>& lst) {
    for (list<int>::const_iterator it = lst.begin(); it != lst.end(); ++it) {
        cout << *it << " ";
    }
}

/* Task 10 */
void rangedForPrint(const list<int>& lst) {
    for (const int& n : lst) cout << n << " ";
}

/* Task 12 */
auto listFind(const list<int>& lst, int target) {
// list<int>::const_iterator listFind(const list<int>& lst, int target) {
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        if (*it == target) return it;
    }
    return lst.end();
}

/* Task 15 */
bool isEven(const int& n) { return n % 2 == 0; }

/* Task 16 */
struct isEvenFunctor {
    bool operator() (const int& n) { return n % 2 == 0; }
};

/* Task 19 */
list<int>::const_iterator ourFind(list<int>::const_iterator begin, list<int>::const_iterator end, int target) {
    cout << "In the template !!!\n";
    for (list<int>::const_iterator it = begin; it != end; ++it) {
        if (*it == target) return it;
    }
    return end;
}

/* Task 20 */
template<class T, class C>
C ourFind(C begin, C end, T target) {
    cout << "In the template !!!\n";
    for (C it = begin; it != end; ++it) {
        if (*it == target) return it;
    }
    return end;
}

int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    vector<int> v1 = {2,1,4,3};
    for (const int& n : v1) cout << n << " ";

    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    list<int> l1(v1.begin(), v1.end());
    for (const int& n : l1) cout << n << " ";

    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(v1.begin(), v1.end());
    for (const int& n : v1) cout << n << " ";
    cout << endl;
    for (const int& n : l1) cout << n << " ";

    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    for (size_t i = 0; i < v1.size(); i+=2) cout << v1[i] << " ";

    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
    // for (size_t i = 0; i < l1.size(); i+=2) cout << l1[i] << " ";

    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";
    for (vector<int>::iterator it = v1.begin(); it != v1.end(); it+=2) {
        cout << *it << " ";
    }

    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    for (list<int>::iterator it = l1.begin(); it != l1.end(); ++++it) {
        cout << *it << " ";
        // ++it;
    }

    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";
    l1.sort();
    for (const int& n : l1) cout << n << " ";

    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    iterPrint(l1);

    cout << "\n=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    rangedForPrint(l1);

    cout << "\n=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    for (auto it = l1.begin(); it != l1.end(); ++it) {
        cout << *it << " ";
        ++it;
    }

    cout << "\n=======\n";

    
    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    cout << *(listFind(l1, 3));

    cout << "\n=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    cout << *(listFind(l1, 3));

    cout << "\n=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    cout << *(find(l1.begin(), l1.end(), 3));

    cout << "\n=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    cout << *(find_if(l1.begin(), l1.end(), isEven));

    cout << "\n=======\n";

    // 16. Functor
    cout << "Task 16:\n";
    isEvenFunctor functor;
    cout << *(find_if(l1.begin(), l1.end(), functor));
    cout << *(find_if(l1.begin(), l1.end(), isEvenFunctor()));
    cout << "\n=======\n";
    
    // 17. Lambda
    cout << "Task 17:\n";
    cout << *(find_if(l1.begin(), l1.end(), [] (const int& n) { return n % 2 == 0; }));

    cout << "\n=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int* arr1 = new int[4];
    copy(v1.begin(), v1.end(), arr1);
    find(arr1, arr1 + 4, 1);
    for (size_t i = 0; i < 4; i++) { cout << arr1[i] << " "; }

    cout << "\n=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    cout << *(ourFind(l1.begin(), l1.end(), 4));

    cout << "\n=======\n";
    
    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    cout << *(ourFind(v1.begin(), v1.end(), 4)) << endl;
    cout << *(ourFind(l1.begin(), l1.end(), 4));

    cout << "\n=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    ifstream inn;
    inn.open("pooh-nopunc.txt");
    vector<string> tokens;
    string token;
    while (inn >> token) {
        if (find(tokens.begin(), tokens.end(), token) == tokens.end()) {
            tokens.push_back(token);
        }
    }
    inn.close();

    for (const string& str : tokens) {
        cout << str << endl;
    }
    cout << "Size: " << tokens.size();

    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";
    inn.open("pooh-nopunc.txt");
    set<string> tokenSet;
    while (inn >> token) {
        tokenSet.insert(token);
    }
    inn.close();

    for (const string& str : tokenSet) {
        cout << str << endl;
    }
    cout << "Size: " << tokenSet.size();

    cout << "\n=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    inn.open("pooh-nopunc.txt");
    map<string, vector<int>> wordMap;
    size_t i = 0;
    while (inn >> token) {
        wordMap[token].push_back(i);
        i++;
    }
    inn.close();

    for (const auto& entry : wordMap) {
        cout << entry.first << " : " << endl;
        cout << "\t";
        for (const int& n : entry.second) cout << n << " ";
        cout << endl;
    }

    cout << "\n=======\n";
}
