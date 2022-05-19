/**
 * 
 * pathos - Simulation engine 
 * 2022 - Gabriel Santamaria
 * 
**/

#include "map.h"

typedef double weight; // weight of our roads (has to be between 0 and 1: 0: perfect road, 1: a wall)

/**
 * @brief Computes the maximum size of a tile of the given map
 * 
 * @param n_tiles : number of tiles in a row
 * @param w_size 
 * @return int 
 */
int compute_tile_size(size_t n_tiles, struct windowSize w_size)
{
    return (int) floor((w_size.height / n_tiles));
}

/**
 * @brief Computes the maximum size of the map that can be drawn into the screen
 * 
 * @param n_tiles : number of tiles in a row
 * @param w_size 
 * @return int 
 */
int compute_max_size(size_t n_tiles, struct windowSize w_size)
{
    int t_size = compute_tile_size(n_tiles, w_size);
    return (int) t_size * n_tiles;
}

/**
 * @brief Draws the map onto the screen.
 * 
 * @param map 
 * @param w_size 
 * @param w_colors 
 */
void draw_map(int map_size, weight map[map_size][map_size], struct windowSize w_size, struct windowColors w_colors, SDL_Renderer* renderer)
{
    int tile_size = compute_tile_size(map_size, w_size);
    int max_size = compute_max_size(map_size, w_size);

    int start_x = (w_size.width - max_size - 300) / 2 + 300;
    int start_y = (w_size.height - max_size) / 2;

    SDL_SetRenderDrawColor(renderer, w_colors.background.r, w_colors.background.g, w_colors.background.b, w_colors.background.a);

    SDL_Rect bg_rect = {
        .w = w_size.width,
        .h = w_size.height,
        .x = 0,
        .y = 0
    };

    SDL_RenderFillRect(renderer, &bg_rect);

    SDL_SetRenderDrawColor(renderer, w_colors.walls.r, w_colors.walls.g, w_colors.walls.b, w_colors.walls.a);

    for (size_t i = 0; i < map_size; i++)
    {
        for (size_t j = 0; j < map_size; j++)
        {
            SDL_Rect tile = {
                .h = tile_size,
                .w = tile_size,
        
                .x = start_x,
                .y = start_y
            };
            tile.x += tile_size * j;
            tile.y += tile_size * i;
            
            if (map[i][j] == (weight) 0)
                SDL_RenderFillRect(renderer, &tile);
        }        
    }

    SDL_RenderPresent(renderer); 
}

/**
 * @brief Handle everything about the map
 * 
 * @param data 
 * @param w_size 
 * @param w_colors 
 */
void map_handle(struct Data data, struct windowSize w_size, struct windowColors w_colors, SDL_Renderer * renderer)
{
    int map_size;
    int safe_size;

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(data.map, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    // Two firsts lines are 
    if ((read = getline(&line, &len, fp)) != -1)
        map_size = strtol(line, NULL, 10);

    if ((read = getline(&line, &len, fp)) != -1)
        safe_size = strtol(line, NULL, 10);

    // Now we know the exact size of our map so we can create it
    weight map[map_size][map_size];

    int i = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        int j = 0;
        int n = strlen(line);
        for (int j = 0; j < n; j++)
        {
            switch (line[j])
            {
                case '#':
                    map[i][j] = (weight) 0.0;
                    break;
                case ' ':
                    map[i][j] = (weight) 1.0;
                    break;
                default:
                    break;
            }
        }
        i++;
    }

    // Now we can draw the map into the screen.
    draw_map(map_size, map, w_size, w_colors, renderer);

    fclose(fp);
    if (line)
        free(line);
}
