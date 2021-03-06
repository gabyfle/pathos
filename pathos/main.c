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

#include <time.h>

#include "defines.h"
#include "util.h"
#include "config.h"

#include "gui.h"
#include "menu.h"

#include "map.h"
#include "api/api.h"

#include "entity.h"

extern int buttons_count;
extern struct Button buttons[256];

/**
 * @brief Create a very simple loading screen
 * 
 * @param window 
 * @param renderer 
 */
void draw_loading_screen(int width, int height, SDL_Renderer * renderer)
{
    TTF_Font * Ubuntu = TTF_OpenFont("ubuntu.ttf", 50);
    const SDL_Color white = { .r = 255, .g = 255, .b = 255, .a = 255 };

    SDL_Rect background = {
        .x = 0,
        .y = 0,
        .w = width,
        .h = height
    };

    SDL_SetRenderDrawColor(renderer, 109, 59, 109, 255);
    SDL_RenderFillRect(renderer, &background);

    SDL_Rect txt_rect = background;

    int txt_w;
    int txt_h;

    SDL_Surface* txt_surface = TTF_RenderText_Blended(Ubuntu, "Loading...", white); 
    SDL_Texture* txt_texture = SDL_CreateTextureFromSurface(renderer, txt_surface);

    txt_w = txt_surface->w;
    txt_h = txt_surface->h;

    txt_rect.w = txt_w;
    txt_rect.h = txt_h;

    txt_rect.x = abs(width - txt_rect.w) / 2;
    txt_rect.y = abs(height - txt_rect.h) / 2;

    SDL_RenderCopy(renderer, txt_texture, NULL, &txt_rect);

    SDL_FreeSurface(txt_surface);
    SDL_DestroyTexture(txt_texture);

    TTF_CloseFont(Ubuntu);

    SDL_RenderPresent(renderer);
}

int main(int argc, char *argv [])
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    srand(time(NULL));

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window *window;
    SDL_Renderer *renderer;

    print(1, "Loading configuration files.");

    WSIZE dim = get_window_size(L);
    WCOLORS colors = get_window_colors(L);

    const char * script = get_script(L);
    const char * map = get_map(L);
    const int n_ents = get_ents_number(L);

    print(1, "Using script: ");
    print(1, script);

    print(1, "Using map:");
    print(1, map);

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

    draw_loading_screen(dim.width, dim.height, renderer);

    DATA data = {
        .script = script,
        .map = map,
        .ents_number = n_ents
    };

    MAP_DATA * m_data = map_handle(data, dim, colors);

    init_api(L, &data, m_data);

    if (luaL_loadfile(L, script) || lua_pcall(L, 0, 0, 0))
        error(L, "Unable to load script file: %s", lua_tostring(L, -1));

    Entity * entities = create_entities(L, m_data, data.ents_number);

    init_ents_api(L, entities);

    State pathos = {
        .c_data = data,
        .m_data = m_data,
        .entities = entities
    };

    int quit = 0;

    init_menu(dim);

    while(!quit) {
        SDL_Event evnt;
        
        draw_map(m_data, dim, colors, renderer);
        draw_entities(&pathos, renderer);
        draw_menu(data, dim, renderer);

        while(SDL_PollEvent(&evnt)) {
            if(evnt.type == SDL_QUIT || 
              (evnt.type == SDL_WINDOWEVENT && evnt.window.event == SDL_WINDOWEVENT_CLOSE) ||
              (evnt.type == SDL_KEYDOWN && evnt.key.keysym.sym == SDLK_ESCAPE)) { quit = 1; }

            for (size_t i = 0; i < buttons_count; i++){ // Looping throught all buttons
                button_do_click(buttons[i], &evnt, renderer);
            }
        }
        handle_entities(L, &pathos);

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);

        SDL_Delay(10);
    }

    if(renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if (window != NULL)
        SDL_DestroyWindow(window);
    
    free(entities);
    free(m_data->map);
    free(m_data);

    lua_close(L);
    SDL_Quit();
    return EXIT_SUCCESS;
}
