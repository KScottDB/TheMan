////////////////////////////////////////
/// PROJECT "THE MAN": .TMF DECODING ///
///         STINKY GAMES 2020        ///
////////////////////////////////////////
//     This file contains code for    //
//        decoding .TMF files.        //
//         See /GFX/SPRENC.PY.        //
////////////////////////////////////////

#include <stdio.h>
#include <errno.h>

#include "TYPEDEFS.H"

word twoDtoOneD(word x, word y, word w) {
	return x%w + (y * w);
}

void drawBG(struct Image background, int x_offs, int y_offs) {
	if (background.width == SCREEN_WIDTH &&
	    background.height == SCREEN_HEIGHT &&
		x_offs % SCREEN_WIDTH == 0 &&
		y_offs % SCREEN_HEIGHT == 0) {
			vgaCopy(background.data, SCREEN_AREA);
	} else {
		int x,y;
		
		for (x=0; x <= SCREEN_WIDTH; x++) for (y=0; y <= SCREEN_HEIGHT; y++) {
			VGARAM[ twoDtoOneD(x,y,SCREEN_WIDTH) ] = 
				background.data[
					twoDtoOneD(x+x_offs, (y+y_offs)%background.height, background.width) % (background.width*background.height)
				];
		}
	}
}

#define msg_imgcantload "loadIMG: Can't load %s\n"
struct Image loadImg(const char* filename) {
	struct Image img;
	byte* header;
	word  pal_size, image_width, image_height;
	FILE* fp;
	
	fp = fopen(filename, "r");
	if (fp == NULL) {
		gfxEnd();

		printf(msg_imgcantload, filename);
		printf("fopen() returned NULL.\nerrno: %c\n", errno);
		
		exit(2);
	}
	
	header = (char*) malloc(4);
	fread(header, 4, 1, fp); // Get header
	
	// DEBUGGING: Check "magic number".
	if (strcmp(header, "TMF") != 0) {
		gfxEnd();
		
		printf(msg_imgcantload, filename);
		printf("Magic number incorrect\n");
		
		exit(1);
	}

	free(header); // we've done all we need from the header.
	
	fread(&img.palsize, 2, 1, fp); // Get palette size
	img.palette = (byte*) malloc(img.palsize);
	
	fread(img.palette, img.palsize, 1, fp); // Get palette
	
	fread(&img.width, 2, 1, fp); // Get image size
	fread(&img.height, 2, 1, fp);
	
	img.data = (byte*) malloc(img.width * img.height);
	
	fread(img.data, img.width * img.height, 1, fp);

	fclose(fp);

	return img;
}