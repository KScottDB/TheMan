////////////////////////////////////////
/// PROJECT "THE MAN": VGA RENDERER  ///
///         STINKY GAMES 2020        ///
////////////////////////////////////////
// This file is here for portability. //
// Later on, I can replace routines   //
//    in this file with ones that     //
//        aren't real-mode VGA.       //
//   Code here could be more easily   //
//       ported to SDL, etc.          //
////////////////////////////////////////

#include <dos.h>
#include "TYPEDEFS.H"

// thanks kiri for a lot of vga codez!!

#define VGA_REGISTER_INPUT_STATUS_1 0x3da
#define VGA_PALETTE_COLORID_WRITE 	0x3c8
#define VGA_PALETTE_COLOR_IO      	0x3c9
#define VGA_STATUS_BIT_RETRACE 		8

void VStart(void) // ReTrace Start
{
	while(
		inp(VGA_REGISTER_INPUT_STATUS_1) & VGA_STATUS_BIT_RETRACE
	) {}
}

void VEnd(void) // ReTrace End
{
	while(
		!(inp(VGA_REGISTER_INPUT_STATUS_1) & VGA_STATUS_BIT_RETRACE)
	) {}
}

void VSync(void) {
    VStart(); VEnd();
}

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define SCREEN_AREA SCREEN_WIDTH*SCREEN_HEIGHT

#define PAL_SIZE 256*3

byte* VGARAM = (byte*)0xA0000000;
byte* PALRAM;

void vgaMode(byte mode) {
	union REGS regs;

	regs.h.ah = 0x00;
	regs.h.al = mode;
	int86(0x10, &regs, &regs);
	// equivalent: asm { mov ax, [mode]; int 10h }
}

void gfxStart(void) {
	PALRAM = (byte*) malloc(PAL_SIZE);
	vgaMode(0x13);
}

void gfxEnd(void) {
	vgaMode(0x3);
}

void palUpdate(void) {
    int i;

	outp(VGA_PALETTE_COLORID_WRITE, 0);
	for (i = 0; i <= PAL_SIZE; i++) { // set palette
		outp(VGA_PALETTE_COLOR_IO, PALRAM[i] >> 2);
	}
}

void palSet(char* palette, int pal_size) {
	memcpy(PALRAM, palette, pal_size);
	palUpdate();
}

void vgaCopy(char* memory, int amount) {
    memcpy(VGARAM, memory, amount);
}