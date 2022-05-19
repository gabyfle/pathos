/**
 * 
 * pathos - Simulation engine 
 * 2022 - Gabriel Santamaria
 * 
**/

#include "config.h"

/**
 * get_script
 * Gets the simulation script that we should use for the engine
 * @param lua_State* L the Lua state
 * @return char*
 */
char * get_script(lua_State *L)
{
    char * script;

    if (luaL_loadfile(L, CONFIG_FILE) || lua_pcall(L, 0, 0, 0))
        error(L, "Unable to load config file: %s", lua_tostring(L, -1));

    lua_getglobal(L, "Script");
    if (!lua_isstring(L, -1))
        error(L, "Script is a %s but a string were expected. Please, see manual to have a proper config file.", lua_typename(L, lua_type(L, -1)));

    script = lua_tostring(L, -1);

    return script;
}

/**
 * get_map
 * Gets the simulation map that we should use for the engine
 * @param lua_State* L the Lua state
 * @return char*
 */
char * get_map(lua_State *L)
{
    char * map;

    if (luaL_loadfile(L, CONFIG_FILE) || lua_pcall(L, 0, 0, 0))
        error(L, "Unable to load config file: %s", lua_tostring(L, -1));

    lua_getglobal(L, "Map");
    if (!lua_isstring(L, -1))
        error(L, "Map is a %s but a string were expected. Please, see manual to have a proper config file.", lua_typename(L, lua_type(L, -1)));

    map = lua_tostring(L, -1);

    return map;
}

/**
 * get_window_size
 * Gets the Window size from the configuration file (config.lua) and returns it inside a struct
 * @param lua_State* L the Lua state
 * @return struct windowSize
 */
struct windowSize get_window_size(lua_State *L)
{
    int isInt;
    struct windowSize size;

    if (luaL_loadfile(L, CONFIG_FILE) || lua_pcall(L, 0, 0, 0))
        error(L, "Unable to load config file: %s", lua_tostring(L, -1));

    lua_getglobal(L, "Window");
    if (!lua_istable(L, -1))
        error(L, "Window is a %s but a table were expected. Please, see manual to have a proper config file.", lua_typename(L, lua_type(L, -1)));

    lua_pushstring(L, "height");
    lua_gettable(L, -2);

    size.height = (int) lua_tointegerx(L, -1, &isInt);
    if (!isInt)
        error(L, "Invalid Window.height parameter. An integer were expected but a %s were given.", lua_typename(L, lua_type(L, -1)));

    lua_pop(L, 1);

    lua_pushstring(L, "width");
    lua_gettable(L, -2);

    size.width = (int) lua_tointegerx(L, -1, &isInt);
    if (!isInt)
        error(L, "Invalid Window.width parameter. An integer were expected but a %s were given.", lua_typename(L, lua_type(L, -1)));

    lua_pop(L, 1);

    return size;
}

/**
 * get_color_table
 * Gets the color table from the latest variable pushed onto the Lua stack
 * We assume that this variable is a valid color table
 * @return SDL_Color
 */
static SDL_Color get_color_table(lua_State *L)
{
    int isInt;
    SDL_Color color;

    Uint8* map[] = {
        &color.r,
        &color.g,
        &color.b,
        &color.a
    };

    for (int i = 0; i < 4; i++)
    {
        lua_pushinteger(L, (i+1)); // lua tables are indexed from 1
        lua_gettable(L, -2);

        Uint8 * ptr = (Uint8 *) map[i];

        *ptr = (int)(lua_tonumberx(L, -1, &isInt));

        if (!isInt)
            error(L, "Key number %d is a %s but an integer were expected.", (i + 1), lua_typename(L, lua_type(L, -1)));

        lua_pop(L, 1);
    }
    

    return color;
}

struct windowColors get_window_colors(lua_State *L)
{
    struct windowColors colors;

    if (luaL_loadfile(L, CONFIG_FILE) || lua_pcall(L, 0, 0, 0))
        error(L, "Unable to load config file: %s", lua_tostring(L, -1));

    lua_getglobal(L, "Colors");
    if (!lua_istable(L, -1))
        error(L, "Colors is a %s but a table were expected. Please, see manual to have a proper config file.", lua_typename(L, lua_type(L, -1)));

    lua_pushstring(L, "background");
    lua_gettable(L, -2);

    if (!lua_istable(L, -1))
        error(L, "The field background of the Color table should be a valid table but a %s were given.", lua_typename(L, lua_type(L, -1)));

    colors.background = get_color_table(L);

    lua_pop(L, 1);

    lua_pushstring(L, "walls");
    lua_gettable(L, -2);

    if (!lua_istable(L, -1))
        error(L, "The field walls of the Color table should be a valid table but a %s were given.", lua_typename(L, lua_type(L, -1)));


    colors.walls = get_color_table(L);

    lua_pop(L, 1);

    lua_pushstring(L, "units");
    lua_gettable(L, -2);

    if (!lua_istable(L, -1))
        error(L, "The field units of the Color table should be a valid table but a %s were given.", lua_typename(L, lua_type(L, -1)));

    colors.units = get_color_table(L);

    lua_pop(L, 1);

    return colors;
}
