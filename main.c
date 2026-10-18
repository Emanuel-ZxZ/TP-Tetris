#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include "Tablero.h"
#include "pieza.h"

#define f 20
#define c 10

#define TOUPPER(X) ((X)>='a'&&(X)<='z' ? (X)-('a'-'A') : (X)) //creo que las macros iban en el .h pero lo deje aca para probarlo

int main()
{
    srand((unsigned int)time(NULL));

    Tablero mi_tablero; //creamos el tablero del jugador
    pieza p;//creamos donde se va a almacenar la pieza
    pieza piezasiguiente;//donde vamos a guardar la siguiente pieza
    pieza piezatemp;
    int puntaje=0;
    int juegoactivo=1;
    int esvalido;
    char movimiento;

    // Creacion del tablero con las dimensiones elegidas
    if (!crear_tablero(&mi_tablero, f, c))
    {
        printf("Error: No se pudo asignar memoria para el tablero.\n");
        return 1;
    }

    pieza_aleatoria(&piezasiguiente,c);//eric: creamos la siguiente pieza para mostrarla
    p=piezasiguiente;//eric: guardamos la siguiente pieza en p
    pieza_aleatoria(&piezasiguiente,c);
    while (juegoactivo)
    {
        printf("=== TETRIS DE CONSOLA ===\n");
        printf("PUNTAJE: %d pts\n", puntaje);
        printf("[A] Izq  [D] Der  [S] Bajar  [W] Rotar  [Q] Salir\n\n");
        imprimir_pieza(&piezasiguiente);//se muestra la siguiente pieza

        movimiento=getch();//eric: leemos el movimiento del jugador
        movimiento=TOUPPER(movimiento);// eric: la normalizamos para la funcion

        piezatemp=p;//guardamos una copia para calcular el movimineto sin perder la posicion
        mover_pieza(&piezatemp,movimiento);
        esvalido=hay_colision(&mi_tablero,&piezatemp);// 0 si no choca 1 si choca y 2 se ignora el movimiento porque se sale de los bordes

        if (esvalido==0)
        {
            p=piezatemp;

        }
        else if(esvalido==1)//hubo colision
        {

            fijar_pieza(&mi_tablero,&piezatemp);///falta hacer
            int filaslimpiadas=limpiar_lineas_completas(&mi_tablero);

            if (filaslimpiadas>0)
            {
                puntaje+=300*filaslimpiadas;
            }

            p=piezasiguiente;//eric: guardamos la siguiente pieza en p
            pieza_aleatoria(&piezasiguiente,c);//eric: creamos la siguiente pieza para mostrarla

            if (hay_colision(&mi_tablero, &p))
            {
                printf("GAME OVER!\n");
                juegoactivo = 0;
            }
        }
    }
    // Liberaci�n de memoria antes de finalizar
    destruir_tablero(&mi_tablero);
    printf("\nMemoria liberada correctamente.\n");

    return 0;
}
