CC = g++
DEBUG = -g
CFLAGS = -Wall `sdl-config --cflags` -I./ -I./../.. -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
LIBS = `sdl-config --libs` -lm  -lSDL_image -lpng -lGL -lGLU 

OBJECTS = main.o ../../render.o ../../image.o ../../animation.o ../../sprite.o ../../tile.o ../../collision.o ../../font.o ../../primitives.o ../../utils.o ../../audio.o ../../timer.o ../../input.o 

all: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o test01 $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o test01
