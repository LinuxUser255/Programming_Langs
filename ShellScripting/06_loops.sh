#!/usr/bin/env bash

set -euo pipefail


main() {

    # ─────────────────────────────────────────────
    # Basic for loop — iterating a list
    # ─────────────────────────────────────────────

    for fruit in apple banana cherry; do
        echo "$fruit"
    done


    # ─────────────────────────────────────────────
    # For loop — iterating a range
    # ─────────────────────────────────────────────

    for i in {1..5}; do
        echo "Number: $i"
    done


    # ─────────────────────────────────────────────
    # For loop — range with a step
    # {start..end..step}
    # ─────────────────────────────────────────────

    for i in {0..10..2}; do
        echo "Even: $i"
    done


    # ─────────────────────────────────────────────
    # C-style for loop
    # ─────────────────────────────────────────────

    for (( i=0; i<=5; i++ )); do
        echo "i = $i"
    done


    # ─────────────────────────────────────────────
    # While loop
    # ─────────────────────────────────────────────

    count=1
    while [ "$count" -le 5 ]; do
        echo "Count: $count"
        (( count++ ))
    done


    # ─────────────────────────────────────────────
    # Until loop — opposite of while
    # Runs until condition becomes true
    # ─────────────────────────────────────────────

    n=1
    until [ "$n" -gt 5 ]; do
        echo "n = $n"
        (( n++ ))
    done


    # ─────────────────────────────────────────────
    # Loop control: break and continue
    # ─────────────────────────────────────────────

    for i in {1..10}; do
        [ "$i" -eq 3 ] && continue     # skip 3
        [ "$i" -eq 7 ] && break        # stop at 7
        echo "$i"
    done


    # ─────────────────────────────────────────────
    # Loop over an array
    # ─────────────────────────────────────────────

    colors=("red" "green" "blue")
    for color in "${colors[@]}"; do
        echo "$color"
    done


    # ─────────────────────────────────────────────
    # Loop over command output
    # ─────────────────────────────────────────────

    for file in $(ls /tmp); do
        echo "File: $file"
    done


    # ─────────────────────────────────────────────
    # CODE GOLF — compact loop styles
    #
    # Bash lets you collapse loops onto one line.
    # Useful for quick one-liners in the terminal.
    # ─────────────────────────────────────────────

    # Expansion — standard one-liner
    for i in {1..10}; do echo "$i"; done

    # Undocumented method — replaces do...done with { }
    for i in {1..10}; { echo "$i"; }

    # C-style one-liner
    for (( i=0; i<=10; i++ )); do echo "$i"; done

    # Tiny C-style — omit init and update, let i++ live in condition
    # i is implicitly 0 (unset treated as 0 in arithmetic context)
    i=0
    for (( ; i++<10; )) { echo "$i"; }

}

main
