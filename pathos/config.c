/**
 * 
 * pathos - Simulation engine 
 * 2022 - Gabriel Santamaria
 * 
**/

#include "util.h"
#include "config.h"

struct windowSize get_window_size(lua_State *L)
{
    struct windowSize size;

    if (luaL_loadfile(L, CONFIG_FILE) || lua_pcall(L, 0, 0, 0))
        error(L, "Unable to load config file: %s", lua_tostring(L, -1));

    lua_getglobal(L, "Window");
    if (!lua_istable(L, -1))
        error(L, "Window is a %s but a table were expected. Please, see manual to have a proper config file.", lua_type(L, -1));    
}
