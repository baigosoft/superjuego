#ifndef MD2_H_
#define MD2_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "render.h"

#ifdef DREAMCAST
//#include "kos.h"
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#endif



#define MD2_IDENT                (('2'<<24) + ('P'<<16) + ('D'<<8) + 'I')


// obj header
typedef struct
{
    int     ident;              // magic number. must be equal to "IDP2"
    int     version;            // md2 version. must be equal to 8

    int     skinwidth;          // width of the texture
    int     skinheight;         // height of the texture
    int     framesize;          // size of one frame in bytes

    int     num_skins;          // number of textures
    int     num_vertices;            // number of vertices
    int     num_st;             // number of texture coordinates
    int     num_tris;           // number of triangles
    int     num_glcmds;         // number of opengl commands

    int     offset_skins;          // offset to skin names (64 bytes each)
    int     offset_st;             // offset to s-t texture coordinates
    int     offset_tris;           // offset to triangles
    int     offset_frames;         // offset to frame data
    int     offset_glcmds;         // offset to opengl commands
    int     offset_end;            // offset to end of file

} SE_obj_header;


/* Vector */
typedef float SE_vec3[3];



/* Texture name */
typedef struct
{
  char name[64];
} SE_obj_skin;

/* Texture coords */
typedef struct
{
  short s;
  short t;
} SE_obj_texcoord;

/* Triangle info */
typedef struct
{
  unsigned short vertex[3];
  unsigned short st[3];
} SE_obj_triangle;

/* Compressed vertex */
typedef struct
{
	unsigned char v[3];
	unsigned char normalIndex;
} SE_obj_vertex;

/* Model frame */
typedef struct
{
	SE_vec3 scale;
	SE_vec3 translate;
	char name[16];
	SE_obj_vertex *verts;
} SE_obj_frame;

/* GL command packet */
typedef struct
{
  float s;
  float t;
  int index;
} SE_obj_glcmd;

/* OBJ model structure */
typedef struct 
{
  SE_obj_header header;
  SE_obj_skin *skins;
  SE_obj_texcoord *texcoords;
  SE_obj_triangle *triangles;
  SE_obj_frame *frames;

  int *glcmds;

} SE_obj_model;



/*model*/
SE_md2_model *SE_md2_load(char *file);
void SE_md2_unload(SE_md2_model *mdl);


/*animator*/
SE_md2_animator *SE_md2_animator_create(SE_md2_model *mdl);
void SE_md2_animator_render(SE_md2_animator *ani, SE_image *img);
void SE_md2_animator_position(SE_md2_animator *ani,float posx,float posy,float posz);
void SE_md2_animator_zoom(SE_md2_animator *ani,float zoom);
void SE_md2_animator_rotation(SE_md2_animator *ani,float rotationx,float rotationy,float rotationz);
void SE_md2_animator_frames(SE_md2_animator *ani, int framestart, int frameend);

#endif

