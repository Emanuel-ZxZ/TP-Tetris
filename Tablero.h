#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED
#include "pieza.h"
typedef struct {
    int** grilla;
    size_t filas;
    size_t columnas;
} Tablero;

int  crear_tablero(Tablero *t, size_t filas, size_t columnas);
void destruir_tablero(Tablero *t);
void inicializar_tablero(Tablero *t);
void imprimir_tablero(const Tablero *t);
int hay_colision(const Tablero *t, const pieza *p);
int fila_completa(const Tablero *t, int fila);
void bajar_filas(Tablero *t, int fila);
int limpiar_lineas_completas(Tablero *t);


#endif // TABLERO_H_INCLUDED
