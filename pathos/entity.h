/**
 * 
 * pathos - Simulation engine 
 * 2022 - Gabriel Santamaria
 * 
**/

#include <lua5.4/lua.h>
#include <lua5.4/lauxlib.h>
#include <lua5.4/lualib.h>

#include <stdlib.h>

#include "defines.h"
#include "util.h"

Entity * create_entities(int);
void handle_entities(lua_State *, DATA, Entity *, SDL_Renderer *);
