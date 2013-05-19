/* ray_test.c - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

#include "../test_helper.h"
#include "../../src/ray.c"

void test_rays(){
	Vec o, d;
	Ray a;
	double x;
	
	CONTEXT("Rays")
		CONTEXT("initialisation")
			vecSet(1.0, 2.0, 3.0, &o);
			vecSet(1.0, 1.0, 1.0, &d);
			rayInit(&o, &d, &a);
			
			expect(dblEqual(1.0, vecLength(&(a.direction))), "direction should be a unit vector");
		END_CONTEXT
	END_CONTEXT
}