#include <stdio.h>
#include "teclas.h"
#include "casillas.h"
#include "partida.h"

void imprime_casilla (t_casilla *casilla) {
  printf("%c", casilla->contenido);
}

void mover(int direccion, t_partida *partida, t_tablero tablero) {
  int mov = 0;
  int f_dest = partida->pers.posE.pos_y;
  int c_dest = partida->pers.posE.pos_x;
  int f_dest2 = f_dest;
  int c_dest2 = c_dest;

  switch(direccion) {
    case UP:
      f_dest--;
      f_dest2--;
      f_dest2--;
      break;
    case DOWN:
      f_dest++;
      f_dest2++;
      f_dest2++;      
      break;
    case LEFT:
      c_dest--;
      c_dest2--;
      c_dest2--;
      break;
    case RIGHT:
      c_dest++;
      c_dest2++;
      c_dest2++;
      break;
    case CANCEL: 
      break;
    default:
      return;                  
  }
  
  mov = puede_mover(partida, f_dest, c_dest, f_dest2, c_dest2);
  if (mov == 1) {
    //muevo encargado
    if(partida->casilla[partida->pers.posE.pos_y][partida->pers.posE.pos_x].objetivo==1) {
      partida->casilla[partida->pers.posE.pos_y][partida->pers.posE.pos_x].contenido = OBJETIVO;
    } else if(partida->casilla[partida->pers.posE.pos_y][partida->pers.posE.pos_x].caja==1) {       
      partida->casilla[partida->pers.posE.pos_y][partida->pers.posE.pos_x].contenido = CAJA;
      partida->casilla[partida->pers.posE.pos_y][partida->pers.posE.pos_x].caja=1;
    } else {
      partida->casilla[partida->pers.posE.pos_y][partida->pers.posE.pos_x].contenido = VACIO;
    }

    partida->pers.posE.pos_y = f_dest;
    partida->pers.posE.pos_x = c_dest;
    partida->casilla[partida->pers.posE.pos_y][partida->pers.posE.pos_x].contenido = ENCARGADO;
    partida->pers.pasos++; //contar pasos

  } else if(mov == 2) {
    //muevo la caja
    if(partida->casilla[f_dest][c_dest].objetivo==1){
      partida->casilla[f_dest][c_dest].contenido = OBJETIVO;
      partida->casilla[f_dest][c_dest].caja=0;
    } else {
      partida->casilla[f_dest][c_dest].contenido = VACIO;
      partida->casilla[f_dest][c_dest].caja=0;
    }
    
    if(partida->casilla[f_dest2][c_dest2].objetivo == 1 && partida->casilla[f_dest][c_dest].caja==0) {
      partida->casilla[f_dest2][c_dest2].contenido = CAJA_OBJETIVO;
      partida->casilla[f_dest2][c_dest2].caja=1;
    } else {
      partida->casilla[f_dest2][c_dest2].contenido = CAJA;
      partida->casilla[f_dest2][c_dest2].caja=1;
    }

    //muevo el encargado
    if(partida->casilla[partida->pers.posE.pos_y][partida->pers.posE.pos_x].objetivo==1) {
      partida->casilla[partida->pers.posE.pos_y][partida->pers.posE.pos_x].contenido = OBJETIVO;
    } else if(partida->casilla[partida->pers.posE.pos_y][partida->pers.posE.pos_x].caja==1) {
      partida->casilla[partida->pers.posE.pos_y][partida->pers.posE.pos_x].contenido = CAJA;
    } else {
      partida->casilla[partida->pers.posE.pos_y][partida->pers.posE.pos_x].contenido = VACIO;
    }

    partida->pers.posE.pos_y = f_dest;
    partida->pers.posE.pos_x = c_dest;
    partida->casilla[partida->pers.posE.pos_y][partida->pers.posE.pos_x].contenido = ENCARGADO;
    partida->pers.pasos++; //contar pasos

    puntua(partida->puntos, partida, f_dest, c_dest, f_dest2, c_dest2);
    contar_empujes(partida->nCajas, partida, f_dest, c_dest, f_dest2, c_dest2);
  }
  return;
}

int puede_mover (t_partida *partida, int f_dest, int c_dest, int f_dest2, int c_dest2) {
  int mov = 0;
  
  if(partida->casilla[f_dest][c_dest].contenido == MURO) {
    mov = 0;
  } else if (partida->casilla[f_dest][c_dest].contenido == VACIO) {
    mov = 1;
  } else if(partida->casilla[f_dest][c_dest].caja == 1 ) {
    if(partida->casilla[f_dest2][c_dest2].contenido == MURO || partida->casilla[f_dest2][c_dest2].caja == 1) {
      mov = 0;
    } else if (partida->casilla[f_dest2][c_dest2].contenido == VACIO) {
      mov = 2;
    } else if(partida->casilla[f_dest2][c_dest2].objetivo == 1) {
      mov = 2;
    }
  } else if(partida->casilla[f_dest][c_dest].contenido == OBJETIVO) {
    mov = 1;
  }
  return mov;
}
