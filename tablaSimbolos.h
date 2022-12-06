
/* Función que crea la tabla de símbolos y la rellena con las palabras reservadas del lenguaje. */
void iniciarTabla();
short pertenece(char* cadena);
short perteneceTabla(char* cadena, short tipo);
short obtenerTipo(char* cadena);
float obtenerValor(char* cadena);
short insertaActualiza(char* cadena, float valor);
float ejecutarFuncion(char* cadena, float argumento);
float ejecutarFuncion2(char* cadena, float argumento1, float argumento2);
void imprimirTabla();
void imprimirEstado();
void eliminarTabla();
void borrarVariables();
