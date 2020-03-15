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

void main() {
	struct Image bg;
	
	gfxStart();

	bg = loadImg("BG.TMF");
	drawBG(bg);

	VSync();

	while(!kbhit()) {}

	gfxEnd();

	// Debugging
	printf("Execution ended normally.");

	return;
}
