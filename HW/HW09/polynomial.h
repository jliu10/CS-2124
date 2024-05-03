#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <iostream>

class Polynomial {
private:
    struct Node {
        int data;
        Node* next;
    };

    friend std::ostream& operator<<(std::ostream& os, const Polynomial& p);

    friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);
public:
    Polynomial(const std::vector<int>& v = {0});

    // Copy constructor
    Polynomial(const Polynomial& other);

    // Destructor
    ~Polynomial();

    // Assignment operator
    Polynomial& operator=(const Polynomial& rhs);

    Polynomial& operator+=(const Polynomial& rhs);

    int evaluate(int x) const;

private:
    Node* head; // sentinel
    int degree;
};

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);

bool operator!=(const Polynomial& lhs, const Polynomial& rhs);

#endif