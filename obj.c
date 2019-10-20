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

#include "super.h"
#include "anorms.h"


SE_obj_model *SE_obj_load(char *file)
{
	FILE *fp;
	int i;
	SE_obj_model *model;
	SE_image *img;
	
	printf("Loading md2 model from file: %s\n",file);
	

	fp = fopen (file, "rb");
	if (!fp)
	{
		printf ("Error: couldn't open \"%s\"!\n", file);
		return 0;
	}

	model=(SE_md2_model *)malloc(sizeof(SE_md2_model));

	/* Read header */
	fread (&model->header, 1, sizeof (SE_md2_header), fp);

	printf("num of texcoords %d\n",model->header.num_st);
	printf("num of skins %d\n",model->header.num_skins);
	printf("num of triangles %d\n",model->header.num_tris);

	if ((model->header.ident != 844121161) || (model->header.version != 8))
	{
		/* Error! */
		printf("Error: bad version or identifier\n");
		fclose (fp);
		return 0;
	}

	/* Memory allocations */
	model->skins = (SE_md2_skin *)malloc(sizeof(SE_md2_skin) * model->header.num_skins);
	model->texcoords = (SE_md2_texcoord *)malloc(sizeof(SE_md2_texcoord) * model->header.num_st);
	model->triangles = (SE_md2_triangle *)malloc (sizeof(SE_md2_triangle) * model->header.num_tris);
	model->frames = (SE_md2_frame *)malloc (sizeof(SE_md2_frame) * model->header.num_frames);
	model->glcmds = (int *)malloc (sizeof(int) * model->header.num_glcmds);

	/* Read model data */
	fseek (fp, model->header.offset_skins, SEEK_SET);
	fread (model->skins, sizeof (SE_md2_skin), model->header.num_skins, fp);

	fseek (fp, model->header.offset_st, SEEK_SET);
	fread (model->texcoords, sizeof (SE_md2_texcoord),model->header.num_st, fp);

	fseek (fp, model->header.offset_tris, SEEK_SET);
	fread (model->triangles, sizeof (SE_md2_triangle),model->header.num_tris, fp);

	fseek (fp, model->header.offset_glcmds, SEEK_SET);
	fread (model->glcmds, sizeof (int), model->header.num_glcmds, fp);

	/* Read frames */
	fseek (fp, model->header.offset_frames, SEEK_SET);
	for (i = 0; i < model->header.num_frames; ++i)
	{
		/* Memory allocation for vertices of this frame */
		model->frames[i].verts = (SE_md2_vertex *)malloc (sizeof(SE_md2_vertex)*model->header.num_vertices);

		/* Read frame data */
		fread (model->frames[i].scale, sizeof(SE_vec3), 1, fp);
		fread (model->frames[i].translate, sizeof(SE_vec3), 1, fp);
		fread (model->frames[i].name, sizeof(char), 16, fp);
		fread (model->frames[i].verts, sizeof(SE_md2_vertex),model->header.num_vertices, fp);
	}

	fclose (fp);
	return model;
}

/**
 * Free resources allocated for the model.
 */


void SE_md2_unload(SE_md2_model *mdl)
{
  int i;

  if (mdl->skins)
    {
      free (mdl->skins);
      mdl->skins = NULL;
    }

  if (mdl->texcoords)
    {
      free (mdl->texcoords);
      mdl->texcoords = NULL;
    }

  if (mdl->triangles)
    {
      free (mdl->triangles);
      mdl->triangles = NULL;
    }

  if (mdl->glcmds)
    {
      free (mdl->glcmds);
      mdl->glcmds = NULL;
    }

  if (mdl->frames)
    {
      for (i = 0; i < mdl->header.num_frames; ++i)
	{
	  free (mdl->frames[i].verts);
	  mdl->frames[i].verts = NULL;
	}

      free (mdl->frames);
      mdl->frames = NULL;
    }
}

/**
 * Render the model at frame n.
 */

void SE_md2_animator_render(SE_md2_animator *ani, SE_image *img)
{
	int i, j;
	float s[3], t[3];
	SE_vec3 v;
	SE_md2_frame *pframe;
	SE_md2_vertex *pvert;

	SE_vector normal[3];
	SE_vector vertex[3];

	ani->currentframe++;

	if(ani->currentframe>=ani->frameend) ani->currentframe=ani->framestart;
	
	/* Check if n is in a valid range */
	//if ((n < 0) || (n > ani->mdl->header.num_frames - 1))
	//return;


//	pvert=malloc(sizeof(pvert));

	for (i = 0; i < ani->mdl->header.num_tris; ++i)
	{
		/* Draw each vertex */
		for (j = 0; j < 3; ++j)
		{
			pframe = &ani->mdl->frames[ani->currentframe];
			pvert = &pframe->verts[ani->mdl->triangles[i].vertex[j]];

			/* Compute texture coordinates */
			s[j] = (float)ani->mdl->texcoords[ani->mdl->triangles[i].st[j]].s / ani->mdl->header.skinwidth;
			t[j] = (float)ani->mdl->texcoords[ani->mdl->triangles[i].st[j]].t / ani->mdl->header.skinheight;
//			s[j] = (float)mdl->texcoords[mdl->triangles[i].st[j]].s / mdl->img->w;
//			t[j] = (float)mdl->texcoords[mdl->triangles[i].st[j]].t / mdl->img->h;

			/* Normal vector */
			normal[j].x=*anorms_table[pvert->normalIndex];
			normal[j].y=*anorms_table[pvert->normalIndex];
			normal[j].z=*anorms_table[pvert->normalIndex];

			/* Calculate vertex real position - AGREGADO ZOOM */
			vertex[j].x = (((pframe->scale[0] * pvert->v[0]) + pframe->translate[0])) * ani->zoom;
			vertex[j].y = (((pframe->scale[1] * pvert->v[1]) + pframe->translate[1])) * ani->zoom;
			vertex[j].z = (((pframe->scale[2] * pvert->v[2]) + pframe->translate[2])) * ani->zoom;


		}

			SE_image_triangle_draw(img,vertex,s,t, ani->x, ani->y, ani->z,ani->rotx,ani->roty, ani->rotz);

	}

}


SE_md2_animator *SE_md2_animator_create(SE_md2_model *mdl)
{
SE_md2_animator *ani;

ani=(SE_md2_animator *)malloc(sizeof(SE_md2_animator));

ani->mdl=mdl;

ani->x=0.0f;
ani->y=0.0f;
ani->z=0.0f;
ani->delayperc=0.0f;
ani->zoom=0.0f;
ani->rotx=0.0f;
ani->roty=0.0f;
ani->rotz=0.0f;
ani->r=0.0f;
ani->g=0.0f;
ani->b=0.0f;
ani->alpha=0.0f;

ani->status=0.0f;
ani->counter=0.0f;
ani->currentframe=0.0f;
ani->framestart=0;
ani->frameend=mdl->header.num_frames;

return ani;
}


/*setea posicion en los 3 ejes*/
void SE_md2_animator_position(SE_md2_animator *ani,float posx,float posy,float posz)
{
ani->x=posx;
ani->y=posy;
ani->z=posz;
}


void SE_md2_animator_zoom(SE_md2_animator *ani,float zoom)
{
ani->zoom=zoom;
}

/*setea rotaciones*/
void SE_md2_animator_rotation(SE_md2_animator *ani,float rotationx,float rotationy,float rotationz)
{
ani->rotx=rotationx;
ani->roty=rotationy;
ani->rotz=rotationz;
}

void SE_md2_animator_frames(SE_md2_animator *ani, int framestart, int frameend)
{
ani->framestart=framestart;
ani->frameend=frameend;
}
