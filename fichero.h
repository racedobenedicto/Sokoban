#ifndef FICHERO_H
#define FICHERO_H

#include <stdio.h>

#define LONG_LINEA_FICHERO	70
#define	LINEA_NO_VACIA		1
#define LINEA_VACIA		0


int es_nombre_nivel(char linea[LONG_LINEA_FICHERO]);

int tipo_linea (char linea[LONG_LINEA_FICHERO]);

FILE *abrir_fichero(char nombre_fichero[]);

int leer_linea_fichero(FILE * fichero, char linea[LONG_LINEA_FICHERO]);

int es_fin_de_fichero(FILE * fichero);

void cerrar_fichero(FILE * fichero);

#endif // FICHERO_H

