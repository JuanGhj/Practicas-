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
#define LARGO 21
typedef struct
{
	char cliente[LARGO];
	char producto[LARGO];
	float monto;
}Pedido;
void menu1(void) // Menu inicial
{
	printf("\n\nDese cargar pedidos\n0=no    1=si   \n");
	return;
}
void menu2(void)
{
	printf("\n\nDese cargar otro pedidos\n0=no     1=si    2=imprimir pedidos    3= buscar un pedido por cliente\n");
	return;
}
void expandirMemoria(Pedido** p, int* capacidad)
{
	Pedido* temp;                                              // Variable temporal de tipo Pedido (struct).
	*capacidad *= 2;
	temp = (Pedido*)realloc(*p, *capacidad * (sizeof(Pedido))); // Duplico las dimensiones del arreglo con el llamado a esta funcion.
	if (temp != NULL) *p = temp;                               // Solo se agrega memoria,  si el administrador de memoria da un puntero distinto del nulo. 
	return;
}
void cargarPedidos(Pedido* p, int* cantidad, int i) // Capacidad: memoria disponible
                                                    // Cantidad:  memoria ocupada
{

	printf("Pedido N%d", i + 1);
	printf("\nCliente N%d:  ", i + 1);
	scanf("%20s", p[i].cliente);
	printf("\nProducto N%d:  ", i + 1);
	scanf("%20s", p[i].producto);
	printf("\nmonto:  ");
	scanf("%f", &p[i].monto);
	*cantidad = *cantidad + 1;                     // Con cada iteracion sumo +1,  en el contador de la memoria ocupada.

	return;
}
void imprimirPedidos(Pedido* p, int* cantidad)     // Paso por referencia cantidad,  para que solo imprima elementos existentes,  y no todo el arreglo (Que puede contener basura).
{
	int i = 0;
	printf(" N     Cliente      Producto      monto\n");
	for (i = 0;i < *cantidad;i++)
	{
		printf("%2d     %6s      %8s      %2.2f   \n", i + 1, p[i].cliente, p[i].producto, p[i].monto);
	}
	return;
}
void ordenarPorMonto(Pedido* p, int* cantidad)
{
	int j = 0;
	int pasada = 0;
	int posMin;
	Pedido temp;
	for (pasada = 0;pasada < *cantidad;pasada++)
	{
		temp = p[pasada];
		posMin = pasada;
		for (j = posMin;j < *cantidad;j++)
		{
			if (p[j].monto > p[posMin].monto) posMin = j;
			else if (p[j].monto == p[posMin].monto && strcmp(p[j].cliente, p[posMin].cliente) < 0)posMin = j; // Desempate alfabetico,  en caso de coincidir el monto.
		}
		p[pasada] = p[posMin];
		p[posMin] = temp;
	}
	return;
}


int buscarPedido(Pedido* p, const int* cantidad, char* clave)
{
	int i = 0;
	int j = 0;
	char copiaC[LARGO];              // Copia de la clave para no alterar la original.
	char copiaN[LARGO];              // Copia del cliente a analizar
	strcpy(copiaC, clave);           // Creo una copia de la clave.
	while (copiaC[i] != '\0')
	{
		copiaC[i] = tolower(copiaC[i]);
		i++;
	}
	copiaC[i] = '\0';                // Agrego el terminador \0 a mano.
	                                 // A diferencia de los ejercicios anteriores,  en este no creo una copia total del arreglo de cadenas a analizar,  sino que copio y paso a minusculas 1 nombre por iteracion.
	for (i = 0;i < *cantidad;i++)
	{
		strcpy(copiaN, p[i].cliente);
		j = 0;                       // Reinicio del subindice de columnas.
		while (copiaN[j] != '\0')
		{
			copiaN[j] = tolower(copiaN[j]);
			j++;
		}
		copiaN[j] = '\0';           // Agrego el terminador \0 a mano.
		if (strcmp(copiaN, copiaC) == 0)return i;
	}
	return -1;
}
int main()
{
	int cantidad = 0;              // Tamano inicial del arreglo,  en caso de llamar a la funcion 'PedirMemoriaInicial'.
	int opcion = 0;
	int hallado = 0;
	int contadormenu = 0;
	char clave[LARGO];
	int capacidad = 2;
	Pedido* p = (Pedido*)calloc(capacidad, sizeof(Pedido));     // Pido memoria para 2 pedidos.
	int i = 0;
	printf("\nBienvenido");
	do
	{
		if (contadormenu == 0)
		{
			menu1();
			contadormenu++;
		}
		else menu2();

		scanf("%d", &opcion);
		switch (opcion)
		{
		case 0:
		{
			printf("\nGracias por usar este programa!!\n\n");
		};break;
		case 1:
		{
			if (cantidad == capacidad)
			{
				expandirMemoria(&p, &capacidad);
			}
			cargarPedidos(p, &cantidad, i);
			i++;
		};break;
		case 2:
		{
			printf("Pedidos ordenados por monto --> de mayor a menor\n:::::::::::::::::::::::::::::::::::::::::::::::::.\n\n");
			ordenarPorMonto(p, &cantidad);
			imprimirPedidos(p, &cantidad);
		};break;
		case 3:
		{
			printf("Ingrese el cliente:  ");
			scanf("%20s", clave);
			hallado = buscarPedido(p, &cantidad, clave);
			if (hallado != -1)
			{
				printf("\nPrimir conincidencia (mayor monto):\n");
				printf("\n%s   %s    %2.2f\n\n", p[hallado].cliente, p[hallado].producto, p[hallado].monto);
			}
			else printf("\nCliente %s no hallado\n", clave);
		};break;
		default:
		{
			printf("\nOpcion invalida\n");
		};break;
		}
	} while (opcion != 0);
	free(p);                                // Libero la memoria pedida <Inicial y realocada>.
	return 0;
}