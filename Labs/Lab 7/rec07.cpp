/*
  rec07.cpp
  CS2124
  Implement the class Rational, so that the following program works.
 */

#include <iostream>
using namespace std;

int greatestCommonDivisor(int x, int y);

// Put your Rational class here.
class Rational {
    friend ostream& operator<<(ostream& os, const Rational& n) {
       os << n.numerator << "/" << n.denominator;
       return os;
    }
    friend bool operator==(const Rational& r1, const Rational& r2) {
        return r1.numerator == r2.numerator && r1.denominator == r2.denominator;
    }
    friend bool operator<(const Rational& r1, const Rational& r2) {
        return r1.numerator * r2.denominator < r2.numerator * r1.denominator;
    }
    friend istream& operator>>(istream& is, Rational& n) {
        int num, denom;
        char slash;
        is >> num >> slash >> denom;
        if (denom == 0) {
            cerr << "Error: division by 0 is undefined" << endl;
            exit(1);
        }
        n.numerator = num;
        n.denominator = denom;
        n.normalize();
        return is;
    }
public:
    Rational(int num = 0, int denom = 1) {
        if (denom == 0) {
            cerr << "Error: division by 0 is undefined" << endl;
            exit(1);
        }
        numerator = num;
        denominator = denom;
        this->normalize();
    }

    void normalize() {
        int gcd = greatestCommonDivisor(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
        if (denominator < 0) {
            numerator *= -1;
            denominator *= -1;
        }
    }

    Rational& operator+=(const Rational& n) {
        numerator = (numerator * n.denominator) + (n.numerator * 
            denominator);
        denominator *= n.denominator;
        this->normalize();
        return *this;
    }

    // Post
    Rational operator++(int dummy) {
        Rational t = *this;
        numerator += denominator;
        this->normalize();
        return t;
    }

    // Pre
    Rational& operator++() {
        numerator += denominator;
        this->normalize();
        return *this;
    }

    explicit operator bool() const {
        return numerator != 0;
    }
private:
    int numerator;
    int denominator;
};



// Any functions that are not members and not friends should have
// prototypes here and their definitions after main.
Rational operator+(const Rational& r1, const Rational& r2);
Rational operator--(Rational& n, int dummy);
Rational& operator--(Rational& n);
bool operator!=(const Rational& r1, const Rational& r2);
bool operator<=(const Rational& r1, const Rational& r2);
bool operator>(const Rational& r1, const Rational& r2);
bool operator>=(const Rational& r1, const Rational& r2);

int main()
{
    Rational a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;	// Implement as member
    cout << "a = " << a << endl;
    
    // Implement + as non-member, but not a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;
    
    // How does this manage to work?
    // It does NOT require writing another == operator. 
    cout << "1 == one: " << boolalpha << (1 == one) << endl;
    
    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing? Why shouldn't it compile?
    //cout << "a-- -- = " << (a-- --) << endl;
    cout << "a = " << a << endl;


    // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    } 

    // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    } 

    cout << "Comparisons\n";
    Rational twoFifths(2, 5);
    Rational threeHalves(3, 2);
    Rational minusFive(-5);
    cout << twoFifths << " < " << threeHalves << " : " 
         << (twoFifths < threeHalves) << endl;
    cout << twoFifths << " <= " << 1 << " : " << (twoFifths <= 1) << endl;
    cout << threeHalves << " < " << twoFifths << " : "
         << (threeHalves < twoFifths) << endl;
    cout << threeHalves << " > " << threeHalves << " : "
         << (threeHalves > threeHalves) << endl;
    cout << threeHalves << " >= " << threeHalves << " : "
         << (threeHalves >= threeHalves) << endl;
    cout << minusFive << " >= " << threeHalves << " : "
         << (minusFive >= threeHalves) << endl;
}

int greatestCommonDivisor(int x, int y)
{
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

// Any functions that are not members and not friends should have
// their definitions here...
Rational operator+(const Rational& r1, const Rational& r2) {
    Rational temp = r1;
    temp += r2;
    return temp;
}

// Post
Rational operator--(Rational& n, int dummy) {
    Rational t = n;
    Rational n1(-1, 1);
    n += n1;
    return t;
}

// Pre
Rational& operator--(Rational& n) {
    Rational n1(-1,1);
    n += n1;
    return n;
}

bool operator!=(const Rational& r1, const Rational& r2) {
    return !(r1 == r2);
}

bool operator<=(const Rational& r1, const Rational& r2) {
    return r1 < r2 || r1 == r2;
}

bool operator>(const Rational& r1, const Rational& r2) {
    return !(r1 <= r2);
}

bool operator>=(const Rational& r1, const Rational& r2) {
    return !(r1 < r2);
}
