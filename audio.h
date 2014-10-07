#ifndef AUDIO_H_
#define AUDIO_H_



#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#define SE_music Mix_Music
#define SE_sound Mix_Chunk





//int soundEnabled;
//int musicEnabled;
//int musicPlaying;

/*initialization related functions*/
void SE_audio_init(int rate, int bits, int stereo);
void SE_audio_close();
void SE_audio_enablesound();
void SE_audio_disablesound();
void SE_audio_enablemusic();
void SE_audio_disablemusic();

/*music related functions*/
SE_music *SE_audio_loadmusic(char *filename);
void SE_audio_playmusic(SE_music *musicid);
void SE_audio_stopmusic();
void SE_audio_setmusicvolume(int volume);
int SE_audio_isplayingmusic();

/*sound effects related functions*/
SE_sound *SE_audio_loadsound(char *filename);
void SE_audio_playsound(SE_sound *soundid);
void SE_audio_setsoundvolume(int volume);


#endif
