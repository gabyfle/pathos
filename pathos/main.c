/**
 * 
 * pathos - Simulation engine 
 * 2022 - Gabriel Santamaria
 * 
**/

#include <SDL2/SDL.h>

#include <lua5.4/lua.h>
#include <lua5.4/lauxlib.h>
#include <lua5.4/lualib.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "util.h"
#include "config.h"
#include "map.h"

int main(int argc, char *argv [])
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    print(1, "Loading configuration files.");

    struct windowSize dim = get_window_size(L);
    struct windowColors colors = get_window_colors(L);

    char * script = get_script(L);

    print(1, "Using script: ");
    print(1, script);

    print(1, "Configuration loaded!");
    print(2, "Everything works perfectly.");

    lua_close(L);
    return EXIT_SUCCESS;
}