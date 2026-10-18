#ifndef PIEZA_H_INCLUDED
#define PIEZA_H_INCLUDED

typedef struct
{
    int tipo; // 0 a 6  I,J,L,O,S,T,Z
    int rotacion; // 1 A 4 (0 90 18 270)
    int x,y; //coordenadas
    int forma [4][4];
}pieza;

void pieza_aleatoria(pieza *p, size_t columnas_tablero);// funcion para generar piezas aleatorias
void obtener_matriz_pieza(int tipo, int forma[][4]);// funcion para cargar los valores de la matriz forma


void mover_pieza (pieza *p, char movimiento); //carga el movimiento despues de ser validado (despues de que se controle de que no se mueva fuera de los limites
                                                         //y de que no choque con otra pieza)

void imprimir_pieza (pieza *p);
void inicializar_pieza (pieza *p);

void rotar(pieza *p);

#endif // PIEZA_H_INCLUDED
