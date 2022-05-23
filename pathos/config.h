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

#include "defines.h"
#include "util.h"

#define CONFIG_FILE "config.lua"

char * get_script(lua_State *L);
char * get_map(lua_State *L);

WSIZE get_window_size(lua_State *L);

WCOLORS get_window_colors(lua_State *L);
