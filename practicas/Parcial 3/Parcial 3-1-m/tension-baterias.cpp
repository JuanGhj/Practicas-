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
void iniciarPunteros(double* arr[], double* tension, int N, int contador[])
{
    int i = 0;
    for (i = 0;i < N;i++)
    {
        arr[i] = &tension[i];
        contador[i] = i + 1;  // Aprovecho el bucle for para cargar el arreglo auxiliar para imprimir el N de celda.  Posteriormente se va a cambiar de orden con la ordenacion.
    }
    return;
}
void cargarValoresDeTension(double arr[], int N)
{
    int i = 0;
    for (i = 0;i < N;i++)
    {
        *(arr + i) = rand() % 4 + (rand()%13)/10.0; // El primer termino genera valores aleatorios entre 0 y 3
                                                   // El segundo termino genera numero aleatorios entre 0 y 1.2
    }
    return;
}
void ImprimirArreglo(double *arr[], int A[],int N)
{
    int i = 0;
    for (i = 0;i < N;i++)
    {
        printf("%2d            %.2lf  \n", A[i], *arr[i]);
    }
    return;
}
void ordenarTension(double *arr[],int N, int contador[])
{
    int pasada = 0;
    int j = 0;
    int tempC=0;
    double temp;
    double *tempP;
    for (pasada = 0;pasada < N;pasada++)   // Ordeno con algoritmo de incersion.  El criterio de ordenacion,  es la tension,  menor a mayor.
    {
       tempP = arr[pasada];
        tempC = contador[pasada];
        temp = *arr[pasada];
        j = pasada - 1;
        while (j >= 0 && *arr[j] > temp)   // Como debo mantener la concordancia con el valor de celda
                                           // lo que intercambio en el arreglo de tension (mediante el
                                           // arreglo de punteros como subindices) tambien debo hacerlo
                                           // en el arrreglo auxiliar contador de celdas.
        {
          arr[j + 1] = arr[j];
            contador[j + 1] = contador[j];
            j--;
        }
        arr[j + 1] = tempP;
        contador[j + 1] = tempC;
    }
    return;
}
int main()
{
    srand(time(NULL));
    const int N = 10;
    int contador[N]; // Arreglo auxiliar de tipo entero para imprimir las celdas.
    double tension[N];
    double* Arr[N]; // Arreglo de punteros para ordenar por subindice.
    cargarValoresDeTension(tension, N);
    iniciarPunteros(Arr, tension, N, contador);
    printf("Valores originales");
    printf("\nCelda          valor de tension\n");
    ImprimirArreglo(Arr,contador ,N);
   ordenarTension(Arr, N, contador);
    printf("Valores de tension ordenados de mayor a menor");
    printf("\nCelda          valor de tension\n");
    ImprimirArreglo(Arr, contador, N);
    return 0;
}