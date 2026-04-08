#!/usr/bin/env bash

set -euo pipefail

MAX_JOBS=$(nproc)
joblist=()

# I need a task() function to ping a list of hosts (IPs)
task() { # create the task function
    local host=$1
    if ping -c 1 -W 1 $host &>/dev/null; then
        echo "$host is up"
    else
        echo "$host is down"
    fi
}

run_in_parallel() {
    task "$1" & # calling the task function and run it in the background &
    joblist+=($!)
    if (( ${#joblist[@]} >= $MAX_JOBS )); then
        wait -n
        joblist=("${joblist[@]:1}")
    fi
}


main() {
    local_hosts=("1.1.1.1" "8.8.8.8" "192.168.1.1" "google.com" "github.com")
    for host in "${local_hosts[@]}"; do
        run_in_parallel "$host" # call the run_in_parallel function for each host
    done
    wait
}

main
