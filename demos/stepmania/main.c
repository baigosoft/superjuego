#include <stdio.h>
#include <stdlib.h>
#include "string.h"

/*todo se mide en milisegundos (creo que va a funcionar)*/

typedef struct
{

	float beat;
	float bpm;

}SMbpm;

typedef struct
{

	float beat;
	int stop;

}SMstop;

typedef struct
{

	char notestype[20];
	char description[30];
	char diffclass[20];
	int diffmeter:
	int *notedata[10];

}SMnotes;


typedef struct
{

	char title[50];
	char subtitle[50];
	char artist[50];
	char bannerpath[50];
	char bgpath[50];
	char musicpath[50];

	int offset;
	int samplestart;
	int samplelenght;
	
	int numbpms;

	SMbpm **bpms;

	SMstop **stops;

	SMnotes **notes;

}SMdata; 

SMdata *readsm(char *pathfile)
{

	SMdata *tsm;
	tsm = (SMdata*)malloc(sizeof(SMdata));

	FILE *smfile;
	smfile = open(pathfile,"r");

	char line[30];
	char tag[20];
	char value[10];

	while(!feof(smfile))
	{
		fgets(line,100,smfile);
		sscanf(line,"%[^ :]%*[ :]%[^:;]",tag,value);

		if(strcmp(tag,"#TITLE") == 0)tsm->title;

	}
	
	fclose(smfile);

	return tsm;
		
}



int main(int argc,char* args[])
{






}
