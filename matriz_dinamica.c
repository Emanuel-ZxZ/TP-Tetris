#include <stdlib.h>
#include "matriz_dinamica.h"

void** crearMatriz(size_t filas, size_t columnas, size_t tam_dato) {
    void** matriz = malloc(sizeof(void*) * filas);
    if (!matriz) {
        return NULL;
    }

    for (size_t i = 0; i < filas; i++) {
        *(matriz + i) = malloc(tam_dato * columnas);
        if (!(*(matriz + i)))
        {
            // Liberar lo reservado previamente si falla alguna fila
            for (size_t k = 0; k < i; k++)
            {
                free(*(matriz + k));
            }
            free(matriz);
            return NULL;
        }
    }

    return matriz;
}

void liberarMatriz(void** matriz, size_t filas) {
    if (!matriz) return;

    for (size_t i = 0; i < filas; i++) {
        free(*(matriz + i));
    }
    free(matriz);
}
