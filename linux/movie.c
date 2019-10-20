#include "movie.h"




int i;


void SE_movie_init()
{

	av_register_all();

}



SE_movie *SE_movie_load(char *path_file)
{

	SE_movie *movie;

	movie = (SE_movie*)malloc(sizeof(SE_movie));

	movie->mdata = (SE_movie_data*)malloc(sizeof(SE_movie_data));

	strcpy(movie->video_path,path_file);

	avformat_open_input(&movie->mdata->pFormatCtx,path_file,NULL,NULL);

	if(avformat_find_stream_info(movie->mdata->pFormatCtx, NULL)<0)
    {
		printf("SE_movie: no hay informacion de stream");
	}

	movie->mdata->videoStream=-1;
	for(i=0; i<movie->mdata->pFormatCtx->nb_streams; i++)
	{
		if(movie->mdata->pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO) 
		{
			movie->mdata->videoStream=i;
			break;
		}
	}
	if(movie->mdata->videoStream==-1)printf("no se encontró stream");

	movie->mdata->pCodecCtx=movie->mdata->pFormatCtx->streams[movie->mdata->videoStream]->codec;

	movie->mdata->pCodec=avcodec_find_decoder(movie->mdata->pCodecCtx->codec_id);
	if(movie->mdata->pCodec==NULL) 
	{
		printf("SE_movie: codec no soportado");
	}
  
	if(avcodec_open2(movie->mdata->pCodecCtx, movie->mdata->pCodec,&movie->mdata->optionsDict)<0)
	{	
		printf("no se puede abrir codec");		
	}  

	movie->mdata->pFrame=av_frame_alloc();

	if(movie->mdata->pFrame==NULL)
	{
		printf("SE_movie: primer frame vacio o nulo");
	}

	movie->mdata->pFrameRGB=av_frame_alloc();

	movie->width = movie->mdata->pCodecCtx->width;
	
	movie->height = movie->mdata->pCodecCtx->height;

	movie->mdata->numBytes = avpicture_get_size(AV_PIX_FMT_BGR24, movie->mdata->pCodecCtx->width, movie->mdata->pCodecCtx->height);

	movie->mdata->buffer=(uint8_t *)av_malloc(movie->mdata->numBytes*sizeof(uint8_t));

	avpicture_fill((AVPicture *)movie->mdata->pFrameRGB,movie->mdata->buffer,AV_PIX_FMT_BGR24,movie->mdata->pCodecCtx->width,movie->mdata->pCodecCtx->height);

	glGenTextures(1,&movie->mdata->texture_video);
	glBindTexture(GL_TEXTURE_2D,movie->mdata->texture_video); 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,movie->mdata->pCodecCtx->width,movie->mdata->pCodecCtx->height,0, GL_RGB, GL_UNSIGNED_BYTE,movie->mdata->pFrameRGB->data[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	movie->mdata->sws_ctx =  sws_getContext(movie->mdata->pCodecCtx->width,
											movie->mdata->pCodecCtx->height,
											movie->mdata->pCodecCtx->pix_fmt,
											movie->mdata->pCodecCtx->width,
											movie->mdata->pCodecCtx->height,
											AV_PIX_FMT_BGR24,
											SWS_BILINEAR,
											NULL,
											NULL,
											NULL);



	return movie;

}

void SE_movie_play(SE_movie *movie)
{

	int i=0;

	for(;;)
	{
		for(;;)
		{
			if(av_read_frame(movie->mdata->pFormatCtx,&movie->mdata->packet)>=0) 
			{
    	
				// Is this a packet from the video stream?
    			if(movie->mdata->packet.stream_index==movie->mdata->videoStream)
				{
					// Decode video frame
					avcodec_decode_video2(movie->mdata->pCodecCtx,movie->mdata->pFrame,&movie->mdata->frameFinished,&movie->mdata->packet);
      
					// Did we get a video frame?
					if(movie->mdata->frameFinished)
					{
						// Convert the image from its native format to RGB
						sws_scale(movie->mdata->sws_ctx,
								 (uint8_t const * const *)movie->mdata->pFrame->data,
								  movie->mdata->pFrame->linesize,
								  0,
								  movie->mdata->pCodecCtx->height,
								  movie->mdata->pFrameRGB->data,
								  movie->mdata->pFrameRGB->linesize);
				
						//Convert RGB frame to texture
						glBindTexture( GL_TEXTURE_2D,movie->mdata->texture_video);
						glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
						glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
						glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
						glTexSubImage2D(GL_TEXTURE_2D,
										0,0,0,
										movie->mdata->pCodecCtx->width,
										movie->mdata->pCodecCtx->height,
										GL_RGB,GL_UNSIGNED_BYTE,
										movie->mdata->pFrameRGB->data[0]);

						break;

					}

					// Free the packet that was allocated by av_read_frame
    				av_free_packet(&movie->mdata->packet);

				}
    
			

			}else{
				av_seek_frame(movie->mdata->pFormatCtx,movie->mdata->videoStream,0,AVSEEK_FLAG_FRAME);
			} 
		
		}

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.4f, 0.4f, 0.0f);
		glBindTexture(GL_TEXTURE_2D,movie->mdata->texture_video);
		glScalef(1.0f, -1.0f, 1.0f);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f); 
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-1.0f, 1.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(1.0f, 1.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(1.0f, -1.0f, 0.0f);
 	   glEnd();
 	   glScalef(1.0f, -1.0f, 1.0f);
	
 	   SDL_GL_SwapBuffers();

	}

}
