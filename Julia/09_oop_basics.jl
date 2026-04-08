# 09_oop_basics.jl
# Julia doesn't have classes like Python or C++.
# Instead it uses structs for data and multiple dispatch for behaviour.
# This is Julia's core design — and it's more powerful than traditional OOP.

# --- Struct (immutable by default) ---
struct Point
    x::Float64
    y::Float64
end

p = Point(3.0, 4.0)
println(p.x)        # 3.0
println(p.y)        # 4.0

# p.x = 10.0  ← error: immutable struct cannot be modified

# --- Mutable struct ---
mutable struct Person
    name::String
    age::Int
end

alice = Person("Alice", 30)
println(alice.name)     # "Alice"

alice.age = 31          # allowed — mutable
println(alice.age)      # 31

# --- Methods via multiple dispatch ---
# Functions are defined outside the struct — behaviour is attached to types
function greet(p::Person)
    println("Hi, I'm $(p.name) and I'm $(p.age) years old.")
end

function birthday!(p::Person)
    p.age += 1
end

greet(alice)            # "Hi, I'm Alice and I'm 31 years old."
birthday!(alice)
greet(alice)            # "Hi, I'm Alice and I'm 32 years old."

# --- Constructors ---
struct Circle
    radius::Float64
    Circle(r) = r < 0 ? error("Radius cannot be negative") : new(r)
end

c = Circle(5.0)
println(c.radius)       # 5.0
# Circle(-1.0)          # error: "Radius cannot be negative"

# --- Multiple dispatch ---
# The same function name behaves differently depending on argument types
struct Rectangle
    width::Float64
    height::Float64
end

area(c::Circle)    = π * c.radius^2
area(r::Rectangle) = r.width * r.height
area(p::Point)     = 0.0    # a point has no area

println(area(Circle(5.0)))          # 78.53...
println(area(Rectangle(4.0, 6.0)))  # 24.0
println(area(Point(1.0, 2.0)))      # 0.0

# --- Abstract types (like interfaces / base classes) ---
abstract type Animal end

struct Dog <: Animal
    name::String
end

struct Cat <: Animal
    name::String
end

speak(a::Dog) = println("$(a.name) says: Woof!")
speak(a::Cat) = println("$(a.name) says: Meow!")

dog = Dog("Rex")
cat = Cat("Whiskers")

speak(dog)      # "Rex says: Woof!"
speak(cat)      # "Whiskers says: Meow!"

# Works polymorphically
animals = Animal[dog, cat, Dog("Buddy")]
for a in animals
    speak(a)
end
