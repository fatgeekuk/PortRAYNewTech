# README.md - part of PortRAY NewTech Developed under GPLv3 by Peter (fatgeekuk) Morris. See https://github.com/fatgeekuk/PortRAYNewTech

This is the very early beginnings of a new implementation of my old raytracer (PortRAY)

While the original PortRAY had as its aim to be completely portable (dos, OS/2, windows, unix, linux). In fact anywhere an ANSI C compiler could roam with a decent stack frame.
This new version aims only to be unix compatible. With this in mind, heavy usage of MMAP is now available to assist in some of the heavy lifting.

In addition to being a ray tracer, this will also be a testbed for implementing C code with TDD principles (modified to handle static languages).
As such, it includes my lightweight CSPEC framework. Which requires a small RUBY program to perform some janitorial tasks.

Getting Started
===============

running the tests :-

    make tests

making portray :-

    make portray

executing portray :-

    bin/portray examples/example_1.sce

This will eventually generate a TGA file of the resultant scene. At the moment, it will simply acknowledge that it does not HATE the example scene file.

Review the WIKI for progress (or lack thereof)

Goals
=====

The original PortRAY took me over 6 years to write, I was learning C for the first year or so, and after that was using PortRAY
to experiment with different global illumination models. After a while, the codebase sort of fragmented. One goal from this project
is to build a coherent toolbox of components so that I can continue exploring while re-using much of the previous code to speed things up.

In addition, I am finding writing C to be quite therapeutic. I have spent much of the intervening time between PortRAY 1 (abandoned around 1996)
and this reboot working with web frameworks and scripting languages in a commercial setting. Being able to concentrate on 'bits n bytes' with no
other pressures but the prettiness of the code is a refreshing change.

Don't expect this ever to be finished. If it starts approaching the functiality implemented in PortRAY 1, I will be extremely please and not a little
surprised.

Finally, this is being released under GPLv3. So, it cannot be used in closed source product without my consent.
