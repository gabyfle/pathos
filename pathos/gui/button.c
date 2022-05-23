/**
 * 
 * pathos - Simulation engine 
 * 2022 - Gabriel Santamaria
 * 
**/

#include "button.h"

int buttons_count = 0;
struct Button buttons[256];

/**
 * @brief Draw a button into the screen
 * 
 * @param dim Dimension of the button (pos + size)
 * @param bg Button's background color
 * @param txt_color Button's text color
 * @param txt Button's text
 */
void button_draw(struct Button btn, SDL_Renderer * renderer)
{
    SDL_SetRenderDrawColor(renderer, btn.background.r, btn.background.g, btn.background.b, btn.background.a);
    SDL_RenderFillRect(renderer, &btn.dim);

    SDL_Rect txt_rect = btn.dim;

    TTF_Font * Ubuntu = TTF_OpenFont("ubuntu.ttf", 16);

    int txt_w;
    int txt_h;

    SDL_Surface* txt_surface = TTF_RenderText_Blended(Ubuntu, btn.txt, btn.txt_color); 
    SDL_Texture* txt_texture = SDL_CreateTextureFromSurface(renderer, txt_surface);

    txt_w = txt_surface->w;
    txt_h = txt_surface->h;

    txt_rect.w = txt_w;
    txt_rect.h = txt_h;

    txt_rect.x = btn.dim.x + (abs(btn.dim.w - txt_rect.w) / 2);
    txt_rect.y = btn.dim.y + (abs(btn.dim.h - txt_rect.h) / 2);

    SDL_RenderCopy(renderer, txt_texture, NULL, &txt_rect);

    SDL_FreeSurface(txt_surface);
    SDL_DestroyTexture(txt_texture);

    TTF_CloseFont(Ubuntu);
}

void button_draw_border(struct Button btn, SDL_Color color, SDL_Renderer * renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_Rect left = {
        .x = btn.dim.x,
        .y = btn.dim.y,
        .w = 5,
        .h = btn.dim.h
    };

    SDL_Rect right = {
        .x = btn.dim.x + btn.dim.w - 5,
        .y = btn.dim.y,
        .w = 5,
        .h = btn.dim.h
    };

    SDL_Rect top = {
        .x = btn.dim.x,
        .y = btn.dim.y,
        .w = btn.dim.w,
        .h = 5
    };

    SDL_Rect bottom = {
        .x = btn.dim.x,
        .y = btn.dim.y + btn.dim.h - 5,
        .w = btn.dim.w,
        .h = 5
    };

    SDL_RenderFillRect(renderer, &left);
    SDL_RenderFillRect(renderer, &right);
    SDL_RenderFillRect(renderer, &top);
    SDL_RenderFillRect(renderer, &bottom);
}

/**
 * @brief Draw a lighter border when button is overed
 * 
 * @param btn 
 * @param renderer 
 */
void button_hover(struct Button btn, SDL_Renderer * renderer)
{
    int x, y;

    SDL_PumpEvents();
    SDL_GetMouseState(&x, &y);

    if (x >= btn.dim.x &&
            x <= (btn.dim.x + btn.dim.w) &&
            y >= btn.dim.y &&
            y <= (btn.dim.y + btn.dim.h)
        ) {
        SDL_Color hover = btn.background;
        hover.r += 20;
        hover.g += 20;
        hover.b += 20;
        button_draw_border(btn, hover, renderer);
    } else {
        button_draw_border(btn, btn.background, renderer);
    }
}

/**
 * @brief Draw a darker border when button is pressed
 * 
 * @param btn 
 * @param renderer 
 */
void button_pressed(struct Button btn, SDL_Renderer * renderer)
{
    int x, y;
    Uint32 buttons;

    SDL_PumpEvents();
    buttons = SDL_GetMouseState(&x, &y);

    if ((x >= btn.dim.x &&
            x <= (btn.dim.x + btn.dim.w) &&
            y >= btn.dim.y &&
            y <= (btn.dim.y + btn.dim.h)
        ) && ((buttons & SDL_BUTTON_LMASK) != 0))
    {
        SDL_Color pressed = btn.background;
        pressed.r -= 20;
        pressed.g -= 20;
        pressed.b -= 20;
        button_draw_border(btn, pressed, renderer);
    }
}

/**
 * @brief On click button event
 * 
 * @param f 
 */
void button_do_click(struct Button btn, SDL_Event* evnt, SDL_Renderer * renderer)
{   
    if (evnt->type == SDL_MOUSEBUTTONDOWN) {
        if (evnt->button.button == SDL_BUTTON_LEFT &&
                evnt->button.x >= btn.dim.x &&
                evnt->button.x <= (btn.dim.x + btn.dim.w) &&
                evnt->button.y >= btn.dim.y &&
                evnt->button.y <= (btn.dim.y + btn.dim.h)
        ) {
            btn.pressed = true;
            btn.do_click();
        }
    } else if (evnt->type == SDL_MOUSEBUTTONUP) {
        btn.pressed = false;
    }

    if (evnt->type == SDL_MOUSEMOTION) {
        if (evnt->motion.x >= btn.dim.x &&
            evnt->motion.x <= (btn.dim.x + btn.dim.w) &&
            evnt->motion.y >= btn.dim.y &&
            evnt->motion.y <= (btn.dim.y + btn.dim.h)
        ) {
            btn.hover = true;
        }
    }

    button_hover(btn, renderer);
    button_pressed(btn, renderer);
}

/**
 * @brief Create a button based on a button structure
 * 
 * @param button 
 */
void button_create(struct Button button)
{
    if (buttons_count < sizeof(buttons)/sizeof(*(buttons))) {
        buttons[buttons_count] = button;

        buttons_count++;
    } else {
        error(NULL, "An error happenned while trying to create a new button: max limit reached.");
    }
}
