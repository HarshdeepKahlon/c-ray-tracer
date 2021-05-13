FLAGS=-D_LINUX -ffast-math -funroll-loops -O3 -g -lm
LIBS=-lGL -lglut -lGLU -lpthread
INCDIR=-I../include
LIBDIR=-L../lib -L/usr/X11R6/lib
CC=gcc

raytracer: raytracer.c 
	$(CC) raytracer.c Utility.c Cube.c $(FLAGS) $(INCDIR) $(LIBDIR) $(LIBS) -o raytracer
