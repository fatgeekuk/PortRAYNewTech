# dummy_writer.c - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech

#include "../headers/targa.h"

int main(){
	TGAFile tgaFile;
	int i;
	tgaInit(&tgaFile, "output.tga", 1024, 768);
	for(i=100; i<924; i++){ tgaPlot(&tgaFile, i, 100, 255, 255, 255); tgaPlot(&tgaFile, i, 686, 255, 255, 255); };
	for(i=100; i<686; i++){ tgaPlot(&tgaFile, 100, i, 255, 255, 255); tgaPlot(&tgaFile, 924, i, 255, 255, 255); };
	tgaClose(&tgaFile);
}