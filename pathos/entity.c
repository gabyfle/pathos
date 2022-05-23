/**
 * 
 * pathos - Simulation engine 
 * 2022 - Gabriel Santamaria
 * 
**/

#include "entity.h"

/**
 * @brief Draw a single entity onto the screen renderer
 * 
 * @param entity 
 * @param renderer 
 */
void draw_entity(Entity entity, SDL_Renderer* renderer)
{
    //SDL_SetRenderDrawColor(renderer, entity.color.r, entity.color.g, entity.color.b, entity.color.a);
    //SDL_RenderFillRect(renderer, &entity.dim);
}

/**
 * @brief Draw the previously created entities into the screen, using draw_entity
 * 
 * @param renderer 
 */
void draw_entities(int n, Entity entities[n], SDL_Renderer* renderer)
{
    if (entities[0].color.g == entities[1].color.r)
        return;
}

/**
 * @brief Create n entity objects, stored in entities
 * 
 * @param number number of entity to create
 */
Entity * create_entities(int number)
{
    Entity entities[number];
    for (size_t i = 0; i < number; i++)
    {
        entities[i] = (Entity) {
            .dim = {
                .x = 0,
                .y = 0,
                .h = 10,
                .w = 10
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
void handle_entities(lua_State * L, DATA data, Entity entities[data.ents_number], SDL_Renderer * renderer)
{
    char * script = data.script;
    if (luaL_loadfile(L, script) || lua_pcall(L, 0, 0, 0))
        error(L, "Unable to load script file: %s", lua_tostring(L, -1));

    for (size_t i = 0; i < data.ents_number; i++)
    {
        lua_getglobal(L, "entity");
        lua_pushnumber(L, (double) i);

        if (lua_pcall(L, 1, 1, 0) != LUA_OK)
            error(L, "An error occurred while executing 'entity' on entity number %d: %s", i, lua_tostring(L, -1));

        lua_rawgeti(L, -1, 1);
        printf("1 = %d\n", lua_tointeger(L, -1));
        //printf("1 = %f\n", lua_rawgeti(L, -1, 2));

        lua_pop(L, 1);
        lua_pop(L, 1);
    }

    draw_entities(8, create_entities(8), renderer);
}
