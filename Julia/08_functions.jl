# 08_functions.jl
# Functions are first-class in Julia. The last expression is the return value.

# --- Basic function ---
function greet(name)
    println("Hello, $name!")
end

greet("Alice")      # "Hello, Alice!"

# --- Return a value ---
function add(a, b)
    return a + b    # explicit return
end

println(add(3, 4))  # 7

# --- Implicit return (last expression is returned) ---
function multiply(a, b)
    a * b           # no return keyword needed
end

println(multiply(6, 7))     # 42

# --- Default arguments ---
function greet_lang(name, lang="Julia")
    println("Hello from $lang, $name!")
end

greet_lang("Bob")               # "Hello from Julia, Bob!"
greet_lang("Bob", "Rust")       # "Hello from Rust, Bob!"

# --- Keyword arguments (after the semicolon) ---
function connect(host; port=8080, ssl=false)
    println("Connecting to $host:$port  ssl=$ssl")
end

connect("localhost")
connect("example.com", port=443, ssl=true)

# --- Multiple return values (returns a Tuple) ---
function min_max(arr)
    return minimum(arr), maximum(arr)
end

lo, hi = min_max([3, 1, 4, 1, 5, 9])
println("min=$lo  max=$hi")     # min=1  max=9

# --- Compact one-line function syntax ---
square(x) = x^2
println(square(5))      # 25

# --- Anonymous functions (lambdas) ---
double = x -> x * 2
println(double(10))     # 20

# Can be used inline
nums = [1, 2, 3, 4, 5]
doubled = map(x -> x * 2, nums)
println(doubled)        # [2, 4, 6, 8, 10]

# --- Variadic functions (splat operator) ---
function total(nums...)
    sum(nums)
end

println(total(1, 2, 3, 4, 5))   # 15

# --- Type annotations on arguments ---
function divide(a::Float64, b::Float64)
    if b == 0.0
        error("Division by zero")
    end
    a / b
end

println(divide(10.0, 4.0))      # 2.5

# --- Higher order functions ---
function apply(f, value)
    f(value)
end

println(apply(square, 6))       # 36
println(apply(x -> x + 100, 6)) # 106

# --- filter, map, reduce ---
nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
evens    = filter(x -> x % 2 == 0, nums)
squares  = map(x -> x^2, nums)
total    = reduce(+, nums)

println(evens)      # [2, 4, 6, 8, 10]
println(squares)    # [1, 4, 9, 16, 25, 36, 49, 64, 81, 100]
println(total)      # 55
