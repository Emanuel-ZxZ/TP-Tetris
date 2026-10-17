#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED

typedef struct {
    int** grilla;
    size_t filas;
    size_t columnas;
} Tablero;

int  crear_tablero(Tablero *t, size_t filas, size_t columnas);
void destruir_tablero(Tablero *t);
void inicializar_tablero(Tablero *t);
void imprimir_tablero(const Tablero *t);
int  casilla_ocupada(const Tablero *t, int fila, int columna);
int  limpiar_lineas_completas(Tablero *t);

void imprimir_tablero_con_pieza();///FALTA HACER
#endif // TABLERO_H_INCLUDED
