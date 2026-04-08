# Creating Safe Subshells



## 1. `$()` Spawns a Subshell — Avoid in Tight Loops

Every `$()` is a fork. The OS clones the entire bash process, runs the command in the child, pipes the result back to the parent, then the child dies. That lifecycle has real cost.

```bash
# Bad — 3 forks per file, multiplied across every file
for file in *.log; do
    base=$(basename "$file")       # fork 1
    size=$(du -sh "$file")         # fork 2
    ts=$(date +%H:%M:%S)           # fork 3
    echo "$ts $base $size"
done

# Good — zero forks, all builtins
for file in *.log; do
    base="${file##*/}"             # parameter expansion, no fork
    printf '%(%H:%M:%S)T  %s\n' -1 "$base"   # printf builtin, no fork
    # du still needs a fork — it's external, no way around that one
done
```

The key is isolating which commands *must* be external (like `du`) and which can be replaced with builtins. Only fork when you have no alternative.

```bash
# Another common bad pattern — subshell inside a condition
if [[ $(wc -l < file.txt) -gt 100 ]]; then

# Better — avoid the subshell entirely with grep -c
if grep -c '' file.txt | grep -q '^[1-9][0-9][0-9]'; then

# Or just use awk once at the end, outside a loop
awk 'END { exit (NR <= 100) }' file.txt && echo "over 100 lines"
```

```bash
# Subshell cost compounds inside nested loops — very bad
for dir in */; do
    for file in "$dir"*.log; do
        owner=$(stat -c '%U' "$file")    # fork on every file in every dir
        echo "$owner: $file"
    done
done

# Better — let find + stat do one pass
find . -name "*.log" -exec stat -c '%U %n' {} +
```

---

## 2. `[[ ]]` Over `[ ]`

`[ ]` is a real external command that lives on disk. You can find it at `/usr/bin/[` on many systems. Every time you write `[ ]` in a script, bash has to look it up, fork, execute it, and wait for it to return. `[[ ]]` is a bash keyword — it never leaves the process.

```bash
# Bad — external command, forks every evaluation
if [ "$status" = "active" ]; then
if [ -f "$file" ] && [ -r "$file" ]; then   # two forks

# Good — builtin keyword, no fork, and supports && inside
if [[ "$status" == "active" ]]; then
if [[ -f "$file" && -r "$file" ]]; then     # one evaluation, no fork
```

`[[ ]]` also removes several whole categories of bugs that `[ ]` is prone to:

```bash
# Bad — word splitting bites you if $name has spaces
if [ $name = "alice" ]; then       # breaks if name="alice smith"

# Good — [[ ]] never word-splits variables
if [[ $name == "alice" ]]; then    # safe, no quotes even needed here
```

`[[ ]]` also gives you regex matching for free, which would otherwise require forking `grep`:

```bash
# Bad — forks grep just to test a pattern
if echo "$input" | grep -q '^[0-9]+$'; then
    echo "is a number"
fi

# Good — [[ =~ ]] does regex natively, no fork
if [[ "$input" =~ ^[0-9]+$ ]]; then
    echo "is a number"
fi
```

```bash
# Practical example — validating an IP address without any forks
ip="192.168.1.1"
octet='([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])'
if [[ "$ip" =~ ^$octet\.$octet\.$octet\.$octet$ ]]; then
    echo "Valid IP"
fi
```

---

## 3. `(( ))` for Arithmetic

`expr` is an external binary. `$(( ))` is a subshell. `(( ))` is a builtin that does arithmetic entirely inside the current process — no fork, no pipe, no child process.

```bash
# Bad — expr is an external command, forks every call
result=$(expr $a + $b)
count=$(expr $count + 1)

# Bad — $(( )) is still a subshell (lighter than expr, but still forks)
result=$(( a + b ))

# Good — (( )) is a builtin, runs in-process
(( result = a + b ))
(( count++ ))
(( count += 1 ))
```

Inside loops this matters a lot:

```bash
# Bad — forking expr 10,000 times
total=0
for i in $(seq 1 10000); do
    total=$(expr $total + $i)
done

# Good — (( )) never leaves the shell
total=0
for (( i=1; i<=10000; i++ )); do
    (( total += i ))
done
```

`(( ))` also works cleanly as a condition — it exits 0 (true) when the expression is nonzero, and 1 (false) when zero, just like a proper conditional:

```bash
# Idiomatic — read like "if count is at or above MAX"
if (( count >= MAX_JOBS )); then
    wait "${joblist[0]}"
fi

# Also works as a standalone expression
(( count++ ))         # increment
(( seen[$key]++ ))    # increment associative array value
(( total += size ))   # accumulate
```

```bash
# Practical: byte counter without any forks
total=0
while IFS= read -r line; do
    (( total += ${#line} ))   # ${#line} is string length, also a builtin
done < file.txt
echo "Total bytes: $total"
```

---

## 4. Redirect Once, Not Per Line

A file descriptor is a resource the OS manages. Opening a file with `>>` inside a loop means: open file, seek to end, write, close file — on every single iteration. With thousands of lines that's thousands of open/close syscalls.

```bash
# Bad — file opened and closed on every line
while IFS= read -r line; do
    echo "$line" >> output.txt     # syscall: open, seek, write, close
done < input.txt

# Good — file opened once before the loop, closed once after
while IFS= read -r line; do
    echo "$line"                   # just writes to stdout
done < input.txt > output.txt     # redirect happens once, outside
```

This extends to any block, not just while loops:

```bash
# Bad — opening the log file on every function call
log() {
    echo "$(date): $*" >> app.log
}

# Good — open once at script start, write via fd for the rest of execution
exec 3>> app.log      # open fd 3 pointing to app.log

log() {
    printf '%(%H:%M:%S)T %s\n' -1 "$*" >&3    # write to already-open fd
}
```

The `exec 3>>` trick opens a file descriptor at the process level. Every subsequent write to `&3` reuses the same open handle — one open syscall for the entire script lifetime.

```bash
# Practical: processing and filtering a large file in one pass
# Bad — three passes over the file, three opens
grep "ERROR" app.log > errors.txt
grep "WARN"  app.log > warnings.txt
grep "INFO"  app.log > info.txt

# Good — one pass, three output redirects held open by awk
awk '
    /ERROR/ { print > "errors.txt" }
    /WARN/  { print > "warnings.txt" }
    /INFO/  { print > "info.txt" }
' app.log
```

---

## 5. `read -r` Always

Without `-r`, bash interprets backslashes inside the input as escape sequences — `\n` becomes a newline, `\t` a tab, and a trailing `\` causes it to join the next line. This is almost never what you want when reading files, and it costs bash extra parsing work on every line.

```bash
# Bad — backslashes get consumed and interpreted
while read line; do
    echo "$line"
done < file.txt
# Input:  C:\Users\alice\docs
# Output: C:UsersalicedocsF   (backslashes eaten)

# Good — read -r passes backslashes through literally
while IFS= read -r line; do
    echo "$line"
done < file.txt
# Input:  C:\Users\alice\docs
# Output: C:\Users\alice\docs
```

`IFS=` (empty) alongside `-r` prevents a second class of bugs — leading and trailing whitespace being stripped:

```bash
# Bad — leading spaces stripped by default IFS
while read -r line; do
    echo "$line"
done <<< "    indented content"
# Output: "indented content"  (spaces gone)

# Good — IFS= preserves all whitespace
while IFS= read -r line; do
    echo "$line"
done <<< "    indented content"
# Output: "    indented content"
```

This matters especially when reading config files, code, or any structured text where indentation is meaningful.

```bash
# Practical: reading a CSV where fields may contain backslashes
while IFS=',' read -r name path value; do
    echo "Name:  $name"
    echo "Path:  $path"    # C:\Windows\System32 preserved correctly
    echo "Value: $value"
done < data.csv
```

---

## 6. `grep -q` Not `grep | /dev/null`

`grep` by default reads the entire file and prints every match. `-q` (quiet mode) tells it to stop the moment it finds the first match and return immediately. That means for a 1 million line file where the match is on line 3, `-q` reads 3 lines. Without it, grep reads all 1 million.

```bash
# Bad — reads entire file, spawns a pipe process to discard output
if grep "ERROR" app.log > /dev/null; then

# Bad — pipe to /dev/null is an extra forked process
if grep "ERROR" app.log | cat > /dev/null; then

# Good — stops at first match, no pipe, no extra process
if grep -q "ERROR" app.log; then
    echo "Errors found"
fi
```

Inside a loop this is dramatic:

```bash
# Bad — full file scan on every iteration
for log in /var/log/*.log; do
    if grep "CRITICAL" "$log" > /dev/null; then
        echo "Alert in: $log"
    fi
done

# Good — short-circuits on first match in each file
for log in /var/log/*.log; do
    if grep -q "CRITICAL" "$log"; then
        echo "Alert in: $log"
    fi
done
```

```bash
# Practical: check if a user exists before doing work
username="alice"

if grep -q "^${username}:" /etc/passwd; then
    echo "$username exists"
else
    echo "$username not found"
fi

# Combined with -l to find which files contain a pattern (stops per-file)
grep -rl "TODO" ./src      # -r recursive, -l filename only, -q implicit per file
```

---

## 7. `cut`, `tr`, `sed`, `awk` — Use Judiciously

These are powerful tools but every invocation is an external process. The goal is to use them **once on many lines** rather than **many times on one line each**.

```bash
# Bad — forks awk on every file
for file in *.log; do
    size=$(awk 'END{print NR}' "$file")    # fork per file
    echo "$file: $size lines"
done

# Good — one awk call handles all files
awk 'FNR==1{ if(NR>1) print file": "count" lines"; file=FILENAME; count=0 }
     { count++ }
     END { print file": "count" lines" }' *.log
```

Use **parameter expansion** as a drop-in replacement for `cut`, `basename`, `dirname`, and simple `sed` — all with zero forks:

```bash
file="/var/log/nginx/access.log.gz"

# Bad — forks for each of these
base=$(basename "$file")           # fork
dir=$(dirname "$file")             # fork
name=$(echo "$base" | cut -d. -f1) # fork + pipe
ext=$(echo "$base" | cut -d. -f2)  # fork + pipe

# Good — parameter expansion, all builtins, zero forks
base="${file##*/}"          # access.log.gz  (strip longest leading path)
dir="${file%/*}"            # /var/log/nginx  (strip filename)
name="${base%%.*}"          # access          (strip longest trailing ext)
ext="${base#*.}"            # log.gz          (strip shortest leading part)
```

The parameter expansion operators to memorize:

```bash
var="hello.world.txt"

${var#*.}    # world.txt      — remove shortest match from front
${var##*.}   # txt            — remove longest match from front
${var%.*}    # hello.world    — remove shortest match from back
${var%%.*}   # hello          — remove longest match from back
```

For `tr` and simple character replacement, bash can handle it directly:

```bash
# Bad — forks tr just to uppercase a string
upper=$(echo "$name" | tr '[:lower:]' '[:upper:]')

# Good — bash 4+ has builtin case conversion
upper="${name^^}"    # uppercase
lower="${name,,}"    # lowercase
```

When you genuinely need `awk` or `sed`, batch everything into one call:

```bash
# Bad — sed called once per line to process a file
while IFS= read -r line; do
    cleaned=$(echo "$line" | sed 's/[[:space:]]*$//')   # fork per line
    echo "$cleaned"
done < input.txt

# Good — sed processes the entire file in one call
sed 's/[[:space:]]*$//' input.txt > output.txt
```

---

## The Summary Cheatsheet

```
ALWAYS                          INSTEAD OF
------                          ----------
[[ ]]                           [ ] or test
(( ))                           expr or $(( ))
${var##*/}                      $(basename "$var")
${var%/*}                       $(dirname "$var")
${var^^} / ${var,,}             $(echo "$var" | tr ...)
grep -q                         grep | /dev/null
redirect > once outside loop    >> inside loop
IFS= read -r                    read (bare)
one awk/sed on whole file       awk/sed per line in loop
```

The underlying principle is always the same: **the shell is fastest when it stays inside itself.** Every time you reach for an external command, you're paying a fork-exec-wait tax. Pay it once on large data, not repeatedly on small data.

