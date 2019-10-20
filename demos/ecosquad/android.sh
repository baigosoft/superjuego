#!/bin/sh
ANDROID_NDK=/home/cabral/Descargas/android-ndk-r8e

PREFIX=${ANDROID_NDK}/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin/arm-linux-androideabi-
export CC=${PREFIX}gcc
export CXX=${PREFIX}g++
export AS=${PREFIX}gcc
export LD=${PREFIX}gcc
export AR=${PREFIX}ar cru
export RANLIB=${PREFIX}ranlib
export STRIP=${PREFIX}strip
export OBJCOPY=${PREFIX}objcopy

export MACHDEP="--sysroot=$ANDROID_NDK/platforms/android-4/arch-arm -g -mandroid -mthumb-interwork"

export CFLAGS="${MACHDEP} -Os -Wall -mandroid -msoft-float -march=armv5te -mtune=xscale"

export CXXFLAGS="${CFLAGS}"

export LDFLAGS="${MACHDEP}"

echo "make -f makefile.android"