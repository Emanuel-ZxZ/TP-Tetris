#include <stdio.h>
#include "Tablero.h"
#include "pieza.h"
int main()
{
    int f = 0;
    int c = 0;
    Tablero mi_tablero;
    //EMA:Prueba de tablero
    printf("=== CONFIGURACION DEL TABLERO DE TETRIS ===\n");

    // EMA: Creanme 10 y 20 es lo ideal, probe con 30 y seria demasiado grande.
    // Lectura y validación directa del tamaño
    do {
        printf("Ingrese filas (minimo 10, estandar 20): ");
        scanf("%d", &f);
    } while (f < 10);

    do {
        printf("Ingrese columnas (minimo 6, estandar 10): ");
        scanf("%d", &c);
    } while (c < 6);

    size_t filas = (size_t)f;
    size_t columnas = (size_t)c;

    // Creación del tablero con las dimensiones elegidas
    if (!crear_tablero(&mi_tablero, filas, columnas)) {
        printf("Error: No se pudo asignar memoria para el tablero.\n");
        return 1;
    }

    printf("\n--- TABLERO INICIAL (%zux%zu) ---\n", mi_tablero.filas, mi_tablero.columnas);
    imprimir_tablero(&mi_tablero);

    // Simulación: llenamos la última fila para probar la detección y limpieza de líneas
    for (size_t col = 0; col < mi_tablero.columnas; col++) {
        mi_tablero.grilla[mi_tablero.filas - 1][col] = 1;
    }

    printf("\n--- TABLERO CON FILA INFERIOR LLENA ---\n");
    imprimir_tablero(&mi_tablero);

    // Limpieza de líneas
    int limpiadas = limpiar_lineas_completas(&mi_tablero);
    printf("\nLineas despejadas: %d\n", limpiadas);

    printf("\n--- TABLERO LUEGO DE LIMPIAR ---\n");
    imprimir_tablero(&mi_tablero);

    // Liberación de memoria antes de finalizar
    destruir_tablero(&mi_tablero);
    printf("\nMemoria liberada correctamente.\n");

    return 0;
}
