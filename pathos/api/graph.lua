---
-- pathos engine
-- Graph code for Pathos' Lua API
-- Gabriel Santamaria - 2022
---

local WHITE, DARK = 0, 1

Graph = Graph or {}
Graph.__index = Graph

Graph.Edge = Graph.Edge or {}
Graph.Edge.__index = Graph.Edge

Graph.Node = Graph.Node or {}
Graph.Node.__index = Graph.Node

--- Node:new()
-- @breif Creates a new node
function Graph.Node:create()
    local obj = {}
    setmetatable(obj, self)

    obj.neighbours = {}
    obj.color = WHITE

    return obj
end

--- Node:getNeighbours()
-- @brief Returns the neighbours list of the node
function Graph.Node:getNeighbours()
    return self.neighbours
end

--- Node:addNeighbour(node)
-- @brief Adds a new neighbour in the neighbours list of the node
-- @param node: node to add to the list
function Graph.Node:addNeighbour(node)
    self.neighbours[#self.neighbours+1] = node
end

--- Node:mark()
-- @breif Marks or unmarks the current node (used for algorithms such as bfs)
function Graph.Node:mark()
    self.color = 1 - self.color
end

--- Node:getMark()
-- @brief Returns the current state of the node
function Graph.Node:getMark()
    return self.color
end

--- Edge:new(s, e, weight)
-- @brief Creates a new edge between two nodes
-- @param s : starting node
-- @param e : ending node
-- @param weight: weight of the connection between the two nodes
function Graph.Edge:create(s, e, weight)
    local obj = {}
    setmetatable(obj, self)

    obj.s = s
    obj.e = e
    obj.weight = weight or 0

    s:addNeighbour(e)

    return obj
end

--- Edge:starting()
-- @brief Returns the starting node
function Graph.Edge:starting()
    return self.s
end

--- Edge:ending()
-- @brief Returns the ending node
function Graph.Edge:ending()
    return self.e
end

--- Edge:weight()
-- @brief Returns the weight of the edge
function Graph.Edge:weight()
    return self.weight
end

--- Edge:setWeight(w)
-- @brief change the weight of the edge
-- @param w : new weight
function Graph.Edge:setWeight(w)
    self.weight = w
end

--- Graph:new()
-- @brief Graph class constructor
-- @param int n: number of nodes
function Graph:new(n)
    local obj = {}
    setmetatable(obj, self)

    obj.edges = {}
    obj.nodes = {}

    for _ = 1, n do obj.nodes[#obj.nodes+1] = self.Node:create() end

    return obj
end

--- Graph:addEdge(n, m, weight, bi)
-- @brief Adds a new edge to the graph
-- @param n: starting node id
-- @param m: ending node id
-- @param weight: weight of the edge
-- @param bi: whether or not the edge is bidirectionnal
function Graph:addEdge(n, m, weight, bi)
    if (n > #self.nodes) or (m > #self.nodes) then error("Something went wrong with the given parameter", 2) end
    if not type(bi) == "boolean" then error("An error occurred: wrong parameter", 2) end
    weight = weight or 0

    self.edges[#self.edges+1] = self.Edge:create(self.nodes[n], self.nodes[m], weight)
    -- if the edge is "bidirectionnal", we're adding the same edge in the other direction
    if bi then self.edges[#self.edges+1] = self.Edge:create(self.nodes[m], self.nodes[n], weight) end
end

--- Graph:bfs(start, f)
-- @brief Breadth-First Search algorithm
-- @param start: starting node of the algorithm
-- @param f: function to apply on each node
function Graph:bfs(start, f)
    local file = {}

    file[#file+1] = start

    start:mark()

    while #file > 0 do
        local s = file[#file]
        file[#file] = nil -- equivalent to file:pop if we were using queues
        f(s)
        for _, node in pairs(s:getNeighbours()) do
            if node:getMark() == WHITE then
                file[#file+1] = node
                node:mark()
            end
        end
    end
end
