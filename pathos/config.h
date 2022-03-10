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

#define CONFIG_FILE "config.lua"

struct windowSize {
    unsigned int width;
    unsigned int height;
};

struct windowColors {
    SDL_Color background;
    SDL_Color walls;
    SDL_Color units;
};

struct windowSize get_window_size(lua_State *L);

struct windowColors get_window_colors(lua_State *L);
