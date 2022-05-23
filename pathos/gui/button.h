/**
 * 
 * pathos - Simulation engine 
 * 2022 - Gabriel Santamaria
 * 
**/

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <stdlib.h>

#include "../defines.h"
#include "../util.h"

void button_create(struct Button);
void button_do_click(struct Button, SDL_Event*, SDL_Renderer*);
void button_draw(struct Button, SDL_Renderer*);
