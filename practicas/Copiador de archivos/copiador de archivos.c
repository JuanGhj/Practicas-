#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
int main(void)
{
	int ch;
	FILE *pOrigen;
	FILE *pDestino;
	const char* archivoOrigen = "Entrada.txt" ;
	const char* archivoDestino = "Salida.txt" ;

	// Apertura del archivo de origen.

	pOrigen = fopen(archivoOrigen, "r");
	if (pOrigen == NULL)
	{
		printf("No se pudo abrir el archivo de origen");
		return -1;
	}
	 // Apertura del archivo de Salida
	pDestino = fopen(archivoDestino, "w");
	if (pDestino == NULL)
	{
		printf("\nNo se pudo abrir el archivo de salida");
		return - 2;
	}
// Leer un caracter por vez y pasarlo del archivo txt de origen al del destino.
	ch = getc(pOrigen);
	while (ch != EOF)
	{
		putc(ch, pDestino);
		ch = getc(pOrigen);
	}

	// Cierre de archivos.
	fclose(pDestino);
	fclose(pOrigen);
	printf("\nFin del copiador de archivos\n\n");
	
	return 0;
}