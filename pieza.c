#include <stdio.h>
#include <stdlib.h>
#include "pieza.h"
// LO QUE ESTA HECHO CON INDICES DESPUES LO CAMBIO A ARIMETICA DE PUNTEROS
void pieza_aleatoria(pieza *p, size_t columnas_tablero)
{
    if (!p) return;

    //Elegir un tipo de pieza al azar del 0 al 6
    p->tipo = rand() % 7;
    p->rotacion = 0;

    // Centra la pieza arriba en el tablero
    p->x = ((int)columnas_tablero / 2) - 2;
    p->y = 0;

    // Copia la matriz 4x4 correspondiente a la forma elegida
    obtener_matriz_pieza(p->tipo,p->forma);
}
void obtener_matriz_pieza(int tipo, int forma[][4]) // recibe la matriz de pieza original para guardar la forma correspondiente
{

    // creamos una matriz temporal
    int temp[4][4] = {0};

    switch (tipo) {
        case 0: // Pieza I
            temp[1][0] = 1; temp[1][1] = 1; temp[1][2] = 1; temp[1][3] = 1;
            break;
        case 1: // Pieza J
            temp[0][0] = 1;
            temp[1][0] = 1; temp[1][1] = 1; temp[1][2] = 1;
            break;
        case 2: // Pieza L
            temp[0][2] = 1;
            temp[1][0] = 1; temp[1][1] = 1; temp[1][2] = 1;
            break;
        case 3: // Pieza O
            temp[0][1] = 1; temp[0][2] = 1;
            temp[1][1] = 1; temp[1][2] = 1;
            break;
        case 4: // Pieza S
            temp[0][1] = 1; temp[0][2] = 1;
            temp[1][0] = 1; temp[1][1] = 1;
            break;
        case 5: // Pieza T
                            temp[0][1] = 1;
            temp[1][0] = 1; temp[1][1] = 1; temp[1][2] = 1;
            break;
        case 6: // Pieza Z
            temp[0][0] = 1; temp[0][1] = 1;
                            temp[1][1] = 1; temp[1][2] = 1;
            break;
    }

    // se copia la matriz temp a la matriz forma q es la que usamos
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            forma[i][j] = temp[i][j];
        }
    }
}


