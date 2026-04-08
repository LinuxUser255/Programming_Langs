-- 07_oop_basics.lua
-- Lua uses metatables for OOP
local Person = {}
Person.__index = Person

function Person.new(name, age)
    local self = setmetatable({}, Person)
    self.name = name
    self.age = age
    return self
end

function Person:introduce()
    print("Hi, I'm " .. self.name .. " and I'm " .. self.age .. " years old.")
end

local p = Person.new("Emma", 27)
p:introduce()
