
CC=gcc -Wall
HEADER_FILES_DIR = .
INCLUDES = -I $(HEADER_FILES_DIR)
#nombre del ejecutable o archivo de salida
OUTPUT = calculadora

LIB_HEADERS = $(HEADER_FILES_DIR)/arbolBinario.h tablaSimbolos.h lex.yy.h sintactico.tab.h  definiciones.h funciones.h errores.h
#fuentes
SRCS = main.c tablaSimbolos.c arbolBinario.c lex.yy.c sintactico.tab.c errores.c
#ficheros .o: todos los .o con un análogo .c en SRCS
OBJS = $(SRCS:.c=.o)
#regla 1 (dependencia de los .o)
#si no hay librerías adicionales, no existe la variable $(LIBS),
#por lo que se elimina $(LIBS) de la regla siguiente
$(OUTPUT): $(OBJS)
	$(CC) -o $(OUTPUT) $(OBJS) -lm
#regla 2 (genera los .o cuando es necesario, dependencia de los .c y .h)
#$@ es el nombre del fichero que se genera con la regla (.o)
#$< es el nombre del primer prerrequisito (el archivo .c cuyo .o se está generando)
%.o: %.c $(LIB_HEADERS)
	$(CC) -c -o $@ $< $(INCLUDES)
regla 3 que borra el ejecutable (prerrequisito: clean)
cleanall: clean
	rm -f $(OUTPUT)
#regla 4 que borra los ficheros .o y los de backup (terminan en ~)
clean:
	rm -f *.o *~
