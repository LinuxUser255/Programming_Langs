#!/usr/bin/env bash

set -euo pipefail


# ─────────────────────────────────────────────
# Declaring functions
# Two valid styles, both identical in behavior
# ─────────────────────────────────────────────

# Style 1 — function keyword
function greet {
    echo "Hello, World!"
}

# Style 2 — parentheses (more portable, preferred)
greet2() {
    echo "Hello again, World!"
}

# Code golf — one liner
say_hi() { echo "Hi!"; }


# ─────────────────────────────────────────────
# Arguments
# $1, $2, $3... are positional arguments
# $@ is all arguments
# $# is the argument count
# ─────────────────────────────────────────────

greet_user() {
    local name="$1"
    local age="$2"
    echo "Name: $name | Age: $age"
}

# Compact version
greet_compact() { echo "Hello, $1!"; }


# ─────────────────────────────────────────────
# Default argument values
# ─────────────────────────────────────────────

greet_default() {
    local name="${1:-stranger}"
    echo "Hello, $name!"
}


# ─────────────────────────────────────────────
# Return values
# bash functions return exit codes (0=success, 1=failure)
# To return a value, use echo and capture with $()
# ─────────────────────────────────────────────

add() {
    local result=$(( $1 + $2 ))
    echo "$result"
}

is_even() {
    (( $1 % 2 == 0 ))      # returns 0 (true) or 1 (false) automatically
}

# Compact math function
square() { echo $(( $1 * $1 )); }
cube()   { echo $(( $1 * $1 * $1 )); }


# ─────────────────────────────────────────────
# Local vs global scope
# ─────────────────────────────────────────────

counter=0

increment() {
    local step="${1:-1}"        # local — only lives inside this function
    (( counter += step ))       # counter is global — modified directly
}


# ─────────────────────────────────────────────
# Recursive functions
# ─────────────────────────────────────────────

factorial() {
    local n="$1"
    (( n <= 1 )) && echo 1 && return
    echo $(( n * $(factorial $(( n - 1 ))) ))
}

# Fibonacci — compact recursive style
fib() { (( $1 <= 1 )) && echo "$1" || echo $(( $(fib $(($1-1))) + $(fib $(($1-2))) )); }


# ─────────────────────────────────────────────
# Functions as commands — with exit codes
# Use return 0 for success, return 1 for failure
# Lets you use functions directly in if statements
# ─────────────────────────────────────────────

file_exists() { [[ -f "$1" ]]; }
is_empty()    { [[ -z "$1" ]]; }
is_number()   { [[ "$1" =~ ^[0-9]+$ ]]; }


# ─────────────────────────────────────────────
# Variadic functions — accepting any number of args
# ─────────────────────────────────────────────

sum_all() {
    local total=0
    for n in "$@"; do
        (( total += n ))
    done
    echo "$total"
}

print_all() { for arg in "$@"; do echo "  -> $arg"; done; }


# ─────────────────────────────────────────────
# main — call everything here
# ─────────────────────────────────────────────

main() {

    echo "--- Basic function calls ---"
    greet
    greet2
    say_hi


    echo ""
    echo "--- Arguments ---"
    greet_user "Alice" 30
    greet_compact "Bob"


    echo ""
    echo "--- Default arguments ---"
    greet_default "Alice"
    greet_default              # uses default: stranger


    echo ""
    echo "--- Return values ---"
    result=$(add 7 3)
    echo "7 + 3 = $result"

    echo "square of 5 = $(square 5)"
    echo "cube of 3   = $(cube 3)"

    is_even 4 && echo "4 is even" || echo "4 is odd"
    is_even 7 && echo "7 is even" || echo "7 is odd"


    echo ""
    echo "--- Scope ---"
    echo "Counter before: $counter"
    increment
    increment 5
    echo "Counter after:  $counter"


    echo ""
    echo "--- Recursion ---"
    echo "5! = $(factorial 5)"
    echo "fib(8) = $(fib 8)"


    echo ""
    echo "--- Functions as commands ---"
    if file_exists "/etc/hostname"; then
        echo "/etc/hostname exists."
    fi

    is_number "42"  && echo "42 is a number."
    is_number "abc" || echo "abc is not a number."

    is_empty "" && echo "empty string detected."


    echo ""
    echo "--- Variadic functions ---"
    echo "Sum of 1 2 3 4 5 = $(sum_all 1 2 3 4 5)"
    print_all "apple" "banana" "cherry"

}

main
