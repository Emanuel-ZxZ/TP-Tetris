#include <stdio.h>
#include <time.h>

#include <ctype.h>
#include <conio.h>
#include <windows.h>
#include "Tablero.h"
#include "pieza.h"
#include "juego.h"
#define f 20
#define c 10

int main()
{
    system("mode con: cols=50 lines=30");
    srand((unsigned int)time(NULL));

    Tablero mi_tablero; //creamos el tablero del jugador
    pieza p;//creamos donde se va a almacenar la pieza
    pieza piezasiguiente;//donde vamos a guardar la siguiente pieza
    pieza piezatemp;
    int puntaje=0;
    int juegoactivo=1;
    int esvalido;
    char movimiento;

    int contador_pasos = 0;
    int velocidad_caida = 10; // Cada 10 ciclos del loop la pieza cae 1 casillero solo
    // Creacion del tablero con las dimensiones elegidas
    if (!crear_tablero(&mi_tablero, f, c))
    {
        printf("Error: No se pudo asignar memoria para el tablero.\n");
        return 1;
    }
    ocultar_cursor();
    pieza_aleatoria(&piezasiguiente,c);//eric: creamos la siguiente pieza para mostrarla
    p=piezasiguiente;//eric: guardamos la siguiente pieza en p
    pieza_aleatoria(&piezasiguiente,c);

    while (juegoactivo)
    {
        limpiar_pantalla_sin_parpadeo();
        printf("            === TETRIS DE CONSOLA ===\n");
        printf("                PUNTAJE: %d pts\n", puntaje);
        printf("[A] Izq  [D] Der  [S] Bajar  [W] Rotar  [Q] Salir\n\n");
        imprimir_pieza(&piezasiguiente);//se muestra la siguiente pieza
        printf("\n");
        imprimir_tablero_pieza(&mi_tablero,&p);
        if (kbhit())
        {
            movimiento=getch();//eric: leemos el movimiento del jugador
            movimiento=toupper(movimiento);// eric: la normalizamos para la funcion


            //agregué esto para que lea la Q como salida
            if (movimiento == 'Q') {
            printf("                === GAME OVER! ===\n\nPuntaje final: %d",puntaje); //detallito
            juegoactivo = 0;
            }

            piezatemp=p;//guardamos una copia para calcular el movimineto sin perder la posicion
            mover_pieza(&piezatemp,movimiento);
            esvalido=hay_colision(&mi_tablero,&piezatemp);// 0 si no choca 1 si choca y 2 se ignora el movimiento porque se sale de los bordes

            if (esvalido==0)
            {
                p=piezatemp;
            }
            else if(esvalido==1)//hubo colision
            {

                fijar_pieza(&mi_tablero,&p);//fijamos la pieza original antes de hacer el movimiento
                int filaslimpiadas=limpiar_lineas_completas(&mi_tablero);

                if (filaslimpiadas>0)
                {
                    puntaje+=300*filaslimpiadas;
                }

                p=piezasiguiente;//eric: guardamos la siguiente pieza en p
                pieza_aleatoria(&piezasiguiente,c);//eric: creamos la siguiente pieza para mostrarla

                if (hay_colision(&mi_tablero, &p))
                {
                    printf("                === GAME OVER! ===\n\nPuntaje final: %d",puntaje); //detallito
                    juegoactivo = 0;
                }

            }
        }
        /// GRAVEDAD
        contador_pasos++;
        
        /*if (contador_pasos >= velocidad_caida)
        {
            contador_pasos = 0; //reinicia el contador

            piezatemp = p;
            piezatemp.y += 1; //intenta bajar 1 casillero solo por gravedad

            if (hay_colision(&mi_tablero, &piezatemp) == 0)
            {
                p.y += 1; // La gravedad la hace bajar
            }
            
            else
            {
                // Si por gravedad toca el piso/pieza -> Se fija automáticamente
                fijar_pieza(&mi_tablero, &p);
                int lineas = limpiar_lineas_completas(&mi_tablero);
                if (lineas > 0) puntaje += 300 * lineas;

                p = piezasiguiente;
                pieza_aleatoria(&piezasiguiente, mi_tablero.columnas);

                if (hay_colision(&mi_tablero, &p) != 0) {
                    printf("                === GAME OVER! ===\n\nPuntaje final: %d",puntaje);
                    juegoactivo = 0;
                }
            }
        }*/

        if (contador_pasos >= velocidad_caida)
        {
            contador_pasos = 0; //reinicia el contador

            if (gravedad(&mi_tablero, &p) == 0){ // cambie agregando al funcion de gravedad. no borre el anterior por las dudas
                // Si por gravedad toca el piso/pieza -> Se fija automáticamente
                fijar_pieza(&mi_tablero, &p);
                int lineas = limpiar_lineas_completas(&mi_tablero);
                if (lineas > 0) puntaje += 300 * lineas;

                p = piezasiguiente;
                pieza_aleatoria(&piezasiguiente, mi_tablero.columnas);

                if (hay_colision(&mi_tablero, &p) != 0) {
                    printf("                === GAME OVER! ===\n\nPuntaje final: %d",puntaje);
                    juegoactivo = 0;
                }
            }
        }


        
        Sleep(50); //Pequeña pausa de 50ms para mantener una tasa constante de refresco

    }
    // Liberaci�n de memoria antes de finalizar
    destruir_tablero(&mi_tablero);
    printf("\nMemoria liberada correctamente.\n");

    return 0;
}
