# 01_hello.jl
# Your first Julia program.
# Run it: julia 01_hello.jl

# Basic print
println("Hello, World!")

# print() does not add a newline
print("Hello ")
print("Julia\n")

# String interpolation with $
name = "Programmer"
println("Hello, $name!")

# Expression interpolation
x = 7
println("7 squared is $(x^2)")
