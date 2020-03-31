/*
** EPITECH PROJECT, 2020
** my_rpg	
** File description:
** map_movement_system.c
*/


#include "components/controllable_component.h"
#include "components/map_linker.h"
#include "map_utils.h"
#include "system.h"


static void update_entity(gc_engine *engine, void *system, gc_entity *entity, \
float dtime)
{
    struct controllable_component *ctl = GETCMP(entity, controllable_component);
    struct map_linker *link = GETCMP(entity, map_linker);
    gc_scene *scene = engine->scene;
    gc_list *maps = scene->get_entity_by_cmp(scene, "vertex_component");
    struct vertex_component *map;
    gc_vector2i map_pos = (gc_vector2i){
        link->tile->corners[0]->x + ctl->movement_x,
        link->tile->corners[0]->y - ctl->movement_y
    };
    struct tile *new_tile;

    if (!maps)
        return;
    map = GETCMP(maps->data, vertex_component);
    new_tile = get_tile_at(map, map_pos);
    if (new_tile && !new_tile->solid && ctl->move_callback <= 0) {
        link->tile->entity = NULL;
        new_tile->entity = entity;
        ctl->move_callback = 10;
    }
    ctl->move_callback--;
}

static void ctr(void *system, va_list list)
{
}

static void destroy(void *system)
{
}

const gc_system map_movement_system = {
    name: "map_movement_system",
    component_name: "map_movement",
    size: sizeof(gc_system),
    ctr: ctr,
    dtr: NULL,
    check_dependencies: &system_check_dependencies,
    update_entity: &update_entity,
    destroy: &destroy
};