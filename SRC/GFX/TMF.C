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
	
	header = (char*) malloc(4);
	
	fp = fopen(filename, "r");
	
	fread(header, 4, 1, fp); // Get header

	// DEBUGGING: Check "magic number".
	if (strcmp(header, "TMF") != 0) {
		gfxEnd();

		printf("Error in TMF parser: Magic number incorrect.\n");

		exit(2);
	}
	
	fread(&pal_size, 2, 1, fp); // Get palette size
	palette = malloc(pal_size);
	
	fread(palette, pal_size, 1, fp); // Get palette
	
    palSet(palette, pal_size);
	
	fread(&image_width, 2, 1, fp); // Get image size
	fread(&image_height, 2, 1, fp);

	// DEBUGGING: Check image size. All backgrounds should be
	// 320*200 at this point.
	if (image_width != 320 || image_height != 200) {
		gfxEnd();

		printf("Error in TMF parser: Image size incorrect.\nimage_width: %u\n", image_width);
		printf("image_height: %u\n", image_height);
		printf("ftell(): %ld\n", ftell(fp));

		exit(2);
	}
	
	image = (byte*) malloc(image_width * image_height);
	
	fread(image, image_width * image_height, 1, fp);
	
    vgaCopy(image, image_width * image_height);

	fclose(fp);
}