-- 03_conditionals.lua
local age = 20

if age < 18 then
    print("Minor")
elseif age >= 18 and age < 65 then
    print("Adult")
else
    print("Senior")
end

local status = "active"
if status == "active" then
    print("User is active")
else
    print("Unknown")
end
