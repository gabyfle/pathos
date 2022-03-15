--[[----------------------------
--                            --
--    pathos map generator    --
--          2022              --
-- Code from: rosettacode.org --
--                            --
-----------------------]]-------
local random = math.random
local print = print

math.randomseed(os.time())

local height = 400 -- each map is 400x400 tile
local width  = 400

local grid = {}

for i=1, (height * 2 + 1) do
    grid[i] = {}
    for j=1, (width * 2 + 1) do
        grid[i][j] = true
    end
end

--- shuffle
-- Reorder a table in a random way using Fisher-Yates
local function shuffle(t)
    local n  = #t
    for i=n, 1, -1 do
        local j = random(1, i)
        t[j], t[i] = t[i], t[j]
    end

    return t
end

--- average
--- Returns the average for a and b
local function average(a, b)
    return (a + b) / 2
end

--- recursive_bracktraking
-- The recursive backtracking algorithm for maze generation
--- Algorithm from: https://rosettacode.org/wiki/Maze_generation#Lua
local function rec_bracktraking(w, h)
    local directions = {
        {x = 0, y = -2},
        {x = 2, y = 0},
        {x = -2, y = 0},
        {x = 0, y = 2},
    }

    local function walk(x, y)
        grid[y][x] = false

        local d = { 1, 2, 3, 4 }
        shuffle(d)
        for _, dirnum in ipairs(d) do
            local xx = x + directions[dirnum].x
            local yy = y + directions[dirnum].y
            if grid[yy] and grid[yy][xx] then
                grid[average(y, yy)][average(x, xx)] = false
                walk(xx, yy)
            end
        end
    end
   
    walk(random(1, w) * 2, random(1, h) * 2)
end

--- write_map
-- Write the grid into the map so that we can use it inside the Pathos engine
local function write_map(path, grid, safe)
    local file = io.open(path, "w+")
    file:write(tostring(safe) .. "\n")

    local s = {}
    for i=1, (height * 2 + 1) do
        for j=1, (width * 2 + 1) do
            if grid[i][j] then
                table.insert(s, "#")
            else
                table.insert(s, " ")
            end
        end
        table.insert(s, "\n")
    end
    file:write(table.concat(s))
end

local safe = random(1, math.floor(height / 2)) -- safe area
rec_bracktraking(width, height)
write_map("default.txt", grid, safe)
