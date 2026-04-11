// 12_error_handling.cpp
//
// Error handling in C++: exceptions, try/catch/throw,
// the standard exception hierarchy, and error codes.
//
// Compile: g++ -std=c++17 -Wall -o 12_error_handling 12_error_handling.cpp

#include <iostream>
#include <string>
#include <stdexcept>   // std::exception, runtime_error, invalid_argument, etc.
#include <vector>
#include <limits>
#include <optional>    // std::optional (C++17) — a cleaner alternative to error codes

// ── Custom exception classes ──────────────────────────────────────────────────

// Inherit from std::runtime_error — the idiomatic way to define custom exceptions
class InsufficientFundsError : public std::runtime_error {
private:
    double _balance;
    double _amount;

public:
    InsufficientFundsError(double balance, double amount)
        : std::runtime_error("Insufficient funds"),
          _balance(balance),
          _amount(amount) {}

    double balance() const { return _balance; }
    double amount()  const { return _amount;  }

    // Override what() to include context
    const char *what() const noexcept override {
        // Return the base message — for detailed info use balance()/amount()
        return "InsufficientFundsError: balance too low for requested amount";
    }
};

class NegativeAmountError : public std::invalid_argument {
public:
    explicit NegativeAmountError(double amount)
        : std::invalid_argument("Amount cannot be negative: " + std::to_string(amount)) {}
};

// ── Bank account class that throws exceptions ─────────────────────────────────

class BankAccount {
private:
    std::string _owner;
    double      _balance;

public:
    BankAccount(const std::string &owner, double initial_balance)
        : _owner(owner), _balance(initial_balance) {
        if (initial_balance < 0.0) {
            throw NegativeAmountError(initial_balance);
        }
    }

    void deposit(double amount) {
        if (amount <= 0.0) {
            throw NegativeAmountError(amount);
        }
        _balance += amount;
        std::cout << "  Deposited $" << amount << " — balance: $" << _balance << std::endl;
    }

    void withdraw(double amount) {
        if (amount <= 0.0) {
            throw NegativeAmountError(amount);
        }
        if (amount > _balance) {
            throw InsufficientFundsError(_balance, amount);
        }
        _balance -= amount;
        std::cout << "  Withdrew $" << amount << " — balance: $" << _balance << std::endl;
    }

    double balance() const { return _balance; }
    const std::string &owner() const { return _owner; }
};

// ── Function that throws standard exceptions ──────────────────────────────────

int parse_positive_int(const std::string &input) {
    // stoi throws std::invalid_argument if not a number
    // stoi throws std::out_of_range if too large
    int value = std::stoi(input);
    if (value <= 0) {
        throw std::domain_error("Value must be positive, got: " + std::to_string(value));
    }
    return value;
}

std::string get_element(const std::vector<std::string> &v, int index) {
    return v.at(index);   // .at() throws std::out_of_range, [] does not
}

// ── std::optional — clean alternative to error codes ─────────────────────────
// Returns a value or "nothing" — no exceptions, no null pointers

std::optional<int> safe_divide(int a, int b) {
    if (b == 0) {
        return std::nullopt;   // return "nothing"
    }
    return a / b;
}

std::optional<double> find_average(const std::vector<double> &values) {
    if (values.empty()) {
        return std::nullopt;
    }
    double sum = 0.0;
    for (double v : values) sum += v;
    return sum / static_cast<double>(values.size());
}

// ── noexcept — mark functions that never throw ────────────────────────────────

int safe_abs(int x) noexcept {
    return x < 0 ? -x : x;
}

int main() {
    // ── 1. Basic try/catch ────────────────────────────────────────────────────
    std::cout << "=== 1. Basic try/catch ===" << std::endl;

    try {
        std::vector<int> v = {1, 2, 3};
        std::cout << "  v.at(1) = " << v.at(1) << std::endl;
        std::cout << "  v.at(5) = " << v.at(5) << std::endl;   // throws
    } catch (const std::out_of_range &e) {
        std::cout << "  Caught out_of_range: " << e.what() << std::endl;
    }

    // ── 2. Multiple catch blocks ──────────────────────────────────────────────
    std::cout << "\n=== 2. Multiple catch blocks ===" << std::endl;

    std::vector<std::string> inputs = {"42", "abc", "-5", "99999999999"};

    for (const auto &input : inputs) {
        try {
            int val = parse_positive_int(input);
            std::cout << "  Parsed '" << input << "' = " << val << std::endl;
        } catch (const std::invalid_argument &e) {
            std::cout << "  Invalid argument for '" << input << "': " << e.what() << std::endl;
        } catch (const std::out_of_range &e) {
            std::cout << "  Out of range for '" << input << "': " << e.what() << std::endl;
        } catch (const std::domain_error &e) {
            std::cout << "  Domain error for '" << input << "': " << e.what() << std::endl;
        }
    }

    // ── 3. Custom exceptions ──────────────────────────────────────────────────
    std::cout << "\n=== 3. Custom Exceptions ===" << std::endl;

    try {
        BankAccount account("Alice", 500.0);
        account.deposit(200.0);
        account.withdraw(100.0);
        account.withdraw(1000.0);   // throws InsufficientFundsError
    } catch (const InsufficientFundsError &e) {
        std::cout << "  " << e.what() << std::endl;
        std::cout << "  Balance: $" << e.balance()
                  << "  Requested: $" << e.amount() << std::endl;
    } catch (const NegativeAmountError &e) {
        std::cout << "  " << e.what() << std::endl;
    }

    // ── 4. Catching by base class ─────────────────────────────────────────────
    std::cout << "\n=== 4. Catching by std::exception ===" << std::endl;

    // Always catch the most specific exception first.
    // std::exception catches everything as a fallback.
    try {
        BankAccount account("Bob", 100.0);
        account.withdraw(-50.0);   // throws NegativeAmountError
    } catch (const InsufficientFundsError &e) {
        std::cout << "  InsufficientFunds: " << e.what() << std::endl;
    } catch (const std::invalid_argument &e) {
        // NegativeAmountError inherits from invalid_argument — caught here
        std::cout << "  invalid_argument: " << e.what() << std::endl;
    } catch (const std::exception &e) {
        // Fallback — catches anything inheriting from std::exception
        std::cout << "  std::exception: " << e.what() << std::endl;
    } catch (...) {
        // Last resort — catches absolutely anything, including non-std exceptions
        std::cout << "  Unknown exception caught" << std::endl;
    }

    // ── 5. Re-throwing exceptions ─────────────────────────────────────────────
    std::cout << "\n=== 5. Re-throwing ===" << std::endl;

    auto process = [](int value) {
        try {
            if (value < 0) {
                throw std::runtime_error("negative value in process()");
            }
            std::cout << "  process(" << value << ") OK" << std::endl;
        } catch (const std::exception &e) {
            std::cout << "  process() caught and re-throwing: " << e.what() << std::endl;
            throw;   // re-throw the same exception — preserves original type
        }
    };

    try {
        process(5);
        process(-1);
    } catch (const std::exception &e) {
        std::cout << "  Outer catch: " << e.what() << std::endl;
    }

    // ── 6. Exceptions in constructors ─────────────────────────────────────────
    std::cout << "\n=== 6. Exception in Constructor ===" << std::endl;

    try {
        BankAccount bad_account("Charlie", -100.0);   // throws
    } catch (const NegativeAmountError &e) {
        std::cout << "  Constructor threw: " << e.what() << std::endl;
        std::cout << "  Object was never constructed — no cleanup needed" << std::endl;
    }

    // ── 7. std::optional — exception-free error signaling ─────────────────────
    std::cout << "\n=== 7. std::optional ===" << std::endl;

    // No exceptions — caller checks if result has a value
    auto result1 = safe_divide(10, 3);
    auto result2 = safe_divide(10, 0);

    if (result1.has_value()) {
        std::cout << "  10 / 3 = " << result1.value() << std::endl;
    }

    if (!result2.has_value()) {
        std::cout << "  10 / 0 = undefined (division by zero)" << std::endl;
    }

    // value_or() — return a default if empty
    std::cout << "  result2.value_or(-1) = " << result2.value_or(-1) << std::endl;

    std::vector<double> data  = {1.5, 2.5, 3.5, 4.5};
    std::vector<double> empty = {};

    auto avg1 = find_average(data);
    auto avg2 = find_average(empty);

    std::cout << "  avg of {1.5,2.5,3.5,4.5}: "
              << avg1.value_or(0.0) << std::endl;
    std::cout << "  avg of {}: "
              << (avg2.has_value() ? std::to_string(avg2.value()) : "no data") << std::endl;

    // ── 8. noexcept ───────────────────────────────────────────────────────────
    std::cout << "\n=== 8. noexcept ===" << std::endl;
    std::cout << "  safe_abs(-7) = " << safe_abs(-7) << std::endl;
    std::cout << "  safe_abs(3)  = " << safe_abs(3)  << std::endl;
    std::cout << "  noexcept functions: compiler can optimize more aggressively" << std::endl;

    // ── 9. Standard exception hierarchy ──────────────────────────────────────
    std::cout << "\n=== 9. Standard Exception Hierarchy ===" << std::endl;
    std::cout << "  std::exception" << std::endl;
    std::cout << "  ├── std::logic_error      — errors in program logic (preventable)" << std::endl;
    std::cout << "  │   ├── invalid_argument  — bad argument value" << std::endl;
    std::cout << "  │   ├── domain_error      — argument outside valid domain" << std::endl;
    std::cout << "  │   ├── length_error      — exceeds max allowable size" << std::endl;
    std::cout << "  │   └── out_of_range      — value outside expected range" << std::endl;
    std::cout << "  └── std::runtime_error    — errors only detectable at runtime" << std::endl;
    std::cout << "      ├── overflow_error    — arithmetic overflow" << std::endl;
    std::cout << "      ├── underflow_error   — arithmetic underflow" << std::endl;
    std::cout << "      └── range_error       — result outside representable range" << std::endl;

    return 0;
}
