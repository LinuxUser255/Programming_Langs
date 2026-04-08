#!/usr/bin/env bash

set -euo pipefail


main() {

    # ─────────────────────────────────────────────
    # Basic case statement
    # Syntax:
    #   case "$variable" in
    #       pattern) commands ;;
    #   esac
    # ─────────────────────────────────────────────

    day="Monday"

    case "$day" in
        "Monday")
            echo "Start of the work week."
        ;;

        "Friday")
            echo "End of the work week."
        ;;

        "Saturday" | "Sunday")
            echo "Weekend!"
        ;;

        *)
            echo "Midweek: $day"
        ;;
    esac


    # ─────────────────────────────────────────────
    # Wildcard / glob patterns in case
    #
    # *   matches anything
    # ?   matches any single character
    # [abc] matches a, b, or c
    # ─────────────────────────────────────────────

    filename="report.pdf"

    case "$filename" in
        *.pdf)
            echo "PDF file."
        ;;

        *.txt | *.md)
            echo "Text file."
        ;;

        *.jpg | *.png)
            echo "Image file."
        ;;

        *)
            echo "Unknown file type."
        ;;
    esac


    # ─────────────────────────────────────────────
    # The Neofetch pattern — using : and $_
    #
    # The : (colon) is a no-op command in bash.
    # It does nothing, but it does set $_ to its last argument.
    # $_ always holds the last argument of the last command run.
    #
    # This lets you set a value inside a case branch
    # without needing a separate variable assignment in each branch.
    # Then after the case block, you capture it once with os="$_"
    # ─────────────────────────────────────────────

    case "$OSTYPE" in
        "darwin"*)
            : "MacOS"
        ;;

        "linux"*)
            : "Linux"
        ;;

        *"bsd"* | "dragonfly" | "bitrig")
            : "BSD"
        ;;

        "cygwin" | "msys" | "win32")
            : "Windows"
        ;;

        *)
            printf '%s\n' "Unknown OS detected, aborting..." >&2
            exit 1
        ;;
    esac

    # Capture the value set by : inside the case block
    os="$_"
    echo "Detected OS: $os"

}

main
