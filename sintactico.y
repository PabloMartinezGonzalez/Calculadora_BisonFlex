%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#ifdef NaN
#endif
#include "lex.yy.h"
#include "definiciones.h"
#include "errores.h"
#include "arbolBinario.h"
#include "tablaSimbolos.h"



extern int yylex();
void yyerror(char* s);
void imprimirAyuda();
short flagEcho=1;
%}

%union {
float	num;
char* lexema;
}


%start input

%token <num> NUM
%token <lexema> IDENTIFICADOR
%token <lexema> ARCHIVO

%token WORKSPACE
%token TABLA
%token HELP
%token LOAD
%token CLEAN
%token _ECHO

%token OP_SUMA_COMP
%token OP_RESTA_COMP
%token OP_COMP_MENIG
%token OP_COMP_MAYIG

%right OP_ASIGNACION
%left '-' '+' OP_SUMA_COMP OP_RESTA_COMP
%left '*' '/' '%'
%left NEG
%right '^'

%type <num> expresion

%%
input:	
	| input line
;

line:   '\n'
		| ';'
		| expresion '\n'	
		| error '\n' 	{ yyclearin; yyerrok;}
		| expresion ';'	{ if( !isnan($1)) if(flagEcho==1) printf("> %.4f\n",$1);}
		| error ';' 	{ yyclearin; yyerrok;}
		
		| WORKSPACE	';'	{ imprimirEstado(); }
		| WORKSPACE	'\n'	{ imprimirEstado(); }
            | TABLA ';'		{ imprimirTabla(); }	
            | TABLA '\n'	{ imprimirTabla(); }	
            | HELP ';'		{ imprimirAyuda(); }
            | HELP '\n'		{ imprimirAyuda(); }	
            | CLEAN ';'		{ borrarVariables(); }
            | CLEAN '\n'	{ borrarVariables(); }
            | _ECHO ';'		{ if(flagEcho==1){ printf("> Desactivando la opción ';' para imprimir\n"); flagEcho=0;}
            			  else{ printf("> Activando la opción ';' para imprimir\n"); flagEcho=1;}
            			}
            | _ECHO '\n'		{ if(flagEcho==1){ printf("Desactivando la opción ';' para imprimir\n"); flagEcho=0;}
            			  else{ printf("> Activando la opción ';' para imprimir\n"); flagEcho=1; }
            			}
            | LOAD '(' ARCHIVO ')' '\n'	{ cargarArchivo($3); free($3);}
            | LOAD '(' ARCHIVO ')' ';'	{ cargarArchivo($3); free($3);}
;

expresion:	NUM	{$$ = $1;}
		| IDENTIFICADOR	{ if(perteneceTabla($1, VARIABLE) || perteneceTabla($1, CONSTANTE)) $$=obtenerValor($1);
					 	else{
					 		yyerror("ERROR: Variable no inicializada");
					 		$$=NAN;
					 	}
					  free($1);	
					}
		| IDENTIFICADOR OP_ASIGNACION expresion	{ if(!perteneceTabla($1, CONSTANTE)){
										if(!isnan($3)) insertaActualiza($1, $3);
										$$ = $3;
									  } else {
										yyerror("ERROR: No se puede modificar una constante");
										$$ = NAN;
									  }
									  free($1);
									}
		| IDENTIFICADOR OP_SUMA_COMP expresion	{ if(!perteneceTabla($1, CONSTANTE)){
										if(perteneceTabla($1, VARIABLE)){
											$$ = obtenerValor($1) + $3;
											if(!isnan($3)) insertaActualiza($1, $$);
										} else {
											yyerror("ERROR: Variable no inicializada");
											$$=NAN;
										}
										}else {
											yyerror("ERROR: No se puede modificar una constante");
											$$=NAN;
										}
										free($1);
									}
									
		| IDENTIFICADOR OP_RESTA_COMP expresion	{ if(!perteneceTabla($1, CONSTANTE)){
										if(perteneceTabla($1, VARIABLE)){
											$$ = obtenerValor($1) - $3;
											if(!isnan($3)) insertaActualiza($1, $$);
										} else {
											yyerror("ERROR: Variable no inicializada");
											$$=NAN;
										}
										}else {
											yyerror("ERROR: No se puede modificar una constante");
											$$=NAN;
										}
										free($1);
									}
		| expresion '+' expresion   	{ $$ = $1 + $3;}
        	| expresion '-' expresion 	{ $$ = $1 - $3;}
        	| expresion '*' expresion 	{ $$ = $1 * $3;}
        	| expresion '/' expresion 	{ if($3 != 0) $$ = $1 / $3;
        							else{ 
        								yyerror("ERROR: Se ha introducido una división por cero.");
        								$$=NAN;
        							} 
        						}
        	| expresion '^' expresion 	{ $$ = pow($1, $3); }
		| '-' expresion %prec NEG 	{ $$ = -$2; }
            | expresion '%' expresion 	{ $$ = (int)$1 % (int)$3; }													
	
		| '(' expresion ')'		{ $$ = $2; }
            
            | IDENTIFICADOR '(' expresion ')'	{ if(perteneceTabla($1, FUNCION)) 
            							$$ = ejecutarFuncion($1, $3);
            						  else{ yyerror("Funcion no declarada");
            						  	  $$=NAN;}
            						  free($1);	  
            						  }
          	| IDENTIFICADOR '(' expresion ',' expresion ')'	{ if(perteneceTabla($1, FUNCION)) $$ = ejecutarFuncion2($1, $3, $5);
            						  		else{ yyerror("Funcion no declarada");
            						  	  			$$=NAN;}
            						  	  	free($1);
            						  		}
            
            
;




%%


void yyerror(char* s){
  printf ("> %s <\n\n", s);
}

void imprimirAyuda(){
	FILE *help;
	if((help = fopen("HELP.txt", "r")) == NULL) 
		yyerror("No se ha podido abrir el fichero de ayuda");
	else{
		fclose(help);
		system("cat HELP.txt");
	}
}
