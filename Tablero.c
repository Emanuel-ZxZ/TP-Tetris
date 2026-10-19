#include <stdio.h>
#include "Tablero.h"
#include "matriz_dinamica.h"
#include "pieza.h"

#define TAM_PIEZA 4
int crear_tablero(Tablero *t, size_t filas, size_t columnas) {
    t->filas = filas;
    t->columnas = columnas;
    t->grilla = (int**)crearMatriz(filas, columnas, sizeof(int));

    if (!t->grilla) {
        return 0; // Error al asignar memoria
    }

    inicializar_tablero(t);
    return 1; // �xito
}

void destruir_tablero(Tablero *t) {
    if (t->grilla) {
        liberarMatriz((void**)t->grilla, t->filas);
        t->grilla = NULL;
    }
}

void inicializar_tablero(Tablero *t) {
    for (size_t i = 0; i < t->filas; i++) {
        for (size_t j = 0; j < t->columnas; j++) {
            t->grilla[i][j] = 0;
        }
    }
}

int hay_colision(const Tablero *t, const pieza *p)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {

            if (p->forma[i][j] == 1) {//mapeamos la posicion de la pieza en el tablero

                int fila    = p->y + i;
                int columna = p->x + j;

                if (columna < 0 || columna >= (int)t->columnas) { //preguntamos las paredes
                    return 2;
                }
                if (fila >= (int)t->filas) {//preguntamos el piso
                    return 1;
                }

                if (fila >= 0 && t->grilla[fila][columna] != 0) { //preguntamos si ya existen piezas fijas
                    return 1;
                }
            }
        }
    }
    return 0;   // No hay colisión
}


int fila_completa(const Tablero *t, int fila)//revisa columna a columna si esta ocupada si la fila esta llena manda un 1 si no 0 marcando
{
    int j;

    for (j = 0; j < (int)t->columnas; j++)
        if (t->grilla[fila][j] == 0)
            return 0;
    return 1;
}

void bajar_filas(Tablero *t, int fila)//se le pasa la fila que esta completa y copia la fia encima de esta en la posicion siguiente asi hasta la fila 0
{
    int k, j;

    for (k = fila; k > 0; k--)
        for (j = 0; j < (int)t->columnas; j++)
            t->grilla[k][j] = t->grilla[k - 1][j];
    for (j = 0; j < (int)t->columnas; j++)//este for pone en 0 a la primera fila despues de todo el movimiento para dar paso a la siguiente pieza es necesario para no tener piezas bugueadas
        t->grilla[0][j] = 0;
}

int limpiar_lineas_completas(Tablero *t)//esta te recorre toda la tabla para ver si hubo mas de una fila llena y las va eliminando y contandolas eliminadas
{
    int lineas = 0, i;

    for (i = (int)t->filas - 1; i >= 0; i--)
    {
        if (fila_completa(t, i))
        {
            bajar_filas(t, i);
            lineas++;
            i++;
        }
    }
    return lineas;
}

void imprimir_tablero(const Tablero *t) {
    for (size_t i = 0; i < t->filas; i++) {
        printf("|");
        for (size_t j = 0; j < t->columnas; j++) {
            if (t->grilla[i][j] == 0) {
                printf(" . ");
            } else {
                printf(" # ");
            }
        }
        printf("|\n");
    }
    printf("--------------------------------\n");
}

void imprimir_tablero_pieza(const Tablero *t, const pieza *p)
{
    for (int i=0; i<t->filas;i++)
    {
        printf("             |");//Borde izquierdo del tablero

        for (int j=0;j<t->columnas;j++)
        {
            int es_bloque_pieza = 0;


            if ((i>=p->y && i < p->y + 4) && (j >= p->x && j < p->x + 4))
            {
                int rel_y = i - p->y;
                int rel_x = j - p->x;


                if (p->forma[rel_y][rel_x] != 0)//Si en esa posición del molde 4x4 hay un bloque de la ficha 1
                {
                    es_bloque_pieza = 1;
                }
            }


            if (es_bloque_pieza)//Decisión de qué imprimir en pantalla
            {
                printf("# "); // Bloque de la pieza activa que va cayendo
            }
            else if (*(*(t->grilla+i)+j)!=0)
            {
                printf("X "); // Bloques de piezas fijadas anteriormente
            }
            else
            {
                printf(". "); // Casilla vacía del tablero
            }
        }

        printf("|\n"); // Borde derecho del tablero y salto de línea
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
