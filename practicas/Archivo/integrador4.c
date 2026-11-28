/*


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

int buscarNombre(char n[])
{
    Contacto* p;
    FILE* entrada;
    entrada = fopen(ENTRADA, "rb");

    if (entrada == NULL) {
        printf("\nError al abrir el archivo binario\n");
        return -1;
    }
    fseek(entrada, 0l, SEEK_END);
    int cantidad = ftell(entrada) / sizeof(Contacto);
    p = (Contacto*)calloc(cantidad, sizeof(Contacto));
    fseek(entrada, 0l, SEEK_SET);
    if (p == NULL)
    {
        printf("\nError al asignar memoria dinamica\n");
        exit(EXIT_FAILURE);
    }
    fread(p, sizeof(Contacto), cantidad, entrada);
    for (int i = 0; i < cantidad; i++) {
        if (_stricmp(n, p[i].nombre) == 0)
        {
            free(p);
            fclose(entrada);
            return i;
        }
    }
    free(p);
    fclose(entrada);
    return -1;
}
void cargarContactos()
{
    static int i = 0;
    FILE* entrada;
    Contacto p;
    entrada = fopen(ENTRADA, "ab+");
    if (entrada == NULL)
    {
        printf("\nError al abrir el archivo binario\n");
        exit(EXIT_FAILURE);
    }

    printf("\nContacto N: %d", i + 1);
    printf("\nNombre:  ");
    scanf("%30s", p.nombre);
    printf("\nApellido:  ");
    scanf("%30s", p.apellido);
    printf("\nTelefono:  ");
    scanf("%d", &p.numT);
    printf("\nCorreo:  ");
    scanf("%30s", p.correo);
    printf("\n");
    i++;

    fwrite(&p, sizeof(Contacto), 1, entrada);

    fclose(entrada);
    return;
}
void imprimirContactos()
{
    int i;

    FILE* entrada;
    Contacto* a;
    int cantidad = 0;
    entrada = fopen(ENTRADA, "rb+");

    if (entrada == NULL) {
        entrada = fopen(ENTRADA, "wb+");
        printf("\nArchivo de acceso directo creado con exito\n");
    }
    fseek(entrada, 0l, SEEK_END);
    cantidad = ftell(entrada) / sizeof(Contacto);
    fseek(entrada, 0l, SEEK_SET);
    a = (Contacto*)calloc(cantidad, sizeof(Contacto));
    if (a == NULL)
    {
        printf("\nError al asignar memoria dinamica\n");
        exit(EXIT_FAILURE);
    }
    fread(a, sizeof(Contacto), cantidad, entrada);
    for (i = 0;i < cantidad; i++)
    {
        printf("\n\nContactos %d\n", i + 1);
        printf("Nombre  %s\n", a[i].nombre);
        printf("Apellido %s\n", a[i].apellido);
        printf("Telefono %d\n", a[i].numT);
        printf("Correo %s", a[i].correo);
        printf("\n\n");
    }
    free(a);
    fclose(entrada);
}
void eliminar(int eliminado)
{
    FILE* entrada;
    int i = 0;
    Contacto* p = NULL;
    int cantidad = 0;
    entrada = fopen(ENTRADA, "r+b");
    if (entrada == NULL) {
        printf("\nError al abrir el archivo binario\n");
        exit(EXIT_FAILURE);
    }
    fseek(entrada, 0l, SEEK_END); // final del archivo
    cantidad = ftell(entrada) / sizeof(Contacto);
    fseek(entrada, 0l, SEEK_SET);
    p = (Contacto*)calloc(cantidad, sizeof(Contacto));
    if (p == NULL)
    {
        printf("\nError al asignar memoria dinamica\n");
        exit(EXIT_FAILURE);
    }

    fread(p, sizeof(Contacto), cantidad, entrada);
    fclose(entrada);
    entrada = fopen(ENTRADA, "wb");
    if (entrada == NULL) {
        printf("\nError al abrir el archivo binario\n");
        exit(EXIT_FAILURE);
    }
    // El -1 se contempla en el [i+1] del bucle while
    i = eliminado;
    while (i < cantidad - 1)
    {
        p[i] = p[i + 1];
        i++;
    }
    cantidad = cantidad - 1;
    fseek(entrada, 0l, SEEK_SET);  // -> movemos el puntero al inicio del archivo
    fwrite(p, sizeof(Contacto), cantidad, entrada);
    free(p);
    fclose(entrada);
}

void editar(int editado) {
    FILE* entrada;
    Contacto* p;
    int cantidad = 0;
    entrada = fopen(ENTRADA, "r+b");

    if (entrada == NULL) {
        printf("\nError al abrir el archivo binario\n");
        exit(EXIT_FAILURE);
    }
    fseek(entrada, 0l, SEEK_END);
    cantidad = ftell(entrada) / sizeof(Contacto);
    fseek(entrada, 0l, SEEK_SET);
    p = (Contacto*)calloc(cantidad, sizeof(Contacto));
    if (p == NULL)
    {
        printf("\nError al asignar memoria dinamica\n");
        exit(EXIT_FAILURE);
    }
    fread(p, sizeof(Contacto), cantidad, entrada);

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
    fseek(entrada, 0l, SEEK_SET); // Movemos el puntero al inicio del archivo
    fwrite(p, sizeof(Contacto), cantidad, entrada);
    free(p);
    fclose(entrada);
}
void menu2(void)
{
    printf("Desea:\n0_Salir\n1_Agregar contactos\n2_imprimir\n3_Buscar contacto\n4_Editar contacto\n5_Eliminar contacto\n6_Exportar\n");
    return;
}

void exportar()
{
    int i = 0;
    FILE* entrada = NULL;  // Binario
    FILE* secuencial = NULL;
    Contacto* p = NULL;

    entrada = fopen(ENTRADA, "rb+");
    if (entrada == NULL) {
        printf("\nError al abrir el archivo de acceso directo\n");
        exit(EXIT_FAILURE);
    }
    printf("\nSe creo el archivo \"contactos.bin\"\n");
    secuencial = fopen(SALIDA, "w+");
    if (secuencial == NULL) {
        printf("\nError al abrir el archivo de acceso secuencial\n");
        exit(EXIT_FAILURE);
    }

    fseek(entrada, 0l, SEEK_END);
    int cantidad = ftell(entrada) / sizeof(Contacto);
    fseek(entrada, 0l, SEEK_SET);
    p = (Contacto*)calloc(cantidad, sizeof(Contacto));
    printf("\nSe creo el archivo \"contacto.txt\"\n");
    if (p == NULL)
    {
        printf("\nError al asignar memoria dinamica\n");
        exit(EXIT_FAILURE);
    }

    fread(p, sizeof(Contacto), cantidad, entrada);

    for (i = 0;i < cantidad;i++)
    {
        fprintf(secuencial, "%s %s %d %s\n", p[i].nombre, p[i].apellido, p[i].numT, p[i].correo);
    }
    free(p);
    fclose(entrada);
    fclose(secuencial);
}
int main()
{
    Contacto* contactos = NULL;
    int cantidad = 0;
    int capacidad = 0;
    char clave[LARGO];
    int eliminado = 0;
    int opcion = 0;
    int editado = 0;



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
            cargarContactos();
        }; break;
        case 2:
        {
            imprimirContactos();
        };break;
        case 3:
        {

            printf("\nIngresar el nombre:     ");
            scanf("%30s", clave);
            int hallado = buscarNombre(clave);
            if (hallado != -1) {
                FILE* entrada;
                entrada = fopen(ENTRADA, "rb");

                if (entrada == NULL) {
                    printf("\nError al abrir el archivo binario\n");
                    exit(EXIT_FAILURE);
                }
                fseek(entrada, 0l, SEEK_END);
                int cantidad = ftell(entrada) / sizeof(Contacto);
                fseek(entrada, 0l, SEEK_SET);
                contactos = (Contacto*)calloc(cantidad, sizeof(Contacto));
                if (contactos == NULL)
                {
                    printf("\nError al asignar memoria dinamica\n");
                    exit(EXIT_FAILURE);
                }
                fread(contactos, sizeof(Contacto), cantidad, entrada);
                printf("Coincidencia: \n");
                printf("Nombre:     %s\n", contactos[hallado].nombre);
                printf("Apellido:   %s\n", contactos[hallado].apellido);
                printf("Telefono:   %d\n", contactos[hallado].numT);
                printf("Correo:     %s\n", contactos[hallado].correo);
                fclose(entrada);
            }
            else {
                printf("Contacto \"%s\" no encontrado\n", clave);
            }
        };break;
        case 4:
        {
            printf("\nQue contacto desea editar:  ");
            scanf("%30s", clave);
            if ((editado = buscarNombre(clave)) != -1)
            {
                editar(editado);
            }
            else {
                printf("\nContacto \"%s\" no encontrado\n", clave);
            }
        };break;
        case 5:
        {
            printf("\nQue contacto desea eliminar:  ");
            scanf("%30s", clave);
            if ((eliminado = buscarNombre(clave)) != -1) {

                eliminar(eliminado);
            }
            else {
                printf("\nContacto \"%s\" no encontrado\n", clave);
            }
        };break;
        case 6: {
            exportar();
        };break;
        default:
        {
            printf("\nOpci%cn invalida\n", 162);
        };break;
        }
    } while (opcion != 0);
    return 0;
}