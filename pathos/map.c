/**
 * 
 * pathos - Simulation engine 
 * 2022 - Gabriel Santamaria
 * 
**/

#include "map.h"

/**
 * @brief Computes the maximum size of a tile of the given map
 * 
 * @param n_tiles : number of tiles in a row
 * @param w_size 
 * @return int 
 */
int compute_tile_size(size_t n_tiles, WSIZE w_size)
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
int compute_max_size(size_t n_tiles, WSIZE w_size)
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
void draw_map(MAP_DATA * m_data, WSIZE w_size, WCOLORS w_colors, SDL_Renderer* renderer)
{
    weight ** map = m_data->map;
    int max_size = compute_max_size(m_data->map_size, w_size);

    SDL_SetRenderDrawColor(renderer, w_colors.background.r, w_colors.background.g, w_colors.background.b, w_colors.background.a);

    SDL_Rect bg_rect = {
        .w = w_size.width,
        .h = w_size.height,
        .x = 0,
        .y = 0
    };

    SDL_RenderFillRect(renderer, &bg_rect);

    SDL_Rect safe_rect = {
        .w = max_size,
        .h = m_data->safe_size * m_data->tile_size,
        .x = m_data->screen_pos.x,
        .y = m_data->screen_pos.y
    };

    SDL_SetRenderDrawColor(renderer, w_colors.safe.r, w_colors.safe.g, w_colors.safe.b, w_colors.safe.a);

    SDL_RenderFillRect(renderer, &safe_rect);

    SDL_SetRenderDrawColor(renderer, w_colors.walls.r, w_colors.walls.g, w_colors.walls.b, w_colors.walls.a);

    for (size_t i = 0; i < m_data->map_size; i++)
    {
        for (size_t j = 0; j < m_data->map_size; j++)
        {
            SDL_Rect tile = {
                .h = m_data->tile_size,
                .w = m_data->tile_size,
        
                .x = m_data->screen_pos.x,
                .y = m_data->screen_pos.y
            };
            tile.x += m_data->tile_size * j;
            tile.y += m_data->tile_size * i;
            
            if ((m_data->map[i * m_data->map_size + j] == (weight) 0)) {
                SDL_RenderFillRect(renderer, &tile);
            }
        }        
    }
}

/**
 * @brief Handle everything about the map
 * 
 * @param data 
 * @param w_size 
 * @param w_colors 
 */
MAP_DATA * map_handle(DATA data, WSIZE w_size, WCOLORS w_colors)
{
    MAP_DATA * m_data = (MAP_DATA *) malloc(sizeof(MAP_DATA));

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

    int tile_size = compute_tile_size(map_size, w_size);
    int max_size = compute_max_size(map_size, w_size);

    int start_x = (w_size.width - max_size - 300) / 2 + 300;
    int start_y = (w_size.height - max_size) / 2;

    // Now we know the exact size of our map so we can create it
    weight * map = (weight *) malloc(map_size * map_size * sizeof(weight));  

    int i = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        int n = strlen(line);
        for (int j = 0; j < n; j++)
        {
            int offset = i * map_size + j;
            switch (line[j])
            {
                case '#':
                    map[offset] = (weight) 0.0;
                    break;
                case ' ':
                    map[offset] = (weight) 1.0;
                    break;
                default:
                    break;
            }
        }
        i++;
    }

    m_data->tile_size = tile_size;
    m_data->screen_pos = (SDL_Point) { .x = start_x, .y = start_y };
    m_data->map = map;
    m_data->map_size = map_size;
    m_data->safe_size = safe_size;

    fclose(fp);
    if (line)
        free(line);

    return m_data;
}
