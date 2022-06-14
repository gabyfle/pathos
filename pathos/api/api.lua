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
                { i-1, j, weight(i-1, j) },
                { i, j-1, weight(i, j-1) },
                { i, j+1, weight(i, j+1) },
                { i+1, j, weight(i+1, j) }
            }

            -- Nodes id are in the form of (i * map_size + j)

            for _, w in pairs(neighbours) do
                if (w[3] > 0) then
                    g:addEdge(i * n + j, w[1] * n + w[2])
                end
            end
        end
    end

    -- Now we can try to delete useless nodes so that processing the graph
    -- will be much quicker

    for k, node in pairs(g:getNodes()) do
        if true then
            
        end
    end

    return g
end
