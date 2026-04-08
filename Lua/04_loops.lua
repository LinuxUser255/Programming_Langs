-- 04_loops.lua
-- For loop (numeric)
for i = 0, 4 do
    io.write("For: " .. i .. " ")
end
print()

-- Table iteration (like for-each)
local numbers = {10, 20, 30}
for _, num in ipairs(numbers) do
    io.write(num .. " ")
end
print()

-- While
local count = 0
while count < 3 do
    print("While: " .. count)
    count = count + 1
end
