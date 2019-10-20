#include <stdio.h>
#include <stdlib.h>

/*DIFFICULTY CLASSES*/

#define DANCESINGLE 0
#define DANCEDOUBLE 1
#define DANCECOUPLE 2
#define DANCESOLO 3
#define PUMPSINGLE 4
#define PUMPDOUBLE 5
#define PUMPCOUPLE 6

/*DIFFICULTY METER VALUES*/

#define BEGGINER 0
#define EASY 1
#define MEDIUM 2
#define HARD 3
#define CHALLENGE 4



/*dance-single = 4 notes/row (Left,Down,Up,Right)
dance-double = 8 notes/row
dance-couple = 8 notes/row
dance-solo = 6 notes/row
pump-single = 5 notes/row
pump-double = 10 notes/row
pump-couple = 10 notes/row
ez2-single = 5 notes/row
ez2-double = 10 notes/row
ez2-real = 7 notes/row
para-single = 5 notes/row*/



typedef struct
{

	float beat;
	float bpm;

}SMbpm;

typedef struct
{

	float beat;
	float stop;

}SMstop;

typedef struct
{

}SMplayer;


typedef struct
{

	int notestype;/* tipo de notas.Ej:DANCESINGLE */
	char description[200];/* descripcion */
	int diffclass;/* clase de dificultad.Ej:CHALLENGE */
	int diffmeter;/* medidor de dificultad.Ej:8 */
	int numnoterow;/*numero de notas por fila (ej: pump single -> 5 notas por fila)*/

}SMnotedata;


typedef struct
{

	char smfilepath[50];
	char title[50];
	char subtitle[50];
	char artist[50];
	char bannerpath[50];
	char bgpath[50];
	char musicpath[50];

	float offset;
	
	int numnoteset;/*numero de set de notes*/

	SMnotedata *notesetarray;

}SMdata; 



void smdata_bpm_add(SMdata *smd,float beat,float bpm)
{

	if(smd->numbpms == 0)
	{
		smd->numbpms++;
		smd->bpmarray = (SMbpm*)malloc(sizeof(SMbpm));
		smd->bpmarray->beat = beat;
		smd->bpmarray->bpm = bpm; 
		
	}else{

		smd->numbpms++;
		smd->bpmarray = (SMbpm*)realloc(smd->bpmarray,(smd->numbpms) * (sizeof(SMbpm)));
		smd->bpmarray[smd->numbpms - 1].beat = beat;
		smd->bpmarray[smd->numbpms - 1].bpm = bpm; 

	}

}



void smdata_stop_add(SMdata *smd,float beat,float stop)
{

	if(smd->numstops == 0)
	{
		smd->numstops++;
		smd->stoparray = (SMstop*)malloc(sizeof(SMstop));
		smd->stoparray->beat = beat;
		smd->stoparray->stop = stop; 
		
	}else{

		smd->numstops++;
		smd->stoparray = (SMstop*)realloc(smd->stoparray,(smd->numstops) * (sizeof(SMstop)));
		smd->stoparray[smd->numstops - 1].beat = beat;
		smd->stoparray[smd->numstops - 1].stop = stop; 

	}

}

void smdata_smnote_add(SMdata *smd,int notestype,char *description,int diffclass,int diffmeter,int numnoterow)
{

	if(smd->numnoteset == 0)
	{
		smd->numnoteset++;
		smd->notesetarray = (SMnotes*)malloc(sizeof(SMnotes));
		smd->notesetarray->notestype = notestype;
		strcpy(smd->notesetarray->description,description);
		smd->notesetarray->diffclass = diffclass;
		smd->notesetarray->diffmeter = diffmeter;
		smd->notesetarray->numnoterow = numnoterow;
		smd->notesetarray->numnotedata = 0;
		smd->notesetarray->notedata = NULL;
		smd->notesetarray->numres = 0;
		smd->notesetarray->resolution = NULL;
		
	}else{

		smd->numnoteset++;
		smd->notesetarray = (SMnotes*)realloc(smd->notesetarray,(smd->numnoteset) * (sizeof(SMnotes)));
		smd->notesetarray[(smd->numnoteset) - 1].notestype = notestype;
		strcpy(smd->notesetarray[(smd->numnoteset) - 1].description,description);
		smd->notesetarray[(smd->numnoteset) - 1].diffclass = diffclass;
		smd->notesetarray[(smd->numnoteset) - 1].diffmeter = diffmeter;
		smd->notesetarray[(smd->numnoteset) - 1].numnoterow = numnoterow;
		smd->notesetarray[(smd->numnoteset) - 1].notedata = NULL;
		smd->notesetarray[(smd->numnoteset) - 1].numnotedata = 0;
		smd->notesetarray[(smd->numnoteset) - 1].numres = 0;
		smd->notesetarray[(smd->numnoteset) - 1].resolution = NULL;

	}

}

void smdata_smnote_notes_add(SMdata *smd,int numnoteset,char *data)
{

	int numnoterow = smd->notesetarray[numnoteset].numnoterow;
	int numnotedata = 0;

	if(smd->notesetarray[numnoteset].numnotedata == 0)
	{
		smd->notesetarray[numnoteset].numnotedata++;
		smd->notesetarray[numnoteset].notedata = (char**)malloc(sizeof(char*));
		*(smd->notesetarray[numnoteset].notedata) = (char*)malloc(numnoterow * sizeof(char));
		
		strcpy(*(smd->notesetarray[numnoteset].notedata),data);

	}else{

		smd->notesetarray[numnoteset].numnotedata++;
		numnotedata = smd->notesetarray[numnoteset].numnotedata;
		smd->notesetarray[numnoteset].notedata = (char**)realloc(smd->notesetarray[numnoteset].notedata,(numnotedata) * sizeof(char*));
		smd->notesetarray[numnoteset].notedata[numnotedata - 1] = (char*)malloc(numnoterow * sizeof(char));
		
		strcpy(smd->notesetarray[numnoteset].notedata[numnotedata - 1],data);

	}
	

}

void smdata_smnote_resolution_add(SMdata *smd,int numnoteset,int resolution)
{

	int numres = 0;

	if((smd->notesetarray[numnoteset].numres) == 0)
	{

		smd->notesetarray[numnoteset].numres++;	
		smd->notesetarray[numnoteset].resolution = (int*)malloc(sizeof(int));
		*(smd->notesetarray[numnoteset].resolution) = resolution;

	}else{

		smd->notesetarray[numnoteset].numres++;	
		numres = smd->notesetarray[numnoteset].numres;
		smd->notesetarray[numnoteset].resolution = (int*)realloc(smd->notesetarray[numnoteset].resolution,(numres) * sizeof(int));
		smd->notesetarray[numnoteset].resolution[numres - 1] = resolution;

	}



}

SMdata *smdata_readdata(char *pathfile)
{

	FILE *smfile;
	smfile = fopen(pathfile,"r");

	SMdata *tsm;
	tsm = (SMdata*)malloc(sizeof(SMdata));

	strcpy(tsm->smfilepath,pathfile); 

	char line[1000];
	char tag[20];
	char value[800];



	while(!feof(smfile))
	{

					
		fgets(line,1000,smfile);

		sscanf(line,"%[^ :]%*[ :]%[^:;]",tag,value);

		if(strcmp(tag,"#TITLE") == 0)strcpy(tsm->title,value);
		if(strcmp(tag,"#SUBTITLE") == 0)strcpy(tsm->subtitle,value);
		if(strcmp(tag,"#ARTIST") == 0)strcpy(tsm->artist,value);
		if(strcmp(tag,"#BANNER") == 0)strcpy(tsm->bannerpath,value);
		if(strcmp(tag,"#BACKGROUND") == 0)strcpy(tsm->bgpath,value);
		if(strcmp(tag,"#MUSIC") == 0)strcpy(tsm->musicpath,value);

		if(strcmp(tag,"#OFFSET") == 0)
		{	
			tsm->offset = (float)atof(value);
		}
		
		if(strcmp(tag,"#BPMS") == 0)
		{
			char *token;			
			char beat[20];
			char bpm[20];			
			token = strtok(value,",");
			
			while(token != NULL)
			{
				
				sscanf(token,"%[^=]%*[=]%[^=]",beat,bpm);

				smdata_bpm_add(tsm,atof(beat),atof(bpm));	

				token = strtok(NULL,",");

				memset(beat,0,20);
				memset(bpm,0,20);

			
			}

		}

		if(strcmp(tag,"#STOPS") == 0)
		{

			char *token;			
			char beat[20];
			char stop[20];			
			token = strtok(value,",");
			
			while(token != NULL)
			{
				
				sscanf(token,"%[^=]%*[=]%[^=]",beat,stop);

				smdata_stop_add(tsm,atof(beat),atof(stop));	

				token = strtok(NULL,",");

				memset(beat,0,20);
				memset(stop,0,20);
			
			}


		}

		if(strcmp(tag,"#NOTES") == 0)
		{

			char templine[100];
			char tempvalue[100];

			int contline = 0;

			int notestype = 0;
			char description[200];
			int diffclass = 0;
			int diffmeter = 0;
			int numnoterow = 0;		

			char c;


			fgets(templine,100,smfile);

			c = templine[0];
		
			while(c != ';')
			{
				
				switch(contline)
				{
					case 0:
						sscanf(templine,"%*[ ]%[^:]",tempvalue);
						if(strcmp(tempvalue,"dance-single") == 0)
						{							
							notestype = DANCESINGLE;
							numnoterow = 4;
						}
						if(strcmp(tempvalue,"dance-double") == 0)
						{							
							notestype = DANCEDOUBLE;
							numnoterow = 8;
						}
						if(strcmp(tempvalue,"dance-couple") == 0)
						{							
							notestype = DANCECOUPLE;
							numnoterow = 8;
						}
						if(strcmp(tempvalue,"dance-solo") == 0)
						{							
							notestype = DANCESOLO;
							numnoterow = 6;
						}
						if(strcmp(tempvalue,"pump-single") == 0)
						{							
							notestype = PUMPSINGLE;
							numnoterow = 5;
						}
						if(strcmp(tempvalue,"pump-double") == 0)
						{							
							notestype = PUMPDOUBLE;
							numnoterow = 10;
						}
						if(strcmp(tempvalue,"pump-couple") == 0)
						{							
							notestype = PUMPCOUPLE;
							numnoterow = 10;
						}
						break;
					case 1:
						sscanf(templine,"%*[ ]%[^:]",tempvalue);
						strcpy(description,tempvalue);
						break;
					case 2:
						sscanf(templine,"%*[ ]%[^:]",tempvalue);
						if(strcmp(tempvalue,"Begginer") == 0)diffclass = BEGGINER;
						if(strcmp(tempvalue,"Easy") == 0)diffclass = EASY;
						if(strcmp(tempvalue,"Medium") == 0)diffclass = MEDIUM;
						if(strcmp(tempvalue,"Hard") == 0)diffclass = HARD;
						if(strcmp(tempvalue,"Challenge") == 0)diffclass = CHALLENGE;
						break;	
					case 3:
						sscanf(templine,"%*[ ]%[^:]",tempvalue);
						diffmeter = atoi(tempvalue);
						break;
					
					default:						
						break;	

				}

				
				
		
				memset(templine,0,100);
				memset(tempvalue,0,100);


				fgets(templine,100,smfile);

				c = templine[0];

				contline++;


			}

			smdata_smnote_add(tsm,notestype,description,diffclass,diffmeter,numnoterow);


		}


		memset(line,0,1000);
		memset(tag,0,20);
		memset(value,0,800);
		
	}
	

	fclose(smfile);

	return tsm;
		
}

void smdata_readnotes(SMdata *smd)
{


	FILE *smfile;
	smfile = fopen(smd->smfilepath,"r");

	char line[1000];
	char tag[20];
	char value[800];

	int numnoteset = 0;

	int numnoterow = 0;

	char *note = NULL;

	int contres = 0;/*contador de resolucion de notas*/



	while(!feof(smfile))
	{

		fgets(line,1000,smfile);

		sscanf(line,"%[^ :]%*[ :]%[^:;]",tag,value);


		if(strcmp(tag,"#NOTES") == 0)
		{

			char templine[100];
			char tempvalue[100];

			int contline = 0;

			char c1 = 0;

			char c2 = 0;
			
			char c3 = 0;	

			char temp[2];

			fgets(templine,100,smfile);

			c1 = templine[0];

			numnoterow = smd->notesetarray[numnoteset].numnoterow;

			note = (char*)malloc(numnoterow * sizeof(char));
		
			while(c1 != ';')
			{
								
				if(contline > 4)
				{

					c2 = templine[0];
					sscanf(templine,"%s",temp); 
					c3 = temp[0];
				
					if(c2 == ',')
					{
						c2 = 0;
						smdata_smnote_resolution_add(smd,numnoteset,contres);
						contres = 0;						
				
					}else if(c3 != '/'){	

						strcpy(note,templine);
						smdata_smnote_notes_add(smd,numnoteset,note);
						contres++;

					}//if					
								
				}//if
		
				
		
				memset(templine,0,100);
				memset(tempvalue,0,100);


				fgets(templine,100,smfile);

				c1 = templine[0];

				contline++;


			}//while
		
			numnoteset++;		


		}//if


	}//while


}

void printvalues(SMdata *smd)
{

	printf("TITLE: %s \n",smd->smfilepath);
	printf("TITLE: %s \n",smd->title);
	printf("SUBTITLE: %s \n",smd->subtitle);
	printf("ARTIST: %s \n",smd->artist);
	printf("BANNER: %s \n",smd->bannerpath);
	printf("BACKGROUND: %s \n",smd->bgpath);
	printf("MUSIC: %s \n",smd->musicpath);
	printf("OFFSET: %f \n",smd->offset);

	int i,j;
	
	printf("beat	bpm \n");

	for(i=0;i<(smd->numbpms);i++)
	{
		printf("%f %f \n",smd->bpmarray[i].beat,smd->bpmarray[i].bpm);
	}	

	printf("beat	stop \n");

	for(i=0;i<(smd->numstops);i++)
	{
		printf("%f %f \n",smd->stoparray[i].beat,smd->stoparray[i].stop);
	}	

	for(i=0;i<(smd->numnoteset);i++)
	{
		
		printf("notestype: %d\n",smd->notesetarray[i].notestype);
		printf("description: %s\n",smd->notesetarray[i].description);
		printf("diffclass: %d\n",smd->notesetarray[i].diffclass);
		printf("diffmeter: %d\n",smd->notesetarray[i].diffmeter);
		printf("numnoterow: %d\n\n",smd->notesetarray[i].numnoterow);
		
		for(j=0;j< (smd->notesetarray[i].numnotedata);j++)
		{
	
			printf("%s\n",smd->notesetarray[i].notedata[j]);

		}



	}


}



int main(int argc,char* argv[])
{



	SMdata *newsm;

	newsm = smdata_readdata("prueba2.sm");

	smdata_readnotes(newsm);	

	printvalues(newsm);

	return 0;


}
