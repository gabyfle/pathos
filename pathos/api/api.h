/**
 * 
 * pathos - Simulation engine 
 * 2022 - Gabriel Santamaria
 * 
**/

#include "../defines.h"

#include <lua5.4/lua.h>
#include <lua5.4/lauxlib.h>
#include <lua5.4/lualib.h>

void init_api(lua_State *, DATA *, MAP_DATA *);
void init_ents_api(lua_State *, Entity *);
