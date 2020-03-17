#ifndef TYPEDEFS_H
#define TYPEDEFS_H

typedef unsigned char  byte;
typedef unsigned short word;

struct Image {
    byte* data;
    byte* palette;
    word palsize;
    word width;
    word height;
};

// kiri VGA defs

#define VGA_REGISTER_INPUT_STATUS_1 0x3da
#define VGA_PALETTE_COLORID_WRITE 	0x3c8
#define VGA_PALETTE_COLOR_IO      	0x3c9
#define VGA_STATUS_BIT_RETRACE 		8

// used to be RENDERER.C:

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 200
#define SCREEN_AREA   SCREEN_WIDTH*SCREEN_HEIGHT

#define SCREENMODE   0x13
#define SCREENEXMODE 0x03

#define PAL_SIZE 256*3

#endif