# 07_loops.jl
# Julia has for and while loops. Ranges are 1-based and inclusive.

# --- for loop over a range ---
for i in 1:5
    println(i)          # 1 2 3 4 5
end

# Step in a range
for i in 1:2:10
    print("$i ")        # 1 3 5 7 9
end
println()

# Countdown
for i in 5:-1:1
    print("$i ")        # 5 4 3 2 1
end
println()

# --- for loop over an array ---
fruits = ["apple", "banana", "cherry"]
for fruit in fruits
    println(fruit)
end

# With index using enumerate
for (i, fruit) in enumerate(fruits)
    println("$i: $fruit")
end

# --- while loop ---
n = 1
while n <= 5
    println(n)
    n += 1
end

# --- break and continue ---
for i in 1:10
    if i == 3
        continue        # skip 3
    end
    if i == 7
        break           # stop at 7
    end
    print("$i ")        # 1 2 4 5 6
end
println()

# --- nested loops ---
for i in 1:3
    for j in 1:3
        print("($i,$j) ")
    end
    println()
end

# --- loop as expression with comprehension ---
evens = [x for x in 1:10 if x % 2 == 0]
println(evens)          # [2, 4, 6, 8, 10]

# --- while with a condition and break ---
x = 100
while true
    x -= 17
    if x < 0
        break
    end
    println(x)
end

# --- zip: loop over two arrays together ---
names  = ["Alice", "Bob", "Carol"]
scores = [95, 87, 92]
for (name, score) in zip(names, scores)
    println("$name scored $score")
end
