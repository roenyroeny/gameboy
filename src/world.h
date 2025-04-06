#pragma once

#include "mytypes.h"

#define WORLD_WIDTH 64
#define WORLD_HEIGHT 32

typedef struct world_tile
{
    u8 id;
};

void world_init(void);

