/**
 * 
 * pathos - Simulation engine 
 * 2022 - Gabriel Santamaria
 * 
**/

#include "menu.h"

extern int buttons_count;
extern struct Button buttons[256];

/**
 * @brief Draw the global background color of the pathos main window
 * 
 * @param color 
 * @param renderer 
 */
void menu_background(SDL_Color color, SDL_Color txt_bg_c, int w_height, SDL_Renderer* renderer)
{
    SDL_Rect menu;
             menu.x = 0;
             menu.y = 0;
             menu.h = w_height;
             menu.w = 300;

    SDL_Rect separator = {
        .x = 298,
        .y = 0,
        .w = 4,
        .h = w_height
    };

    if(0 != SDL_SetRenderDrawColor(renderer, txt_bg_c.r, txt_bg_c.g, txt_bg_c.b, txt_bg_c.a))
        error(NULL, "An error occurred while trying to set a new render color: %s", SDL_GetError());
    SDL_RenderFillRect(renderer, &separator);

    if(0 != SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a))
        error(NULL, "An error occurred while trying to set a new render color: %s", SDL_GetError());
    SDL_RenderFillRect(renderer, &menu);
}

void close_do_click(void)
{
    print(4, "Quitting pathos. Have a good day!");
    SDL_Quit();
    exit(EXIT_SUCCESS);
}

void start_engine(void)
{
    print(2, "Engine is starting...");
}

/**
 * @brief Adds buttons and stuff like that to the menu
 * 
 * @param renderer 
 */
void add_gui_elements(int w_height)
{
    SDL_Color red = {.r=220, .g=53, .b=69, .a=255};
    SDL_Color green = {.r=40, .g=167, .b=69, .a=255};
    SDL_Color white = {.r=255, .g=255, .b=255, .a=255};

    SDL_Rect close_rect = {
        .h = 40,
        .w = 250,
        .y = w_height - 65,
        .x = 25
    };

    SDL_Rect start_rect = {
        .h = 55,
        .w = 250,
        .y = 280,
        .x = 25
    };

    struct Button close_btn = {
        .background = red,
        .txt_color = white,
        .dim = close_rect,
        .do_click = close_do_click,
        .txt = "Quit pathos"
    };

    struct Button start_btn = {
        .background = green,
        .txt_color = white,
        .dim = start_rect,
        .do_click = start_engine,
        .txt = "Start simulation"
    };

    button_create(start_btn);
    button_create(close_btn);
}

void draw_data(char * data_title, const char data[], SDL_Point pos, SDL_Color txt_bg_c, SDL_Color txt_color, SDL_Renderer * renderer)
{
    TTF_Font * Categories = TTF_OpenFont("ubuntu.ttf", 17);
    TTF_Font * Data = TTF_OpenFont("ubuntu.ttf", 14);

    SDL_Rect txt_rect;

    int txt_w;
    int txt_h;

    SDL_Surface* txt_surface = TTF_RenderText_Blended(Categories, data_title, txt_color);
    SDL_Texture* txt_texture = SDL_CreateTextureFromSurface(renderer, txt_surface);

    txt_w = txt_surface->w;
    txt_h = txt_surface->h;

    txt_rect.w = txt_w;
    txt_rect.h = txt_h;

    txt_rect.x = pos.x;
    txt_rect.y = pos.y;

    SDL_RenderCopy(renderer, txt_texture, NULL, &txt_rect);

    txt_surface = TTF_RenderText_Blended(Data, data, txt_color);
    txt_texture = SDL_CreateTextureFromSurface(renderer, txt_surface);

    txt_w = txt_surface->w;
    txt_h = txt_surface->h;

    txt_rect.w = txt_w;
    txt_rect.h = txt_h;

    txt_rect.x = 30;
    txt_rect.y = pos.y + 30;

    SDL_Rect txt_background = txt_rect;
    txt_background.x -= 5;
    txt_background.y -= 5;
    txt_background.h += 10;
    txt_background.w = 300 - 2 * txt_background.x;

    SDL_SetRenderDrawColor(renderer, txt_bg_c.r, txt_bg_c.g, txt_bg_c.b, txt_bg_c.a);
    SDL_RenderFillRect(renderer, &txt_background);

    SDL_RenderCopy(renderer, txt_texture, NULL, &txt_rect);

    TTF_CloseFont(Categories);
    TTF_CloseFont(Data);
}

/**
 * @brief Draw the main menu of pathos
 * 
 * @param background
 * @param text_color 
 * @param renderer 
 */
void draw_menu(DATA data, WSIZE w_size, SDL_Renderer* renderer)
{
    SDL_Color background = {
        .r = 109,
        .g = 59,
        .b = 109,
        .a = 255
    };

    SDL_Color txt_bg_c = {
        .r = 89,
        .g = 39,
        .b = 89,
        .a = 255
    };

    SDL_Color txt_color = {
        .r = 255,
        .g = 255,
        .b = 255,
        .a = 255
    };

    menu_background(background, txt_bg_c, w_size.height, renderer);

    SDL_Rect txt_rect;

    TTF_Font * Title = TTF_OpenFont("ubuntu.ttf", 34);
    TTF_Font * Copyright = TTF_OpenFont("ubuntu.ttf", 10);

    int txt_w;
    int txt_h;

    SDL_Surface* txt_surface = TTF_RenderText_Blended(Title, "pathos", txt_color); 
    SDL_Texture* txt_texture = SDL_CreateTextureFromSurface(renderer, txt_surface);

    txt_w = txt_surface->w;
    txt_h = txt_surface->h;

    txt_rect.w = txt_w;
    txt_rect.h = txt_h;

    txt_rect.x = (abs(300 - txt_rect.w) / 2);
    txt_rect.y = 65;

    SDL_RenderCopy(renderer, txt_texture, NULL, &txt_rect);

    SDL_Point pos = {.x = 25, .y = 150};
    const char * script = data.script;
    draw_data("Using script:", script, pos, txt_bg_c, txt_color, renderer);

    pos.y = 215;

    const char * map = data.map;
    draw_data("Using map:", map, pos, txt_bg_c, txt_color, renderer);

    txt_surface = TTF_RenderText_Blended(Copyright, "Gabriel Santamaria", txt_color);
    txt_texture = SDL_CreateTextureFromSurface(renderer, txt_surface);

    txt_w = txt_surface->w;
    txt_h = txt_surface->h;

    txt_rect.w = txt_w;
    txt_rect.h = txt_h;

    txt_rect.x = (abs(300 - txt_rect.w) / 2);
    txt_rect.y = 110;

    SDL_RenderCopy(renderer, txt_texture, NULL, &txt_rect);

    for (size_t i = 0; i < buttons_count; i++)
        button_draw(buttons[i], renderer);

    SDL_FreeSurface(txt_surface);
    SDL_DestroyTexture(txt_texture);

    TTF_CloseFont(Title);
    TTF_CloseFont(Copyright);
}

/**
 * @brief Initialize the menu before drawing it
 * 
 * @param w_size 
 */
void init_menu(WSIZE w_size)
{
    add_gui_elements(w_size.height);
}
