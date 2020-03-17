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

	vgaMode(SCREENMODE);
}

void gfxEnd(void) {
	vgaMode(SCREENEXMODE);
}

void palUpdate(void) {
    int i;

	outp(VGA_PALETTE_COLORID_WRITE, 0);
	for (i = 0; i <= PAL_SIZE; i++) { // set palette
		outp(VGA_PALETTE_COLOR_IO, PALRAM[i] >> 2);
	}
}

void vgaCopy(char* memory, int amount) {
    memcpy(VGARAM, memory, amount);
}