/*
NOMBRE: Juan Jose González
LEGAJO: 23456
LABORATORIO:
EJERCICIO:

									   */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#define VENDEDORES 4
#define PRODUCTOS 6
#define LARGO 81
typedef struct
{
	char nombre[LARGO];
	int ventas[PRODUCTOS];
	int total;
	char categoria[LARGO];
}Vendedor;
void cargarVendedores(Vendedor v[], char nombres[][LARGO])
{
	int i = 0;
	int j;
	printf("\nIngrese los nombres de los vendedores: \n");

	for (i = 0;i < VENDEDORES;i++)
	{
		strcpy(v[i].nombre, nombres[i]);
	}

	for (i = 0;i < VENDEDORES;i++)
	{
		for (j = 0;j < PRODUCTOS;j++)
		{
			v[i].ventas[j] = rand() % 51;
		}
	}
	return;
}
void cargarTotales(Vendedor *v)
{
	int i = 0;
	int j=0;
	int sumaParcial=0;
	for (i = 0;i < VENDEDORES;i++)
	{
		sumaParcial = 0;// Inicializo ventas a cero antes de asignarle la suma,  ya que de lo contarrio contiene basura o elementos anteriores.
		for (j = 0;j < PRODUCTOS;j++)
		{
			sumaParcial =sumaParcial+ v[i].ventas[j];
		}
		v[i].total = sumaParcial;
	}
	return;
}
void asignarCategoria(Vendedor *v)
{
	int i = 0;
	char max[LARGO]="Senior";
	char min[LARGO] = "Junior";
	for (i = 0;i < VENDEDORES;i++)
	{
		if (v[i].total <= 150)strcpy(v[i].categoria, min);
		else  strcpy(v[i].categoria, max);
	}
	return;
}
void imprimirVendedores(Vendedor* v)
{
	int i = 0;
	printf("\n ___________________________________________________________");
	printf("\n|  Vendedor    |     Total de ventas      |     Categoria   |\n");
	printf("|--------------|--------------------------|-----------------|\n");
	for (i = 0;i < VENDEDORES;i++)
	{
		printf("|  %9s   |           %3d            |    %9s    |\n", v[i].nombre, v[i].total, v[i].categoria);
	}
	printf("|______________|__________________________|_________________|");
	printf("\n\n");
	return;
}
void ordenarPorVentas(Vendedor* v) // Ordeno en base al total de ventas,  por algoritmo de insersión.
{
	int j = 0;
	int pasada = 0;
	Vendedor temp;
	for (pasada = 0;pasada < VENDEDORES;pasada++)
	{
		temp = v[pasada];
		j = pasada - 1;
		while (j >= 0 && v[j].total <temp.total)
		{
			v[j + 1] = v[j];
			j--;
		}
		v[j + 1] = temp;
	}
	return;
}
void ranking(Vendedor* v, char productos[][LARGO])
{
	int i = 0;
	int j = 0;
	int mayor=0;
	int posMax = 0;
	printf("\productos      mejor vendedor por producto \n");
	for (i = 0;i < PRODUCTOS;i++)
	{
		mayor = 0; // Reinicio del comparador de ventas por producto.
		printf("%8s", productos[i]);
		for (j = 0;j < VENDEDORES;j++)
		{
			if (v[j].ventas[i] > mayor)
			{
				mayor = v[j].ventas[i];
				posMax = j;
			}
		}
		printf("  %s (%d  ventas) \n", v[posMax].nombre, v[posMax].ventas[posMax]);
	}
	return;
}
int buscarVendedor(Vendedor* v, char clave[LARGO])
{
	int i = 0;
	int j = 0;
	char copiaC[LARGO]; // copia de la clave ingresada por usuario,  para no alterar la clave original.
	char copiaB[VENDEDORES][LARGO];
	strcpy(copiaC, clave);
	for (i = 0;i < VENDEDORES;i++)
	{
		strcpy(copiaB[i], v[i].nombre);
	}
	i = 0;
	while (copiaC[i] != '\0')
	{
		copiaC[i] = tolower(copiaC[i]);
		i++;
	}
	copiaC[i] = '\0'; // Agrego el terminador \0 a mano.
	for (i = 0;i < VENDEDORES;i++)
	{
		j = 0; // Reinicio de indice de columnas.
		while (copiaB[i][j] != '\0')
		{
			copiaB[i][j] = tolower(copiaB[i][j]);
			j++;
		}
		copiaB[i][j] = '\0'; // Agrego el terminador \0 a mano.
	}
	for (i = 0;i < VENDEDORES;i++)
	{
		if (strcmp(copiaB[i], copiaC) == 0)
		{
			return i;
		}
	}
	return -1;
}
void imprimirBusqueda(Vendedor* v, char productos[][LARGO])
{
	char clave[LARGO];
	int hallado = 0;
	printf("Buscar productos que vendio un vendedor:  ");
	scanf("%80s", clave);
	printf("\n\n");
	hallado = buscarVendedor(v, clave);
	if (hallado != -1)
	{
		printf("Concidencia: %s,    %d ventas totales \n\n", v[hallado].nombre, v[hallado].total);
		printf("Ventas por articulo: \n");
		for (int i = 0;i < PRODUCTOS;i++)
		{
			printf(" %10s ", productos[i]);
		}
		puts("");

		for (int j = 0;j < PRODUCTOS;j++)
		{
			printf(" %10d ", v[hallado].ventas[j]);

		}
	}
	else printf("\nVendedor %s no hallado\n\n", clave);
}
int main()
{
	srand(time(NULL));
	char productos[PRODUCTOS][LARGO] = {"Pelota","Lata","Agua","Termo","Pc","Helicoptero"};
	char nombres[VENDEDORES][LARGO] = { "Carlos", "Marcelo", "Juan", "Nicolas" };
	Vendedor vendedores[VENDEDORES]; // Arreglo de tipo estructura <Vendedor> de 4 elementos.
	cargarVendedores(vendedores, nombres);
	cargarTotales(vendedores);
	asignarCategoria(vendedores);
	printf("Lista de vendedores:\n");
	imprimirVendedores(vendedores);
	printf("\nLista de vendedores ordenada por total de ventas\n");
	ordenarPorVentas(vendedores);
	imprimirVendedores(vendedores);
	ranking(vendedores, productos);
	imprimirBusqueda(vendedores, productos);
	return 0;
}