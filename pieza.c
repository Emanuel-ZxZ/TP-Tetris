#include <stdio.h>
#include <stdlib.h>
#include "pieza.h"
#include "Tablero.h"

#define TAM_PIEZA 4
// LO QUE ESTA HECHO CON INDICES DESPUES LO CAMBIO A ARIMETICA DE PUNTEROS
void pieza_aleatoria(pieza *p, size_t columnas_tablero)
{

    //Elegir un tipo de pieza al azar del 0 al 6
    p->tipo = rand() % 7; //FLOR: probé esto pero por algun motivo necesita de la biblioteca time.h y en el main poner: "srand(time(NULL));" si no siempre genera la misma pieza, todavia no entiendo muy bien el porqué
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

//FLOR:
//Habia pensado en poner una macro para asignar el tamaño de la matriz con un #define TAM_PIEZA 4 pero ahora lo cambio
//Pense en inicialiar primero la matriz con ceros para evitar que haya basura o algo y para despues poder imprimirla
//Iría antes de la fc obtener la pieza

void inicializar_pieza (pieza *p){
for(int i=0;i<4;i++){
    for(int j=0;j<TAM_PIEZA;j++){
        p->forma[i][j]=0;
    }
}
}

void imprimir_pieza (pieza*p){
for (int i = 0; i < TAM_PIEZA; i++) {
    for (int j = 0; j < TAM_PIEZA; j++) {
        if (p->forma[i][j] == 1) {
            printf("#");
        } else {
            printf(".");
        }
}
printf("\n");
}
}

void fijar_pieza(Tablero *t, const pieza *p)//copia la pieza del 4x4 y la pega en la matris
{
    int i, j;//i=fila, j=columna

    for (i = 0; i < TAM_PIEZA; i++)
        for (j = 0; j < TAM_PIEZA; j++)
            if (p->forma[i][j] == 1 && p->y + i >= 0)
                t->grilla[p->y + i][p->x + j] = p->tipo + 1;
}

