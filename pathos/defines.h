/**
 * 
 * pathos - Simulation engine 
 * 2022 - Gabriel Santamaria
 * 
**/

#include <SDL2/SDL.h>
#include <stdbool.h>

#ifndef DEFINES
    #define DEFINES
    struct Button {
        SDL_Rect dim;
        SDL_Color background;
        SDL_Color txt_color;
        char * txt;

        void (*do_click)(void);

        bool pressed;
        bool hover;
    };

    struct Data {
        const char * script;
        const char * map;
    };

    struct windowSize {
        unsigned int width;
        unsigned int height;
    };

    struct windowColors {
        SDL_Color background;
        SDL_Color walls;
        SDL_Color units;
    };
#endif