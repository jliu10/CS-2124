/*
  rec14_starter code
 */

#include <iostream>
#include <vector>
#include <algorithm>  // max
using namespace std;


// Node type for the linked list
struct Node {
    int data = 0;
    Node* next = nullptr;
};

// Node type for the binary tree
struct TNode {
    int data = 0;
    TNode* left = nullptr;
    TNode* mid = nullptr;
    TNode* right = nullptr;
};



/////////////////////////////////////////////////////////////////////////
//
// Provided code for use in testing
//
void listPrint(const Node* headPtr);
void listClear(Node*& headPtr);
Node* listBuild(const vector<int>& vals);


//
// Your functions go here
//
//   Task 1 function:
Node* listSum(Node* l1, Node* l2) {
    if (!l1 && !l2) return nullptr;
    if (!l1) return new Node{l2->data, listSum(nullptr, l2->next)};
    if (!l2) return new Node{l1->data, listSum(l1->next, nullptr)};

    return new Node{l1->data + l2->data, listSum(l1->next, l2->next)};
}

//   Task 2 function:
int treeMax(const TNode* tree) {
    if (!tree) throw invalid_argument("Tree is empty.");

    int result = tree->data;
    if (tree->left) result = max(result, treeMax(tree->left));
    if (tree->mid) result = max(result, treeMax(tree->mid));
    if (tree->right) result = max(result, treeMax(tree->right));

    return result;
}

//   Task 3 function:
bool palindrome(const char arr[], unsigned len) {
    if (len <= 1) return true;

    // cout << "Comparing " << *arr << " with " << *(arr + len - 2) << endl;
    return *arr == *(arr + len - 1) && palindrome(arr + 1, len - 2);
}

//   Task 4 function:
bool parity(int n) {
    if (n <= 1) return n == 0;

    bool recur = parity(n / 2);
    return ((n % 2 == 0) && recur) || ((n % 2 == 1) && !recur);
}

//   Task 5 function:
unsigned towers(unsigned n, char src, char spare, char dest) {
    if (n == 0) return 0;

    int t1 = towers(n - 1, src, dest, spare);

    int t2 = towers(n - 1, spare, src, dest);

    return 1 + t1 + t2;
}

void mystery(int n) {
    if (n > 1) {
        cout << 'a';
        mystery(n/2);
        cout << 'b';
        mystery(n/2);
    }
    cout << 'c';
}
/**
 * a( a(c)b(c)c )b( a(c)b(c)c )c
*/

int main() {
    // We have provided some test code to save you time. Certainly fee
    // free to write more!

    // Task 1:
    cout << "\n==============\n#1: Testing listSum\n";
    Node* l1 = listBuild({2, 7, 1, 8});
    cout << "List (l1): ";
    listPrint(l1);
    
    Node* l2 = listBuild({9, 1, 4, 1});
    cout << "List (l2): ";
    listPrint(l2);

    Node* l3 = listBuild({3, 1, 4, 1, 5, 9});
    cout << "List (l3): ";
    listPrint(l3);

    cout << "The sum of l1 and l2: ";
    Node* l4 = listSum(l1, l2);
    listPrint(l4);

    cout << "The sum of l1 and l3: ";
    Node* l5 = listSum(l1, l3);
    listPrint(l5);

    cout << "The sum of l3 and l1: ";
    Node* l6 = listSum(l3, l1);
    listPrint(l6);

    listClear(l1);
    listClear(l2);
    listClear(l3);
    listClear(l4);
    listClear(l5);
    listClear(l6);


    // Task 2:
    TNode a{1}, b{2}, c{4}, d{-8, &a, &b, &c}, e{-16}, f{-32, &d, &e};
    cout << "treeMax(&f): " << treeMax(&f) << endl;

    // How do you keep this from crashing? try/catch! Here in main!
    try {
        cout << treeMax(nullptr) << endl;
    }
    catch (exception& e) {
        cerr << "Exception caught: " << e.what() << endl;
    }

    
    // Task 3:
    cout << "\n==============\n"
	 << "#3) Testing palindrome\n";
    cout << boolalpha
	 << "palindrome(\"racecar\", 7): " << palindrome("racecar", 7) << endl
	 << "palindrome(\"noon\", 4): " << palindrome("noon", 4) << endl
	 << "palindrome(\"raceXar\", 7): " << palindrome("raceXar", 7) << endl
	 << "palindrome(\"noXn\", 4): " << palindrome("noXn", 4) << endl
     << "palindrome(\"mom\", 3): " << palindrome("mom", 3) << endl;
    
    

    // Task 4:
    cout << "\n==============\n"
	 << "#4) Are there an even number of 1's in binary representation?\n";
    cout << boolalpha;
    for (int i = 0; i < 10; ++i) {
        cout << i << ": " << parity(i) << endl;
    }


    
    // Task 5:
    cout << "\n==============\n"
	 << "#5) How many moves are required for various sized towers?";
    for (int i = 1; i < 30; ++i) {
	cout << "towers(" << i << ", 'a', 'b', 'c'): " 
	     << towers(i, 'a', 'b', 'c') << endl;
    }

    // Task 6:
    /** Predictions:
     * 0 -> c
     * 1 -> c
     * 2 -> acbcc
     * 3 -> acbcc
     * 4 -> aacbccbacbccc
     * 5 -> aacbccbacbccc
     * 6 -> aacbccbacbccc
     * 7 -> aacbccbacbccc
     * 8 -> aaacbccbacbcccbaacbccbacbcccc
     * 9 -> aaacbccbacbcccbaacbccbacbcccc
     * 10 -> aaacbccbacbcccbaacbccbacbcccc
    */
    cout << "\n==============\n";
    for (int i = 0; i <= 10; ++i) {
	    cout << "mystery(" << i << ") = ";
        mystery(i);
        cout << endl;
    }

}


//
// The provided utility functions:
//

// listPrint prints out the data values in the list.
// All the values are printed on a single line with blanks separating them.
void listPrint(const Node* headPtr) {
    const Node* curr = headPtr;
    while (curr != nullptr) {
        cout << curr->data << ' ';
        curr = curr->next;
    }
    cout << endl;
}

// listClear frees up all of the nodes in list setting the the head
// pointer to null.
void listClear(Node*& headPtr) {
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
}

// listBuild returns a list with the same values as in the vector.
Node* listBuild(const vector<int>& vals) {
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
	result = new Node{vals[index-1], result};
    }
    return result;
}
