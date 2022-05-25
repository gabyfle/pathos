## About

Lua api code of the `pathos` engine.

## API Documentations and usage

The Lua's API of ` pathos` is very simple and lightweight to understand, and it contains everything you need to create escape plans.

For complete usage examples, please, feel free to see the folder `scripts` of the `pathos` project.

### Map

#### `map_size()`

`map_size()` returns the size (in tiles) of the map.

Example:
```lua
local ms = map_size()

print(string.format("Size of the map: %d", ms))
```


#### `safe_size()`

`safe_size()` returns the size (in tiles) of the safe area.

Example:
```lua
local ss = safe_size()

print(string.format("Size of the safe area: %d", ss))
```


#### `weight(i, j)`

`weight(i, j)` returns the weight of the tile at position (i, j).

Example:
```lua
local m_size = map_size() -- we get the size of the map
local w = weight(i, j)

local i = math.random(1, m_size)
local j = math.random(1, m_size)

print(string.format("Weight of tile (%d, %d): %f", i, j, w))
```

### Entities

#### `ents_number()`

`ents_number()` returns the number of entities in the simulation.

Example:
```lua
local en = ents_number()

print(string.format("NUmber of entities: %d", en))
```

#### `ent_pos(id)`

`ent_pos(id)` returns the tile number of the entity of id `id`.

Example:
```lua
local id = math.random(1, ents_number())

print(string.format("Position of entity of id %d: %d", id, ent_pos(id)))
```
