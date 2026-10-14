/*
Nombre: González Juan
Laboratorio:
Ejercicio:



*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define VENDEDORES 4
#define PRODUCTOS 6
#define LARGO 81
void copiarMatriz(int original[][PRODUCTOS], int copia[][PRODUCTOS]) // Creo una copia, ya que al momento de hacer el ranking es inevitable desordenar
                                                                     // la matriz de ventas,  por lo que,  si se desean efectuar operacions posteriores
																	 //  conviene mantener la original y desordenar una copia.
{
	int i = 0;
	int j = 0;
	for (i = 0;i < VENDEDORES;i++)
	{
		for (j = 0;j < PRODUCTOS;j++)
		{
			copia[i][j] = original[i][j];
		}
	}
	return;
}

void iniciarPunteros(char nombres[][LARGO], char* p[])
{
	int i = 0;
	for (i = 0;i < VENDEDORES; i++)
	{
		p[i] = nombres[i];
	}
	return;
}
void cargarVentas(int ventas[][6])
{
	int i = 0;
	int j = 0;
	for (i = 0;i < VENDEDORES;i++)
	{
		for (j = 0;j < PRODUCTOS;j++)
		{
			ventas[i][j] = rand() % 51;
		}
	}
	return;
}
void imprimirVentas(int ventas[][PRODUCTOS], char nombre[][LARGO], char productos[][LARGO])
{
	int i = 0;
	int j = 0;
	printf("Nombre                     ventas por producto \n\n           ");
	for (j = 0;j < PRODUCTOS;j++)
	{
		printf(" %8s  ", productos[j]);
	}
	printf("\n");
	for (i = 0;i < VENDEDORES;i++)
	{
		printf("%6s", nombre[i]);
		for (j = 0;j < PRODUCTOS;j++)
		{
			printf(" %10d ", ventas[i][j]);
		}
		printf("\n");
	}


	return;
}
void imprimirRanking(char productos[][LARGO],int ventas[][PRODUCTOS], int pasada, char *nombre[]) // Va de la mano con la funcion de debajo,  "ordenarEimprimirRanking".  Se encarga de imprmir un productos,  sus ventas ordenadas de mayor a menor,  y a quien le pertenecen dichas ventas.
{
	int i = 0;
	printf("%9s    ", productos[pasada]);
	for (i = 0;i < VENDEDORES;i++)
	{
		printf(" %7s %3d  ",nombre[i], ventas[i][pasada]);
	}
	printf("\n");
	return;
}
void ordenarEimprimirRanking(int ventas[][PRODUCTOS], char productos[][LARGO],char *p[], char nombre[][LARGO])
{
	int vendedor = 0; // Variable que uso como indice del producto analizado.
	int pasada = 0;
	int j = 0;
	int temp1;
	char* tempP;
	printf("\n\nProducto               cantidad de ventas por vendedor: \n\n");
	for (vendedor = 0;vendedor < PRODUCTOS;vendedor++)
	{
		iniciarPunteros(nombre, p); // Reinicio los punteros (sino,  solo la primer fila coincidia. )
		for (pasada = 0;pasada < VENDEDORES;pasada++)
		{
			j = pasada - 1;
			tempP = p[pasada];
			temp1 = ventas[pasada][vendedor];
			while (j >= 0 && temp1 > ventas[j][vendedor])
			{
				ventas[j + 1][vendedor] = ventas[j][vendedor];
				p[j + 1] = p[j];
				j--;
			}
			ventas[j + 1][vendedor] = temp1;
			p[j + 1] = tempP;
		}
		imprimirRanking(productos,ventas, vendedor, p);
	}

	return;
}
void totalPorVendedor(const int ventas[][PRODUCTOS], int ventasTotales[])
{
	int i = 0;
	int j = 0;
	for (i = 0;i < VENDEDORES;i++)
	{
		ventasTotales[i] = 0; // Reinicio y elimino el contenido "Basura".
		for (j = 0;j < PRODUCTOS;j++)
		{
			ventasTotales[i] += ventas[i][j];
		}
	}
	return;
}
void imprimirVentasTotales(char nombre [][LARGO], int ventasPV[])
{
	int i = 0;
	int j;
	int posMIN;
	int pasada = 0;
	char tempN[LARGO];
	int temp;
	for (pasada = 0;pasada < VENDEDORES;pasada++)   // Previo a la impresion,  ordeno por seleccion,  lo cual me permite 
	{                                           	// usar varios criterios de ordenacion,  por ejemplo,   si el numero 
		posMIN = pasada;                            // de ventas coincide,  desempata el orden alfabetico.
		temp = ventasPV[pasada];                   
		strcpy(tempN, nombre[pasada]);
		for (j = posMIN;j < VENDEDORES;j++)
		{
			if (ventasPV[j] > ventasPV[posMIN])
			{
				posMIN = j;
			}
			else if(ventasPV[j]==ventasPV[posMIN] && strcmp(nombre[j], nombre[posMIN])<0)
			{
				posMIN = j;
			}
		}
		ventasPV[pasada] = ventasPV[posMIN]; // Efectuo el swap de ventas.
		ventasPV[posMIN] = temp;
		strcpy(nombre[pasada], nombre[posMIN]); // Efectuo el swap de cadenas mediante la funcion strcpy.
		strcpy(nombre[posMIN], tempN);
	}
	printf("\n\nVendedor         ventas totales\n");
	for (i = 0;i < VENDEDORES;i++)
	{
		printf("%6s                      %3d  \n\n", nombre[i], ventasPV[i]);
	}
	return;
}
int buscarVentas(char clave[], char nombre[][LARGO])
{
	int i = 0;
	int j = 0;
	char copiaClave[LARGO];
	char copiaNOMBRES[VENDEDORES][LARGO];
	strcpy(copiaClave, clave); // Creo una copia de la clave,  para pasar a minuscula,  y posteiormente la paso a minusculas (la copia es para no alterar la clave original).
	while (copiaClave[i] != '\0')
	{
		copiaClave[i] = tolower(copiaClave[i]);
		i++;
	}
	copiaClave[i] = '\0';           // Agrego a mano el terminador \0.
	for (i = 0;i < VENDEDORES;i++)  // Copio la matriz de caracteres de nombres,  para no alterar el arreglo de cadenas original.
	{
		strcpy(	copiaNOMBRES[i], nombre[i]);
}
	for (i = 0;i < VENDEDORES;i++)
	{
		j = 0; // Reinicio del indice de columnas.
		while (copiaNOMBRES[i][j] != '\0')
		{
			copiaNOMBRES[i][j] = tolower(copiaNOMBRES[i][j]);
			j++;
}
		copiaNOMBRES[i][j] = '\0'; // Agrego a mano el terminador \0.
	}
	for (i = 0;i < VENDEDORES;i++)
	{
		if (strcmp(copiaClave, copiaNOMBRES[i]) == 0) return i;
	}
	return -1;
}
void menu(void)
{
	printf("Dese continuar?\n");
	printf("1 consultar ventas por vendedor\n");
	printf("2 salir    ");
	return;
}
int main(void)
{
	srand(time(NULL));
	int hallado=0;
	int opcion = 0;
	char clave[LARGO];
	int totalPV[VENDEDORES];  // Arreglo auxiliar para guardar el total de ventas por cada vendedor.
	int copiaV[VENDEDORES][PRODUCTOS];
	int ventas[VENDEDORES][PRODUCTOS];
	char nombres[VENDEDORES][LARGO] = { "Ramiro","Juan","Carla","Felipe" };
	char productos[PRODUCTOS][LARGO] = { "Regla","Lata","Auto","Botella","Peluche","Termo" };
	char* nombresPtr[VENDEDORES]; // Arreglo de puntero a caracter para ordenar por subindice los nombres.
	iniciarPunteros(nombres, nombresPtr);
	cargarVentas(ventas);
	copiarMatriz(ventas, copiaV);
	imprimirVentas(ventas, nombres, productos);
	ordenarEimprimirRanking(copiaV, productos, nombresPtr, nombres);
	totalPorVendedor(ventas, totalPV);
	imprimirVentasTotales(nombres, totalPV);
	do {
		menu();
		scanf("%d", &opcion);
		switch (opcion)
		{
		case 1:
		{
			printf("\nIngrese el nombre del vendedor\n");
			scanf("%80s", clave);
			hallado = buscarVentas(clave, nombres);
			if (hallado != -1)
			{
				printf("\nEl vendedor %s  tiene un total de %d ventas\n\n", nombres[hallado], totalPV[hallado]);
			}
			else printf("Vendedores \"  %s \" no hallado\n\n", clave);
		}break;
		case 2: printf("\n\nGracias por usar este programa!!\n\n");break;

		default: printf("\nOpcion invalida\n");break;
		}
	} while (opcion != 2);
	return 0;
}
