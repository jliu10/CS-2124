class Base {

};

class Derived : public Base {

};

int main() {
    Base b;
    Derived d;
    Base* bp = nullptr;
    Derived* dp = nullptr;

    b = d;
    // d = b;
    bp = dp;
    // dp = bp;
    bp = &b;
    bp = &d;
    // dp = &b;
    dp = &d;
}