/**
 * 
 * pathos - Simulation engine 
 * 2022 - Gabriel Santamaria
 * 
 * LUA C API - SEE README.md FOR API DOCUMENTATION
 * 
**/

#include "api.h"

MAP_DATA * m_data;

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
 * @brief Returns weight(i, j)
 * 
 * @param L 
 * @return int 
 */
static int lua_get_map_weight(lua_State * L)
{
    double i = luaL_checknumber(L, 1);
    double j = luaL_checkinteger(L, 2);

    if (i < 0 || i > m_data->map_size)
        luaL_error(L, "Parameter i must be between %d and %d", 0, m_data->map_size);

    if (j < 0 || j > m_data->map_size)
        luaL_error(L, "Parameter j must be between %d and %d", 0, m_data->map_size);


    weight w = m_data->map[i * m_data->map_size + j];

    lua_pushnumber(L, (double) w);

    return 1;
}
