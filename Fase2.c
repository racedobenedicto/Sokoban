#include <stdio.h>
#include <string.h>
#include <time.h>
#include "partida.h"
#include "teclas.h" 
#include "casillas.h"
#include "fichero.h"

int main() {
  int opcion, direccion, i, j, duracion, pos=0, nivel_max, inicio=0, n=0, col;
  char fichero[20], nivel[100];
  t_tablero tablero[100];
  FILE *file;
  t_partida partida;
  time_t t_inicial, t_final;

  partida.puntos = 0;
  partida.nCajas = 0;

  do{
    printf("Menu: Con que fichero de niveles quieres jugar?\n\n0) Yo introducire el nombre del fichero\n1) Original.txt  The 50 original levels from Sokoban plus the 40 from Extra\n2) Easy.txt      Colection for testing purposes\n3) 100Boxes.txt  This colection includes 10 small levels of 10 pacages each\n4) 696.txt       696 collection\n");
    printf("Que opcion eliges? [0 - 4]: ");
    scanf("%d", &opcion);
  } while(opcion<0 || opcion>4);
  
  strcpy(fichero, "-1");

  if(opcion == 0) {
    do {
      printf("Introduce el nombre del fichero: ");
      scanf("%[^\n]", fichero);
      if(strcmp(fichero,"Original.txt")==0) opcion=1;
      if(strcmp(fichero,"Easy.txt")==0) opcion=2;
      if(strcmp(fichero,"100Boxes.txt")==0) opcion=3;
      if(strcmp(fichero,"696.txt")==0) opcion=4;
    } while(opcion==0); 
  }

  switch (opcion) {
    case 1:
      printf("Por que nivel empiezas? [1 - 90]: ");
      scanf("%s", &nivel);
      strcpy(fichero, "Original.txt");
      nivel_max=90;
      break;
    case 2:
      printf("Por que nivel empiezas? [1 - 2]: ");
      scanf("%d", &nivel);
      strcpy(fichero, "Easy.txt");
      nivel_max=2;
      break;
    case 3:
      printf("Por que nivel empiezas? [1 - 10]: ");
      scanf("%d", &nivel);
      strcpy(fichero, "100Boxes.txt");
      nivel_max=10;
      break;
    case 4:
      printf("Por que nivel empiezas? [1 - 694]: ");
      scanf("%d", &nivel);
      strcpy(fichero, "696.txt");
      nivel_max=694;
      break;
    default:
      printf("Opción incorrecta, vuelve a empezar");
      break;      
  }
  
  if(strcmp(fichero,"-1")!=0){
    file = abrir_fichero(fichero);
    if(file == NULL) {
      printf("Error abriendo fichero");
    } else {
      i=0;
      pos=-1;
      while(!es_fin_de_fichero(file)) {
        //leemos tablero a tablero
        pos = leer_tablero(file, nivel, &tablero[i]);
        if(pos==1) {
          inicio = i;
          pos = 0;
        }
        i++;
      }
      //empezamos partida
      do {
        inicializa(tablero[inicio], &partida);
        mostrar_partida(partida, &tablero[inicio]);
        time(&t_inicial); //Empieza el juego 
        do {
          direccion = lee_tecla();
          borrar_pantalla();
          juega(direccion, &partida, tablero[inicio]);
          if(direccion == RESTART || direccion == CLEAR) {
            restart_game(&partida, tablero[inicio]);
          }
          if(partida.puntos == partida.nObj) {
            printf("NIVEL SUPERADO!!!\n");
            direccion = OTHER;
            inicio++;
          }
          if(direccion == CANCEL) printf("Adios!!!\n");
        } while(direccion != CANCEL && direccion != OTHER);

        time(&t_final); //Acaba el juego
        duracion = t_final - t_inicial;
        printf("\nRUN FINISHED; real time: %ds\n\n", duracion);  
        sleep(2);  

      } while(inicio<nivel_max && direccion != CANCEL && direccion == OTHER);
      
      cerrar_fichero(file);
    }
  }
}
