#!/usr/bin/env bash
set -euo pipefail
IFS=$'\n\t'

MAX_JOBS=$(nproc)
joblist=()

task() {
    local dir="dir_$1"
    mkdir -p "$dir"

    for (( f=1; f<=10; f++ )); do
        echo "file_$f.txt" > "$dir/file_$f.txt"
    done

    echo "Done. Created: $dir with 10 files."
}

run_pool() {
    task "$1" &
    joblist+=($!)

    if (( ${#joblist[@]} >= MAX_JOBS )); then
        wait "${joblist[0]}"
        joblist=("${joblist[@]:1}")
    fi
}

main() {
    for (( i=1; i<=10; i++ )); do
        run_pool "$i"
    done

    wait
    echo "All jobs done."
}

main "$@"
