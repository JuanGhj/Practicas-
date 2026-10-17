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
#include <string.h>
#include <time.h>
#define LONGITUD 21
typedef struct
{
    char marca [LONGITUD];
    char modelo[LONGITUD];
    int anio;
    char serie[LONGITUD];
}Computadora;

void imprimirElementos(int nro, Computadora *pc)
{
    int i = 0;
    printf("       Marca      modelo        a%co       nro. serie   \n", 164);
    for (i = 0;i < nro;i++)
    {
        printf("%11s     %11s      %d        %4s   ", pc[i].marca, pc[i].modelo, pc[i].anio, pc[i].serie);
        puts("");
    }
    return;
}
void ordenarPorMarca(int nro, Computadora* pc)
{
    int j = 0;
    int pasada = 0;
    int posMin;
    Computadora temp;
    for (pasada = 0;pasada < nro;pasada++)
    {
        temp = pc[pasada];
        posMin = pasada;
        for (j = posMin;j < nro;j++)
        {
            if (strcmp(pc[j].marca, pc[posMin].marca) < 0)posMin = j;
            else if (strcmp(pc[j].marca, pc[posMin].marca) == 0 && pc[j].anio < pc[posMin].anio)posMin = j;  // en caso de coincidir alfabeticamente,  desempata por año (menor primero)
        }
        pc[pasada] = pc[posMin];
        pc[posMin] = temp;
    }
    imprimirElementos(nro, pc);
    return;
}
void cargarElementos(int nro, Computadora *pc)
{
    int i = 0;
    for (i = 0;i < nro;i++)
    {
        printf("Ingrese la marca de la pc %d:  ", i + 1);
        scanf("%20s",pc[i].marca);
        printf("Ingrese el modelo de la pc %d:  ", i + 1);
        scanf("%20s",pc[i].modelo);
        printf("Ingrese el a%co de la pc %d:  "  ,164, i + 1);
        scanf("%d",&pc[i].anio);
        printf("Ingrese el N de serie de la pc %d:  ", i + 1);
        scanf("%20s",pc[i].serie);
        printf("\n\n");
    }
    ordenarPorMarca(nro, pc);
    return;
}
void generarArregloDinamico(int nro)
{
    Computadora* pcGamer;
    pcGamer = (Computadora*)calloc(nro, sizeof(Computadora));

    cargarElementos(nro, pcGamer);
    free(pcGamer);
    return;
}
int main()
{
    int nroPc=0;
    printf("\nIngrese el numero de computadoras a ingresar:  ");
    scanf("%d", &nroPc);
    generarArregloDinamico(nroPc);
    return 0;
}