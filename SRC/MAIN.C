#include <alloc.h>
#include <conio.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "GFX/RENDERER.C"
#include "GFX/TMF.C"

#include "TYPEDEFS.H"

// Needed to stop compiler complaining
#undef outp

struct Image bg;
struct Image sprites;

void sprBgPals() {
	if (bg.palsize > 16*3) {
		gfxEnd();
		printf("sprBgPals: Background palette will overflow into spritesheet palette!\n");
		printf("\"bg\" needs to be no more than 16 colors.\n");
		
		exit(4);
	}
	if (sprites.palsize > PAL_SIZE) {
		gfxEnd();
		printf("sprBgPals: Spritesheet palette will overflow PALRAM!\n");
		printf("sprites.palette needs to be <= %i!\n", PAL_SIZE);
		
		exit(3);
	}
	
	memcpy(PALRAM, sprites.palette, sprites.palsize);
	memcpy(PALRAM, bg.palette, bg.palsize);
	
	palUpdate();
}

void main() {
	bg = loadImg("BG.TMF");
	sprites = loadImg("SPRITES.TMF");
	
	gfxStart();
	
	drawBG(bg);
	sprBgPals();
	
	VSync();
	
	while(!kbhit()) {}
	
	gfxEnd();
	
	free(bg.data); free(bg.palette);
	// Debugging
	printf("Execution ended normally.");
	
	return;
}
