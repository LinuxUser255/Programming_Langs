# 04_variables_constants.jl
# Julia is dynamically typed but you can annotate types.
# Variables are mutable. Constants are declared with const.

# Basic assignment
x = 10
name = "Julia"
pi_approx = 3.14159
is_fun = true

println(x)          # 10
println(name)       # "Julia"
println(pi_approx)  # 3.14159
println(is_fun)     # true

# Type annotation (optional, but good for clarity and performance)
y::Int64 = 42
z::Float64 = 3.14
println(y)
println(z)

# Check type at runtime
println(typeof(x))          # Int64
println(typeof(name))       # String
println(typeof(pi_approx))  # Float64
println(typeof(is_fun))     # Bool

# Multiple assignment
a, b, c = 1, 2, 3
println(a, b, c)    # 123

# Swap without a temp variable
a, b = b, a
println(a, b)       # 21

# Constants — cannot be reassigned
const MAX_JOBS = 8
const APP_NAME = "MyApp"
println(MAX_JOBS)   # 8
println(APP_NAME)   # "MyApp"

# Reassigning a const raises a warning (or error depending on context)
# MAX_JOBS = 9  ← would warn: "redefining constant"

# Julia has built-in math constants
println(pi)         # 3.141592653589793
println(ℯ)          # 2.718281828459045  (type \euler then Tab)
println(Inf)        # Inf
println(NaN)        # NaN

# Numeric types
println(typemax(Int64))     # 9223372036854775807
println(typemin(Int64))     # -9223372036854775808

# Type conversion
n = 3.9
println(Int(floor(n)))      # 3  — truncates
println(Float64(42))        # 42.0
println(string(100))        # "100"
println(parse(Int, "42"))   # 42
