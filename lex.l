%{
	#include "y.tab.h"
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	int lineCounter = 1; 					// Contador de línea para mantener el seguimiento del número de línea actual

	extern int printLineNumber(int num); 	// Declaración de la función externa printLineNumber definida en otro lugar
%}

/* Definición de una expresión regular para una letra */
letter  [a-zA-Z]
/* Definición de una expresión regular para un dígito */
digit 	[0-9]
/* Expresión regular para uno o más dígitos */
digits 	{digit}+
/* Expresión regular para un identificador */
id 		{letter}({letter}|{digit})*
/* Expresión regular para un número entero opcionalmente precedido por un signo negativo */
num 	"-"?{digits}
/* Expresión regular para un número de punto flotante opcionalmente precedido por un signo negativo y seguido de una parte fraccionaria y opcionalmente una parte exponencial */
fnum 	"-"?{digits}.{digits}("E"{digits}+)?
/* Expresión regular para operadores relacionales */
relop 	"=="|"!="|">"|">="|"<"|"<="
/* Expresión regular para operadores lógicos */
boolop 	"&&"|"||"
/* Expresión regular para operadores aritméticos y de bits */
op 		"+"|"-"|"*"|"/"|"%"|"&"|"|"
/* Expresión regular para literales booleanos */
binary 	"true"|"false"

%%

"System.out.println"	{return SYSTEM_OUT;} 																	// Reconocimiento de la cadena "System.out.println" y retorno del token correspondiente
"if"    				{return IF_WORD;} 																		// Reconocimiento de la palabra reservada "if" y retorno del token correspondiente
"else"   				{return ELSE_WORD;} 																	// Reconocimiento de la palabra reservada "else" y retorno del token correspondiente
"while"  				{return WHILE_WORD;} 																	// Reconocimiento de la palabra reservada "while" y retorno del token correspondiente
"for"   				{return FOR_WORD;} 																		// Reconocimiento de la palabra reservada "for" y retorno del token correspondiente
"int"   				{return INT_WORD;} 																		// Reconocimiento de la palabra reservada "int" y retorno del token correspondiente
"float"    				{return FLOAT_WORD;} 																	// Reconocimiento de la palabra reservada "float" y retorno del token correspondiente
"boolean" 				{return BOOLEAN_WORD;} 																	// Reconocimiento de la palabra reservada "boolean" y retorno del token correspondiente
{op}    				{yylval.aopval = strdup(yytext); return ARITH_OP;} 										// Reconocimiento de operadores aritméticos y de bits y retorno del token correspondiente
{num}    				{yylval.ival = atoi(yytext); return INT;} 												// Reconocimiento de números enteros y retorno del token correspondiente
{fnum}    				{yylval.fval = atof(yytext); return FLOAT;} 											// Reconocimiento de números de punto flotante y retorno del token correspondiente
{relop} 				{yylval.aopval = strdup(yytext); return RELA_OP;} 										// Reconocimiento de operadores relacionales y retorno del token correspondiente
{boolop} 				{yylval.aopval = strdup(yytext); return BOOL_OP;} 										// Reconocimiento de operadores lógicos y retorno del token correspondiente
{binary} 				{if(!strcmp(yytext,"true")){ yylval.bval = 1;} else { yylval.bval = 0;} return BOOL;} 	// Reconocimiento de literales booleanos y retorno del token correspondiente
{id}    				{yylval.idval = strdup(yytext);return IDENTIFIER;} 										// Reconocimiento de identificadores y retorno del token correspondiente
";" 					{return SEMI_COLON;} 																	// Reconocimiento del punto y coma y retorno del token correspondiente
"=" 					{return EQUALS;} 																		// Reconocimiento del signo igual y retorno del token correspondiente
"(" 					{return LEFT_BRACKET;} 																	// Reconocimiento del paréntesis izquierdo y retorno del token correspondiente
")" 					{return RIGHT_BRACKET;} 																// Reconocimiento del paréntesis derecho y retorno del token correspondiente
"{" 					{return LEFT_BRACKET_CURLY;} 															// Reconocimiento de la llave izquierda y retorno del token correspondiente
"}" 					{return RIGHT_BRACKET_CURLY;} 															// Reconocimiento de la llave derecha y retorno del token correspondiente
\n    					{++lineCounter;    printLineNumber(lineCounter);} 										// Reconocimiento de un salto de línea y actualización del contador de línea

%%

int yywrap() {
   return -1;
}
