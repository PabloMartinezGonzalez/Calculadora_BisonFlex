#include <stdlib.h>
#include "sintactico.tab.h"
#include "tablaSimbolos.h"
#include "lex.yy.h"


int main(int argc, char **argv) {
	
	printf("\n--------------------CALCULADORA--------------------\n\n"
		"Este programa consiste en una calculadora científica que permite al usuario realizar diversas operaciones matemáticas," 
		"tanto básicas, como funciones complejas. Su funcionamioento es mediante la entrada de expresiones en la terminal, o bien "
		"cargando archivos que contengan operaciones, las cuales se realizarán. Además, se permiten definicion de variables y su "
		"utilización a lo largo de la ejecución, como tambien el uso de valores de distintas constantes. Los comandos disponibles para "
		"manejar la calcualdora, a parte de realizar las operaciones, son las siguientes:\n\n"
		"\t- \"quit\"\tTermina la ejecución del programa calculadora, borrando las variables presentes.\n"
		"\t- \"workspace\"\tMuestra todas las variables declaradas y sus valores correspondientes.\n"
		"\t- \"clean\"\tBorra las variables almacenadas y sus valores.\n"
		"\t- \"tablaS\"\tMuestra toda la tabla de símbolos.\n"
		"\t- \"help\"\tMuestra la ayuda.\n"
		"\t- \"load(fichero)\"\tCarga y ejecuta el archivo que se introduzca en el apartado de \"fichero\" ejecutando sus operaciones maetemáticas.\n" 
		"\t- \"echo\"\tActiva y desactiva alternadamente la opción de imprimir el resultado de la operación con el uso de ';'.\n\n"
		"---------------------------------------------------\n\n");
	
	//Inicialización de los elementos necesarios para antes de comenzar a analizar
	iniciarTabla();
      //Comprobación de si se han introducido argumentos
      if(argc > 2) {
      	printf("Error: Número de argumentos inválido\n");
		return (EXIT_FAILURE);
	}
	else if(argc == 2){
		if(!strcmp(argv[1], "-help")) 
			imprimirAyuda();
		else 
			cargarArchivo(argv[1]);
	}
	yyparse();
	eliminarTabla();
	return (EXIT_SUCCESS);
}
