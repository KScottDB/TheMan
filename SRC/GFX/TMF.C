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

void drawBG(struct Image background) {
	word x,y;

	if (background.width == SCREEN_WIDTH &&
	    background.height == SCREEN_HEIGHT) {
			vgaCopy(background.data, SCREEN_AREA);
	} else {
		char* bgbuffer = malloc(SCREEN_AREA);

		for (x=0; x <= SCREEN_WIDTH; x++) for (y=0; y <= SCREEN_HEIGHT; y++) {
			bgbuffer[ twoDtoOneD(x,y,SCREEN_WIDTH) ] = 
				background.data[
					twoDtoOneD(x, y%background.height, background.width)
				];
		}
		vgaCopy(bgbuffer, SCREEN_AREA);
		free(bgbuffer);
	}
}

#define msg_imgcantload "loadIMG: Can't load %s\n"
struct Image loadImg(const char* filename) {
	struct Image img;
	byte *header;
	word pal_size, image_width, image_height;
	FILE* fp;
	
	header = (char*) malloc(4);
	
	fp = fopen(filename, "r");
	if (fp == NULL) {
		gfxEnd();

		printf(msg_imgcantload, filename);
		printf("fopen() returned NULL.\nerrno: %c\n", errno);
		
		exit(3);
	}
	
	fread(header, 4, 1, fp); // Get header
	
	// DEBUGGING: Check "magic number".
	if (strcmp(header, "TMF") != 0) {
		gfxEnd();
		
		printf(msg_imgcantload, filename);
		printf("Magic number incorrect\n");
		
		exit(2);
	}

	free(header); // we've done all we need from the header.
	
	fread(&pal_size, 2, 1, fp); // Get palette size
	img.palette = malloc(pal_size);
	
	fread(img.palette, pal_size, 1, fp); // Get palette
	
	fread(&img.width, 2, 1, fp); // Get image size
	fread(&img.height, 2, 1, fp);
	
	img.data = (byte*) malloc(image_width * image_height);
	
	fread(img.data, image_width * image_height, 1, fp);

	fclose(fp);

	return img;
}