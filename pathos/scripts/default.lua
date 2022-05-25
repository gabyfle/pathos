---
-- pathos engine
-- Default script for Pathos
-- Gabriel Santamaria - 2022
---

-- Function that is applied to each entity, each frame
-- to determine its movements
function entity(id)
    local d = { {1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} }
    return d[math.random(1, #d)]
end

-- Algorithm to create the escape plan
function algorithm()
end
