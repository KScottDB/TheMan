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
	char thisk;
	int x = 0, y = 0;
	byte gameRunning = 1;

	bg = loadImg("BG.TMF");
	sprites = loadImg("SPRITES.TMF");
	
	gfxStart();

	while (gameRunning) {
		drawBG(bg, x, y);
		sprBgPals();

		while (kbhit()) {
			thisk = getch();
			switch (thisk) {
				
				//// SPECIAL CASES
				case 0:
					// Escape sequence
					break;
				
				//// HOTKEYS
				case 'q': // q => Quit
					gameRunning = 0;
					break;

				//// MOVEMENT
				case 'H': case 'w': // Up (Up arrow, W)
					y--; break;
				case 'P': case 's': // Down (Down arrow, S)
					y++; break;
				case 'K': case 'a': // Left (Left arrow, A)
					x--; break;
				case 'M': case 'd': // Right (Right arrow, D)
					x++; break;

				default: // key unaccounted for
					printf("%c", thisk);
					// print it on-screen for now
			}
		}

		VSync();
	}
	
	gfxEnd();
	
	free(bg.data); free(bg.palette);
	// Debugging
	printf("Execution ended normally.");
	
	return;
}
