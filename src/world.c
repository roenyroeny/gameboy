#include "world.h"

struct world_tile world_map[WORLD_WIDTH][WORLD_HEIGHT];


void world_init(void)
{
    world_map[0][0].id = 1;
    world_map[0][1].id = 1;
    world_map[0][2].id = 1;
    world_map[2][0].id = 1;
    world_map[2][1].id = 1;
    world_map[2][2].id = 1;
    world_map[1][0].id = 1;
    world_map[1][1].id = 0;
    world_map[1][2].id = 1;
}



