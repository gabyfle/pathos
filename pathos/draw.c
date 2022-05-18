/**
 * 
 * pathos - Simulation engine 
 * 2022 - Gabriel Santamaria
 * 
**/

#include "draw.h"

/**
 * @brief Draw the global background color of the pathos main window
 * 
 * @param color 
 * @param renderer 
 */
void draw_background(SDL_Color color, SDL_Renderer* renderer)
{
    if(0 != SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a))
        error(NULL, "An error occurred while trying to set a new render color: %s", SDL_GetError());    
}

/**
 * @brief Draw the main menu of pathos
 * 
 * @param text_color 
 * @param renderer 
 */
void draw_menu(SDL_Color text_color, SDL_Renderer* renderer)
{

}
