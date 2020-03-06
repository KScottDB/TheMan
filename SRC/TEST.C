#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <alloc.h>
#include <graphics.h>
#include <dos.h>

#include "CONTRIB/KIRI.C"

#define screenWidth 320
#define screenHeight 200
#define screenArea screenWidth*screenHeight

#define palSize 256*3

void loadRaw(unsigned char far* VRAM, const char* filename, int seek) {
	unsigned file_handle;
	unsigned nread;
	union REGS regs;

	_dos_open(filename, 0, &file_handle);
	
	// seek to seek in nread
	regs.h.ah = 0x42;
	regs.h.al = 0x0;
	regs.x.bx = nread;
	regs.x.cx:dx = seek; //????????
	intdos(regs, NULL);

	_dos_read(file_handle, VRAM, screenArea, &nread);

	assert(nread == screenArea);

	_dos_close(file_handle);
}

void loadBG(unsigned char far* VRAM, const char* filename) {
	unsigned char* palette = malloc(palSize); 
	int i;
	FILE* fp;
	char* buffer = malloc(19);

	fp = fopen(filename, "r");

	fread(buffer, 19, 1, fp); // CHECK HEADERS
	assert(buffer == "TMF\00T\00PAL'D-IMG\00P\00");
	
	fread(palette, palSize, 1, fp);

	outp(VGA_PALETTE_COLORID_WRITE, 0);
	for (i = 0; i <= palSize; i++) { // set palette
		outp(VGA_PALETTE_COLOR_IO, buffer[i] >> 2);
	}

	loadRaw(VRAM, filename, fseek(fp,0,0));
}

void changeVideoMode(int mode) {

	// Construct registers object

	union REGS regs;
	struct WORDREGS wr;

 	wr.ax = mode;
	regs.x = wr;

	// Pass to int86

	int86(0x10, &regs, NULL);
	// equivalent: asm { mov ax, [mode]; int 10h }

	return;

}

int main() {
	FILE* fp;
	unsigned char far* VRAM = MK_FP(0xA000, 0);
//	char* BG = malloc(screenArea);

	changeVideoMode(0x13); // Switch to 256-color VGA

	loadBG(VRAM, "BG.TMF");

	vgaRTS(); vgaRTE();

	getch();
	getch();
	getch();
	getch();

	changeVideoMode(0x2); // switch back to text mode
	
	return 0;
}
