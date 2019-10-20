TARGET=testmd2
CC = g++
DEBUG = -g
CFLAGS = -O2 -Wall `sdl-config --cflags` -I./ -I$(SE_BASE)/linux -I$(SE_BASE)/include -c $(DEBUG) 
LFLAGS = -Wall $(DEBUG)
LIBS = `sdl-config --libs` -lm  -lSDL_image -lSDL_mixer -lpng -lGL -lGLU 


include ../../config.mk

all: $(TARGET)

OBJS += main.o char.o enemy.o title.o menu.o zone.o

rm-elf:
	-rm -f $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(TARGET) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
