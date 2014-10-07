/*

	Convertidor de archivos csv separados por comas o caracteres, o espacios a formato binario
	Para convertir tilemaps hechos con csv, a el formato binario del mappy 

	para compilar desde linea de comando, tipear:
	gcc -o csvconv csvconv.c

	usage:csvconv [WHITE|COMMA] nombre_archivo_a_convertir nro_columnas nro_filas nombre_archivo_nuevo

	ejemplo, con el archivo adjunto "mapa.csv", de 20 columnas y 15 filas:
	./csvconv COMMA mapa.csv 20 15 mapa.map
	

	autor: Jorge Luis Cabral
	mail: jorge@arcadenea.com.ar

	licencia:zlib

*/


#include <stdio.h>
#include <stdlib.h>


#define COMMA 0
#define WHITE 1

void loadmap(int type,char *path_old,int numtilex,int numtiley,char *path_new)
{

	FILE *old;
	FILE *new;

	old = fopen(path_old,"r");
	new = fopen(path_new,"wb");

	int numtiles = numtilex * numtiley;

	char *temparray = (char*)malloc(numtiles * sizeof(char*));

	int i = 0;

	int v = 0;

		
	for(i=0;i < (numtilex * numtiley);i++)
	{
		if(type == COMMA)
		{		

			fscanf(old,"%d%*c",&v);	
		
		}else if(type == WHITE){

			fscanf(old,"%d",&v);	

		}else{
			printf("error,tipo no soportado");
		}
		temparray[i] = v;


	}		
	
	

	fwrite(temparray,sizeof(char),numtiles,new);
	for(i=0;i < (numtilex * numtiley);i++)
	{
		printf("%d",temparray[i]);

	}	

	fclose(old);
	fclose(new);

}





int main(int argc,char* argv[])
{

	int i;
	printf("convertidor de csv a mapa binario\n");

	for(i=1;i < 6;i++)
	{
		if(argv[i] == NULL)
		{	
			printf("usage:csvconv [WHITE|COMMA] nombre_archivo_a_convertir nro_columnas nro_filas nombre_archivo_nuevo\n");
			return 1;
		}
	}	
	loadmap(atoi(argv[1]),argv[2],atoi(argv[3]),atoi(argv[4]),argv[5]);

	return 0;

}
