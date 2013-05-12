/* vectors_test.c - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

#include "../test_helper.h"
#include "../../src/vectors.c"

void test_vectors(){
	Vec a, b, c, d;
	
	CONTEXT("Vectors")
		CONTEXT("initialisation")
			vecSet(0.0, 0.0, 0.0, &a);
			expect(dblEqual(a.x, 0.0), "x should be zero!");
			expect(dblEqual(a.y, 0.0), "y should be zero!");
			expect(dblEqual(a.z, 0.0), "z should be zero!");
	
		NEXT_CONTEXT("instance methods")
			vecSet(1.0, 2.0, 3.0, &a);
			vecSet(2.0, 4.0, 6.0, &b);
	
			CONTEXT("COMPARISON")
				vecSet(1.0, 2.0, 3.0, &c);
				expect(vectorEqual(&a, &c), "a should be equal to c");
				expect_not(vectorEqual(&a, &b), "a should not equal b");
		
			NEXT_CONTEXT("ADD")
				addVector(&a, &c, &d);
				expect(vectorEqual(&d, &b), "a+c does not equal b");
	
			NEXT_CONTEXT("SUB")
				subVector(&b, &a, &d);
				expect(vectorEqual(&d, &c), "b-a does not equal c");
		
			NEXT_CONTEXT("SCALE")
				scaleVector(2.0, &a, &b);
				expect(vectorEqual(&d, &a), "twice a does not equal b");
				
			NEXT_CONTEXT("COPY")
				vecCopy(&a, &b);
				expect(dblEqual(b.x, 1.0), "x should be one!");
				expect(dblEqual(b.y, 2.0), "y should be two!");
				expect(dblEqual(b.z, 3.0), "z should be three!");
				
			END_CONTEXT
	
		END_CONTEXT
	END_CONTEXT
}