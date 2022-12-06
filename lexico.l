
%{
#include "tablaSimbolos.h"
#include "definiciones.h"
#include "errores.h"
#include "sintactico.tab.h"

void cargarArchivo(char* file);

%}

/* No se define función para la opcion yywrap */
%option noyywrap

/* Para contar las líneas. */
%option yylineno

%option nounput
%option noinput

/* Definciones de las expresiones obtenidas de GO */

NEWLINE                       \n
DELIM                      	[ \t\r]
ESPACIO                   	{DELIM}+
UNICODE_CHAR                  .
UNICODE_LETTER                [A-Za-z]

LETTER                        {UNICODE_LETTER}|_

DECIMAL_DIGIT                 [0-9]
UNICODE_DIGIT                 {DECIMAL_DIGIT}
SEMICOLON                     ;
COLON					,
IDENTIFIER                    {LETTER}({LETTER}|{UNICODE_DIGIT})*

OP_PUNC                       [+*/%^,.!><()-]|{SEMICOLON}|{COLON}
OP_ASIG                       =
OP_SUMA_CMPX                  \+=
OP_RESTA_CMPX                 \-=
OP_COMP_MENIG                 <=
OP_COMP_MAYIG                 >=

DECIMAL_DIGITS                {DECIMAL_DIGIT}*
DECIMAL_LIT                   0|[1-9](_?{DECIMAL_DIGITS})?


DECIMAL_EXPONENT			[eE][+-]?{DECIMAL_DIGITS}
FLOAT_LIT				{DECIMAL_DIGITS}\.{DECIMAL_DIGITS}?{DECIMAL_EXPONENT}?|{DECIMAL_DIGITS}{DECIMAL_EXPONENT}|\.{DECIMAL_DIGITS}{DECIMAL_EXPONENT}?

NUMBER				{DECIMAL_LIT}|{FLOAT_LIT}

ARCHIVO				{IDENTIFIER}\.{IDENTIFIER}


%%

{NEWLINE}                     return ((int) *yytext);
{ESPACIO}  

{IDENTIFIER}                  {
						yylval.lexema = (char *) malloc(sizeof(char)*(yyleng+1));
						strcpy(yylval.lexema, yytext);
		                        yylval.lexema[yyleng] = '\0';
						if(pertenece(yylval.lexema)){
				                  switch(obtenerTipo(yylval.lexema)){
				                  	case QUIT_: 
				                  		printf("\n----Saliendo de la calculadora----\n");
				                  		free(yylval.lexema);
				                  		yyterminate();
				                  		break;
				                  	case LOAD_: 
					                  	free(yylval.lexema);
				                  		return(LOAD);
				                  		break;
				                  	case ECHO_: 
				                  		free(yylval.lexema);
				                  		return(_ECHO);
				                  		break;
				                  	case WORKSPACE_:
					                  	free(yylval.lexema);
				                  		return(WORKSPACE);
				                  		break;
				                  	case TABLAS_:
				                  		free(yylval.lexema);
				                  		return(TABLA);
				                  		break;
				                  	case HELP_:
				                  		free(yylval.lexema);
				                  		return(HELP);
				                  		break;
				                  	case CLEAN_:
				                  		free(yylval.lexema);
				                  		return(CLEAN);
				                  		break;
				                  	default:
				                  		return(IDENTIFICADOR);
				                  		break;
				                  }
		                        }else
		                        	return(IDENTIFICADOR);
                              }
{NUMBER}				{
					yylval.num=atof(yytext);
					return (NUM);
					}
{ARCHIVO}				{
					yylval.lexema = (char *) malloc(sizeof(char)*(yyleng+1));
					strcpy(yylval.lexema, yytext);
                              yylval.lexema[yyleng] = '\0';
                              return (ARCHIVO);
					}
{OP_ASIG}                       return (OP_ASIGNACION);
{OP_RESTA_CMPX}                 return (OP_RESTA_COMP);
{OP_SUMA_CMPX}                  return (OP_SUMA_COMP);

{OP_PUNC}                       return ((int) *yytext);
.                             { errorL(yylineno); }
<<EOF>>                       {fclose(yyin); yyrestart(stdin);}

%%

void cargarArchivo(char* file){
    printf("\nAbriendo el fichero...\n");
    if((yyin = fopen(file, "r")) == NULL) {
		errorNF("Fallo al abrir el archivo.");
		yyin = stdin;
	}
}



