#include <alloc.h>
#include <conio.h>
#include <dos.h>
#include <graphics.h>
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
	changeVideoMode(0x13); // Switch to 256-color VGA
	
	loadBG("BG.TMF");
	vgaRTS(); vgaRTE();

	while(!kbhit()) {}

	changeVideoMode(0x3); // switch back to text mode

	return;
}
