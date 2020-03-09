#include <alloc.h>
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// CONTRIBUTIONS
#include "CONTRIB/KIRI.C"

// Needed to stop compiler complaining
#undef outp

typedef unsigned char  byte;
typedef unsigned short word;

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define SCREEN_AREA SCREEN_WIDTH*SCREEN_HEIGHT

#define PAL_SIZE 256*3

void loadBG(byte far* video, const char* filename) {
	byte *palette, *header, *image;
	word image_width, image_height;
	int i, j;
	FILE *fp;

	palette = (byte*) malloc(PAL_SIZE);
	header =  (byte*) malloc(3);

	fp = fopen(filename, "r");

	fread(header, 3, 1, fp); // READ HEADER (SKIP)

	fread(palette, PAL_SIZE, 1, fp);

	fread(&image_width, 2, 1, fp);
	fread(&image_height, 2, 1, fp);

	image = (byte*) malloc(image_width * image_height);

	fread(image, image_width * image_height, 1, fp);

	outp(VGA_PALETTE_COLORID_WRITE, 0);
	for (i = 0; i <= PAL_SIZE; i++) { // set palette
		outp(VGA_PALETTE_COLOR_IO, palette[i] >> 2);
	}

	memcpy(video, image, SCREEN_AREA);
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
	int x, y, color;
	word i;
	byte far* VGA = (byte far*) MK_FP(0xA000, 0);

	changeVideoMode(0x13); // Switch to 256-color VGA

	loadBG(VGA, "BG.TMF");
	vgaRTS(); vgaRTE();

	while(!kbhit()) {}

	changeVideoMode(0x3); // switch back to text mode

	return;
}
