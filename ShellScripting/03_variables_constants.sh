#!/usr/bin/env bash

set -euo pipefail


main() {

    # ─────────────────────────────────────────────
    # Declaring variables
    # No spaces around the = sign
    # ─────────────────────────────────────────────

    name="Alice"
    age=30
    pi=3.14

    echo "$name"
    echo "$age"
    echo "$pi"


    # ─────────────────────────────────────────────
    # Reading a variable
    # Always quote variables to avoid word splitting
    # ─────────────────────────────────────────────

    echo "$name"            # correct
    echo "${name}"          # also correct — braces make boundary explicit


    # ─────────────────────────────────────────────
    # Braces — needed when concatenating
    # ─────────────────────────────────────────────

    prefix="super"
    echo "${prefix}man"     # superman
    echo "$prefixman"       # empty — bash looks for variable named "prefixman"


    # ─────────────────────────────────────────────
    # readonly — constant variables, cannot be changed
    # ─────────────────────────────────────────────

    readonly MAX_RETRIES=5
    echo "Max retries: $MAX_RETRIES"

    # MAX_RETRIES=10  # would cause: bash: MAX_RETRIES: readonly variable


    # ─────────────────────────────────────────────
    # local — scoped to the function, not global
    # ─────────────────────────────────────────────

    demo_scope() {
        local scoped_var="I am local"
        global_var="I am global"
        echo "$scoped_var"
    }

    demo_scope
    echo "$global_var"      # accessible
    # echo "$scoped_var"    # would error: unbound variable


    # ─────────────────────────────────────────────
    # Integer variables with declare -i
    # Arithmetic is evaluated automatically
    # ─────────────────────────────────────────────

    declare -i num=10
    num+=5
    echo "$num"             # 15

    declare -i result=10*3
    echo "$result"          # 30


    # ─────────────────────────────────────────────
    # Arithmetic with (( ))
    # ─────────────────────────────────────────────

    x=10
    y=4

    echo $(( x + y ))       # 14
    echo $(( x - y ))       # 6
    echo $(( x * y ))       # 40
    echo $(( x / y ))       # 2  (integer division)
    echo $(( x % y ))       # 2  (remainder)
    echo $(( x ** y ))      # 10000  (exponent)

    (( x++ ))               # increment
    (( x-- ))               # decrement
    echo "$x"               # 10


    # ─────────────────────────────────────────────
    # Command substitution — store command output in a variable
    # ─────────────────────────────────────────────

    current_date=$(date +"%Y-%m-%d")
    current_user=$(whoami)
    file_count=$(ls /tmp | wc -l)

    echo "Date: $current_date"
    echo "User: $current_user"
    echo "Files in /tmp: $file_count"


    # ─────────────────────────────────────────────
    # Environment variables — available to child processes
    # export makes a variable visible outside the script
    # ─────────────────────────────────────────────

    export APP_ENV="production"
    echo "Environment: $APP_ENV"

    # Common built-in environment variables
    echo "Home dir  : $HOME"
    echo "Shell     : $SHELL"
    echo "Hostname  : $HOSTNAME"
    echo "Path      : $PATH"


    # ─────────────────────────────────────────────
    # Special variables
    # ─────────────────────────────────────────────

    echo "Script name : $0"       # name of the script
    echo "PID         : $$"       # process ID of the script
    echo "Last exit   : $?"       # exit code of last command
    echo "Arg count   : $#"       # number of arguments passed
    echo "All args    : $@"       # all arguments as separate words


    # ─────────────────────────────────────────────
    # Default values
    # ${var:-default}  — use default if unset or empty
    # ${var:=default}  — assign default if unset or empty
    # ${var:?message}  — error and exit if unset or empty
    # ${var:+value}    — use value only if var IS set
    # ─────────────────────────────────────────────

    unset  username
    echo "${username:-guest}"               # guest  (username unchanged)
    echo "${username:=guest}"               # guest  (username is now set to guest)
    echo "$username"                        # guest

    mode="debug"
    echo "${mode:+running in $mode mode}"   # running in debug mode


    # ─────────────────────────────────────────────
    # Unsetting a variable
    # ─────────────────────────────────────────────

    temp="temporary"
    echo "$temp"
    unset temp
    echo "${temp:-gone}"                    # gone

}

main
