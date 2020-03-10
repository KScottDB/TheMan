#include "TYPEDEFS.H"

void loadBG(const char* filename) {
	byte *palette, *header, *image;
	word pal_size, image_width, image_height;
	FILE *fp;

	header  = (byte*) malloc(4);

	fp = fopen(filename, "r");

	fread(header, 4, 1, fp); // Get header
	//assert(header == "TMF"); // Magic number check (DOESN'T WORK???)
	
	assert(sizeof(word) == 2);

	fread(&pal_size,     2, 1, fp); // Get palette size
	palette = malloc(pal_size);

	fread(palette, pal_size, 1, fp); // Get palette

    setPal(palette, pal_size);

	fread(&image_width,  2, 1, fp); // Get image size
	fread(&image_height, 2, 1, fp);

	image = (byte*) malloc(image_width * image_height);

	fread(image, image_width * image_height, 1, fp);

    VRAMCopy(image, image_width * image_height);
}