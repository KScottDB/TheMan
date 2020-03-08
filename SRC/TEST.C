#include <alloc.h>
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Needed to stop compiler complaining
#undef outp

#define VGA_REGISTER_INPUT_STATUS_1 0x3da
#define VGA_STATUS_BIT_RETRACE 8
#define VGA_PALETTE_COLORID_WRITE 0x3c8
#define VGA_PALETTE_COLOR_IO      0x3c9

typedef unsigned char  byte;
typedef unsigned short word;

// VGA_* defines from Kiri also ^^
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

// Thanks for vgaRTS/RTE, @Kiri#0486! (DOS Shareware Zone server)

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define SCREEN_AREA SCREEN_WIDTH*SCREEN_HEIGHT

#define PAL_SIZE 256*3

void loadBG(byte far* video, const char* filename) {
	byte *palette, *header;
	int i, j;
	FILE *fp;

	palette = (byte*) malloc(PAL_SIZE);
	header = (byte*) malloc(3);

	fp = fopen(filename, "r");

	fread(header, 3, 1, fp); // READ HEADER (SKIP)

	fread(palette, PAL_SIZE, 1, fp);

	outp(VGA_PALETTE_COLORID_WRITE, 0);
	for (i = 0; i <= PAL_SIZE; i++) { // set palette
		outp(VGA_PALETTE_COLOR_IO, palette[i] >> 2);
	}

	fread(video, SCREEN_AREA, 1, fp);
}

void changeVideoMode(byte mode) {
	union REGS regs;

	regs.h.ah = 0x00;
	regs.h.al = mode;
	int86(0x10, &regs, &regs);
	// equivalent: asm { mov ax, [mode]; int 10h }
}

void main() {
	// FILE* fp;
	int x,y,color;
	word i;
	byte far*VGA = (byte far*)MK_FP(0xA000, 0);

	changeVideoMode(0x13); // Switch to 256-color VGA

	loadBG(VGA, "BG.TMF");
	vgaRTS(); vgaRTE();

	while(!kbhit()) {}

	changeVideoMode(0x3); // switch back to text mode

	return;
}
