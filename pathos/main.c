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

void f(void)
{
    return;
}

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

    SDL_Rect dimension;
    dimension.x = 0;
    dimension.y = 0;
    dimension.h = 50;
    dimension.w = 200;

    SDL_Color bg;
    bg.r = 255;
    bg.g = 0;
    bg.b = 0;
    bg.a = 255;

    SDL_Color txt;
    txt.r = 255;
    txt.g = 255;
    txt.b = 0;
    txt.a = 255;

    char text[] = "Click me !";

    struct Button btn;
    btn.dim = dimension;
    btn.background = bg;
    btn.txt_color = txt;
    btn.do_click = f;
    btn.txt = text;

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

    button_create(btn, renderer);

    while(!quit) {
        SDL_Event evt;    // no need for new/delete, stack is fine

        // event loop and draw loop are separate things, don't mix them
        while(SDL_PollEvent(&evt)) {
            // quit on close, window close, or 'escape' key hit
            if(evt.type == SDL_QUIT ||
                    (evt.type == SDL_WINDOWEVENT && evt.window.event == SDL_WINDOWEVENT_CLOSE) ||
                    (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_ESCAPE)) {
                quit = 1;}
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