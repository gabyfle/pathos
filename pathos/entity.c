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
Entity * create_entities(int number)
{
    Entity * entities = (Entity *) malloc(number * sizeof(Entity));
    for (size_t i = 0; i < number; i++)
    {
        entities[i] = (Entity) {
            .dim = {
                .x = 400,
                .y = 400,
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
    }

    return entities;
}

/**
 * @brief Handle every entities of the program
 * 
 * @param n_ent : number of entities
 */
void handle_entities(lua_State * L, State * pathos)
{
    char * script = pathos->c_data.script;
    if (luaL_loadfile(L, script) || lua_pcall(L, 0, 0, 0))
        error(L, "Unable to load script file: %s", lua_tostring(L, -1));

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

        pathos->entities[i].dim.x += dx;
        pathos->entities[i].dim.y += dy;

        lua_pop(L, 3);
    }
}
