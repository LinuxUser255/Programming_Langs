# 05_dictionaries.jl
# Dictionaries in Julia are called Dict.
# Key-value pairs. Keys must be unique.

# Create a Dict
person = Dict("name" => "Alice", "age" => 30, "city" => "Austin")
println(person)

# Access by key
println(person["name"])     # "Alice"
println(person["age"])      # 30

# Safe access — returns a default if key missing
println(get(person, "name", "unknown"))     # "Alice"
println(get(person, "job", "unknown"))      # "unknown"

# Add or update a key
person["job"] = "Engineer"
person["age"] = 31
println(person)

# Delete a key
delete!(person, "city")
println(person)

# Check if key exists
println(haskey(person, "name"))     # true
println(haskey(person, "city"))     # false

# Keys and values
println(keys(person))
println(values(person))

# Iterate over key-value pairs
for (k, v) in person
    println("$k => $v")
end

# Typed Dict (more efficient)
scores = Dict{String, Int}("alice" => 95, "bob" => 87, "carol" => 92)
println(scores)

# Length
println(length(scores))     # 3

# Merge two dicts
extra = Dict("dave" => 78)
merged = merge(scores, extra)
println(merged)

# Dict comprehension
squares = Dict(x => x^2 for x in 1:5)
println(squares)    # Dict(1=>1, 2=>4, 3=>9, 4=>16, 5=>25)
