-- 05_functions.lua
local function add(a, b)
    return a + b
end

local function greet(name, age)
    age = age or 25
    print("Hello " .. name .. ", you are " .. age)
end

greet("Bob")
greet("Alice", 32)
print("Sum: " .. add(5, 7))
