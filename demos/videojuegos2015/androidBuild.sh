#!/bin/sh

PROJNAME=superjuego
SDLPATH=/home/cabral/proyectos/superjuego/android/sdl12
ANDROIDSDK=/home/cabral/proyectos/android/android-sdk-linux
ANDROIDNDK=/home/cabral/proyectos/android/android-ndk-r8e
PROJPATH=$SDLPATH/project/jni/application/$PROJNAME
SEPATH=/home/cabral/proyectos/superjuego/git


export PATH=$PATH:$ANDROIDNDK
export PATH=$PATH:$ANDROIDSDK/platform-tools
export PATH=$PATH:$ANDROIDSDK/tools
export PATH=$PATH:$SEPATH
export PATH=$PATH:$SEPATH/include



mkdir $PROJPATH
cp ./*.c $PROJPATH
cp ./AndroidAppSettings.cfg $PROJPATH
cp ./icon.png $PROJPATH
cp $SEPATH/*.c $PROJPATH
cp $SEPATH/android/*.c $PROJPATH

rm $PROJPATH/md2.c
rm $PROJPATH/movie.c
rm $PROJPATH/luascript.c

cd datos
mkdir $PROJPATH/AndroidData
zip $PROJPATH/AndroidData/data.zip * 



cd $SDLPATH
sh build.sh 
adb install -r $SDLPATH/project/bin/MainActivity-debug.apk
