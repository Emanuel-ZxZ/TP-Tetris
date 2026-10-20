#include <windows.h>


void limpiar_pantalla_sin_parpadeo()
{

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);// obtiene el manejador de la consola de Windows
    COORD pos = {0, 0};


    SetConsoleCursorPosition(hConsole, pos);// mueve el cursor de la pantalla a la esquina superior izquierda (0,0)
}

void ocultar_cursor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible=FALSE; // Oculta el cursor
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}
