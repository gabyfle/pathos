/**
 * 
 * pathos - Simulation engine 
 * 2022 - Gabriel Santamaria
 * 
**/

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <stdlib.h>

#include "../util.h"

struct Button {
    SDL_Rect dim;
    SDL_Color background;
    SDL_Color txt_color;
    char * txt;

    void (*do_click)(void);
};

void button_create(struct Button, SDL_Renderer*);
void button_do_click(struct Button, SDL_Event*);
