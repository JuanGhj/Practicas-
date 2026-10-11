/*
Nombre: Juan González
Legajo: 23456
Practica Parcial 3
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
void imprimirNotasOrdenadas(int notas[][5], char materias[][81], char alumnos[][81], int FIL, char* p[5], int pasada);
void cargarNotas(int mat[][5], int FIL, int COL)
{
	int i = 0;
	int j = 0;
	for (i = 0;i < FIL;i++)
	{
		for (j = 0;j < COL;j++)
		{
			mat[i][j] = rand() % 10 + 1;
		}
	}


	return;
}
void iniciarPunteros(char nombres[][81], char* p[5], int FIL)
{
	int i = 0;
	for (i = 0;i < FIL;i++)
	{
		p[i] = nombres[i];
	}
	return;
}
void imprimirNotas(int mat[][5], char materias[][81], char alumnos[][81], int FIL)
{
	int i = 0;
	int j = 0;
	printf("\n\n");
	printf("Alumnos                                 materias\n\n");
	printf("          ");
	for (i = 0;i < FIL;i++)
	{
		
		printf(" %11s |", materias[i]);
	}
	puts("");
	for (i = 0;i < FIL;i++)
	{
		printf("%10s", alumnos[i]);
		for (j = 0;j < FIL;j++)
		{
			printf("      %2d     |", mat[i][j]);
		}
		puts("");
	}
	return;
}

void ordenarPorNotas(int notas[][5], char alumno[][81], char materias[][81], int FIL, char *p[])
{

	int pasada = 0;
	int j = 0;
	int temp;
	int materia = 0;
	char* tempC;
	printf("\n\n");
	printf("materias                   calificacion por alumno\n\n");
	for (materia = 0;materia < FIL;materia++)
	{
		for (pasada = 0;pasada < FIL;pasada++)
		{
			tempC = p[pasada];
			temp = notas[pasada][materia];
			j = pasada - 1;
			while (j >= 0 && temp > notas[j][materia])
			{
				notas[j + 1][materia] = notas[j][materia];
				p[j + 1] = p[j];
				j--;
			}
			notas[j + 1][materia] = temp;
			p[j + 1] = tempC;
		}
		imprimirNotasOrdenadas(notas, materias, alumno, FIL, p, materia);
	}


	return;
}
void imprimirNotasOrdenadas(int notas[][5],char materias[][81], char alumnos[][81], int FIL, char *p[5],int pasada)
{
	int j = 0;
	
		printf("%11s:\n   ", materias[pasada]);
		for (j = 0;j < FIL;j++)
		{
			printf("%10s", p[j]);
		}
		printf("\n");
		for (j = 0;j < FIL;j++)
		{
			printf("%10d", notas[j][pasada]);
		}
		printf("\n\n");
	
	return;
}
int main()
{
	srand(time(NULL));
	const int FIL = 5;
	const int COL = 81;
	char nombres[FIL][COL] = { "Juan","Pablo","Maria","Esteban","Nicolas"};
	char materias[FIL][COL] = {"Quimica","Fisica","Lengua","Matematicas","Historia"};
	int notas[FIL][FIL];
	char* p[5]; // Puntero con arreglo de nombres.
	cargarNotas(notas, FIL, FIL);
	iniciarPunteros(nombres, p, FIL);
	printf("\n\nNotas por alumno y por materia:");
	imprimirNotas(notas,materias, nombres, FIL);
	ordenarPorNotas(notas, nombres, materias, FIL,p);

	//imprimirNotas(notas, materias, nombres, FIL);
	
	return 0;
}