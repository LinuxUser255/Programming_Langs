#!/usr/bin/env bash

set -euo pipefail


main() {

    # ─────────────────────────────────────────────
    # Basic if / elif / else
    # ─────────────────────────────────────────────

    age=20

    if [ "$age" -lt 13 ]; then
        echo "Child."
    elif [ "$age" -lt 18 ]; then
        echo "Teenager."
    else:
        echo "Adult."
    fi

    # ─────────────────────────────────────────────
    # Comparing strings
    # ─────────────────────────────────────────────

    name="Alice"

    if [ "$name" = "Alice" ]; then
        echo "Hello, Alice!"
    else
        echo "You are not Alice."
    fi


    # ─────────────────────────────────────────────
    # Checking if a file exists
    # ─────────────────────────────────────────────

    file="test.txt"

    if [ -f "$file" ]; then
        echo "$file exists."
    else
        echo "$file does not exist."
    fi


    # ─────────────────────────────────────────────
    # Short circuit: &&  and  ||
    #
    # cmd1 && cmd2  — run cmd2 only if cmd1 succeeds
    # cmd1 || cmd2  — run cmd2 only if cmd1 fails
    # ─────────────────────────────────────────────

    # && example: only prints if the variable is set and non-empty
    [ -n "$name" ] && echo "Name is set: $name"

    # || example: fallback if a command fails
    [ -f "$file" ] || echo "Warning: $file is missing."


    # ─────────────────────────────────────────────
    # Ternary-style: condition && "true value" || "false value"
    # This is the closest bash gets to a ternary operator.
    # ─────────────────────────────────────────────

    score=75
    result=$( [ "$score" -ge 60 ] && echo "Pass" || echo "Fail" )
    echo "Result: $result"


    # Another common ternary pattern using arithmetic
    is_even=$(( score % 2 == 0 ? 1 : 0 ))
    echo "Is even: $is_even"   # 1 = true, 0 = false
}

main


