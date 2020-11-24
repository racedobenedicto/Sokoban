#include <stdio.h>
#include <string.h>
#include "partida.h"
#include "teclas.h" 
#include "casillas.h"
#include "colores.h"
#include "fichero.h"

void inicializa(t_tablero tablero, t_partida *partida) {
  int fil, col, i;

  printf("Inicializando tablero...");

  partida->filas = tablero.n_fil;
  partida->columnas = tablero.n_col;
  partida->puntos=0;
  //leemos el nombre del nivel
  for(col=0; col<MAX_C; col++) {
    partida->nivel[col]=tablero.tablero[tablero.n_fil][col];
  }
  //inicializamos las casillas segun su contenido
  for(fil=0; fil<tablero.n_fil; fil++) {
    for(col=0; col<tablero.n_col; col++) {
      partida->casilla[fil][col].contenido = tablero.tablero[fil][col];
      partida->casilla[fil][col].objetivo=0;
      partida->casilla[fil][col].caja=0;
      partida->casilla[fil][col].tipo = NO_MURO;
      switch(tablero.tablero[fil][col]) {
        case '#':
          partida->casilla[fil][col].tipo=MURO;
          break; 
        case 'X': 
        case '.':
          partida->casilla[fil][col].objetivo=1;
          partida->casilla[fil][col].contenido = OBJETIVO;
          break;
        case '*':
          partida->casilla[fil][col].objetivo=1;
          partida->casilla[fil][col].caja=1;
          break;
        case '@':
          partida->pers.posE.pos_x = col;
          partida->pers.posE.pos_y = fil;
          partida->pers.pasos=0; 
          break;
        case '+': 
          partida->pers.posE.pos_x = col;
          partida->pers.posE.pos_y = fil;
          partida->pers.pasos=0; 
          partida->casilla[fil][col].caja=1;
          break;
        case '0':
        case '$':
          partida->casilla[fil][col].caja=1;
          partida->casilla[fil][col].contenido = CAJA;
        case ' ':
        default:
          break;
      }
    }
    printf("\n");
  }
  return;
}

void juega (int tecla, t_partida *partida, t_tablero tablero) {
  menu();
  mostrar_nombre (partida);
  partida->nObj = contar_objetivos(*partida, &tablero);
  mostrar_objetivos(*partida);
    
  mover(tecla, partida, tablero);
    
  mostrar_puntos(*partida);
  mostrar_pasos(*partida);
  mostrar_empujes(*partida);
  mostrar_tablero(partida);
}

void restart_game(t_partida *partida, t_tablero tablero) {
  //marcador a cero
  partida->puntos = 0;
  partida->nCajas = 0;

  borrar_pantalla();
  inicializa(tablero, partida);
  borrar_pantalla();
  
  mostrar_partida(*partida, &tablero);
}

int puntua(int puntos, t_partida *partida, int f_dest, int c_dest, int f_dest2, int c_dest2) {
  //suma o resta puntos
  if(partida->casilla[f_dest2][c_dest2].objetivo == 1) partida->puntos++;
  if(partida->casilla[f_dest][c_dest].objetivo == 1) partida->puntos--;
}

int contar_objetivos(t_partida partida, t_tablero *tablero) {
  int col, fil;

  partida.nObj = 0;
  
  for(fil = 0; fil < tablero->n_fil; fil++) {
    for(col = 0; col < tablero->n_col; col++) {
      if(partida.casilla[fil][col].objetivo==1) partida.nObj++;
    }   
  }
  return (partida.nObj);
}

int contar_empujes (int empujes, t_partida *partida, int f_dest, int c_dest, int f_dest2, int c_dest2) {
  if(partida->casilla[f_dest2][c_dest2].contenido == CAJA) partida->nCajas++;
}

void menu() {
	printf("\nPulsa flechas. Restart 'r'. Clear 'c'. Quit: 'q'\n"
	"Tambien puedes usar 'o'-'p' (izq-der) y 'a'-'z' (arriba-abajo)\n\n");
}

void mostrar_nombre (t_partida *partida) {
  printf_color(BOLD_MAGENTA);
  printf("\nNivel: %s\n\n", partida->nivel);
  //volvemos al color original
  printf_reset_color();
}

void mostrar_puntos (t_partida partida) {
  printf("Puntos = %d\n", partida.puntos);
}

void mostrar_objetivos(t_partida partida) {
  printf("Objetivos = %d\t", partida.nObj);
}

void mostrar_pasos (t_partida partida) {
  printf("Pasos = %d\t", partida.pers.pasos);
}

void mostrar_empujes(t_partida partida) {
  printf("Numero de empujes = %d\n\n", partida.nCajas);
}

void mostrar_tablero (t_partida *partida) {
  int fil, col, i;

  for(fil=0; fil<partida->filas; fil++) {
    for(col=0; col<partida->columnas; col++) {
      //Cambiar de color el tablero segun el contenido
      if(partida->casilla[fil][col].contenido == PARED) {
        printf_color(BOLD_RED);
      } else if(partida->casilla[fil][col].contenido == CAJA) {
        printf_color(YELLOW);
      } else if(partida->casilla[fil][col].contenido == OBJETIVO) {
        printf_color(BOLD_CYAN);
      } else if(partida->casilla[fil][col].contenido == ENCARGADO) {
        printf_color(BOLD_GREEN);
      } else if(partida->casilla[fil][col].contenido == ENCARGADO_CAJA) {
        printf_color(GREEN);
      } else if(partida->casilla[fil][col].contenido == CAJA_OBJETIVO) {
        printf_color(CYAN);
      }
      //imprime el contenido de cada casilla
      imprime_casilla(&partida->casilla[fil][col]);
      //volvemos al color original
      printf_reset_color();
    }
    printf("\n");
  } 
  printf("\n\n");
}

void mostrar_partida (t_partida partida, t_tablero *tablero) { 
  borrar_pantalla();
  mostrar_nombre (&partida);
  partida.nObj = contar_objetivos(partida, tablero);
  mostrar_objetivos(partida);
  mostrar_puntos(partida);
  mostrar_pasos(partida);
  mostrar_empujes(partida);
  mostrar_tablero(&partida);
  menu();
}

int leer_tablero(FILE *file, char nivel[],  t_tablero *tablero){
  char linea[MAX_C] = ".", nivel2[100];
  int i=0,pos=-1, fin=0, j, col;

  while(!es_fin_de_fichero(file) && fin==0){
    leer_linea_fichero(file, linea);
    //limpiamos la fila del tablero en el que se va a guardar la información
    for(j=0;j<MAX_C;j++) {
      tablero->tablero[i][j]=' ';
    }
    // miramos si es final de tablero
    if(linea[0]==';'){
      fin=1;
      //guardamos el nivel
      for(j=2;j<strlen(linea);j++) {
        nivel2[j-2] = linea[j];
      }
      strcpy(tablero->tablero[i],nivel2);
      //comparamos si es el nivel buscado y indicamos la posicion en el array
      if(strcmp(nivel2,nivel)==0) pos=1;
      
      tablero->n_fil = i;
      col=0;
      for(j=0;j<i;j++) {
        if(col<strlen(tablero->tablero[j])) col=strlen(tablero->tablero[j]); 
      }
      tablero->n_col = col;
      //limpiamos variable nivel2
      for(j=1;j<=strlen(nivel2);j++){
        nivel2[j]='\0';
      }
      i=0;
    } else {
      strcpy(tablero->tablero[i],linea);
      for(j=1;j<=strlen(linea);j++) {
        linea[j]='\0';
      }
      i++;
    }
  }
  return pos;
}
