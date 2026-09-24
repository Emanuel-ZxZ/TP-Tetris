#include <stdio.h>
#include "Tablero.h"
#include "matriz_dinamica.h"

int crear_tablero(Tablero *t, size_t filas, size_t columnas) {
    t->filas = filas;
    t->columnas = columnas;
    t->grilla = (int**)crearMatriz(filas, columnas, sizeof(int));

    if (!t->grilla) {
        return 0; // Error al asignar memoria
    }

    inicializar_tablero(t);
    return 1; // Éxito
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

int casilla_ocupada(const Tablero *t, int fila, int columna) {
    if (columna < 0 || (size_t)columna >= t->columnas || (size_t)fila >= t->filas) {
        return 1; // Fora de los límites
    }
    if (fila < 0) {
        return 0; // Zona de entrada de pieza
    }
    return t->grilla[fila][columna] != 0;
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

            i++; // Reevalúa la fila desplazada
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
