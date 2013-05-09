/* targa.c - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "../headers/targa.h"

#define COLOUR_MAP_NONE 0
#define COLOUR_MAP_PRESENT 1
#define IMAGE_TYPE_NODATA 0
#define IMAGE_TYPE_COLOUR_MAP 1
#define IMAGE_TYPE_RGB 2

int tgaInit(TGAFile *tgaFile, char *filename, int width, int height){
	int fd, answer;
	TGAHeader *tgaHeader;
	int i, j;
	char *ptr;
	
	tgaFile->length = sizeof(TGAHeader) + 3 * (width * height);
	
	printf("Calculated Length as %d\n", tgaFile->length);
	// open file for read and write;
	printf("opening file %s\n", filename);
	fd = open(filename, O_RDWR | O_CREAT);
	fchmod(fd, S_IRUSR | S_IWUSR);
	
	if (fd != -1){
		for (i=0; i<tgaFile->length; i++) write(fd, " ", 1);
		printf("file opened aok, writing\n");
		tgaFile->fd = fd;
		tgaFile->width = width;
		tgaFile->height = height;
		tgaFile->pixelWidth = 3;
		
		tgaFile->data =  mmap(0, tgaFile->length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
		close(tgaFile->fd);
		
		if (tgaFile->data == MAP_FAILED){
			printf("Map Failed\n");
		} else {
			tgaHeader = (TGAHeader *)tgaFile->data;

			printf("Writing header\n");
			// initialise the TGA Header
			tgaHeader = (TGAHeader *)tgaFile->data;
			tgaHeader->imageIdentificationLength = 0;
			tgaHeader->colourMapType             = COLOUR_MAP_NONE;
			tgaHeader->imageType                 = IMAGE_TYPE_RGB;
			tgaHeader->lColourMapStartIndex      = 0;
			tgaHeader->hColourMapStartIndex      = 0;
			tgaHeader->lColourMapLength          = 0;
			tgaHeader->hColourMapLength          = 0;
			tgaHeader->bitsPerColourMapEntry     = 0;
			tgaHeader->lXofLowerLeft             = 0;
			tgaHeader->hXofLowerLeft             = 0;
			tgaHeader->lYofLowerLeft             = 0;
			tgaHeader->hYofLowerLeft             = 0;
			tgaHeader->lWidth                    = width & 0x000000ff;
			tgaHeader->hWidth                    = (width & 0x0000ff00) >> 8;
			tgaHeader->lHeight                   = height & 0x000000ff;
			tgaHeader->hHeight                   = (height & 0x0000ff00) >> 8;
			tgaHeader->bitsPerPixel              = 24;
			tgaHeader->flags                     = 0;

			tgaFile->imageBase = tgaFile->data + sizeof(TGAHeader);
			ptr = tgaFile->imageBase;
			for (j=0; j<height; j++){
				for (i=0; i<width; i++){
					*ptr++ = 0xff;
					*ptr++ = 0x00;
					*ptr++ = 0x00;
				}
			}
		}
		
		answer = 0;
	} else {
		answer = 1;
	}

	return answer;
};

int tgaOpen(TGAFile *tgaFile, char *filename, char *mode){
	
};

void tgaClose(TGAFile *tgaFile){
	printf("Closing tga mapping\n");
	msync(tgaFile->data, tgaFile->length, MS_SYNC);
	munmap(tgaFile->data, tgaFile->length);
};

void tgaPlot(TGAFile *tgaFile, int x, int y, int r, int g, int b){
	unsigned char *pixPtr = tgaFile->imageBase + tgaFile->pixelWidth * (tgaFile->width * y + x);
	*pixPtr++ = b;
	*pixPtr++ = g;
	*pixPtr++ - r;
}