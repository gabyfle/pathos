## About

Lua api code of the `pathos` engine.

## API Documentations and usage

The Lua's API of ` pathos` is very simple and lightweight to understand, and it contains everything you need to create escape plans.

### safe_size()

`safe_size()` returns the size (in tiles) of the safe area.

Example:
```lua
local ss = safe_size()

print(string.format("Size of the safe area: %d", ss))
```


### weight(i, j)

`weight(i, j)` returns the weight of the tile at position (i, j).

Example:
```lua
local m_size = map_size() -- we get the size of the map
local w = weight(i, j)

local i = math.random(0, m_size)

print(string.format("Weight of tile (%d, %d): %f", i, j, w))
```
