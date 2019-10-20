#SE_BASE=$(shell pwd)
SE_BASE=/home/cabral/proyectos/superjuego/nuevo

OBJS = \
$(SE_BASE)/sprite.o \
$(SE_BASE)/utils.o \
$(SE_BASE)/box.o \
$(SE_BASE)/transform.o \
$(SE_BASE)/collision.o \
$(SE_BASE)/animation.o \
$(SE_BASE)/font.o \
$(SE_BASE)/tile.o \
$(SE_BASE)/console.o 
#$(SE_BASE)/md2.o


ifdef TARGET_DREAMCAST
OBJS += \
$(SE_BASE)/dc/render.o \
$(SE_BASE)/dc/input.o \
$(SE_BASE)/dc/audio.o \
$(SE_BASE)/dc/timer.o 
else ifdef TARGET_ANDROID
OBJS += \
$(SE_BASE)/android/render.o \
$(SE_BASE)/android/input.o \
$(SE_BASE)/android/audio.o \
$(SE_BASE)/android/timer.o 
else ifdef TARGET_LINUX
OBJS += \
$(SE_BASE)/linux/luascript.o \
$(SE_BASE)/linux/render.o \
$(SE_BASE)/linux/image.o \
$(SE_BASE)/linux/primitives.o \
$(SE_BASE)/linux/input.o \
$(SE_BASE)/linux/audio.o \
$(SE_BASE)/linux/movie.o \
$(SE_BASE)/linux/timer.o
else ifdef TARGET_WIN32
OBJS += \
$(SE_BASE)/win32/render.o \
$(SE_BASE)/win32/image.o \
$(SE_BASE)/win32/primitives.o \
$(SE_BASE)/win32/input.o \
$(SE_BASE)/win32/audio.o \
$(SE_BASE)/win32/timer.o

endif
