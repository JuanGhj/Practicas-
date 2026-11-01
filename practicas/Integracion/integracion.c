/*
NOMBRE: Juan Jose González
LEGAJO: 23456
LABORATORIO:
EJERCICIO:

									   */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#define LARGO 81
typedef struct
{
	char nombre[LARGO];
	int puntos;
	int golesFavor;
	int golesContra;
}Equipo;
void pedirMemoriaInicial(Equipo** p, int* cantidad)
{
	Equipo* temp;
	temp = (Equipo*)calloc(*cantidad, sizeof(Equipo));
	if (temp != NULL)
	{
		*p = temp;
	}
	return;
}
void cargarEquipos(Equipo* p, int* cantidad, const int capacidad)
{
	int i = 0;
	for (i = *cantidad;i < capacidad;i++)
	{
		printf("Equipo %d\n", *cantidad + 1);  // En el caso de la cadena no hace falta usar & ya que en si el nombre del arreglo en un puntero al primer elemento del arreglo,  caso contrario con las variables de tipo entero,  donde es necesario usar el &.
		printf("Nombre del equipo:  ");
		scanf("%20s",p[i].nombre);
		/*

		printf("\nPuntos del equipo:  ");
		scanf("%d", &p[i].puntos);
		printf("\nGoles a favor:  ");
		scanf("%d", &p[i].golesFavor);
		printf("\nGoles en contra:  ");
		scanf("%d", &p[i].golesContra);

		*/
		*cantidad = *cantidad + 1;
	}
	return;
}
void cargarGoles(int* goles, int* cantidad)
{
	int i = 0;
	int j = 0;

	for (i = 0;i < *cantidad;i++)
	{
		for (j = 0;j < *cantidad;j++)
		{
			if (j != i)
			{
				goles[*cantidad * i + j] = rand() % 5;
			}
			else if (j == i)
			{
				goles[(*cantidad*i) + i] = 0;
			}
		}

	}
/*
	for (i = 0;i < *cantidad;i++)
	{
		for (j = 0;j < *cantidad;j++)
		{
			{
				printf("%4d ",goles[(i * (*cantidad)) + j]);
			}
		}
		puts("");
	}
	*/ 
	// Era para verificar que los goles se carguen bien
	return;

}
void cargarGolesEnEquipos(Equipo* e, int* cantidad, int* vector)
{
	int i = 0;
	int j = 0;
	for (i = 0;i < *cantidad;i++)
	{
		for (j = 0;j < *cantidad;j++)
		{
			e[i].golesFavor =e[i].golesFavor+ vector[(i * (*cantidad)) + j];
			e[i].golesContra = e[i].golesContra+vector[(j*(*cantidad))+i];
		}
	}
	return;
}
void imprimirEquipos(Equipo *p, int *goles, int *cantidad)
{
	int i = 0;
	int j = 0;
	int k = 0;
	printf("Tabla de equipos\n");
	for (i = 0;i < *cantidad;i++)
	{
		printf("  %6s", p[i].nombre);
	}
	printf("\n");
	for (i = 0;i < *cantidad;i++)
	{
			printf("%s  ", p[i].nombre);
		for (k = 0;k < *cantidad;k++)
		{
			printf("%7d", goles[(i*(*cantidad))+k]);
		}
		printf(" puntos:  %d",p[i].puntos);
		printf("\n\n");
	}
	return;
}
void asignarPuntos(Equipo* p, int* goles, int* cantidad)
{
	int i = 0;
	int j = 0;
	for (i = 0;i < *cantidad;i++)
	{
		p[i].puntos = 0; // Inicializo puntos en cero,  por si contiene "basura" dentro.
		for (j = 0;j < *cantidad;j++)
		{
			if (i == j)p[i].puntos = p[i].puntos + 0;
			else if (goles[(i * (*cantidad) + j)] > goles[(j * (*cantidad) + i)])p[i].puntos = p[i].puntos + 3;
			else if (goles[(i * (*cantidad) + j)] == goles[(j * (*cantidad) + i)])p[i].puntos = p[i].puntos + 1;
		}
	}


	return;
}
void ordenar(Equipo* e, int* cantidad, int* goles)
{
	int j = 0;
	int equipo = 0;
	int pasada = 0;
	Equipo temp;
	int posMin;
	for (pasada = 0;pasada < *cantidad;pasada++)
	{
		posMin = pasada;
		temp = e[pasada];
		for (j = posMin;j < *cantidad;j++)
		{
			if (e[j].puntos > e[posMin].puntos) posMin = j;
			else if (e[j].puntos == e[posMin].puntos && e[j].golesFavor > e[posMin].golesFavor) posMin = j;  
			else if (e[j].puntos == e[posMin].puntos && e[j].golesFavor == e[posMin].golesFavor && e[j].golesContra < e[posMin].golesContra) posMin = j;
			else if (e[j].puntos == e[posMin].puntos && e[j].golesFavor == e[posMin].golesFavor && e[j].golesContra < e[posMin].golesContra && strcmp(e[j].nombre, e[posMin].nombre)) posMin = j;
		}

		// El primer criterio, son los puntos por equipo, si estos coinciden, el criterio de desempate es el siguiente
/*
		1) Goles a favor
		2) Goles en contra
		3) Orden alfabetico
		< Se pasa a sigueinte instancia en caso de seguir empatando >
*/
		// Swap:
		e[pasada] = e[posMin];
		e[posMin] = temp;
	}
	return;
}
void tablaDePosiciones(Equipo* e, int* cantidad)
{
	int i = 0;
	int j = 0;
	printf("Equipo N         Puntos      GF     GC       Dif\n");
	for (i = 0;i < *cantidad;i++)
	{
		printf("\nEquipo %6s        %d         %d         %d         %d  ", e[i].nombre, e[i].puntos, e[i].golesFavor, e[i].golesContra, e[i].golesFavor - e[i].golesContra);
	}

	return;
}

int buscarEquipo(Equipo *p, char *clave, int *cantidad)
{
	int i = 0;
	int j = 0;
	char auxiliar[LARGO];
	char auxiliar2[LARGO];
	strcpy(auxiliar, clave);
	while (auxiliar[i] != '\0')
	{
		auxiliar[i] = tolower(auxiliar[i]); // Creo una copia -> Paso a minuscular -> Agrego terminador \0 a mano.
		i++;
	}
	auxiliar[i] = '\0';

	for (i = 0;i < *cantidad;i++) // Empleo busqueda secuencial, ya que el arreglo esta ordenado por pts y no por orden alfabetico.
	{
		strcpy(auxiliar2, p[i].nombre);
		while (auxiliar2[j] != '\0')
		{
			auxiliar2[j] = tolower(auxiliar2[j]);
			j++;
		}
		if (strcmp(auxiliar, p[i].nombre) == 0)return i;
		j = 0; // Reinicio del indice j.
	}
	return-1;
}

void ataqueYDefensa(Equipo* e, int* cantidad)
{
	int i = 0;
	int min=0;
	int max=0;
	int mejorDefensa = e[i].golesContra;
	int mejorAtaque = e[i].golesContra; // Inicializo varias variables con los goles en contra y favor del primer equipo,  ya que igualmente,  se van a comparar todos los equipos.
	for (i = 0;i < *cantidad;i++)
	{
		if (e[i].golesFavor > mejorAtaque)
		{
			mejorAtaque = e[i].golesFavor;
			max = i;
		}
		if (e[i].golesContra < mejorDefensa)
		{
			mejorDefensa = e[i].golesContra;
			min = i;
		}
	}
	printf("\nMejor ataque: %s (gf:  %d) ", e[max].nombre, mejorAtaque);
	printf("\nMejor Defensa: %s  (gc: %d", e[min].nombre, mejorDefensa);
	return;
}
int main()
{
	srand(time(NULL));
	Equipo* e;
	int cantidad = 0;
	int capacidad = 0;
	int* goles;
	int hallado=0;
	char clave[LARGO];
	printf("Cuantos equipos desea anotar?");
	scanf("%d", &capacidad);
	pedirMemoriaInicial(&e, &capacidad); // Paso por referencia la direccion de memoria del puntero, para que se pueda modificar el mismo
	cargarEquipos(e, &cantidad, capacidad);
	
	goles = (int*)calloc(cantidad * cantidad, sizeof(int));
	cargarGoles(goles, &cantidad);
	cargarGolesEnEquipos(e, &cantidad, goles);
	asignarPuntos(e, goles, &cantidad);
	printf("Equipos: \n");
	imprimirEquipos(e,goles,&cantidad);
	// Libero memoria pedida.
	ordenar(e, &cantidad, goles);
	printf("Equipos ordenados por puntos de mayor a menor\n");
	imprimirEquipos(e, goles, &cantidad);
	tablaDePosiciones(e, &cantidad);
	printf("\n\nBuscar equipo:  ");
	scanf("%21s", clave);
	hallado = buscarEquipo(e, clave, &cantidad);
	if (hallado == -1)
	{
		printf("Equipo \"%s\" no hallado", clave);
	}
	else printf("Equipo %s\nPts: %d\nGc: %d\nGf: %d" , e[hallado].nombre, e[hallado].puntos, e[hallado].golesContra, e[hallado].golesFavor);	
	ataqueYDefensa(e, &cantidad);
	free(e);     // Libero la memoria pedida para el arreglo de int.
	free(goles); // Libero la memoria pedida para el arreglo de tipo struct.
	return 0;
}