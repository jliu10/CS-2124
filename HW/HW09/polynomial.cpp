#include "polynomial.h"
#include <vector>
#include <iostream>
using namespace std;

ostream& operator<<(ostream& os, const Polynomial& p) {
    int degree = p.degree;
    Polynomial::Node* curr = p.head->next;
    bool max_degree = true;
    if (degree == 0 && curr->data == 0) {
        os << "0";
        return os;
    }
    while (curr) {
        if (degree == 0) {
            if (curr->data != 0) {
                if (!max_degree) {
                    if (curr->data > 0) os << "+";
                }
                os << curr->data;
            }
        }
        else if (curr->data != 0) {
            if (!max_degree && curr->data > 0) os << "+";
            if (curr->data != 1) os << curr->data;
            os << "x";
            if (degree > 1) os << "^" << degree;
            max_degree = false;
        }
        curr = curr->next;
        degree--;
    }

    return os;
}

bool operator==(const Polynomial& lhs, const Polynomial& rhs) {
    if (lhs.degree != rhs.degree) return false;
    Polynomial::Node* lhs_curr = lhs.head->next;
    Polynomial::Node* rhs_curr = rhs.head->next;
    while (lhs_curr) {
        if (lhs_curr->data != rhs_curr->data) return false;
        lhs_curr = lhs_curr->next;
        rhs_curr = rhs_curr->next;
    }
    return true;
}

Polynomial::Polynomial(const vector<int>& v = {0}) {
    if (v.size() == 0) {
        cerr << "Vector cannot be empty\n";
        exit(1);
    }
    head = new Node{0, nullptr};
    degree = v.size() - 1;
    Node* curr;
    Node* prev = head;
    for (size_t i = 0; i < v.size(); i++) {
        curr = new Node{v[i], nullptr};
        prev->next = curr;
        prev = curr;
    }
    prev->next = nullptr;
}

// Copy constructor
Polynomial::Polynomial(const Polynomial& other) {
    degree = other.degree;
    Node* other_curr = other.head->next;
    Node* curr = head;
    while (other_curr) {
        curr->next = new Node{other_curr->data, other_curr->next};
        other_curr = curr->next;
        curr = curr->next;
    }
    curr->next = nullptr;
}

// Destructor
Polynomial::~Polynomial() {
    Polynomial::Node* curr = head;
    Polynomial::Node* next = curr->next;
    while (next) {
        delete curr;
        curr = next;
        next = curr->next;
    }

    if (curr) {
        delete curr;
    }
}

// Assignment operator
Polynomial& Polynomial::operator=(const Polynomial& rhs) {
    // If this < rhs, then insert head nodes and change remaining nodes
    // Else if this > rhs, then need to delete and/or change nodes
    // Else (if this == rhs), then change all nodes

    if (this != &rhs) {
        Node* curr = head->next;
        Node* rhs_curr = rhs.head->next;
        if (degree < rhs.degree) {
            curr = head;
            for (size_t curr_exp = rhs.degree; curr_exp > degree; curr_exp--) {
                // Need to insert new nodes
                Node* node = new Node{rhs_curr->data, curr->next};
                curr->next = node;
                rhs_curr = rhs_curr->next;
                curr = curr->next;
            }
            curr = curr->next;
        }

        Node* prev = curr;
        while (rhs_curr) {
            curr->data = rhs_curr->data;
            prev = curr;
            curr = curr->next;
            rhs_curr = rhs_curr->next;
        }

        if (!curr) {
            degree = rhs.degree;
            return *(this);
        }

        Node* next = curr->next;
        if (degree > rhs.degree) {
            // Delete the rest
            while (next) {
                delete curr;
                curr = next;
                next = curr->next;
            }
            delete curr;
        }
        prev->next = nullptr;
        degree = rhs.degree;
    }
    return *(this);
}

Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
    Node* curr = head->next;
    Node* rhs_curr = rhs.head->next;
    if (degree >= rhs.degree) {
        for (size_t curr_exp = degree; curr_exp > rhs.degree; curr_exp--) {
            curr = curr->next;
        }
    }
    else {            
        curr = head;
        for (size_t curr_exp = rhs.degree; curr_exp > degree; curr_exp--) {
            // Need to insert new nodes
            Node* node = new Node{rhs_curr->data, curr->next};
            curr->next = node;
            rhs_curr = rhs_curr->next;
            curr = curr->next;
        }
        curr = curr->next;
        degree = rhs.degree;
    }
    while (curr != nullptr) {
        curr->data += rhs_curr->data;
        curr = curr->next;
        rhs_curr = rhs_curr->next;
    }

    return *this;
}

int Polynomial::evaluate(int x) const {
    Node* curr = head->next;
    int ret = curr->data;
    while (curr->next) {
        ret *= x;
        curr = curr->next;
        ret += curr->data;
    }
    return ret;
}

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {
    Polynomial ret = lhs;
    ret += rhs;
    return ret;
}

bool operator!=(const Polynomial& lhs, const Polynomial& rhs) {
    return !(lhs == rhs);
}

// class Polynomial {
// private:
//     struct Node {
//         int data;
//         Node* next;
//     };
//     friend ostream& operator<<(ostream& os, const Polynomial& p) {
//         int degree = p.degree;
//         Node* curr = p.head->next;
//         bool max_degree = true;
//         if (degree == 0 && curr->data == 0) {
//             os << "0";
//             return os;
//         }
//         while (curr) {
//             if (degree == 0) {
//                 if (curr->data != 0) {
//                     if (!max_degree) {
//                         if (curr->data > 0) os << "+";
//                     }
//                     os << curr->data;
//                 }
//             }
//             else if (curr->data != 0) {
//                 if (!max_degree && curr->data > 0) os << "+";
//                 if (curr->data != 1) os << curr->data;
//                 os << "x";
//                 if (degree > 1) os << "^" << degree;
//                 max_degree = false;
//             }
//             curr = curr->next;
//             degree--;
//         }

//         return os;
//     }

//     friend bool operator==(const Polynomial& lhs, const Polynomial& rhs) {
//         if (lhs.degree != rhs.degree) return false;
//         Node* lhs_curr = lhs.head->next;
//         Node* rhs_curr = rhs.head->next;
//         while (lhs_curr) {
//             if (lhs_curr->data != rhs_curr->data) return false;
//             lhs_curr = lhs_curr->next;
//             rhs_curr = rhs_curr->next;
//         }
//         return true;
//     }
// public:
//     Polynomial(const vector<int>& v = {0}) {
//         if (v.size() == 0) {
//             cerr << "Vector cannot be empty\n";
//             exit(1);
//         }
//         head = new Node{0, nullptr};
//         degree = v.size() - 1;
//         Node* curr;
//         Node* prev = head;
//         for (size_t i = 0; i < v.size(); i++) {
//             curr = new Node{v[i], nullptr};
//             prev->next = curr;
//             prev = curr;
//         }
//         prev->next = nullptr;
//     }

//     // Copy constructor
//     Polynomial::Polynomial(const Polynomial& other) {
//         // cout << "Copy constructor invoked\n";
//         degree = other.degree;
//         Node* other_curr = other.head->next;
//         Node* curr = head;
//         while (other_curr) {
//             curr->next = new Node{other_curr->data, other_curr->next};
//             other_curr = curr->next;
//             curr = curr->next;
//         }
//         curr->next = nullptr;
//     }

//     // Destructor
//     ~Polynomial() {
//         // cout << "Destructor invoked\n";
//         // cout << "Deleting polynomial with head = " << head->next->data << endl;
//         Node* curr = head;
//         Node* next = curr->next;
//         while (next) {
//             // cout << "curr = " << curr->data << endl;
//             delete curr;
//             curr = next;
//             next = curr->next;
//         }

//         if (curr) {
//             // cout << "Last curr = " << curr->data << endl;
//             delete curr;
//         }
//         // cout << "Got up to here!\n";
//     }

//     // Assignment operator
//     Polynomial& operator=(const Polynomial& rhs) {
//         // If this < rhs, then insert head nodes and change remaining nodes
//         // Else if this > rhs, then need to delete and/or change nodes
//         // Else (if this == rhs), then change all nodes

//         if (this != &rhs) {
//             Node* curr = head->next;
//             Node* rhs_curr = rhs.head->next;
//             if (degree < rhs.degree) {
//                 curr = head;
//                 for (size_t curr_exp = rhs.degree; curr_exp > degree; curr_exp--) {
//                     // Need to insert new nodes
//                     Node* node = new Node{rhs_curr->data, curr->next};
//                     curr->next = node;
//                     rhs_curr = rhs_curr->next;
//                     curr = curr->next;
//                 }
//                 curr = curr->next;
//             }
//             // cout << "HERE curr = " << curr->data << endl;

//             Node* prev = curr;
//             while (rhs_curr) {
//                 // cout << "Assigning " << curr->data << " to " << rhs_curr->data << endl;
//                 curr->data = rhs_curr->data;
//                 prev = curr;
//                 curr = curr->next;
//                 rhs_curr = rhs_curr->next;
//             }

//             if (!curr) {
//                 degree = rhs.degree;
//                 return *(this);
//             }

//             Node* next = curr->next;
//             if (degree > rhs.degree) {
//                 // Delete the rest
//                 while (next) {
//                     delete curr;
//                     curr = next;
//                     next = curr->next;
//                 }
//                 delete curr;
//             }
//             prev->next = nullptr;
//             degree = rhs.degree;
//         }
//         return *(this);
//     }

//     Polynomial& operator+=(const Polynomial& rhs) {
//         Node* curr = head->next;
//         Node* rhs_curr = rhs.head->next;
//         if (degree >= rhs.degree) {
//             for (size_t curr_exp = degree; curr_exp > rhs.degree; curr_exp--) {
//                 curr = curr->next;
//             }
//         }
//         else {            
//             curr = head;
//             for (size_t curr_exp = rhs.degree; curr_exp > degree; curr_exp--) {
//                 // Need to insert new nodes
//                 Node* node = new Node{rhs_curr->data, curr->next};
//                 curr->next = node;
//                 rhs_curr = rhs_curr->next;
//                 curr = curr->next;
//             }
//             curr = curr->next;
//             degree = rhs.degree;
//         }
//         while (curr != nullptr) {
//             curr->data += rhs_curr->data;
//             curr = curr->next;
//             rhs_curr = rhs_curr->next;
//         }

//         return *this;
//     }

//     int evaluate(int x) const {
//         Node* curr = head->next;
//         int ret = curr->data;
//         while (curr->next) {
//             ret *= x;
//             curr = curr->next;
//             ret += curr->data;
//         }
//         return ret;
//     }

// private:
//     Node* head; // sentinel
//     int degree;
// };

// Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {
//     Polynomial ret = lhs;
//     ret += rhs;
//     return ret;
// }

// bool operator!=(const Polynomial& lhs, const Polynomial& rhs) {
//     return !(lhs == rhs);
// }

// int main() {
//     Polynomial p0({6,2});
//     Polynomial p1;
//     cout << "p1: " << p1 << endl;
//     Polynomial p2({1,2,3,5});
//     cout << "p2: " << p2 << endl;
//     Polynomial p3({1,4});
//     Polynomial p4({0,3,1,-6});
//     p2 += p3;
//     cout << "p2: " << p2 << endl;
//     p2 += p4;
//     cout << "p2: " << p2 << endl;
//     cout << "p3: " << p3 << endl;
//     p3 += p2;
//     cout << "p3: " << p3 << endl;

//     p1 = p2;
//     cout << "p1: " << p1 << endl;
//     cout << "p0: " << p0 << endl;

//     Polynomial p5({2,-3,1,-2,3});
//     cout << "Evaluating " << p0 << " at x = " << 2 << endl;
//     cout << p0.evaluate(2) << endl;

//     cout << "Before assignment:\n";
//     cout << "p1: " << p1 << endl;
//     cout << "p0: " << p0 << endl;
//     // p0 = p1;
//     p1 = p0;
//     cout << "After assignment:\n";
//     cout << "p1: " << p1 << endl;
//     // cout << "p0: " << p0 << endl;
// }