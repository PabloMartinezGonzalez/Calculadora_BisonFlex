

typedef struct nodo *abb; //tipo opaco del nodo del arbol


void crea(abb *A);  //Función para crear el arbol
void destruye(abb *A);  //Función para eliminar y liberar memoria del arbol
short pertenece_(abb *A, char* cadena);
short pertenece_tabla(abb *A, char* cadena, short tipo);
void insertaConstantes(abb *A, char* cadena, float valor);
void insertaComandos(abb *A, char* cadena, short tipo);
void insertaFunciones(abb *A, char* cadena, void * func);
float inserta_actualiza(abb *A, char* cadena, float valor);
short obtener_tipo(abb *A, char* cadena);
float obtener_valor(abb *A, char* cadena);
float ejecutar_funcion(abb *A, char* cadena, float argumento);
float ejecutar_funcion2(abb *A, char* cadena, float argumento1, float argumento2);
void imprimir_tabla(abb *A);
void imprimir_estado(abb *A);



