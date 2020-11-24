#ifndef _TABLERO_H_
#define _TABLERO_H_

#define MAX_F     25
#define MAX_C     70

#define CAJA           '0'
#define ENCARGADO      '@'
#define VACIO          ' '
#define PARED          '#'
#define OBJETIVO       'X'
#define ENCARGADO_CAJA '+'  
#define CAJA_OBJETIVO  '*'  

#define MURO 1
#define NO_MURO 0

typedef struct {
  int pos_x;
  int pos_y;
} t_posicion;
  
typedef struct {
  t_posicion posE;
  int pasos;
} t_encargado;
  
typedef struct {
  char contenido;  // caja('0'), encargado('@'), vacio(' '), 
  char tipo;       // pared('#') o no
  char objetivo;   //1 si es objetivo
  char caja;       //1 si hay caja bajo el encargado
} t_casilla;

typedef struct{
  int n_fil, n_col;
  char tablero[MAX_F][MAX_C];
} t_tablero;

typedef struct {
  char nivel[100];
  t_casilla casilla[MAX_F][MAX_C];
  int filas;
  int columnas;
  int nCajas;
  int nObj;
  t_encargado pers;
  int puntos; 
} t_partida;

void inicializa(t_tablero tablero, t_partida *partida); //Introduce el nivel y el tablero en el elemento correspondiente del tipo de dato t_partida

void juega (int tecla, t_partida *partida, t_tablero tablero); //Inicializa el juego y se mantiene en ejecución hasta finalizar la partida

void restart_game(t_partida *partida, t_tablero tablero); //Reinicia el juego a su estado inicial 

int puntua (int puntos, t_partida *partida, int f_dest, int c_dest, int f_dest2, int c_dest2); //Esta funcion sumara un punto al marcador cuando una caja se situe en una posicion de almacenamiento y lo restara cuando esta salga de ella

int contar_objetivos(t_partida partida, t_tablero *tablero); //cuenta el numero de objetivos que hay en el tablero

int contar_empujes(int puntos, t_partida *partida, int f_dest, int c_dest, int f_dest2, int c_dest2); //contara las veces que el encargado empuje una caja
  
void menu(); //Muestra por pantalla que teclas pulsar para mover al encargado

void mostrar_nombre (t_partida *partida);
void mostrar_puntos (t_partida partida);
void mostrar_objetivos(t_partida partida);
void mostrar_pasos (t_partida partida);
void mostrar_empujes(t_partida partida);
void mostrar_tablero (t_partida *partida);
void mostrar_partida (t_partida partida, t_tablero *tablero); //llama a las funciones de mostrar por pantalla los diferentes elementos de la partida

int leer_tablero(FILE * file, char nivel[], t_tablero *tablero); //en la fase 2, lee los tableros de los ficheros

#endif

