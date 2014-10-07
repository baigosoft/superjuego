CC = g++
DEBUG = -g
CFLAGS = -Wall `sdl-config --cflags` -I./ -c $(DEBUG) -fPIC
LFLAGS = -Wall $(DEBUG) -shared 
LIBS = `sdl-config --libs` -lm  -lSDL_image -lpng -lGL -lGLU 
prefix=/usr/lib

OBJECTS = render.o image.o animation.o sprite.o tile.o collision.o tilecamera.o font.o utils.o


all: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o libsjuego.so $(LIBS)


    
install: libsjuego.so
	install -m 0755 libsjuego.so $(prefix)
  

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o test
