// 11_stl.cpp
//
// The Standard Template Library — C++'s built-in collection of containers,
// algorithms, and iterators. This is what you use day-to-day in real code.
//
// This file expands on 06_data_structures.cpp which showed containers exist.
// Here we show how to actually use them.
//
// Compile: g++ -std=c++17 -Wall -o 11_stl 11_stl.cpp

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>   // sort, find, count, min_element, max_element
#include <numeric>     // accumulate, iota
#include <iterator>    // begin, end

// ── Helper: print a vector ────────────────────────────────────────────────────
template <typename T>
void print_vec(const std::vector<T> &v, const std::string &label) {
    std::cout << "  " << label << ": [";
    for (int i = 0; i < static_cast<int>(v.size()); ++i) {
        std::cout << v[i];
        if (i < static_cast<int>(v.size()) - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

int main() {
    // ── 1. std::vector — dynamic array ───────────────────────────────────────
    std::cout << "=== 1. std::vector ===" << std::endl;

    std::vector<int> nums = {5, 3, 8, 1, 9, 2, 7, 4, 6};
    print_vec(nums, "original");

    nums.push_back(10);           // add to end
    nums.insert(nums.begin(), 0); // insert at front
    print_vec(nums, "after push_back(10) and insert(0 at front)");

    nums.pop_back();              // remove from end
    nums.erase(nums.begin());     // remove from front
    print_vec(nums, "after pop_back and erase front");

    std::cout << "  size:     " << nums.size()     << std::endl;
    std::cout << "  front:    " << nums.front()    << std::endl;
    std::cout << "  back:     " << nums.back()     << std::endl;
    std::cout << "  at(2):    " << nums.at(2)      << std::endl;   // bounds-checked
    std::cout << "  capacity: " << nums.capacity() << std::endl;   // reserved memory

    // Range-based for loop — idiomatic C++11+
    std::cout << "  range-for: ";
    for (const int &n : nums) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    // Iterator-based loop
    std::cout << "  iterator: ";
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // ── 2. std::vector with algorithms ───────────────────────────────────────
    std::cout << "\n=== 2. Algorithms on vector ===" << std::endl;

    std::vector<int> v = {5, 3, 8, 1, 9, 2, 7, 4, 6};
    print_vec(v, "unsorted");

    std::sort(v.begin(), v.end());
    print_vec(v, "sorted ascending");

    std::sort(v.begin(), v.end(), std::greater<int>());
    print_vec(v, "sorted descending");

    std::sort(v.begin(), v.end());   // re-sort ascending for rest of examples

    // find — returns iterator
    auto it = std::find(v.begin(), v.end(), 7);
    if (it != v.end()) {
        std::cout << "  found 7 at index: " << std::distance(v.begin(), it) << std::endl;
    }

    // count
    std::vector<int> dupes = {1, 2, 2, 3, 2, 4};
    std::cout << "  count of 2 in {1,2,2,3,2,4}: "
              << std::count(dupes.begin(), dupes.end(), 2) << std::endl;

    // min/max
    std::cout << "  min: " << *std::min_element(v.begin(), v.end()) << std::endl;
    std::cout << "  max: " << *std::max_element(v.begin(), v.end()) << std::endl;

    // accumulate — sum
    int total = std::accumulate(v.begin(), v.end(), 0);
    std::cout << "  sum: " << total << std::endl;

    // reverse
    std::reverse(v.begin(), v.end());
    print_vec(v, "reversed");

    // fill a vector with sequential numbers using iota
    std::vector<int> seq(10);
    std::iota(seq.begin(), seq.end(), 1);   // fill with 1..10
    print_vec(seq, "iota 1..10");

    // ── 3. std::map — ordered key-value store ─────────────────────────────────
    std::cout << "\n=== 3. std::map (ordered) ===" << std::endl;

    std::map<std::string, int> scores;
    scores["Alice"] = 95;
    scores["Bob"]   = 82;
    scores["Carol"] = 91;
    scores["Dave"]  = 78;

    // Iterates in key-sorted order (alphabetical here)
    std::cout << "  All scores (sorted by key):" << std::endl;
    for (const auto &[name, score] : scores) {   // structured bindings (C++17)
        std::cout << "    " << name << ": " << score << std::endl;
    }

    // Lookup
    std::cout << "  Bob's score: " << scores["Bob"] << std::endl;

    // Safe lookup with find ([] inserts a default if key missing)
    auto found = scores.find("Eve");
    if (found == scores.end()) {
        std::cout << "  Eve not found" << std::endl;
    } else {
        std::cout << "  Eve: " << found->second << std::endl;
    }

    // contains (C++20) or count for existence check in C++17
    std::cout << "  Alice in map? " << (scores.count("Alice") > 0 ? "yes" : "no") << std::endl;

    // Erase
    scores.erase("Dave");
    std::cout << "  After erasing Dave, size: " << scores.size() << std::endl;

    // ── 4. std::unordered_map — hash map (faster lookup, no order) ────────────
    std::cout << "\n=== 4. std::unordered_map (hash map) ===" << std::endl;

    std::unordered_map<std::string, std::string> capitals;
    capitals["France"]  = "Paris";
    capitals["Germany"] = "Berlin";
    capitals["Japan"]   = "Tokyo";
    capitals["USA"]     = "Washington D.C.";

    std::cout << "  Capital of Japan: " << capitals["Japan"] << std::endl;
    std::cout << "  Size: " << capitals.size() << std::endl;

    // O(1) average lookup vs O(log n) for std::map
    std::cout << "  Use unordered_map when order doesn't matter (faster)" << std::endl;
    std::cout << "  Use map when you need sorted iteration" << std::endl;

    // ── 5. std::set — unique sorted values ────────────────────────────────────
    std::cout << "\n=== 5. std::set ===" << std::endl;

    std::set<int> unique_nums = {5, 3, 8, 3, 1, 5, 9, 1};
    std::cout << "  Input: {5, 3, 8, 3, 1, 5, 9, 1}" << std::endl;
    std::cout << "  Set (unique + sorted): ";
    for (const int n : unique_nums) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    unique_nums.insert(7);
    unique_nums.insert(3);   // duplicate — ignored
    std::cout << "  After insert(7) and insert(3): size = " << unique_nums.size() << std::endl;

    std::cout << "  Contains 8? " << (unique_nums.count(8) ? "yes" : "no") << std::endl;
    std::cout << "  Contains 4? " << (unique_nums.count(4) ? "yes" : "no") << std::endl;

    // ── 6. std::unordered_set — hash set (faster, no order) ──────────────────
    std::cout << "\n=== 6. std::unordered_set ===" << std::endl;

    std::unordered_set<std::string> seen;
    std::vector<std::string> words = {"apple", "banana", "apple", "cherry", "banana", "date"};

    std::cout << "  Unique words from input: ";
    for (const auto &word : words) {
        if (seen.find(word) == seen.end()) {
            std::cout << word << " ";
            seen.insert(word);
        }
    }
    std::cout << std::endl;

    // ── 7. Lambda functions with algorithms ───────────────────────────────────
    std::cout << "\n=== 7. Lambdas with Algorithms ===" << std::endl;

    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // sort with custom comparator (descending)
    std::sort(data.begin(), data.end(), [](int a, int b) {
        return a > b;
    });
    print_vec(data, "sorted descending via lambda");

    // count_if — count elements matching a predicate
    std::sort(data.begin(), data.end());
    int even_count = std::count_if(data.begin(), data.end(), [](int n) {
        return n % 2 == 0;
    });
    std::cout << "  Even numbers in [1..10]: " << even_count << std::endl;

    // find_if — find first element matching predicate
    auto first_gt5 = std::find_if(data.begin(), data.end(), [](int n) {
        return n > 5;
    });
    if (first_gt5 != data.end()) {
        std::cout << "  First number > 5: " << *first_gt5 << std::endl;
    }

    // for_each — apply a function to every element
    std::cout << "  Doubled values: ";
    std::for_each(data.begin(), data.end(), [](int n) {
        std::cout << n * 2 << " ";
    });
    std::cout << std::endl;

    // ── 8. Container comparison summary ──────────────────────────────────────
    std::cout << "\n=== 8. Container Comparison ===" << std::endl;
    std::cout << "  vector        — ordered, indexed, O(1) end insert, O(n) search" << std::endl;
    std::cout << "  map           — key-value, sorted by key, O(log n) all ops"     << std::endl;
    std::cout << "  unordered_map — key-value, hash table, O(1) avg lookup"         << std::endl;
    std::cout << "  set           — unique values, sorted, O(log n) all ops"        << std::endl;
    std::cout << "  unordered_set — unique values, hash table, O(1) avg lookup"     << std::endl;

    return 0;
}
