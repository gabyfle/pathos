/**
 * 
 * pathos - Simulation engine 
 * 2022 - Gabriel Santamaria
 * 
**/

#include "button.h"

/**
 * @brief Draw a button into the screen
 * 
 * @param dim Dimension of the button (pos + size)
 * @param bg Button's background color
 * @param txt_color Button's text color
 * @param txt Button's text
 */
void button_draw(SDL_Rect dim, SDL_Color bg, SDL_Color txt_color, char * txt, SDL_Renderer * renderer)
{
    SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a);
    SDL_RenderFillRect(renderer, &dim);

    SDL_Rect txt_rect = dim;

    TTF_Font * Ubuntu = TTF_OpenFont("ubuntu.ttf", 16);

    int txt_w;
    int txt_h;

    SDL_Surface* txt_surface = TTF_RenderText_Blended(Ubuntu, txt, txt_color); 
    SDL_Texture* txt_texture = SDL_CreateTextureFromSurface(renderer, txt_surface);

    txt_w = txt_surface->w;
    txt_h = txt_surface->h;

    txt_rect.w = txt_w;
    txt_rect.h = txt_h;

    txt_rect.x = dim.x + (abs(dim.w - txt_rect.w) / 2);
    txt_rect.y = dim.y + (abs(dim.h - txt_rect.h) / 2);

    SDL_RenderCopy(renderer, txt_texture, NULL, &txt_rect);
    SDL_FreeSurface(txt_surface);

    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(txt_texture);

    TTF_CloseFont(Ubuntu);
}
/**
 * @brief On click button event
 * 
 * @param f 
 */
void button_do_click(void (*f)(void))
{
    print(1, "You clicked on a button!");
}

/**
 * @brief Create a button based on a button structure
 * 
 * @param button 
 */
void button_create(struct Button button, SDL_Renderer * renderer)
{
    button_draw(button.dim, button.background, button.txt_color, button.txt, renderer);    
}
