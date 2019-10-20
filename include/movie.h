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

#ifndef MOVIE_H_
#define MOVIE_H_

#include "super.h"

extern "C"{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavformat/avio.h"
#include "libswscale/swscale.h"
#include "libavutil/avstring.h"
#include "libavutil/time.h"
}


//extern typedef struct SE_movie_data;

typedef struct
{

	int videoStream = -1;
	int frameFinished = 0;
	AVFormatContext *pFormatCtx;
	AVCodecContext *pCodecCtx;
	AVCodec *pCodec = NULL;
	AVFrame *pFrame = NULL;
	AVFrame *pFrameRGB = NULL; 
	AVPacket packet;
	int numBytes;
	uint8_t *buffer = NULL;

	AVDictionary *optionsDict = NULL;
	struct SwsContext *sws_ctx = NULL;

	GLuint texture_video;

}SE_movie_data;


typedef struct
{
	
	const char *video_path;
	int width,height;
	int pause;
	int currenttime;	

	SE_movie_data *mdata;


}SE_movie;


void SE_movie_init();

SE_movie *SE_movie_load(char *path_file);

void SE_movie_play(SE_movie *movie);






#endif
