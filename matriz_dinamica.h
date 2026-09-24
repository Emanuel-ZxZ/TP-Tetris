#ifndef MATRIZ_DINAMICA_H_INCLUDED
#define MATRIZ_DINAMICA_H_INCLUDED

void** crearMatriz(size_t filas, size_t columnas, size_t tam_dato);
void   liberarMatriz(void** matriz, size_t filas);

#endif // MATRIZ_DINAMICA_H_INCLUDED
