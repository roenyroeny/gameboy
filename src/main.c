#include <gb/gb.h>
#include <gb/drawing.h>
#include "mytypes.h"

#include "renderer.h"
#include "world.h"

u16 viewx = 0, viewy = 0;

joypads_t joypads;
void main(void)
{
	while(1)
	{
		
        // poll joypads
        joypad_ex(&joypads);
        
		color(BLACK, WHITE, SOLID);
		
		gotogxy(1, 2);
		gprintf("X__");
//		for(u8 c = 0; c < 32; c++)
		{
			gotogxy(0, 1);
			gprintf("Hello World!");
		}
		plot(1, 4, BLACK, SOLID);
		plot(2, 4, BLACK, SOLID);
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

		vsync();
	}
}
