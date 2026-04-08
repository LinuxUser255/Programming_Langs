# 03_lists.jl
# Julia uses Arrays instead of lists. They are 1-based and dynamically typed.

# Create an array
nums = [10, 20, 30, 40, 50]

# Access — 1-based indexing
println(nums[1])        # 10
println(nums[end])      # 50

# Slicing (inclusive)
println(nums[2:4])      # [20, 30, 40]

# Modify an element
nums[3] = 99
println(nums)           # [10, 20, 99, 40, 50]

# Add elements
push!(nums, 60)         # append to end
println(nums)           # [10, 20, 99, 40, 50, 60]

pushfirst!(nums, 0)     # prepend to front
println(nums)           # [0, 10, 20, 99, 40, 50, 60]

# Remove elements
pop!(nums)              # remove from end
popfirst!(nums)         # remove from front
println(nums)           # [10, 20, 99, 40, 50]

# Length
println(length(nums))   # 5

# Check membership
println(20 in nums)     # true
println(99 in nums)     # true

# Iterate
for n in nums
    println(n)
end

# Iterate with index
for (i, v) in enumerate(nums)
    println("index $i = $v")
end

# Array comprehension
squares = [x^2 for x in 1:5]
println(squares)        # [1, 4, 9, 16, 25]

# Mixed types
mixed = [1, "hello", 3.14, true]
println(mixed)

# Typed array (more efficient)
ints = Int64[1, 2, 3, 4, 5]
println(ints)

# Useful functions
println(sum(ints))      # 15
println(minimum(ints))  # 1
println(maximum(ints))  # 5
println(sort([3,1,4,1,5,9]))   # [1, 1, 3, 4, 5, 9]
println(reverse([1,2,3]))      # [3, 2, 1]
