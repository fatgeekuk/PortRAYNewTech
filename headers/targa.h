# targa.h - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech

typedef struct tgafile
{
	int fd;
	int length;
	void *data;
	int width;
	int height;
	int pixelWidth;
	void *imageBase;
} TGAFile;

typedef struct tga_header
{
	char imageIdentificationLength;
	char colourMapType;
	char imageType;
	unsigned char lColourMapStartIndex, hColourMapStartIndex;
	unsigned char lColourMapLength, hColourMapLength;
	char bitsPerColourMapEntry;
	unsigned char lXofLowerLeft, hXofLowerLeft;
	unsigned char lYofLowerLeft, hYofLowerLeft;
	unsigned char lWidth, hWidth;
	unsigned char lHeight, hHeight;
	char bitsPerPixel;
	char flags;
	
} TGAHeader;

int tgaInit(TGAFile *tgaFile, char *filename, int width, int height);
int tgaOpen(TGAFile *tgaFile, char *filename, char *mode);
void tgaClose(TGAFile *tgaFile);
void tgaPlot(TGAFile *tgafile, int x, int y, int r, int g, int b);