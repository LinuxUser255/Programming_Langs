# 10_data_structures.jl
# Julia's core built-in data structures.

# ── Tuple ──────────────────────────────────────────────────────────────────
# Immutable, ordered, fixed size. Good for grouping related values.

t = (1, "hello", 3.14)
println(t)          # (1, "hello", 3.14)
println(t[1])       # 1   (1-based)
println(t[end])     # 3.14

# Unpack
a, b, c = t
println(b)          # "hello"

# Named tuple
person = (name="Alice", age=30)
println(person.name)    # "Alice"
println(person.age)     # 30


# ── Array ──────────────────────────────────────────────────────────────────
# Mutable, ordered, dynamically sized. Julia's workhorse collection.

nums = [10, 20, 30, 40, 50]
push!(nums, 60)
pop!(nums)
println(nums)           # [10, 20, 30, 40, 50]

# 2D array (matrix)
m = [1 2 3;
     4 5 6;
     7 8 9]
println(m)
println(m[2, 3])        # 6  (row 2, col 3)


# ── Dict ───────────────────────────────────────────────────────────────────
# Mutable, unordered key-value store.

scores = Dict("alice" => 95, "bob" => 87)
scores["carol"] = 92
delete!(scores, "bob")
println(scores)

for (k, v) in scores
    println("$k => $v")
end


# ── Set ────────────────────────────────────────────────────────────────────
# Unordered collection of unique values. Fast membership testing.

s = Set([1, 2, 3, 2, 1])
println(s)              # Set([2, 3, 1])  — duplicates removed

push!(s, 4)
delete!(s, 2)
println(s)

println(3 in s)         # true
println(99 in s)        # false

# Set operations
a = Set([1, 2, 3, 4])
b = Set([3, 4, 5, 6])

println(union(a, b))        # {1,2,3,4,5,6}
println(intersect(a, b))    # {3,4}
println(setdiff(a, b))      # {1,2}  — in a but not b


# ── Stack (via Array) ───────────────────────────────────────────────────────
# LIFO — Last In, First Out

stack = []
push!(stack, "first")
push!(stack, "second")
push!(stack, "third")
println(pop!(stack))    # "third"  (last in, first out)
println(stack)


# ── Queue (via Deque from DataStructures.jl or array) ──────────────────────
# FIFO — First In, First Out — using plain array

queue = []
push!(queue, "a")       # enqueue
push!(queue, "b")
push!(queue, "c")
println(popfirst!(queue))   # "a"  (first in, first out)
println(queue)


# ── Range ──────────────────────────────────────────────────────────────────
# Efficient — stores only start, stop, step. No memory for intermediate values.

r = 1:10
println(r)              # 1:10
println(collect(r))     # [1,2,3,4,5,6,7,8,9,10]  — materialise to array

r2 = 0:5:50
println(collect(r2))    # [0,5,10,15,20,25,30,35,40,45,50]


# ── Summary table ──────────────────────────────────────────────────────────
println("""
Structure   | Ordered | Mutable | Unique keys | Use for
------------|---------|---------|-------------|----------------------------
Array       |   yes   |   yes   |     no      | general list / sequence
Tuple       |   yes   |   no    |     no      | fixed grouping of values
NamedTuple  |   yes   |   no    |    keys     | lightweight record / row
Dict        |   no    |   yes   |    keys     | key-value lookup
Set         |   no    |   yes   |   values    | membership / deduplication
Range       |   yes   |   no    |     no      | efficient numeric sequence
""")
