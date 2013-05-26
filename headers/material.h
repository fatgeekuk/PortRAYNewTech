/* material.h - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

typedef struct Material {
	Vec diffuse_colour;
} Material;

Material *allocMaterial();