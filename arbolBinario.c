//Clase de arbol binario inspirado en el realizado en la asigatura de Algoritmos y Estructuras de Datos en el segundo curso
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbolBinario.h"
#include "definiciones.h"

//Estructura del elemento almacenado en cada nodo
typedef struct {
    char* lexema;
    short tipo;
    union{
    	float valor;
    	double (*fnct)();
    } value;
    
}elemento;

//Estructura de los nodos del arbol
struct nodo {
    elemento info;
    struct nodo *izq, *der;
};


//Función para inicializar el arbol binario
void crea(abb *A) {
    *A = NULL;
}

//Función para liberar memoria y destruir el arbol
void destruye(abb *A) {
    if (*A != NULL) {
        destruye(&(*A)->izq);
        destruye(&(*A)->der);
        free((*A)->info.lexema);
        (*A)->info.lexema=NULL;
        free(*A);
        *A = NULL;
    }
}


//Función para comprobar si el arbol es vacio
unsigned esVacio(abb A) {
    return A == NULL;
}

//Función para comprobar si pertenece a la tabla de símbolos un lexema
short pertenece_(abb *A, char* cadena){
    if (esVacio(*A))
        return (0);
    else if (strcmp(cadena,(*A)->info.lexema)==0) return (1);
    
    else if (strcmp(cadena,(*A)->info.lexema)<0)
        return (pertenece_(&(*A)->izq, cadena));
    
    else
        return (pertenece_(&(*A)->der, cadena));
}



//Función para comprobar si pertenece a la tabla de símbolos un lexema, segun un componente léxico concreto
short pertenece_tabla(abb *A, char* cadena, short tipo){
    if (esVacio(*A))
        return (0);
    
    else if (strcmp(cadena,(*A)->info.lexema)==0)
        if((*A)->info.tipo == tipo) return (1);
        else return (0);
    
    else if (strcmp(cadena,(*A)->info.lexema)<0)
        return (pertenece_tabla(&(*A)->izq, cadena, tipo));
    
    else
        return (pertenece_tabla(&(*A)->der, cadena, tipo));
    

}

//Funcion para insertar constantes
void insertaConstantes(abb *A, char* cadena, float valor){
    if (esVacio(*A)) {  
        *A = (abb) malloc(sizeof (struct nodo));  
        (*A)->info.lexema = (char*) malloc((strlen(cadena)+1) * sizeof(char));  
        strcpy((*A)->info.lexema, ""); 
        strncat((*A)->info.lexema, cadena, strlen(cadena));
        (*A)->info.tipo = CONSTANTE; 
        (*A)->info.value.valor = valor; 
        (*A)->izq = NULL;  
        (*A)->der = NULL;
    } else if (strcmp(cadena,(*A)->info.lexema) <0)  
        insertaConstantes(&(*A)->izq, cadena, valor);  
    else   
        insertaConstantes(&(*A)->der, cadena, valor);
}

//Funcion para insertar constantes
void insertaComandos(abb *A, char* cadena, short tipo){
    if (esVacio(*A)) {  
        *A = (abb) malloc(sizeof (struct nodo));  
        (*A)->info.lexema = (char*) malloc((strlen(cadena)+1) * sizeof(char));  
        strcpy((*A)->info.lexema, ""); 
        strncat((*A)->info.lexema, cadena, strlen(cadena));
        (*A)->info.tipo = tipo; 
        (*A)->izq = NULL;  
        (*A)->der = NULL;
    } else if (strcmp(cadena,(*A)->info.lexema) <0)  
        insertaComandos(&(*A)->izq, cadena, tipo);  
    else   
        insertaComandos(&(*A)->der, cadena, tipo);
}

//Funcion para insertar funciones
void insertaFunciones(abb *A, char* cadena, void * func){
    if (esVacio(*A)) {  
        *A = (abb) malloc(sizeof (struct nodo));  
        (*A)->info.lexema = (char*) malloc((strlen(cadena)+1) * sizeof(char));  
        strcpy((*A)->info.lexema, ""); 
        strncat((*A)->info.lexema, cadena, strlen(cadena));
        (*A)->info.tipo = FUNCION; 
        (*A)->info.value.fnct = func; 
        (*A)->izq = NULL;  
        (*A)->der = NULL;
    } else if (strcmp(cadena,(*A)->info.lexema) <0)  
        insertaFunciones(&(*A)->izq, cadena, func);  
    else   
        insertaFunciones(&(*A)->der, cadena, func);
}



//Funcion para insertar o actualizar variables
float inserta_actualiza(abb *A, char* cadena, float valor){
    if (esVacio(*A)){
        *A = (abb) malloc(sizeof (struct nodo));
        (*A)->info.lexema = (char*) malloc((strlen(cadena)+1) * sizeof(char));
        strcpy((*A)->info.lexema, "");
        strncat((*A)->info.lexema, cadena, strlen(cadena));
        (*A)->info.tipo = VARIABLE;
        (*A)->info.value.valor = valor;
        (*A)->izq = NULL;
        (*A)->der = NULL;
        return (valor);
    }
    else if (strcmp(cadena,(*A)->info.lexema)==0){
        (*A)->info.value.valor = valor;
        return ((*A)->info.value.valor);
    }
    else if (strcmp(cadena,(*A)->info.lexema)<0)
        return (inserta_actualiza(&(*A)->izq, cadena, valor));
    
    else
        return (inserta_actualiza(&(*A)->der, cadena, valor));
    
}

short obtener_tipo(abb *A, char* cadena){
	if (strcmp(cadena,(*A)->info.lexema)==0)
        return ((*A)->info.tipo);
    
    else if (strcmp(cadena,(*A)->info.lexema)<0)
        return (obtener_tipo(&(*A)->izq, cadena));
    
    else
        return (obtener_tipo(&(*A)->der, cadena));
}
//Funcion para recuperar el valor de algun elemento de la tabla
float obtener_valor(abb *A, char* cadena){
    if (strcmp(cadena,(*A)->info.lexema)==0)
        return ((*A)->info.value.valor);
    
    else if (strcmp(cadena,(*A)->info.lexema)<0)
        return (obtener_valor(&(*A)->izq, cadena));
    
    else
        return (obtener_valor(&(*A)->der, cadena));
}

//Funcion para ejecutar funciones con un argumento
float ejecutar_funcion(abb *A, char* cadena, float argumento){
	if (strcmp(cadena,(*A)->info.lexema)==0)
        return ((*A)->info.value.fnct(argumento));
        
    else if (strcmp(cadena,(*A)->info.lexema)<0)
        return (ejecutar_funcion(&(*A)->izq, cadena, argumento));
        
    else
        return (ejecutar_funcion(&(*A)->der, cadena, argumento));
}

//Funcion para ejecutar funciones con dos argumentos
float ejecutar_funcion2(abb *A, char* cadena, float argumento1, float argumento2){
	if (strcmp(cadena,(*A)->info.lexema)==0)
        return ((*A)->info.value.fnct(argumento1, argumento2));
        
    else if (strcmp(cadena,(*A)->info.lexema)<0)
        return (ejecutar_funcion2(&(*A)->izq, cadena, argumento1, argumento2));
        
    else
        return (ejecutar_funcion2(&(*A)->der, cadena, argumento1, argumento2));
}

 

//Función recursiva para imprimir el contenido de la tabla de símbolos, que es el contenido del arbol
void imprimir_tabla(abb *A) {
    if (!esVacio(*A)) {
       if (&(*A)->izq != NULL)
            imprimir_tabla(&(*A)->izq);
            
       if((*A)->info.tipo == CONSTANTE) 
       	printf("Lexema: %s\tComponente lexico: Constante\tValor: %.4f\n", (*A)->info.lexema, (*A)->info.value.valor);
       else if((*A)->info.tipo == FUNCION)
       	printf("Lexema: %s\tComponente lexico: Funcion\n", (*A)->info.lexema);
       else if((*A)->info.tipo == VARIABLE)
       	printf("Lexema: %s\tComponente lexico: Variable\tValor: %.4f\n", (*A)->info.lexema, (*A)->info.value.valor);
	else
       	printf("Lexema: %s\tComponente lexico: Comando\n", (*A)->info.lexema);
			
       if (&(*A)->der != NULL)
           imprimir_tabla(&(*A)->der);
    }
}

//Función recursiva para imprimir las variables 
void imprimir_estado(abb *A) {
    if (!esVacio(*A)){
        if (&(*A)->izq != NULL) 
            imprimir_estado(&(*A)->izq);
            
	  if((*A)->info.tipo == VARIABLE) 
       	printf("Variable: %s\tValor: %.4f\n", (*A)->info.lexema, (*A)->info.value.valor);
       	
        if (&(*A)->der != NULL)
            imprimir_estado(&(*A)->der);
    }
}


