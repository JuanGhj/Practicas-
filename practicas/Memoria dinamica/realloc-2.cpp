/*
NOMBRE: Juan Jose González
LEGAJO: 23456
LABORATORIO: Practica Realloc
EJERCICIO: -

									   */



									   /*Arrancá con capacidad para 2 productos (calloc), igual que en el ejercicio de pedidos: cantidad/capacidad, duplicando con realloc cuando se llena (ya lo tenés resuelto, reusalo).
									   Menú con: cargar producto, imprimir, ordenar por precio (de menor a mayor, con desempate alfabético por nombre), buscar por nombre, eliminar por nombre, salir.
									   La parte nueva — eliminar un producto:
									   Buscá la posición del producto por nombre (reusá tu función de búsqueda).
									   Si lo encontrás, tenés que “tapar el hueco”: cada elemento que está después de la posición eliminada se corre un lugar hacia atrás (el que estaba en i+1 pasa a i, el de i+2 pasa a i+1, y así sucesivamente hasta el final).
									   Decrementá cantidad en 1.
									   Pensá: ¿el bucle que corre los elementos va de adelante hacia atrás, o de atrás hacia adelante? Probá los dos mentalmente con un ejemplo de 4 elementos y fijate cuál te pisa datos que todavía no copiaste y cuál no.
									   Desafío extra (opcional, para estirar el tema del realloc): si después de eliminar varias veces cantidad queda muy por debajo de capacidad (por ejemplo, cantidad <= capacidad / 4), achicá la memoria a la mitad con realloc — mismo mecanismo que usaste para agrandar, pero ahora reduciendo. Vas a necesitar el mismo truco del doble puntero que ya entendiste.

									   Por qué vale la pena: insertar al final de un arreglo es fácil (solo escribís en la próxima posición libre), pero eliminar del medio te obliga a mover datos para no dejar “agujeros” — es un patrón que vas a necesitar todo el tiempo de acá en adelante, y es un error clásico mezclar la dirección del bucle de corrimiento y terminar pisando o duplicando un elemento.*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#define LARGO 21
typedef struct
{
	char nombre[LARGO];
	float precio;
	int stock;

}Producto;	
void pedirMemoriaAuxiliar(Producto** p, int* capacidad)
{
	Producto* temp;
	*capacidad *= 2;
	temp = (Producto*)realloc(*p, *capacidad * sizeof(Producto));
	if (temp != NULL) *p = temp;
}
void menu(void)
{
	printf("\n1  Cargar producto\n");
	printf("2  Imprimir\n");
	printf("3  Ordenar por precio de menor a mayor\n");
	printf("4  Buscar por nombre\n");
	printf("5 Eliminar por nombre\n");
	printf("6  Salir\n");

	return;
}
void ordenarPorPrecio(Producto* p, int* cantidad)
{
	int j = 0;
	int pasada = 0;
	int posMin = 0;
	Producto temp;
	for (pasada = 0;pasada < *cantidad;pasada++)
	{
		posMin = pasada;
		temp = p[pasada];
		for (j = posMin;j < *cantidad;j++)
		{
			if (p[j].precio < p[posMin].precio)posMin = j;
			else if (p[j].precio == p[posMin].precio && strcmp(p[j].nombre, p[posMin].nombre) < 0) posMin = j;
		}
		p[pasada] = p[posMin];
		p[posMin] = temp;
	}
	return;
}
void cargarProdcutos(Producto** p, int* capacidad, int* cantidad)
{
	static int i = 0;
		if (*cantidad == *capacidad)
		{
			pedirMemoriaAuxiliar(p, capacidad);
		}
		printf("Producto %d\n",i+1);
		printf("\nNombre:  ");
		scanf("%20s", (*p)[*cantidad].nombre);
		printf("Precio:  ");
		scanf("%f", &(*p)[*cantidad].precio);
		printf("\nStock:  ");
		scanf("%d", &(*p)[*cantidad].stock);
		(*cantidad) = (*cantidad)+1;
	
	return;
}
void imprimir(Producto* p, int* cantidad)
{
	int i = 0;
	printf("Producto      precio       stock\n");
	for (i = 0;i < *cantidad;i++)
	{
		printf("%11s   %2.2f    %4d\n", p[i].nombre, p[i].precio, p[i].stock);
	}
	return;
}
int bucarPorNombre(Producto* p, int* cantidad, char *clave)
{
	int i = 0;
	int j = 0;
	char copiaC[LARGO];
	char copiaN[LARGO];
	strcpy(copiaC, clave);
	for (i = 0;copiaC[i] != '\0';i++)
	{
		copiaC[i] = tolower(copiaC[i]);
	}
	copiaC[i] = '\0'; // Agrego el terminador \0 a mano.
	for (i = 0;i < *cantidad;i++)
	{
		strcpy(copiaN, p[i].nombre);
		for (j = 0;copiaN[j] != '\0';j++)
		{
			copiaN[j] = tolower(copiaN[j]);
		}
		copiaN[j] = '\0';
		if (strcmp(copiaC, copiaN) == 0)return i;
	}
	return-1;
}
void menu2(void)
{
	printf("Bienvenido\nQue desea hacer\n\n");
	printf("1 Cargar un producto\n");
	printf("6 Salir    ");
	return;
}
void eliminarProducto(Producto* p, int* cantidad, char *posicion)
{
	int i = 0;
	int eliminar = 0;
	eliminar= bucarPorNombre(p, cantidad, posicion);
	if (eliminar != -1)
	{
		for (i = eliminar;i < *cantidad-1;i++)
		{
			p[i] = p[i + 1];
		}
		*cantidad = *cantidad - 1; // Cada vez que sumaba un producto al arreglo de tipo estructura <Producto>
		//adicionaba a la variable cantidad,  para que las funciones como imprimir 
		// solo impriman elemento existentes,  por lo que si elimino un elemento 
		// debo hacer la operacion inversa (restar 1).
		printf("\nProducto %s eliminado con exito\n", posicion);
	}
	else printf("\nProducto %s no hallado\n",posicion);
	return;
}
int main()
{
	int i = 0;
	int capacidad = 2;
	Producto *p = (Producto*)calloc(capacidad, sizeof(Producto));
	int opcion = 0;
	int cantidad = 0;
	char eliminar [LARGO];
	int hallado=0;
	char clave[LARGO];
	int contadorMenu=0;
	
	do {
	if (contadorMenu == 0)
	{
		menu2();
	}
	else if(contadorMenu%4==0 || contadorMenu==1) // Sirve para volver a imprimir el menu que le indica al usuario lo que puede
		                                          //hacer luego de que el mismo realice alguna interacciones con el programa,
												  // para que no tenga que volver a subir para ller el menu de nuevo.
	{
		menu();
	}
	scanf("%d", &opcion);
		contadorMenu++;
		switch (opcion)
		{
		case 1:
		{
			cargarProdcutos(&p, &capacidad, &cantidad); // Los parametros capacidad y cantidad son pasados por referencia para que funciones distintas de la funcion main puedan modificar sus valores.
		};break;
		case 2:
		{
			imprimir(p, &cantidad);
		};break;
		case 3:
		{
			ordenarPorPrecio(p, &cantidad);
		};break;
		case 4:
		{
			printf("\nIngrese el nombre del producto:  ");
			scanf("%20s", clave);
			hallado=bucarPorNombre(p, &cantidad, clave);
			if (hallado != -1)
			{
				printf("\nCoincidencia: %s    %2.2f    %d\n", p[hallado].nombre, p[hallado].precio, p[hallado].stock);
			}
			else printf("\nProducto \"%s\" no hallado\n", clave);
		};break;
		case 5:
		{
			printf("Que producto desea eliminar:   ");
			scanf("%20s", eliminar);
			eliminarProducto(p, &cantidad, eliminar);

			
		};break;
		case 6:
		{
			printf("\nGracias por usar este programa!!\n\n");
		};break;
		default:
		{
			printf("\nOpcion invalida\n\n");
		};break;
		}
	} 
	while (opcion != 6);
	free(p); // Libero la memoria pedida.

	return 0;
}