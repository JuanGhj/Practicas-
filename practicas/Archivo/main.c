/*
Nombre: Juan González
Legajo: 23456
Ejercicio: --
Laboratorio: --


*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define LARGO 30
#define ENTRADA "libros.txt"  // -> Nombre archivo de entrada.
#define SALIDA "salida.txt"   // -> Nombre archivo de salida.

typedef struct
{
	int codigo;
	char titulo[LARGO];
	float precio;
 int stock;
}Libro; 
// Defino una estructura de tipo libro.

// * Formato del archivo libro.txt -> [ codigo titulo_sin_espacios precio ] 
// * Ejemplo:
/* 
 
101 Rayuela 4500.50 12
205 Ficciones 3800 0
310 ElAleph 5200.75 7

*/
void pedirMemoriaInicial(Libro **p, int cantidad)
{
	Libro* temp; // Variable temporal de tipo libro, para solo asignar la memoria si el puntero devulto por el administrador de memoria dinamica es distinto de NULL
	temp =(Libro*) calloc(cantidad, sizeof(Libro));
	if (temp == NULL)
	{
		printf("\nError en la asignacion de memoria dinamica.\n");
		exit(EXIT_FAILURE);
	}
	*p = temp;
		return;
}
void cargarLibros(FILE * entrada, int cantidad)
{
	int i = 0;
	int temp1=0;
	char temp2[LARGO];
	float temp3=0;
	int temp4=0;
	for (i = 0;i < cantidad;i++) // Levanto los libros en variables temporales con cada iteracion,   y los guardo en el archivo
	{
		printf("Libro N %d", i + 1);
		printf("\nCodigo: ");
		scanf("%d", &temp1);
		printf("\nTitulo: ");
		scanf("%29s", temp2);
		printf("\nPrecio: ");
		scanf("%f", &temp3);
		printf("\nStock ");
		scanf("%d", &temp4);
		fprintf(entrada, "\n%d %29s %f %d", temp1, temp2, temp3, temp4);
	}
	return;
}
void leerEImprimir(FILE* entrada, Libro *p,int cantidad) // --> Lee e imprime el archivo en panatalla
{
	int i = 0;
	for (i = 0;i < cantidad;i++)
	{
		fscanf(entrada,"\n%d %29s %f %d",&p[i].codigo, p[i].titulo, &p[i].precio, &p[i].stock);                                   // Guardo los datos ingresados en la funcon <cargarLibros> y los cargo en RAM mediante el arreglo de tipo Librodonde previamente reserve memoria para el arreglo dinamico
		printf("\n\nLibro N: %d", i+1);
		printf("\nCodigo:  %d",p[i].codigo);
		printf("\nTitulo: %s",p[i].titulo);
		printf("\nPrecio: %f",p[i].precio);
		printf("\nStock %d",p[i].stock);
	}
	return;
}
void ordenarPorPrecio(Libro* p, int cantidad, FILE* salida)
{
	int j = 0;
	int pasada = 0;
	int posMin=0;
	Libro temp; // Variable temporal tipo estructuctura <Libro>
	for (pasada = 0;pasada < cantidad;pasada++)
	{
		temp = p[pasada];
		posMin = pasada;
	for(j=posMin;j<cantidad;j++)
		{
		if (p[j].precio < p[posMin].precio)posMin = j;
		else if (p[j].precio == p[posMin].precio && strcmp(p[j].titulo, p[posMin].titulo) < 0)posMin = j;
		}
	p[pasada] = p[posMin];  // Swap
	p[posMin] = temp;
	}
	// ====================================================================================
	for (j = 0;j < cantidad;j++)
	{
		fprintf(salida, "%d %29s %f %d\n", p[j].codigo, p[j].titulo, p[j].precio, p[j].stock);  // Imprime a partir del arreglo ya ordenado
	}
	return;
}
void stockCero(FILE* sinS, FILE *salida, int cantidad)
{
	int i = 0;
		int codigo;
		char nombre [LARGO];
		float precio;
		int stock;
	for (i = 0;i < cantidad;i++)
	{
		fscanf(salida, "%d %29s %f %d\n", &codigo, nombre, &precio, &stock);
		if (stock == 0)
		{
			fprintf(sinS,"%d %29s %f %d\n", codigo, nombre, precio, stock);
		}
	}

	return;
}
int main(void)
{
	Libro *libreria; // puntero a Libro -> <Posteriormente voy a reservar memoria dinamina para crear un aarreglo de tamño variable/>
	FILE* entrada;
	FILE* salida;
	FILE* sinStock;
	int cantidad=0;
	entrada = fopen(ENTRADA, "w");
	if (entrada == NULL)
	{
		printf("\nNo se pudo abrir el archivo de antrada\n\n");
		exit(EXIT_FAILURE);
	}
	salida = fopen(SALIDA, "w");
	if (salida == NULL)
	{
		printf("\nNo se pudo abrir el archivo de salida\n\n");
		exit(EXIT_FAILURE);
	}
	printf("\nCuantos libros va a ingresar:  ");
	scanf("%d",&cantidad);
	if (cantidad < 0)
	{
		printf("Cantidad mal ingresada\n\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		pedirMemoriaInicial(&libreria, cantidad); // Paso por referencia la variable de tipo libro  para que se pueda modificar el puntero.
	}
	cargarLibros(entrada, cantidad);
	fclose(entrada);
	 // Cierro y vuelvo a abrir el acrhivo en modo lectura, para cargar su contenido en RAM
	entrada = fopen(ENTRADA, "r");
	if (entrada==NULL)
	{
		printf("\nNO se pudoa brir el archivo de entrada en modo lectura\n");
		exit(EXIT_FAILURE);
	}
	leerEImprimir(entrada,libreria, cantidad);
	ordenarPorPrecio(libreria, cantidad, salida);
	fclose(salida);
	salida = fopen(SALIDA, "r");
	if (salida == NULL)
	{
		printf("\nNO se pudoa brir el archivo de salida en modo lectura\n");
		exit(EXIT_FAILURE);
	}
	sinStock = fopen("Sin-stock.txt","w");
	if (sinStock == NULL)
	{
		printf("\nNo se pudo abrir el archivo de tecto para objetos sin stock\n");
		exit(EXIT_FAILURE);
	}
	stockCero(sinStock, salida, cantidad);
	fclose(sinStock);
	fclose(salida);
	free(libreria); // Libero la memoria 
	fclose(entrada); // Vuelvo a cerrar el archivo de entrada -> <Previamente lo abri en modo lectura para cargar los datos en RAM>
	fclose(salida); 
	// * Apertura de los archivos <Entrada y salida>
	return 0;
}