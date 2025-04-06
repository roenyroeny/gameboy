#include <gb/gb.h>
#include <gb/drawing.h>
#include "mytypes.h"

#include "renderer.h"
#include "world.h"

#include "data.h"

u16 viewx = 0, viewy = 0;

const uint8_t cross_tile[16] = {
    0x00, 0x3C,  // Row 0
    0x00, 0x3C,  // Row 1
    0xFF, 0xFF,  // Row 2
    0xFF, 0xFF,  // Row 3
    0xFF, 0xFF,  // Row 4
    0xFF, 0xFF,  // Row 5
    0x00, 0x3C,  // Row 6
    0x00, 0x3C   // Row 7
};
u8 pallette[]={170, 170,170,170,170,170,170,170};


void vblank_handler()
{
	
    set_bkg_tile_xy(5, 5, 0);  // example: put tile 42 at (5,5)
}

joypads_t joypads;
void main(void)
{
    DISPLAY_OFF;
	// register interrupts
    disable_interrupts();
    add_VBL(vblank_handler);
    enable_interrupts();

	color(BLACK, WHITE, SOLID);
    draw_image(data_tiles);

	const unsigned char checker_tile[] = {
		0xAA, 0xAA,
		0x55, 0x55,
		0xAA, 0xAA,
		0x55, 0x55,
		0xAA, 0xAA,
		0x55, 0x55,
		0xAA, 0xAA,
		0x55, 0x55,
	};
	// write to 0x8000
	LCDC_REG |= 0x10;
   	set_bkg_data(0, 1, checker_tile);


    DISPLAY_ON;
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
		
		wait_vbl_done();
	}
}
