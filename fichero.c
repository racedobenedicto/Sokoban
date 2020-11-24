#include <stdio.h>
#include <string.h>
#include "fichero.h"

int es_nombre_nivel(char linea[LONG_LINEA_FICHERO]) {
  return(linea[0]==';');
}

int tipo_linea (char linea[LONG_LINEA_FICHERO]) {
	if (linea[0]!='\0') {
    return LINEA_NO_VACIA;
  } else {
    return LINEA_VACIA;
  } 
}

FILE *abrir_fichero(char nombre_fichero[]) {    
	return fopen(nombre_fichero, "r");
}

int leer_linea_fichero(FILE *fichero, char linea[LONG_LINEA_FICHERO]) {
	int  i=0;
        
  do {
    fscanf(fichero, "%c", &linea[i]);
    i++;
  } while (linea[i-1]!='\n' && !es_fin_de_fichero(fichero));
  linea[i-1]='\0';
	return tipo_linea(linea);
}

int es_fin_de_fichero(FILE *fichero) {
	return feof(fichero);
}

void cerrar_fichero(FILE *fichero) {
	fclose(fichero);
}
