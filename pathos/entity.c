/**
 * 
 * pathos - Simulation engine 
 * 2022 - Gabriel Santamaria
 * 
**/

#include "entity.h"

/**
 * @brief Draw the previously created entities into the screen, using draw_entity
 * 
 * @param renderer 
 */
void draw_entities(State * pathos, SDL_Renderer* renderer)
{
    for (size_t i = 0; i < pathos->c_data.ents_number; i++)
    {
        SDL_SetRenderDrawColor(renderer, pathos->entities[i].color.r, pathos->entities[i].color.g, pathos->entities[i].color.b, pathos->entities[i].color.a);
        SDL_RenderFillRect(renderer, &pathos->entities[i].dim);
    }
}

/**
 * @brief Create n entity objects, stored in entities
 * 
 * @param number number of entity to create
 */
Entity * create_entities(lua_State * L, MAP_DATA * m_data, int number)
{
    Entity * entities = (Entity *) malloc(number * sizeof(Entity));
    int m_size = m_data->map_size;
    bool spawned = false;
    int nspawn = 0;

    for (size_t id = 0; id < number; id++)
    {
        for (size_t j = 0; j < m_size; j++)
        {
            if (spawned)
                break;

            for (size_t k = 0; k < m_size; k++)
            {
                if (spawned)
                    break;

                lua_getglobal(L, "spawn");
                lua_pushnumber(L, (double) id);

                lua_newtable(L);
                {
                    lua_pushnumber(L, 1);
                    lua_pushnumber(L, j);
                    lua_settable(L, -3);

                    lua_pushnumber(L, 2);
                    lua_pushnumber(L, k);
                    lua_settable(L, -3);
                }

                if (lua_pcall(L, 2, 1, 0) != LUA_OK)
                    error(L, "An error occurred while executing 'spawn' on entity number %d: %s", id, lua_tostring(L, -1));

                int can_spawn = lua_toboolean(L, -1);
                lua_pop(L, 1);

                if (!can_spawn)
                    continue;

                entities[id] = (Entity) {
                    .dim = {
                        .x = m_data->screen_pos.x + j * m_data->tile_size,
                        .y = m_data->screen_pos.y + k * m_data->tile_size,
                        .h = 4,
                        .w = 4
                    },
                    .color = {
                        .r = rand() % 255,
                        .g = rand() % 255,
                        .b = rand() % 255,
                        .a = 255
                    }
                };

                spawned = true;
                nspawn++;

                break;
            }
        }

        spawned = false;
    }

    if (nspawn < number){
        error(L, "An error has occurred while trying to spawn entities: not every entity was able to spawn. Fix your 'spawn' script.");
    }

    return entities;
}

/**
 * @brief Computes the number of the tile
 * 
 * @param m_data 
 * @param pos 
 * @return int : an int under the form i * map_size + j where (i, j) € N
 */
int compute_tile(MAP_DATA * m_data, SDL_Point pos)
{
    int dx = (pos.x - m_data->screen_pos.x);
    int dy = (pos.y - m_data->screen_pos.y);

    //if (dx < 0 || dx > m_data->tile_size * m_data->map_size)
    //    error(NULL, "A particle is outside the map, aborting.");
    //if (dx < 0 || dx > m_data->tile_size * m_data->map_size)
    //    error(NULL, "A particle is outside the map, aborting.");

    return (dy / m_data->tile_size) * m_data->map_size + (dx / m_data->tile_size);
}

/**
 * @brief Computes whether or not the entity can move throught dx, dy
 * 
 * @param m_data 
 * @param ent_pos 
 * @param dx 
 * @param dy 
 * @return true : the particle is able to move (it's not a wall, or the weight is enought)
 * @return false : the particle can't move that way (it's a wall, or the weight isn't enought)
 */
bool can_move(MAP_DATA * m_data, SDL_Point ent_pos, int dx, int dy)
{
    SDL_Point new_pos = { .x = ent_pos.x + dx, .y = ent_pos.y + dy };
    int n_tile = compute_tile(m_data, new_pos);

    return m_data->map[n_tile] > 0;
}

/**
 * @brief Handle every entities of the program
 * 
 * @param n_ent : number of entities
 */
void handle_entities(lua_State * L, State * pathos)
{
    for (size_t i = 0; i < pathos->c_data.ents_number; i++)
    {
        lua_getglobal(L, "entity");
        lua_pushnumber(L, (double) i);

        if (lua_pcall(L, 1, 1, 0) != LUA_OK)
            error(L, "An error occurred while executing 'entity' on entity number %d: %s", i, lua_tostring(L, -1));

        lua_rawgeti(L, -1, 1);
        lua_rawgeti(L, -2, 2);

        int dy = lua_tointeger(L, -1);
        int dx = lua_tointeger(L, -2);

        SDL_Point pos = {.x = pathos->entities[i].dim.x, .y = pathos->entities[i].dim.y};

        if (can_move(pathos->m_data,  pos, dx, dy)) {
            pathos->entities[i].tile_id = compute_tile(pathos->m_data, pos);
            pathos->entities[i].dim.x += dx;
            pathos->entities[i].dim.y += dy;
        }

        lua_pop(L, 3);
    }
}
