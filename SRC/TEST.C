#include <stdio.h>
#include <stdlib.h>
#include <dos.h>

#define VGA_REGISTER_INPUT_STATUS_1 0x3da
#define VGA_STATUS_BIT_RETRACE 8

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

#define screenWidth 320
#define screenHeight 200
#define screenArea 64000

//void loadBG(char* BG) {
//}

int main() {
	FILE* fp;
	char far* VRAM = MK_FP(0xA000, 0);
	char* BG = malloc(screenArea);

	asm {
		mov ax, 13h
		int 10h
	} // Switch video mode

	//loadBG(BG);
	
	
	fp = fopen("BG.TMF", "r");
	fread(BG, screenArea, 1, fp);
	fclose(fp);

	while (1) {
		memcpy(VRAM, BG, screenArea);

		vgaRTS(); vgaRTE();
	}

	return 0;
}