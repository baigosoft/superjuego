make -f makefile.android
cp libecosquad.so libs/armeabi/
cp libs/armeabi/* obj/local/armeabi/
rm -r bin/
/home/cabral/proyectos/android/android-ndk-r8e/toolchains/arm-linux-androideabi-4.7/prebuilt/linux-x86/bin/arm-linux-androideabi-strip obj/local/armeabi/libSDL.so
/home/cabral/proyectos/android/android-ndk-r8e/toolchains/arm-linux-androideabi-4.7/prebuilt/linux-x86/bin/arm-linux-androideabi-strip obj/local/armeabi/libSDL_image.so
/home/cabral/proyectos/android/android-ndk-r8e/toolchains/arm-linux-androideabi-4.7/prebuilt/linux-x86/bin/arm-linux-androideabi-strip obj/local/armeabi/libSDL_mixer.so
/home/cabral/proyectos/android/android-ndk-r8e/toolchains/arm-linux-androideabi-4.7/prebuilt/linux-x86/bin/arm-linux-androideabi-strip obj/local/armeabi/libSDL_ttf.so
/home/cabral/proyectos/android/android-ndk-r8e/toolchains/arm-linux-androideabi-4.7/prebuilt/linux-x86/bin/arm-linux-androideabi-strip obj/local/armeabi/libmikmod.so
/home/cabral/proyectos/android/android-ndk-r8e/toolchains/arm-linux-androideabi-4.7/prebuilt/linux-x86/bin/arm-linux-androideabi-strip obj/local/armeabi/libecosquad.so
ant debug
/home/cabral/proyectos/android/android-sdk-linux/platform-tools/adb install -r ./bin/ecosquad-debug.apk