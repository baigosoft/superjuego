CC = g++
DEBUG = -g
CFLAGS = -Wall `sdl-config --cflags` -I./ -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
LIBS = `sdl-config --libs` -lm  -lSDL_image -lpng -lGL -lGLU 

OBJECTS = files.o pieces.o board.o game.o main.o ../../render.o ../../image.o ../../animation.o ../../sprite.o ../../collision.o  ../../utils.o 

all: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o test05 $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o test05
