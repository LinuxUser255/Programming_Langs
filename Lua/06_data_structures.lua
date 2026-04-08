-- 06_data_structures.lua
-- Tables are both arrays and dictionaries
local nums = {1, 2, 3, 4, 5}
table.insert(nums, 6)

local person = {age = 28}
local unique = {1, 2, 2, 3}  -- duplicates kept in array part

print("List size: " .. #nums)

-- Count unique (simple demo)
local set = {}
for _, v in ipairs({1,2,2,3}) do
    set[v] = true
end
local uniqueCount = 0
for _ in pairs(set) do uniqueCount = uniqueCount + 1 end
print("Unique set size: " .. uniqueCount)
