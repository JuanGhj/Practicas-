Posee la practica del algoritmo para copiar y comparar cadenas de caracteres --> el funcionamiento es el siguiente:

*Se copia la clave a analizar para no alterar la clave original (usualmente con strcpy).

*Se copia el arreglo de cadenas/ matriz de caracteres, ya sea con strcpy o bien por iteración de índices i y j.

*Con la función tolower() de la librería de C <tring.h> y <ctype.h> se pasan a minúsculas los caracteres de la copia de la clave,  y también de la copia de la matriz de caracteres,  donde se planean analizar la coincidencias,  luego es una búsqueda secuencias usando strcmp(),  de la librería <string.h> --> [En caso de encontrar la clave en la matriz (tiene rol de base de datos) se retorna su posición,  caso contrario,  la función de búsqueda retorna -1, para posteriormente hacer saber al usuario que la palabra que busca no fue encontrada]