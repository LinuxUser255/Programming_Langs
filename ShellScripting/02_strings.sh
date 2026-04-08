#!/usr/bin/env bash

set -euo pipefail


main() {

    # ─────────────────────────────────────────────
    # Declaring strings
    # ─────────────────────────────────────────────

    name="Alice"
    greeting='Hello, World!'     # Single quotes: no variable expansion
    echo "$name"
    echo "$greeting"


    # ─────────────────────────────────────────────
    # Concatenation
    # ─────────────────────────────────────────────

    first="Hello"
    second="World"
    combined="$first, $second!"
    echo "$combined"


    # ─────────────────────────────────────────────
    # String length
    # ─────────────────────────────────────────────

    word="Bash"
    echo "Length: ${#word}"          # 4


    # ─────────────────────────────────────────────
    # Substrings
    # ${var:start:length}
    # ─────────────────────────────────────────────

    str="Hello, World!"
    echo "${str:7:5}"               # World
    echo "${str:0:5}"               # Hello


    # ─────────────────────────────────────────────
    # Uppercase / Lowercase  (bash 4+)
    # ─────────────────────────────────────────────

    text="hello world"
    echo "${text^^}"                # HELLO WORLD  (all uppercase)
    echo "${text^}"                 # Hello world  (first char uppercase)

    text2="HELLO WORLD"
    echo "${text2,,}"               # hello world  (all lowercase)
    echo "${text2,}"                # hELLO WORLD  (first char lowercase)


    # ─────────────────────────────────────────────
    # Find and replace
    # ${var/find/replace}   — replaces first match
    # ${var//find/replace}  — replaces all matches
    # ─────────────────────────────────────────────

    sentence="I like cats and cats like me."
    echo "${sentence/cats/dogs}"    # I like dogs and cats like me.
    echo "${sentence//cats/dogs}"   # I like dogs and dogs like me.


    # ─────────────────────────────────────────────
    # Strip from start / end
    # ${var#pattern}   — strip shortest match from start
    # ${var##pattern}  — strip longest match from start
    # ${var%pattern}   — strip shortest match from end
    # ${var%%pattern}  — strip longest match from end
    # ─────────────────────────────────────────────

    filepath="/home/user/docs/report.pdf"
    echo "${filepath##*/}"          # report.pdf   (strip path, keep filename)
    echo "${filepath%/*}"           # /home/user/docs  (strip filename, keep path)
    echo "${filepath##*.}"          # pdf          (strip everything, keep extension)


    # ─────────────────────────────────────────────
    # Default values
    # ${var:-default}  — use default if var is unset or empty
    # ─────────────────────────────────────────────

    unset username
    echo "${username:-guest}"       # guest


    # ─────────────────────────────────────────────
    # Checking if a string is empty / not empty
    # ─────────────────────────────────────────────

    value=""
    [ -z "$value" ] && echo "String is empty."
    [ -n "$name"  ] && echo "String is not empty: $name"


    # ─────────────────────────────────────────────
    # Multiline strings (heredoc)
    # ─────────────────────────────────────────────

    cat <<EOF
This is a
multiline string.
Name: $name
EOF

}

main
