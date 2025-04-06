#include <gb/gb.h>
#include <stdint.h>
#include <gb/drawing.h>
#include "types.h"

void main(void)
{
	color(0, 0, SOLID);
	gotogxy(0, 0);
	gprintf("Hello World!");
}
