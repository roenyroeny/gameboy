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

void vblank_handler()
{
	
    set_bkg_tile_xy(5, 5, 0);  // example: put tile 42 at (5,5)
}

joypads_t joypads;
void main(void)
{
    DISPLAY_OFF;

	draw_image(data_tiles);
	// register interrupts
    //disable_interrupts();
    //add_VBL(vblank_handler);
    //enable_interrupts();
	// draw_image(data_tiles);
	LCDC_REG |= 0x81; // enable background
	SCX_REG = SCY_REG = 0;
	set_bkg_data(32, 32, data_tiles);
	const UWORD pallette[] = {
		RGB_WHITE, RGB_LIGHTGRAY, RGB_DARKGRAY, RGB_BLACK
	};
	set_bkg_palette(0, 1, pallette);
	color(BLACK, WHITE, SOLID);

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
   	// set_bkg_data(16, 16, data_tiles);
	u8 i = 0;
	for(u8 y = 0; y < 16; y++)
	{
		for(u8 x = 0; x < 16; x++)
		{
			set_bkg_tile_xy(x, y, i);
			i++;
		}
	}
	// set_bkg_data(0, 16, checker_tile);
	// set_bkg_data(16, 16, cross_tile);
	set_bkg_tile_xy(0, 0, 0); // set tile 0 at (0, 0)
	set_bkg_tile_xy(1, 0, 1); // set tile 1 at (1, 0)

    DISPLAY_ON;

	while(1)
	{
        // poll joypads
        joypad_ex(&joypads);
		
		// print(36);
        if (joypads.joy0 & J_LEFT && viewx >= 1)
			viewx -= 1;
        if (joypads.joy0 & J_RIGHT && viewx < 0xffff - 2)
			viewx += 1;
        if (joypads.joy0 & J_UP && viewy >= 1)
			viewy -= 1;
        if (joypads.joy0 & J_DOWN && viewy < 0xffff - 2)
			viewy += 1;

		renderer_setTarget(viewx, viewy);
		renderer_render();
		
		wait_vbl_done();
	}
}
