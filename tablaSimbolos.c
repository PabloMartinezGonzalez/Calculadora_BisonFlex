
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "funciones.h"
#include "arbolBinario.h"
#include "definiciones.h"


/* Tamaño de la cadena en que almaceno las lecturas de lexemas de la tabla de símbolos. Sé que el lexema más grande es de longitud 7
   porque el archivo de definiciones es un fichero estático que puedo comprobar en todo momento.
   Si en algún momento añadiese un lexema más grande, es fácil venir aquí y cambiar esta constante.*/
#define TAM 2

abb tabla; 

char *constantes[] = {"e", "pi"};
float valoresC[] = {_E, _PI};

char *comandos[] = {"quit", "load", "echo", "workspace", "tablaS", "clean", "help"};
float valoresCom[] = {QUIT_, LOAD_, ECHO_, WORKSPACE_, TABLAS_, CLEAN_, HELP_};

/* Creo la tabla de símbolos y la relleno con las palabras reservadas del lenguaje. */
void iniciarTabla(){
    crea(&tabla);
    // Introduzco las cosntantes
    for (int i = 0; i < 2; i++) {
        insertaConstantes(&tabla, constantes[i], valoresC[i]);
    }
    
    for (int i = 0; i < 7; i++) {
        insertaComandos(&tabla, comandos[i], valoresCom[i]);
    }
    
    //Insertar funciones
    for (int i = 0; arith_fncts[i].fname != 0; i++) {
        insertaFunciones(&tabla, arith_fncts[i].fname, arith_fncts[i].fnct);
    }
   
}

short pertenece(char* cadena){
	return pertenece_(&tabla, cadena);
}

short perteneceTabla(char* cadena, short tipo){
	return pertenece_tabla(&tabla, cadena, tipo);
}

short obtenerTipo(char* cadena){
	return obtener_tipo(&tabla, cadena);
}
float obtenerValor(char* cadena){
	return obtener_valor(&tabla, cadena);
}

short insertaActualiza(char* cadena, float valor){
    return inserta_actualiza(&tabla, cadena, valor);
}

float ejecutarFuncion(char* cadena, float argumento){
	return ejecutar_funcion(&tabla, cadena, argumento);
}

float ejecutarFuncion2(char* cadena, float argumento1, float argumento2){
	return ejecutar_funcion2(&tabla, cadena, argumento1, argumento2);
}

/* Función para imprimir la tabla de símbolos. */
void imprimirTabla(){
    printf("\n-----------------TABLA DE SÍMBOLOS-----------------\n");
    imprimir_tabla(&tabla);
    printf("------------FIN DE LA TABLA DE SÍMBOLOS------------\n");
    printf("\n\n");
}
void imprimirEstado(){
    printf("\n-----------------ESPACIO DE TRABAJO----------------\n");
    imprimir_estado(&tabla);
    printf("-----------------ESPACIO DE TRABAJO----------------\n");
    printf("\n\n");
}

/* Función para liberar la memoria de la tabla de símbolos. */
void eliminarTabla(){
    destruye(&tabla);
}

void borrarVariables(){
    destruye(&tabla);
    iniciarTabla();
}



