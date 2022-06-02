require('api.graph')

pathos = pathos or {}

-- @brief Creates a graph from the map weight
function pathos.getMapGraph()
    local n = map_size()
    local g = Graph:new(n * n)

    for i = 1, n do
        ::continue::
        for j = 1, n do
            if not (weight(i, j) > 0) then goto continue end -- we got a wall here
            local neighbours = {
                weight(i-1, j),
                weight(i, j-1),
                weight(i, j+1),
                weight(i+1, j)
            }

            -- Nodes id are in the form of (i * map_size + j)

            for id, w in pairs(neighbours) do
                if (w > 0) then
                    g:addEdge(i * n + j, id)
                end
            end
        end
    end

    return g
end
