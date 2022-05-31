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
#include <stdbool.h>

#include "defines.h"
#include "util.h"

Entity * create_entities(lua_State *, MAP_DATA *, int);
void draw_entities(State * pathos, SDL_Renderer * renderer);
void handle_entities(lua_State *, State * pathos);
