TARGET=demo
TARGET_LINUX=1
CC = g++
DEBUG = -g
CFLAGS = -Wall `sdl-config --cflags` `pkg-config --cflags lua5.1 libavformat libavcodec libswscale libavutil`  -I./ -I$(SE_BASE)/linux -I$(SE_BASE)/include -c $(DEBUG) -fpermissive
LFLAGS = -Wall $(DEBUG)
LIBS = `sdl-config --libs` `pkg-config --libs lua5.1 libavformat libavcodec libswscale libavutil` -lm  -lSDL_image -lSDL_mixer -lpng -lGL -lGLU -llua5.1 -ldl 

#-lavdevice -lavformat -lavfilter -lavcodec -lswresample -lswscale -lavutil -lbz2 -lm -lz -lpthread -lpostproc

include ../../config.mk

all: $(TARGET)

OBJS += main.o 

rm-elf:
	-rm -f $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(TARGET) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET) $(OBJS)
