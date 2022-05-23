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

    typedef struct Data {
        const char * script;
        const char * map;
    } DATA;

    typedef struct windowSize {
        unsigned int width;
        unsigned int height;
    } WSIZE;

    typedef struct windowColors {
        SDL_Color background;
        SDL_Color walls;
        SDL_Color units;
    } WCOLORS;

    typedef double weight; // weight of our roads (has to be between 0 and 1: 0: perfect road, 1: a wall)

    typedef struct mapData {
        int map_size; // size of the map in tiles
        int safe_size; // safe area size of the map, in tiles

        weight * map;
    } MAP_DATA;

#endif