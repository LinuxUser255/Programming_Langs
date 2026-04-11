// 07b_oop_expanded.cpp
//
// OOP expanded — builds directly on 07_oop_basics.cpp.
// Covers: encapsulation, inheritance, polymorphism,
// virtual functions, abstract classes, and operator overloading.
//
// Compile: g++ -std=c++17 -Wall -o 07b_oop_expanded 07b_oop_expanded.cpp

#include <iostream>
#include <string>
#include <vector>
#include <memory>    // unique_ptr for polymorphism
#include <cmath>     // std::sqrt

// ── 1. Encapsulation — private data, public interface ────────────────────────

class BankAccount {
private:
    std::string _owner;
    double      _balance;    // private — can't be accessed directly from outside

    // Private helper — internal use only
    void _log(const std::string &msg) const {
        std::cout << "  [" << _owner << "] " << msg << std::endl;
    }

public:
    // Constructor
    BankAccount(const std::string &owner, double initial)
        : _owner(owner), _balance(initial) {
        _log("Account created with balance $" + std::to_string(initial));
    }

    // Destructor
    ~BankAccount() {
        _log("Account closed");
    }

    // Getters — read-only access to private data
    const std::string &owner()   const { return _owner;   }
    double             balance()  const { return _balance;  }

    // Methods that validate before modifying
    bool deposit(double amount) {
        if (amount <= 0.0) {
            _log("Deposit rejected — amount must be positive");
            return false;
        }
        _balance += amount;
        _log("Deposited $" + std::to_string(amount));
        return true;
    }

    bool withdraw(double amount) {
        if (amount <= 0.0) {
            _log("Withdrawal rejected — amount must be positive");
            return false;
        }
        if (amount > _balance) {
            _log("Withdrawal rejected — insufficient funds");
            return false;
        }
        _balance -= amount;
        _log("Withdrew $" + std::to_string(amount));
        return true;
    }

    void print() const {
        std::cout << "  Account[" << _owner << "] balance: $" << _balance << std::endl;
    }
};

// ── 2. Inheritance ────────────────────────────────────────────────────────────

// Base class — represents any 2D shape
class Shape {
protected:
    std::string _color;   // protected — accessible in derived classes

public:
    explicit Shape(const std::string &color) : _color(color) {}

    // Virtual destructor — essential whenever using polymorphism
    virtual ~Shape() {
        std::cout << "  Shape (" << _color << ") destroyed" << std::endl;
    }

    // Pure virtual — derived classes MUST implement these
    virtual double area()      const = 0;
    virtual double perimeter() const = 0;
    virtual std::string name() const = 0;

    // Non-virtual — same for all shapes
    const std::string &color() const { return _color; }

    // Virtual — has a default, can be overridden
    virtual void describe() const {
        std::cout << "  " << name() << " [" << _color << "]"
                  << " area=" << area()
                  << " perimeter=" << perimeter()
                  << std::endl;
    }
};

// Derived class — Circle
class Circle : public Shape {
private:
    double _radius;
    static constexpr double PI = 3.14159265358979;

public:
    Circle(const std::string &color, double radius)
        : Shape(color), _radius(radius) {}

    ~Circle() override {
        std::cout << "  Circle (r=" << _radius << ") destroyed" << std::endl;
    }

    double area()      const override { return PI * _radius * _radius; }
    double perimeter() const override { return 2.0 * PI * _radius; }
    std::string name() const override { return "Circle"; }

    double radius() const { return _radius; }
};

// Derived class — Rectangle
class Rectangle : public Shape {
private:
    double _width;
    double _height;

public:
    Rectangle(const std::string &color, double width, double height)
        : Shape(color), _width(width), _height(height) {}

    ~Rectangle() override {
        std::cout << "  Rectangle (" << _width << "x" << _height << ") destroyed" << std::endl;
    }

    double area()      const override { return _width * _height; }
    double perimeter() const override { return 2.0 * (_width + _height); }
    std::string name() const override { return "Rectangle"; }
};

// Derived class — Triangle
class Triangle : public Shape {
private:
    double _a, _b, _c;   // three side lengths

public:
    Triangle(const std::string &color, double a, double b, double c)
        : Shape(color), _a(a), _b(b), _c(c) {}

    double perimeter() const override {
        return _a + _b + _c;
    }

    double area() const override {
        // Heron's formula
        double s = perimeter() / 2.0;
        return std::sqrt(s * (s - _a) * (s - _b) * (s - _c));
    }

    std::string name() const override { return "Triangle"; }
};

// ── 3. Operator Overloading ───────────────────────────────────────────────────

class Vector2D {
public:
    double x, y;

    Vector2D(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    // + operator
    Vector2D operator+(const Vector2D &other) const {
        return Vector2D(x + other.x, y + other.y);
    }

    // - operator
    Vector2D operator-(const Vector2D &other) const {
        return Vector2D(x - other.x, y - other.y);
    }

    // * scalar multiply
    Vector2D operator*(double scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }

    // == equality
    bool operator==(const Vector2D &other) const {
        return x == other.x && y == other.y;
    }

    // += compound assignment
    Vector2D &operator+=(const Vector2D &other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    double length() const {
        return std::sqrt(x * x + y * y);
    }

    // << stream output operator (non-member, defined as friend)
    friend std::ostream &operator<<(std::ostream &os, const Vector2D &v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }
};

// ── 4. Multiple inheritance ───────────────────────────────────────────────────

class Flyable {
public:
    virtual void fly() const {
        std::cout << "  " << creature_name() << " is flying" << std::endl;
    }
    virtual std::string creature_name() const = 0;
    virtual ~Flyable() = default;
};

class Swimmable {
public:
    virtual void swim() const {
        std::cout << "  " << creature_name() << " is swimming" << std::endl;
    }
    virtual std::string creature_name() const = 0;
    virtual ~Swimmable() = default;
};

class Duck : public Flyable, public Swimmable {
public:
    std::string creature_name() const override { return "Duck"; }

    void quack() const {
        std::cout << "  Duck says: quack!" << std::endl;
    }
};

int main() {
    // ── 1. Encapsulation ──────────────────────────────────────────────────────
    std::cout << "=== 1. Encapsulation ===" << std::endl;

    BankAccount acc("Alice", 1000.0);
    acc.deposit(500.0);
    acc.withdraw(200.0);
    acc.withdraw(5000.0);   // rejected — insufficient
    acc.withdraw(-50.0);    // rejected — negative
    acc.print();

    // acc._balance = 99999;   // ❌ would not compile — _balance is private
    std::cout << "  Balance via getter: $" << acc.balance() << std::endl;

    // ── 2. Inheritance + virtual functions ────────────────────────────────────
    std::cout << "\n=== 2. Inheritance ===" << std::endl;

    Circle    c("red",   5.0);
    Rectangle r("blue",  4.0, 6.0);
    Triangle  t("green", 3.0, 4.0, 5.0);

    c.describe();
    r.describe();
    t.describe();

    // ── 3. Polymorphism ───────────────────────────────────────────────────────
    std::cout << "\n=== 3. Polymorphism ===" << std::endl;

    // Base class pointer — points to different derived types
    // unique_ptr used here — no manual delete needed
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>("orange",  3.0));
    shapes.push_back(std::make_unique<Rectangle>("purple", 5.0, 2.0));
    shapes.push_back(std::make_unique<Triangle>("cyan",   6.0, 8.0, 10.0));
    shapes.push_back(std::make_unique<Circle>("yellow",  1.0));

    std::cout << "  All shapes via base pointer:" << std::endl;
    double total_area = 0.0;
    for (const auto &shape : shapes) {
        shape->describe();          // calls correct derived describe()
        total_area += shape->area();
    }
    std::cout << "  Total area: " << total_area << std::endl;

    // Find largest shape
    const Shape *largest = nullptr;
    double max_area = 0.0;
    for (const auto &shape : shapes) {
        if (shape->area() > max_area) {
            max_area = shape->area();
            largest  = shape.get();
        }
    }
    std::cout << "  Largest: ";
    largest->describe();

    // ── 4. Operator overloading ───────────────────────────────────────────────
    std::cout << "\n=== 4. Operator Overloading ===" << std::endl;

    Vector2D v1(3.0, 4.0);
    Vector2D v2(1.0, 2.0);

    std::cout << "  v1            = " << v1           << std::endl;
    std::cout << "  v2            = " << v2           << std::endl;
    std::cout << "  v1 + v2       = " << (v1 + v2)   << std::endl;
    std::cout << "  v1 - v2       = " << (v1 - v2)   << std::endl;
    std::cout << "  v1 * 2.0      = " << (v1 * 2.0)  << std::endl;
    std::cout << "  v1 == v2?     " << (v1 == v2 ? "yes" : "no")   << std::endl;
    std::cout << "  v1 == v1?     " << (v1 == v1 ? "yes" : "no")   << std::endl;
    std::cout << "  v1.length()   = " << v1.length()  << std::endl;

    v1 += v2;
    std::cout << "  v1 after += v2: " << v1 << std::endl;

    // ── 5. Multiple inheritance ───────────────────────────────────────────────
    std::cout << "\n=== 5. Multiple Inheritance ===" << std::endl;

    Duck duck;
    duck.fly();
    duck.swim();
    duck.quack();

    // Polymorphism through interface pointers
    Flyable   *f = &duck;
    Swimmable *s = &duck;
    f->fly();
    s->swim();

    // ── 6. Key OOP concepts summary ───────────────────────────────────────────
    std::cout << "\n=== 6. OOP Concepts Summary ===" << std::endl;
    std::cout << "  Encapsulation  — private data, public interface via methods" << std::endl;
    std::cout << "  Inheritance    — derived class extends base class" << std::endl;
    std::cout << "  Polymorphism   — base pointer calls derived method at runtime" << std::endl;
    std::cout << "  Abstraction    — pure virtual = interface contract" << std::endl;
    std::cout << "  virtual        — enables runtime dispatch (polymorphism)" << std::endl;
    std::cout << "  override       — confirms method overrides a virtual" << std::endl;
    std::cout << "  virtual ~dtor  — always use with polymorphic base classes" << std::endl;

    std::cout << "\n(Shapes destroyed as unique_ptrs go out of scope)" << std::endl;

    return 0;
}
