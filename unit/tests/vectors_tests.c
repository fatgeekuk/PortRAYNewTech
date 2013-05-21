/* vectors_tests.c - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech */

#include "../test_helper.h"
#include "../../src/vectors.c"

void test_vectors(){
	Vec a, b, c, d;
	double x;
	
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
				expect(vecEqual(&a, &c), "a should be equal to c");
				expect_not(vecEqual(&a, &b), "a should not equal b");
		
			NEXT_CONTEXT("ADD")
				vecAdd(&a, &c, &d);
				expect(vecEqual(&d, &b), "a+c does not equal b");
	
			NEXT_CONTEXT("SUB")
				vecSub(&b, &a, &d);
				expect(vecEqual(&d, &c), "b-a does not equal c");
		
			NEXT_CONTEXT("SCALE")
				vecScale(2.0, &a, &b);
				expect(vecEqual(&d, &a), "twice a does not equal b");
				
			NEXT_CONTEXT("COPY")
				vecCopy(&a, &b);
				expect(dblEqual(b.x, 1.0), "x should be one!");
				expect(dblEqual(b.y, 2.0), "y should be two!");
				expect(dblEqual(b.z, 3.0), "z should be three!");
				
			NEXT_CONTEXT("DOT")
				x = vecDot(&a, &a);
				expect(dblEqual(x, 14.0), "dot should be 14");
			
			NEXT_CONTEXT("LENGTH")
				vecSet(0.0, 3.0, 4.0, &a);
				expect(dblEqual(5.0, vecLength(&a)), "you gotta love pythagoras");
				
			NEXT_CONTEXT("CROSSPRODUCT")
				vecSet(0.0, 0.0, 1.0, &a);
				vecSet(0.0, 1.0, 0.0, &b);
				vecProduct(&a, &b, &c);
				expect(dblEqual(0.0, vecDot(&a, &c)), "A*B should be at right angles to a");
				expect(dblEqual(0.0, vecDot(&b, &c)), "A*B should be at right angles to b");
				expect(dblEqual(1.0, vecLength(&c)), "and it should have unit length");
				
			NEXT_CONTEXT("NORMALISE")
				vecSet(3.0, 2.0, 1.0, &a);
				vecNormalise(&a, &a);
				expect(dblEqual(1.0, vecLength(&a)), "A normalised vector should have unit length");
			END_CONTEXT
		END_CONTEXT
	END_CONTEXT
}