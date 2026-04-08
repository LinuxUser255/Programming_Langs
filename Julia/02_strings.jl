# 02_strings.jl
# Strings in Julia use double quotes. Single quotes are for single characters (Char).

greeting = "Hello, Julia!"

# Length
println(length(greeting))           # 13

# Indexing — Julia is 1-based, not 0-based
println(greeting[1])                # 'H'
println(greeting[end])              # '!'

# Slicing (inclusive range)
println(greeting[1:5])              # "Hello"

# Concatenation with *
first = "Hello"
second = "World"
println(first * ", " * second)      # "Hello, World"

# Repetition with ^
println("ha" ^ 3)                   # "hahaha"

# Interpolation
lang = "Julia"
ver  = 1.9
println("$lang version $ver")       # "Julia version 1.9"

# Common string functions
println(uppercase("hello"))         # "HELLO"
println(lowercase("HELLO"))         # "hello"
println(strip("  hello  "))         # "hello"
println(replace("cat", "c" => "b")) # "bat"
println(startswith("Julia", "Ju"))  # true
println(endswith("Julia", "ia"))    # true
println(contains("Julia", "ul"))    # true

# Split and join
words = split("one two three")
println(words)                      # ["one", "two", "three"]
println(join(words, "-"))           # "one-two-three"

# Multi-line string
msg = """
Line one
Line two
Line three
"""
println(msg)
