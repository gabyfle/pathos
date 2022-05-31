---
-- pathos engine
-- Default script for Pathos
-- Gabriel Santamaria - 2022
---

local entsByLine = math.floor(ents_number() / map_size()) + ents_number() % map_size()

-- Function that handles the spawning of the elements
-- This function spawn entities homogeneously on the whole map
function spawn(id, pos)
    local w = weight(pos[1], pos[2])

    local row = pos[1] + 1
    local line = pos[2] + 1

    if w <= 0 then return false end
    if (id // line >= entsByLine) then
        return false or math.random() > 0.999
    end
    if (id // row >= entsByLine) then
        return false or math.random() > 0.999
    end

    return math.random() >= 0.09
end

-- Function that is applied to each entity, each frame
-- to determine its movements
function entity(id)
    local d = { {1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} }
    return d[math.random(1, #d)]
end

-- Algorithm to create the escape plan
function algorithm()
end
