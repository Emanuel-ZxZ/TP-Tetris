#include <stdio.h>
#include "Tablero.h"
#include "matriz_dinamica.h"
#include "pieza.h"

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
                    return 1;
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

int limpiar_lineas_completas(Tablero *t) {
    int lineas_limpiadas = 0;

    for (int i = (int)t->filas - 1; i >= 0; i--) {
        int fila_llena = 1;

        for (size_t j = 0; j < t->columnas; j++) {
            if (t->grilla[i][j] == 0) {
                fila_llena = 0;
                break;
            }
        }

        if (fila_llena) {
            lineas_limpiadas++;

            for (int k = i; k > 0; k--) {
                for (size_t j = 0; j < t->columnas; j++) {
                    t->grilla[k][j] = t->grilla[k - 1][j];
                }
            }

            for (size_t j = 0; j < t->columnas; j++) {
                t->grilla[0][j] = 0;
            }

            i++; // Reeval�a la fila desplazada
        }
    }

    return lineas_limpiadas;
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
