../bin/dummy_writer: dummy_writer.o vectors.o targa.o
	gcc -o $@ $< vectors.o targa.o -lm

../bin/portray: grammar.o vectors.o targa.o lexer.o storage.o camera.o ring_list.o geometry.o renderer.o ray.o material.o intersection.o illumination_models.o optparse.o chatterbox.o
	gcc -o $@ grammar.o vectors.o targa.o lexer.o storage.o camera.o ring_list.o geometry.o renderer.o ray.o material.o intersection.o illumination_models.o optparse.o chatterbox.o -lm
	
.c.o:
	gcc -o $@ -g -c -O2 $<

vectors.o: vectors.c

geometry.o: geometry.c geometry/plane.c geometry/sphere.c geometry/box.c ../headers/object.h

ring_list.o: ring_list.c

camera.o: camera.c ../headers/storage.h ../headers/camera.h ../headers/vectors.h

targa.o: targa.c

optparse.o: optparse.c ../headers/optparse.h

storage.o: storage.c ../headers/storage.h ../headers/camera.h ../headers/vectors.h

grammar.c: grammar.y
	bison -o $@ -d grammar.y

grammar.o: grammar.c

intersection.o: intersection.c

dummy_writer.o: dummy_writer.c

renderer.o: renderer.c targa.c

illumination_models.o: illumination_models.c

ray.o: ray.c

material.o: material.c

chatterbox.o: chatterbox.c

lexer.c: lexer.l
	flex -o $@ $<

lexer.o: lexer.c


