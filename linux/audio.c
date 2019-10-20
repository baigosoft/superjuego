/*
    Superjuego Engine
    Copyright (C) 2011 Jorge Luís Cabral y Gabriel Ernesto Cabral

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Contact: baigosoft@hotmail.com
*/

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

SE_sound *SE_audio_loadsound(const char *filename)
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

SE_music *SE_audio_loadmusic(const char *filename)
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


