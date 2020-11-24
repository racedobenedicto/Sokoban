#ifndef _CASILLAS_H_
#define _CASILLAS_H_

#include "partida.h"

void imprime_casilla (t_casilla *casilla); //imprime cada casilla con su emoji/caracter

void mover (int direccion, t_partida *partida, t_tablero tablero); //desplaza la caja una posicion en la direccion indicada si la caja se puede mover en esa direccion o desplaza al encargado una posicion en la direccion indicada.
  
int puede_mover (t_partida *partida, int f_dest, int c_dest, int f_dest2, int c_dest2); //comprueba si la caja se puede mover en la direccion indicada, es decir, verifica si la posicion que debe ocupar esta libre (0/1) o comprueba si el encargado se puede mover en la direccion indicada, verifica si la posicion que debe ocupar esta libre o si esta ocupada por una caja que se pueda mover (0/1).

#endif


