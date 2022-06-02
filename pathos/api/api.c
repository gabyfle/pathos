/**
 * 
 * pathos - Simulation engine 
 * 2022 - Gabriel Santamaria
 * 
 * LUA C API - SEE README.md FOR API DOCUMENTATION
 * 
**/

#include "api.h"

DATA * data;
MAP_DATA * m_data;
Entity * entities;

/**
 * @brief Returns the size of the safe area
 * 
 * @param L 
 * @return int 
 */
static int lua_get_safe_size(lua_State * L)
{
    lua_pushinteger(L, m_data->safe_size);
    return 1;
}

/**
 * @brief Returns the size of the map
 * 
 * @param L 
 * @return int 
 */
static int lua_get_map_size(lua_State * L)
{
    lua_pushinteger(L, m_data->map_size);
    return 1;
}

/**
 * @brief Returns the size of a tile in pixels
 * 
 * @param L 
 * @return int 
 */
static int lua_get_tile_size(lua_State * L)
{
    lua_pushinteger(L, m_data->tile_size);
    return 1;
}

/**
 * @brief Returns weight(i, j)
 * 
 * @param L 
 * @return int 
 */
static int lua_get_map_weight(lua_State * L)
{
    int i = luaL_checkinteger(L, 1);
    int j = luaL_checkinteger(L, 2);

    if (i < 0 || i > m_data->map_size)
        luaL_error(L, "Parameter i must be between %d and %d", 0, m_data->map_size);

    if (j < 0 || j > m_data->map_size)
        luaL_error(L, "Parameter j must be between %d and %d", 0, m_data->map_size);


    weight w = m_data->map[i * m_data->map_size + j];

    lua_pushnumber(L, (double) w);

    return 1;
}

/**
 * @brief Returns the number of entities in the simulation
 * 
 * @param L 
 * @return int 
 */
static int lua_get_entity_number(lua_State * L)
{
    lua_pushinteger(L, data->ents_number);
    return 1;
}

/**
 * @brief Returns the tiles number where the entity is.
 * 
 * @param L 
 * @return int 
 */
static int lua_get_entity_pos(lua_State * L)
{
    int id = luaL_checkinteger(L, 1);

    if (id > data->ents_number || 0 > id)
        luaL_error(L, "Entity number %d doens't exist.", id);

    lua_pushnumber(L, entities[id].tile_id);
    return 1;   
}

/**
 * @brief Initialize the Lua API.
 * 
 * @param map_data 
 */
void init_api(lua_State * L, DATA * d, MAP_DATA * map_data)
{
    print(1, "Initializing the Lua API.");

    m_data = map_data;
    data = d;

    lua_pushcfunction(L, lua_get_tile_size);
    lua_setglobal(L, "tile_size");

    lua_pushcfunction(L, lua_get_map_size);
    lua_setglobal(L, "map_size");

    lua_pushcfunction(L, lua_get_safe_size);
    lua_setglobal(L, "safe_size");

    lua_pushcfunction(L, lua_get_map_weight);
    lua_setglobal(L, "weight");

    lua_pushcfunction(L, lua_get_entity_number);
    lua_setglobal(L, "ents_number");

    if (luaL_loadfile(L, "api/api.lua") || lua_pcall(L, 0, 0, 0))
        error(L, "Unable to load script file: %s", lua_tostring(L, -1)); 

    print(2, "Lua API initialized.");
}

/**
 * @brief ENtities Lua API initialization
 * 
 * @param ents 
 */
void init_ents_api(lua_State * L, Entity * ents)
{
    entities = ents;

    lua_pushcfunction(L, lua_get_entity_pos);
    lua_setglobal(L, "ent_pos");
}
