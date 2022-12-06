#include <stdlib.h>
#include <stdio.h>

//Función que imprime el mensaje de error recibido
void error(char* mensaje){
    printf("> ERROR: %s\n", mensaje);
    exit(0);
}
//Función para imprimir errores en el análisis léxico indicando la línea del código donde se produjo
void errorL(int linea){
    printf("> ERROR---> No se pudo detectar el lexema en la linea: %d\n", linea);
}
//Funcion para errores que no cierran el programa
void errorNF(char* mensaje){
    printf("> ERROR: %s\n", mensaje);
}



