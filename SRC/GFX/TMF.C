////////////////////////////////////////
/// PROJECT "THE MAN": .TMF DECODING ///
///         STINKY GAMES 2020        ///
////////////////////////////////////////
//     This file contains code for    //
//        decoding .TMF files.        //
//         See /GFX/SPRENC.PY.        //
////////////////////////////////////////

#include <stdio.h>

#include "TYPEDEFS.H"

void loadBG(const char* filename) {
	byte *palette, *header, *image;
	word pal_size, image_width, image_height;
	FILE* fp;
	
	header = malloc(4);
	
	fp = fopen(filename, "r");
	
	fread(header, 4, 1, fp); // Get header
	assert(strcmp(header, "TMF")); // Magic number check
	
	fread(&pal_size, 2, 1, fp); // Get palette size
	palette = malloc(pal_size);
	
	fread(palette, pal_size, 1, fp); // Get palette
	
    palSet(palette, pal_size);
	
	fread(&image_width, 2, 1, fp); // Get image size
	fread(&image_height, 2, 1, fp);
	
	image = (byte*) malloc(image_width * image_height);
	
	fread(image, image_width * image_height, 1, fp);
	
    vgaCopy(image, image_width * image_height);
}