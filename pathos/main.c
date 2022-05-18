/**
 * 
 * pathos - Simulation engine 
 * 2022 - Gabriel Santamaria
 * 
**/

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <lua5.4/lua.h>
#include <lua5.4/lauxlib.h>
#include <lua5.4/lualib.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "util.h"
#include "config.h"

#include "gui.h"

#include "map.h"

extern int buttons_count;
extern struct Button buttons[256];

int main(int argc, char *argv [])
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_Window *window;
    SDL_Renderer *renderer;

    print(1, "Loading configuration files.");

    struct windowSize dim = get_window_size(L);
    struct windowColors colors = get_window_colors(L);

    char * script = get_script(L);

    print(1, "Using script: ");
    print(1, script);

    print(2, "Configuration loaded!");

    char * win_title[256];
    sprintf(win_title, "pathos engine - %s", script);

    window = SDL_CreateWindow(
        win_title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_UNDEFINED,
        dim.width,
        dim.height,
        SDL_WINDOW_OPENGL
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    if (window == NULL || renderer == NULL)
        error(L, "An error occurred while trying to create the window: %s", SDL_GetError());
    
    int quit = 0;

    while(!quit) {
        SDL_Event evnt;

        while(SDL_PollEvent(&evnt)) {
            if(evnt.type == SDL_QUIT || 
              (evnt.type == SDL_WINDOWEVENT && evnt.window.event == SDL_WINDOWEVENT_CLOSE) ||
              (evnt.type == SDL_KEYDOWN && evnt.key.keysym.sym == SDLK_ESCAPE)) { quit = 1; }

            for (size_t i = 0; i < buttons_count; i++){ // Looping throught all buttons
                button_do_click(buttons[i], &evnt);
            }

            SDL_RenderPresent(renderer);
        }
    }
    

    if(renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if (window != NULL)
        SDL_DestroyWindow(window);
    
    lua_close(L);
    SDL_Quit();
    return EXIT_SUCCESS;
}