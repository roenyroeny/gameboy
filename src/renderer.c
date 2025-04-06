#include "renderer.h"
#include <gb/gb.h>


u16 tgtx = 0;
u16 tgty = 0;
u16 camx = 0;
u16 camy = 0;

void renderer_setTarget(u16 x, u16 y)
{
    tgtx=x;
    tgty=y;
}

void renderer_init()
{
}

void renderer_updateCamera()
{
    if(camx < tgtx)
    {
        camx++;
        SCX_REG += 1;
    }
    if(camx > tgtx)
    {
        camx--;
        SCX_REG -= 1;
    }	
    if(camy < tgty)
    {
        camy++;
        SCY_REG += 1;
    }
    if(camy > tgty)
    {
        camy--;
        SCY_REG -= 1;
    }
}

void renderer_render()
{
    renderer_updateCamera();

}
