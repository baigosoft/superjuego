TARGET=demo10
CC = g++
DEBUG = -g
CFLAGS = -Wall `sdl-config --cflags` `pkg-config --cflags lua5.1` -I./ -I$(SE_BASE)/linux -I$(SE_BASE)/include -c $(DEBUG) 
LFLAGS = -Wall $(DEBUG)
LIBS = `sdl-config --libs` `pkg-config --libs lua5.1` -lm  -lSDL_image -lSDL_mixer -lpng -lGL -lGLU -llua5.1 -ldl


include ../../config.mk

all: rm-elf $(TARGET)

OBJS += main.o 

rm-elf:
	-rm -f $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(TARGET) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)
