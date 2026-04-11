// 13_file_io.cpp
//
// File I/O in C++ using fstream.
// Reading, writing, and appending to files.
// Text mode and structured data.
//
// Compile: g++ -std=c++17 -Wall -o 13_file_io 13_file_io.cpp

#include <iostream>
#include <fstream>     // std::ifstream, ofstream, fstream
#include <sstream>     // std::stringstream
#include <string>
#include <vector>
#include <stdexcept>

// ── A simple struct to demonstrate structured file I/O ────────────────────────
struct Student {
    std::string name;
    int         grade;
    double      gpa;
};

// ── Write students to a CSV file ──────────────────────────────────────────────
void write_students(const std::string &filename, const std::vector<Student> &students) {
    std::ofstream file(filename);   // opens for writing, truncates if exists

    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing: " + filename);
    }

    // Write header
    file << "name,grade,gpa\n";

    // Write each student
    for (const auto &s : students) {
        file << s.name << "," << s.grade << "," << s.gpa << "\n";
    }

    std::cout << "  Wrote " << students.size() << " students to " << filename << std::endl;
}   // file closed automatically here (RAII — ofstream destructor)

// ── Read students from a CSV file ─────────────────────────────────────────────
std::vector<Student> read_students(const std::string &filename) {
    std::ifstream file(filename);   // opens for reading

    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for reading: " + filename);
    }

    std::vector<Student> students;
    std::string line;

    // Skip header line
    std::getline(file, line);

    // Read each data line
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string token;
        Student s;

        std::getline(ss, s.name,  ',');
        std::getline(ss, token,   ',');
        s.grade = std::stoi(token);
        std::getline(ss, token,   ',');
        s.gpa   = std::stod(token);

        students.push_back(s);
    }

    return students;
}   // file closed automatically

// ── Count lines and words in a file ──────────────────────────────────────────
void analyze_file(const std::string &filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Cannot open: " + filename);
    }

    int    line_count = 0;
    int    word_count = 0;
    int    char_count = 0;
    std::string line;

    while (std::getline(file, line)) {
        ++line_count;
        char_count += static_cast<int>(line.size()) + 1;   // +1 for newline

        std::stringstream ss(line);
        std::string word;
        while (ss >> word) {
            ++word_count;
        }
    }

    std::cout << "  Lines: " << line_count << std::endl;
    std::cout << "  Words: " << word_count << std::endl;
    std::cout << "  Chars: " << char_count << std::endl;
}

int main() {
    // ── 1. Write a plain text file ────────────────────────────────────────────
    std::cout << "=== 1. Writing a Text File ===" << std::endl;

    {
        std::ofstream out("hello.txt");
        if (!out) {
            std::cerr << "Failed to open hello.txt for writing" << std::endl;
            return 1;
        }

        out << "Hello from C++ file I/O!\n";
        out << "Line 2: the quick brown fox\n";
        out << "Line 3: jumps over the lazy dog\n";

        std::cout << "  Written to hello.txt" << std::endl;
    }   // out goes out of scope — file closed automatically

    // ── 2. Read a plain text file line by line ────────────────────────────────
    std::cout << "\n=== 2. Reading a Text File ===" << std::endl;

    {
        std::ifstream in("hello.txt");
        if (!in) {
            std::cerr << "Failed to open hello.txt for reading" << std::endl;
            return 1;
        }

        std::string line;
        int line_num = 1;
        while (std::getline(in, line)) {
            std::cout << "  [" << line_num++ << "] " << line << std::endl;
        }
    }

    // ── 3. Append to an existing file ────────────────────────────────────────
    std::cout << "\n=== 3. Appending to a File ===" << std::endl;

    {
        std::ofstream out("hello.txt", std::ios::app);   // std::ios::app = append mode
        if (!out) {
            std::cerr << "Failed to open hello.txt for appending" << std::endl;
            return 1;
        }

        out << "Line 4: appended after the fact\n";
        std::cout << "  Appended line 4 to hello.txt" << std::endl;
    }

    // Verify the append by reading the file again
    {
        std::ifstream in("hello.txt");
        std::string line;
        std::cout << "  File now contains:" << std::endl;
        while (std::getline(in, line)) {
            std::cout << "    " << line << std::endl;
        }
    }

    // ── 4. Read entire file into a string ─────────────────────────────────────
    std::cout << "\n=== 4. Read Entire File into String ===" << std::endl;

    {
        std::ifstream in("hello.txt");
        std::string content(
            (std::istreambuf_iterator<char>(in)),
            std::istreambuf_iterator<char>()
        );
        std::cout << "  File length: " << content.size() << " bytes" << std::endl;
        std::cout << "  First 20 chars: " << content.substr(0, 20) << "..." << std::endl;
    }

    // ── 5. Read word by word ──────────────────────────────────────────────────
    std::cout << "\n=== 5. Read Word by Word ===" << std::endl;

    {
        std::ifstream in("hello.txt");
        std::string word;
        std::vector<std::string> words;
        while (in >> word) {
            words.push_back(word);
        }
        std::cout << "  Total words: " << words.size() << std::endl;
        std::cout << "  First 5: ";
        for (int i = 0; i < 5 && i < static_cast<int>(words.size()); ++i) {
            std::cout << words[i] << " ";
        }
        std::cout << std::endl;
    }

    // ── 6. Structured data — CSV write and read ───────────────────────────────
    std::cout << "\n=== 6. Structured Data (CSV) ===" << std::endl;

    std::vector<Student> students = {
        {"Alice",   12, 3.9},
        {"Bob",     11, 3.4},
        {"Carol",   12, 3.7},
        {"Dave",    10, 3.1},
        {"Eve",     11, 3.8},
    };

    write_students("students.csv", students);

    std::vector<Student> loaded = read_students("students.csv");
    std::cout << "  Loaded " << loaded.size() << " students:" << std::endl;
    for (const auto &s : loaded) {
        std::cout << "    " << s.name << " | grade " << s.grade
                  << " | GPA " << s.gpa << std::endl;
    }

    // ── 7. File analysis ──────────────────────────────────────────────────────
    std::cout << "\n=== 7. File Analysis ===" << std::endl;
    std::cout << "  hello.txt stats:" << std::endl;
    analyze_file("hello.txt");

    // ── 8. Check if file exists ───────────────────────────────────────────────
    std::cout << "\n=== 8. Check File Existence ===" << std::endl;

    auto file_exists = [](const std::string &path) -> bool {
        std::ifstream f(path);
        return f.good();
    };

    std::cout << "  hello.txt exists?   " << (file_exists("hello.txt")    ? "yes" : "no") << std::endl;
    std::cout << "  students.csv exists? " << (file_exists("students.csv") ? "yes" : "no") << std::endl;
    std::cout << "  missing.txt exists?  " << (file_exists("missing.txt")  ? "yes" : "no") << std::endl;

    // ── 9. fstream — read and write same file ─────────────────────────────────
    std::cout << "\n=== 9. fstream (read + write) ===" << std::endl;

    {
        // Create a file
        std::fstream rw("readwrite.txt", std::ios::out);
        rw << "line one\nline two\nline three\n";
    }

    {
        // Open for both reading and writing
        std::fstream rw("readwrite.txt", std::ios::in | std::ios::out);
        if (!rw) {
            std::cerr << "  Failed to open readwrite.txt" << std::endl;
        } else {
            std::string line;
            std::cout << "  Reading readwrite.txt:" << std::endl;
            while (std::getline(rw, line)) {
                std::cout << "    " << line << std::endl;
            }

            // Clear EOF flag, seek to end, append
            rw.clear();
            rw.seekp(0, std::ios::end);
            rw << "line four (appended via fstream)\n";
            std::cout << "  Appended line four" << std::endl;
        }
    }

    // ── 10. Error handling for file operations ────────────────────────────────
    std::cout << "\n=== 10. Error Handling ===" << std::endl;

    try {
        read_students("nonexistent.csv");
    } catch (const std::runtime_error &e) {
        std::cout << "  Caught: " << e.what() << std::endl;
    }

    // Check stream state after operations
    {
        std::ifstream in("hello.txt");
        std::string line;
        // Read all lines
        while (std::getline(in, line)) {}

        std::cout << "  After reading all lines:" << std::endl;
        std::cout << "    eof()  = " << in.eof()  << "  (reached end of file)" << std::endl;
        std::cout << "    fail() = " << in.fail() << "  (operation failed?)"   << std::endl;
        std::cout << "    good() = " << in.good() << "  (stream healthy?)"     << std::endl;
    }

    // ── 11. Open mode flags summary ───────────────────────────────────────────
    std::cout << "\n=== 11. Open Mode Flags ===" << std::endl;
    std::cout << "  std::ios::in     — open for reading" << std::endl;
    std::cout << "  std::ios::out    — open for writing (truncates)" << std::endl;
    std::cout << "  std::ios::app    — append — writes go to end of file" << std::endl;
    std::cout << "  std::ios::ate    — seek to end immediately after open" << std::endl;
    std::cout << "  std::ios::trunc  — truncate file to zero on open" << std::endl;
    std::cout << "  std::ios::binary — binary mode (no newline translation)" << std::endl;
    std::cout << "  Combine with |:  std::ios::in | std::ios::out" << std::endl;

    std::cout << "\nCreated files: hello.txt, students.csv, readwrite.txt" << std::endl;

    return 0;
}
