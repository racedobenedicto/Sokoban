#include <stdio.h>
#include <time.h>
#include "partida.h"
#include "teclas.h" 
#include "casillas.h"
#include "colores.h"

int main() {
  t_tablero tablero = {6, 6, {"######",
                              "#    #",
                              "#@ 0 #",
                              "#    #",
                              "#   X#",
                              "######",
                              "Ejemplo",
                              ""}};
  t_partida partida;
  time_t t_inicial, t_final;
  int direccion, duracion;

  partida.puntos = 0;
  partida.nCajas = 0;
  
  inicializa(tablero, &partida);
  mostrar_partida(partida, &tablero);
  time(&t_inicial); //Empieza el juego 

  do{
    direccion = lee_tecla();
    borrar_pantalla();
    juega(direccion, &partida, tablero);
    if(direccion == RESTART || direccion == CLEAR) {
      restart_game(&partida, tablero);
    }
    if(partida.puntos == partida.nObj) {
      printf("NIVEL SUPERADO!!!\n");
      direccion = CANCEL;
    }
    if(direccion == CANCEL) printf("Adios!!!\n");
  } while(direccion != CANCEL);
  
  time(&t_final); //Acaba el juego
  duracion = tf - ti;
  printf("\nRUN FINISHED; real time: %ds\n\n", duracion);
}
