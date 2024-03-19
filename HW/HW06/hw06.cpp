/*
  bigUnsigned_begin.cpp
  Justin Liu
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Put your class and all function definitions here.

// BigUnsigned class
class BigUnsigned {
     friend ostream& operator<<(ostream& os, const BigUnsigned& big) {
          for (size_t i = big.digits.size(); i > 0; i--) {
               os << big.digits[i - 1];
          }
          return os;
     }

     friend bool operator==(const BigUnsigned& lhs, const BigUnsigned& rhs) {
          if (lhs.digits.size() != rhs.digits.size()) return false;
          for (size_t i = 0; i < lhs.digits.size(); i++) {
               if (lhs.digits[i] != rhs.digits[i]) return false;
          }
          return true;
     }

     friend bool operator<(const BigUnsigned& lhs, const BigUnsigned& rhs) {
          if (lhs.digits.size() != rhs.digits.size()) {
               return lhs.digits.size() < rhs.digits.size();
          }
          for (size_t i = rhs.digits.size(); i > 0; i--) {
               if (lhs.digits[i-1] < rhs.digits[i-1]) return true;
          }
          return false;
     }
public:
     // int constructor
     BigUnsigned(int n = 0) {
          while (n >= 10) { // 2 or more digits
               digits.push_back(n % 10);
               n /= 10;
          }
          digits.push_back(n);
     }

     // string constructor
     BigUnsigned(const string& str) {
          // Digits ASCII in [48,57]
          // Need to find where first "digit substring" ends,
          // then add to vector backwards
          bool foundNonZeroDigit = false;
          size_t firstNonZeroDigit = 0;
          size_t lastDigit = 0;
          for (size_t i = 0; i < str.size(); i++) {
               // Check if char is nondigit
               if (str[i] < 48 || str[i] > 57) break;
               // Now char is a digit
               if (str[i] != 48) { // Nonzero
                    if (!foundNonZeroDigit) {
                         foundNonZeroDigit = true;
                         firstNonZeroDigit = i;
                    }
               }
               lastDigit = i;
          }
          if (!foundNonZeroDigit) digits.push_back(0);
          else { // Add digits backward
               while (lastDigit >= firstNonZeroDigit) {
                    if (lastDigit == 0 && firstNonZeroDigit == 0) {
                         // Edge case where entire number at index 0
                         digits.push_back(str[lastDigit] - '0');
                         break; 
                    }
                    digits.push_back(str[lastDigit] - '0');
                    lastDigit--;
               }
          }
     }

     BigUnsigned& operator+=(const BigUnsigned& rhs) {
          size_t i = 0;
          int carry = 0;
          while (i < digits.size() && i < rhs.digits.size()) {
               digits[i] += rhs.digits[i] + carry;
               if (digits[i] > 9) {
                    carry = 1;
                    digits[i] -= 10;
               }
               else carry = 0;
               i++;
          }
          while (i < digits.size()) {
               if (!carry) break;
               digits[i] += carry;
               if (digits[i] > 9) {
                    carry = 1;
                    digits[i] -= 10;
               }
               else carry = 0;
               i++;
          }
          while (i < rhs.digits.size()) {
               digits.push_back(rhs.digits[i] + carry);
               if (digits[i] > 9) {
                    carry = 1;
                    digits[i] -= 10;
               }
               else carry = 0;
               i++;
          }
          if (carry) digits.push_back(1);
          return *this;
     }

     BigUnsigned& operator++() {
          BigUnsigned one(1);
          (*this) += one;
          return *this;
     }

     BigUnsigned operator++(int dummy) {
          BigUnsigned res = *this;
          BigUnsigned one(1);
          (*this) += one;
          return res;
     }

     explicit operator bool() const {
          return digits[digits.size() - 1] != 0;
     }
private:
     vector<int> digits;
};

bool operator!=(const BigUnsigned& lhs, const BigUnsigned& rhs) {
     return !(lhs == rhs);
}

bool operator<=(const BigUnsigned& lhs, const BigUnsigned& rhs) {
     return (lhs < rhs) || (lhs == rhs);
}

bool operator>(const BigUnsigned& lhs, const BigUnsigned& rhs) {
     return !(lhs <= rhs);
}

bool operator>=(const BigUnsigned& lhs, const BigUnsigned& rhs) {
     return !(lhs < rhs);
}

BigUnsigned operator+(const BigUnsigned& lhs, const BigUnsigned& rhs) {
     BigUnsigned res = lhs;
     res += rhs;
     return res;
}

int main() {
    BigUnsigned zero;
    BigUnsigned one(1);

    cout << "zero: " << zero << endl;
    cout << "one: " << one << endl;

    BigUnsigned val = 1;
    cout << "val: " << val << endl;
    cout << "++val: " << ++val << endl;
    cout << "val: " << val << endl;
    cout << "val++: " << val++ << endl;
    cout << "val: " << val << endl;
    
    cout << "(one + zero): " << (one + zero) << endl;
    cout << "(one + one): " <<  (one + one) << endl;

    cout << boolalpha;
    cout << "one < one: " << (one < one) << endl;
    cout << "zero < one: " << (zero < one) << endl;

    BigUnsigned a = 123;
    BigUnsigned b = 1234;
    BigUnsigned c = 124;
    BigUnsigned d = 12345;

    cout << "a: " << a << ", b: " << b 
         << ", c: " << c << ", d: " << d << endl;
    cout << "a + d: " << (a + d) << endl;
    cout << "d + d: " << (d + d) << endl;
    cout << "a < d: " << (a < d) << endl;
    cout << "d < a: " << (d < a) << endl;
    cout << "zero == zero: " << (zero == zero) << endl
         << "zero == one: " << (zero == one) << endl
         << "a == a: " << (a == a) << endl
         << "a == d: " << (a == d) << endl
         << "d == a: " << (d == a) << endl;

    cout << "(zero == 0): " << (zero == 0) << endl
         << "(one == 0): " << (one == 0) << endl
         << "(1 == one): " << (1 == one) << endl;

    // +=
    cout << "b: " << b << ", c: " << c << endl;
    cout << "(c += b): " << (c += b) << endl;
    cout << "b: " << b << ", c: " << c << endl;


    BigUnsigned x = a;
    cout << "x: " << x << ", a: " << a << endl
         << "x == a: " << (x == a) << endl
         << "a == x: " << (a == x) << endl
         << "a < x: " << (a < x) << endl
         << "a > x: " << (a > x) << endl;
    
    cout << "x > a: " << (x > a) << endl
         << "x >= a: " << (x >= a) << endl
         << "x <= a: " << (x <= a) << endl
         << "x != a: " << (x != a) << endl;
         
    
    BigUnsigned big("987654321");
    BigUnsigned big2("  ");
    BigUnsigned big3("felix");
    BigUnsigned big4("00987654321");

    cout << "big: " << big << endl
         << "big2: " << big2 << endl
         << "big3: " << big3 << endl
         << "big4: " << big4 << endl;

    BigUnsigned big5(98765);
    BigUnsigned big6(2457);
    cout << "big5: " << big5  << ", big6: " <<  big6 << endl
         << "(big5 + big6): " << (big5 + big6) << endl
         << "(big6 + big5): " << (big6 + big5) << endl;


    cout << zero << " is " << (zero ? "true" : "false") << endl;
    cout << one << " is " << (one ? "true" : "false") << endl;
    cout << big4 << " is " << (big4 ? "true" : "false") << endl;
}

