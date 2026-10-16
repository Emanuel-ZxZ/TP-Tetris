#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include "Tablero.h"
#include "pieza.h"

#define f 20
#define c 10
int main()
{
    Tablero mi_tablero; //creamos el tablero del jugador
    srand((unsigned int)time(NULL));
    pieza p;//creamos donde se va a almacenar la pieza
    pieza pieza2;//donde vamos a guardar la siguiente pieza
    char movimiento;
    int colision=0;
    // Creación del tablero con las dimensiones elegidas
    if (!crear_tablero(&mi_tablero, f, c)) {
        printf("Error: No se pudo asignar memoria para el tablero.\n");
        return 1;
    }
    imprimir_tablero(&mi_tablero);
    pieza_aleatoria(&pieza2, c);//creamos la primer pieza fuera del do while
    do
    {
        p=pieza2;//eric: guardamos la siguiente pieza en p
        pieza_aleatoria(&pieza2,c);//eric: creamos la siguiente pieza para mostrarla
        colision=0;
        while (colision==0)//controlamo si la pieza ya choco asi pasamos a la siguiente
        {


            scanf("%c",&movimiento);//eric: leemos el movimiento del jugador
            toupper(movimiento);// eric: la normalizamos para la funcion
            mover_pieza(&p,movimiento);//eric: mueve los valores x y
            while(validar_movimiento())//valida si no choca con las paredes 0 si no choca 1 si lo hace.
                {
                    scanf("%c",&movimiento);//vuelve a pedir el movimineto hasta que este sea valido
                    mover_pieza(&p,movimiento);
                }
            if (validar_colision())// 1 si no colisiona 0 si choca
            {
                //se muestra por pantalla con


            }
            else
            {
                guardar_matriz_en_tablero();
            }

        }
        // una ves sale del while recien aca se pasa el valor de la matriz pieza a el tablero
        void guardar_matriz_en_tablero ()

    }while(!game_over());//controla si la persona ya perdio



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
