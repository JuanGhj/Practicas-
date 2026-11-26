/*
Autores:
> Ajalla Nicolás -> 23404
> González Juan -> 23456

Proyecto integrador 4
                                       */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define LARGO 31
#define ENTRADA "contactos.bin"
#define SALIDA "contacto.txt"
typedef struct
{
    char nombre[LARGO];
    char apellido[LARGO];
    int numT;
    char correo[LARGO];
}Contacto;

int buscarNombre(char n[], Contacto* p, int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        if (_stricmp(n, p[i].nombre) == 0)return i;
    }
    return -1;
}
void cargarContactos(Contacto* p, int capacidad, int* cantidad)
{
    int i = 0;
    for (i = *cantidad;i < capacidad;i++)
    {
        printf("\nContacto N: %d", i + 1);
        printf("\nNombre:  ");
        scanf("%30s", p[i].nombre);
        printf("\nApellido:  ");
        scanf("%30s", p[i].apellido);
        printf("\nTelefono:  ");
        scanf("%d", &p[i].numT);
        printf("\nCorreo:  ");
        scanf("%30s", p[i].correo);
        printf("\n");
        *cantidad = *cantidad + 1;
    }

    return;
}
void imprimirContactos(Contacto* a, int cantidad)
{
    int i;
    for (i = 0;i < cantidad; i++)
    {
        printf("\n\nContactos %d\n", i+1);
        printf("Nombre  %s\n", a[i].nombre);
        printf("Apellido %s\n", a[i].apellido);
        printf("Telefono %d\n", a[i].numT);
        printf("Correo %s", a[i].correo);
        printf("\n\n");
    }
    return;
}
void eliminar(Contacto* p, int eliminado, int* cantidad)
{
    int i = eliminado; // El -1 se contempla en el [i+1] del bucle while
    while (i < *cantidad -1)
    {
        p[i] = p[i + 1];
        i++;
    }
    *cantidad = *cantidad - 1;
}

void editar(Contacto* p, int editado) {
    printf("Ingrese la nueva informaci%cn\n", 162);
    printf("nombre:  ");
    scanf("%30s", p[editado].nombre);
    printf("apellido:    ");
    scanf("%30s", p[editado].apellido);
    printf("telefono:    ");
    scanf("%d", &p[editado].numT);
    printf("correo:  ");
    scanf("%30s", p[editado].correo);
    printf("\n");
}
void pedirMemoria(Contacto** p, int *capacidad)
{
    Contacto* temp;
    *capacidad = *capacidad + 1;
    temp = (Contacto*)realloc(*p, *capacidad * sizeof(Contacto));
    if (temp == NULL)
    {
        printf("\nNo se pudo reasignar memoria\n");
        exit(EXIT_FAILURE);
    }
    *p=temp;
    return;
}
void menu(void)
{
    printf("\nCuantos contactos desea ingresar\n");
    return;
}
void menu2(void)
{
    printf("Desea:\n0_Salir\n1_Agregar contactos\n2_imprimir\n3_Buscar contacto\n4_Editar contacto\n5_Eliminar contacto\n6_Exportar\n");
    return;
}
void pedirCantidad(int* q)
{
    printf("Cuantos contactos se van a ingresar?    ");
    scanf("%d", q);
}

void exportar( Contacto* p, int cantidad)
{
    int i = 0;
    FILE* binario = NULL;  // Binario
    FILE* secuencial = NULL;
    binario = fopen(ENTRADA, "wb+");
    if (binario == NULL) {
        printf("\nError al abrir el archivo de acceso directo\n");
        exit(EXIT_FAILURE);
    }
    printf("\nSe creo el archivo \"contactos.bin\"\n");
    secuencial = fopen(SALIDA, "w+");
    if (secuencial == NULL) {
        printf("\nError al abrir el archivo de acceso secuencial\n");
        exit(EXIT_FAILURE);
    }
    printf("\nSe creo el archivo \"contacto.txt\"\n");
    fwrite(p, sizeof(Contacto), cantidad, binario);
    for (i = 0;i < cantidad;i++)
    {
        fprintf(secuencial, "%s %s %d %s\n", p[i].nombre, p[i].apellido, p[i].numT, p[i].correo);
    }
    fclose(binario);
    fclose(secuencial);
}
int main()
{
    Contacto* contactos;
    int cantidad = 0;
    int capacidad = 0;
    char clave[LARGO];
    int eliminado = 0;
    int opcion = 0;
    int editado = 0;
    pedirCantidad(&capacidad);
    while (capacidad <= 0)
    {
        printf("Ingrese un valor mayor que 0\n");
        pedirCantidad(&capacidad);
    }
    Contacto* temp;
    temp = (Contacto*)calloc(capacidad, sizeof(Contacto));
    if (temp == NULL)
    {
        printf("\nError al asignar memoria\n");
        exit(EXIT_FAILURE);
    }
    contactos = temp;
    cargarContactos(contactos, capacidad, &cantidad);
    do {
        menu2();

        scanf("%d", &opcion);
        switch (opcion)
        {
        case 0:
        {
            printf("\nPrograma finalizado\n");
        };break;
        case 1:
        {
            int agregar = 0;
            printf("Desea a%cadir un nuevo contacto?\n1_Si\n0_No", 164);
            scanf("%d", &agregar);
            if ((agregar == 1) && (capacidad==cantidad))
            {
      
                pedirMemoria(&contactos, &capacidad); // El segundocondicional es ultil para pedir memoria solo si se necesita,  por ejemplo si se elimina un contacto y se quiere ingresar otro,  se tiene un elemento disponible al final del arreglo por lo que no es necesario pedir mas memoria.
                cargarContactos(contactos, capacidad, &cantidad);
            }
            else if (agregar == 1) {
                cargarContactos(contactos, capacidad, &cantidad);
            }
            else if (agregar != 1 && agregar != 0) {
                printf("\nopcion inavlida\n");
            }

        }; break;
        case 2:
        {
            imprimirContactos(contactos, cantidad);
        };break;
        case 3:
        {

            printf("\nIngresar el nombre:     ");
            scanf("%30s", clave);
            int hallado = buscarNombre(clave, contactos, cantidad);
            if (hallado != -1) {
                printf("Coincidencia: \n");
                printf("Nombre:     %s\n", contactos[hallado].nombre);
                printf("Apellido:   %s\n", contactos[hallado].apellido);
                printf("Telefono:   %d\n", contactos[hallado].numT);
                printf("Correo:     %s\n", contactos[hallado].correo);
            }
            else {
                printf("Contacto \"%s\" no encontrado\n", clave);
            }
        };break;
        case 4:
        {
            printf("\nQue contacto desea editar:  ");
            scanf("%30s", clave);
            if ((editado = buscarNombre(clave, contactos, cantidad)) != -1)
            {
                editar(contactos, editado);
            }
            else {
                printf("\nContacto \"%s\" no encontrado\n", clave);
            }
        };break;
        case 5:
        {
            printf("\nQue contacto desea eliminar:  ");
            scanf("%30s", clave);
            if ((eliminado = buscarNombre(clave, contactos, cantidad)) != -1) {

                eliminar(contactos, eliminado, &cantidad);
            }
            else {
                printf("\nContacto \"%s\" no encontrado\n", clave);
            }
        };break;
        case 6: {
            exportar(contactos, cantidad);
        };break;
        default:
        {
            printf("\nOpci%cn invalida\n", 162);
        };break;
        }
    } while (opcion != 0);
    free(contactos);
    return 0;
}