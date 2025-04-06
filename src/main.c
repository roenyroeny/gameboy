#include <gb/gb.h>
#include <gb/drawing.h>
#include "mytypes.h"

#include "renderer.h"
#include "world.h"

#include "data.h"

u16 viewx = 0, viewy = 0;


u8 pallette[]={170, 170,170,170,170,170,170,170};

joypads_t joypads;
void main(void)
{
	gotogxy(1, 2);
	gprintf("X__");
	color(BLACK, WHITE, SOLID);
    draw_image(data_tiles);
	while(1)
	{
        // poll joypads
        joypad_ex(&joypads);
		
		// print(36);
        if (joypads.joy0 & J_LEFT && viewx > 1)
			viewx -= 1;
        if (joypads.joy0 & J_RIGHT && viewx < 0xffff - 2)
			viewx += 1;		 
        if (joypads.joy0 & J_UP && viewy > 1)
			viewy -= 1;
        if (joypads.joy0 & J_DOWN && viewy < 0xffff - 2)
			viewy += 1;

		renderer_setTarget(viewx, viewy);
		renderer_render();

		for(i16 i = 0; i < 16; i++)
			_VRAM9000[i] = 16 + i;
		
		vsync();
	}
}
