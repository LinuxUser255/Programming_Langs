# 06_conditionals.jl
# if / elseif / else — note: no parentheses required around conditions.

x = 15

# Basic if / elseif / else
if x > 20
    println("greater than 20")
elseif x > 10
    println("greater than 10")      # this runs
else
    println("10 or less")
end

# Comparison operators
println(5 == 5)     # true
println(5 != 4)     # true
println(5 > 3)      # true
println(5 < 3)      # false
println(5 >= 5)     # true
println(5 <= 4)     # false

# Logical operators
println(true && false)  # false  (and)
println(true || false)  # true   (or)
println(!true)          # false  (not)

# Ternary operator
age = 20
status = age >= 18 ? "adult" : "minor"
println(status)     # "adult"

# Nested conditions
score = 85
if score >= 90
    println("A")
elseif score >= 80
    println("B")           # this runs
elseif score >= 70
    println("C")
else
    println("F")
end

# if as an expression — returns a value
label = if x > 10
    "big"
else
    "small"
end
println(label)      # "big"

# Check types in conditions
val = 42
if isa(val, Int)
    println("val is an Int")
end

# Chained comparisons (Julia supports these natively)
n = 5
if 1 < n < 10
    println("n is between 1 and 10")    # this runs
end
