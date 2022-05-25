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
        const int ents_number;
    } DATA;

    typedef struct windowSize {
        unsigned int width;
        unsigned int height;
    } WSIZE;

    typedef struct windowColors {
        SDL_Color background;
        SDL_Color safe;
        SDL_Color walls;
        SDL_Color units;
    } WCOLORS;

    typedef double weight; // weight of our roads (has to be between 0 and 1: 0: perfect road, 1: a wall)

    typedef struct mapData {
        int tile_size; // size of a tile in pixels
        int map_size; // size of the map in tiles
        int safe_size; // safe area size of the map, in tiles

        SDL_Point screen_pos; // position of the left corner on the screen

        weight * map;
    } MAP_DATA;

    typedef struct entity {
        SDL_Rect dim;
        SDL_Color color;
        
        int tile_id; // id of the tile were the ent iss
    } Entity;

    typedef struct pathosState {
        DATA c_data; // configuration data
        MAP_DATA * m_data; // map data
        Entity * entities; // entities of the simulation
    } State;

#endif