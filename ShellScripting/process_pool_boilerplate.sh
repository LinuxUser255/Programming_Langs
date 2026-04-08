#!/usr/bin/env bash


set -euo pipefail

# Auto-detect CPU count, or you can set it manually
MAX_JOBS=$(nproc)
joblist=()


#TODO: Put your code here, in the `task()` and `main()` functions.
# Everything else is infrastructure.
task() {
        local item="$1"

        echo "Done: $item"
}


#INFO: Process Pool. Treat this like a library function. Do not touch.
run_pool() {
        task "$1" &
        joblist+=($!)  # Save job Process ID for later waiting

        # Process Pool full: wait for the oldest job to finish, then remove it from the list
        if (( ${#jobslist[@]} >= MAX_JOBS )); then
            wait "${joblist[0]}"
            joblist=("${joblist[@]:1}")
        fi
}


#INFO: Main function.
# Put your code from the `task()` function here.
main() {
    for item in "$@"; do
        run_pool "$item"
    done

    wait # drain any remaining jobs
    echo "All jobs done."

}

main "$@"

