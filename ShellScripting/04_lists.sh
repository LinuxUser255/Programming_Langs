#!/usr/bin/env bash

set -euo pipefail


main() {

    # ─────────────────────────────────────────────
    # Declaring an array
    # ─────────────────────────────────────────────

    fruits=("apple" "banana" "cherry" "date" "elderberry")
    echo "${fruits[@]}" # apple

       # ─────────────────────────────────────────────
    # Access elements
    # ─────────────────────────────────────────────

    echo "${fruits[1]}"             # banana
    echo "${fruits[-1]}"            # cherry  (last element)


    # ─────────────────────────────────────────────
    # All elements
    # ─────────────────────────────────────────────

    echo "${fruits[@]}"             # apple banana cherry


    # ─────────────────────────────────────────────
    # Array length
    # ─────────────────────────────────────────────

    echo "${#fruits[@]}"            # 3


    # ─────────────────────────────────────────────
    # Add elements
    # ─────────────────────────────────────────────

    fruits+=("mango")
    fruits+=("grape" "kiwi")
    echo "${fruits[@]}"             # apple banana cherry mango grape kiwi


    # ─────────────────────────────────────────────
    # Modify an element
    # ─────────────────────────────────────────────

    fruits[0]="avocado"
    echo "${fruits[0]}"             # avocado


    # ─────────────────────────────────────────────
    # Remove an element (unset leaves a gap)
    # ─────────────────────────────────────────────

    unset "fruits[1]"
    echo "${fruits[@]}"             # avocado cherry mango grape kiwi


    # ─────────────────────────────────────────────
    # Slice: ${array[@]:start:length}
    # ─────────────────────────────────────────────

    numbers=(10 20 30 40 50)
    echo "${numbers[@]:1:3}"        # 20 30 40


    # ─────────────────────────────────────────────
    # Loop through an array
    # ─────────────────────────────────────────────

    for fruit in "${fruits[@]}"; do
        echo "Fruit: $fruit"
    done


    # ─────────────────────────────────────────────
    # Loop with index
    # ─────────────────────────────────────────────

    for i in "${!fruits[@]}"; do
        echo "$i: ${fruits[$i]}"
    done


    # ─────────────────────────────────────────────
    # Associative array (key/value — like a dictionary)
    # Requires bash 4+, must be declared with -A
    # ─────────────────────────────────────────────

    declare -A person
    person["name"]="Alice"
    person["age"]="30"
    person["city"]="Raleigh"

    echo "${person["name"]}"        # Alice
    echo "${person["age"]}"         # 30

    # Loop over keys and values
    for key in "${!person[@]}"; do
        echo "$key: ${person[$key]}"
    done


    # ─────────────────────────────────────────────
    # Useful: split a string into an array
    # ─────────────────────────────────────────────

    csv="one,two,three,four"
    IFS="," read -ra items <<< "$csv"
    for item in "${items[@]}"; do
        echo "$item"
    done

}

main

