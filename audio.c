#include "audio.h"

int soundEnabled=0;
int musicEnabled=0;
int musicPlaying=0;

void SE_audio_init(int rate, int bits, int stereo)
{
	
	if (bits==8){
		bits=AUDIO_S8;
	}else{
		bits=AUDIO_S16;
	}

	if (Mix_OpenAudio(rate, bits, stereo, 1024) < 0)
		{
			printf("No se puede inicializar el dispositivo de sonido: %s\n", Mix_GetError());
			soundEnabled = 0;
			musicEnabled = 0;
		}

	soundEnabled = 1;
	musicEnabled = 1;
	//Mix_Chunk* sounds=malloc(sizeof(Mix_Chunk)*MAX_SAMPLES);
}

void SE_audio_close()
{
	Mix_CloseAudio();
}

void SE_audio_enablesound()
{
	soundEnabled=1;
}

void SE_audio_disablesound()
{
	soundEnabled=0;
}

void SE_audio_enablemusic()
{
	musicEnabled=1;
}

void SE_audio_disablemusic()
{
	musicEnabled=0;

}

SE_sound *SE_audio_loadsound(char *filename)
{
	SE_sound *chunk;
	chunk = Mix_LoadWAV(filename);
	if(!chunk){
		printf("error cargando sonido: %s\n",filename);
		return 0;
	}
	
	return chunk;
}

void SE_audio_playsound(SE_sound *soundid)
{
	if(soundEnabled){
		Mix_PlayChannel(-1, soundid, 0);
	}
}

void SE_audio_setsoundvolume(int volume){

	Mix_Volume(-1, volume);

}

SE_music *SE_audio_loadmusic(char *filename)
{
	SE_music *music;

	if (Mix_PlayingMusic())
		Mix_HaltMusic();

	/*if (engine.music != NULL)
		Mix_FreeMusic(engine.music);*/

	music=Mix_LoadMUS(filename);
	if(!music){
		printf("error cargando música: %s\n",filename);
		return 0;
	}

	return music;
	
}

void SE_audio_playmusic(SE_music *musicid)
{
	
	if(musicEnabled){
		Mix_PlayMusic(musicid, -1);
	}
	musicPlaying=1;

}

void SE_audio_stopmusic()
{
	
	if (Mix_PlayingMusic())
		Mix_HaltMusic();
	musicPlaying=0;

}

int SE_audio_isplayingmusic()
{
	return musicPlaying;
}

void SE_audio_setmusicvolume(int volume){

	Mix_VolumeMusic(volume);

}


