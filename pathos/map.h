/**
 * 
 * pathos - Simulation engine 
 * 2022 - Gabriel Santamaria
 * 
**/

#include "defines.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

MAP_DATA * map_handle(DATA, WSIZE, WCOLORS);
void draw_map(MAP_DATA *, WSIZE, WCOLORS, SDL_Renderer*);
