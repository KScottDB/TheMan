#include <dos.h>

   /*                       */
  /* Code here contributed */
 /*    by @Kiri#0486 :)   */
/*                       */

#define VGA_REGISTER_INPUT_STATUS_1 0x3da
#define VGA_PALETTE_COLORID_WRITE 	0x3c8
#define VGA_PALETTE_COLOR_IO      	0x3c9
#define VGA_STATUS_BIT_RETRACE 		8

void vgaRTS(void) // ReTrace Start
{
	while(
		inp(VGA_REGISTER_INPUT_STATUS_1) & VGA_STATUS_BIT_RETRACE
	) {}
}

void vgaRTE(void) // ReTrace End
{
	while(
		!(inp(VGA_REGISTER_INPUT_STATUS_1) & VGA_STATUS_BIT_RETRACE)
	) {}
}