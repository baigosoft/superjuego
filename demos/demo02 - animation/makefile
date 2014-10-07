CC = g++
DEBUG = -g
CFLAGS = -Wall `sdl-config --cflags` -I./ -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
LIBS = `sdl-config --libs` -lm  -lSDL_image -lpng -lGL -lGLU 

OBJECTS = main.o ../../render.o ../../image.o ../../animation.o ../../utils.o 

all: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o test02 $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o test02
