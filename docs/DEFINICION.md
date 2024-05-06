# Definicion

El bytecode generado sigue las instrucciones estándar de bytecode definidas en la Especificación de la Máquina Virtual Java (JVM):
- https://en.wikipedia.org/wiki/Java_bytecode
- https://docs.oracle.com/javase/specs/jvms/se6/html/VMSpecTOC.doc.html

Las gramáticas propuestas cubren las siguientes características:
- Tipos primitivos (int, float) con operaciones en ellos (+, -, *, /)
- Expresiones booleanas
- Expresiones aritméticas
- Declaraciones de asignación
- Estructuras de control:
  - Declaraciones if-else
  - Bucles for
  - Bucles while

### Decisiones de diseño

Por una cuestion de complejidad, las siguientes operaciones no fueron implementada:
- Type casting o [type conversion](https://docs.oracle.com/javase/specs/jls/se7/html/jls-5.html). Por lo tanto, solo es posible asignar una variable del mismo tipo a una variable.
- Ciertas operaciones con booleanos no fueron implementadas, por ejemplo:
  - `true && expr`
  - `true || expr`
- Ciertas palabras y acciones reservadas del lenguaje no han sido implementadas, como el caso de `break`.

## eBNF

Una definición en `eBNF` (extended Backus–Naur Form) basada en la gramática propuesta es:

```ebnf
programa      ::= declaracion SENTENCIA
SENTENCIA     ::= asignacion | estructura_control | imprimir
declaracion   ::= "int" IDENTIFICADOR ";"
asignacion    ::= IDENTIFICADOR "=" EXPRESION ";"
estructura_control ::= "if" "(" condicion ")" "{" SENTENCIA "}" "else" "{" SENTENCIA "}"
imprimir      ::= "System.out.println" "(" IDENTIFICADOR ")" ";"
EXPRESION     ::= TERMINO (("+" | "-") TERMINO)*
condicion     ::= EXPRESION ("==" | "!=") EXPRESION
TERMINO       ::= NUMERO | IDENTIFICADOR
IDENTIFICADOR ::= [a-zA-Z][a-zA-Z0-9]*
NUMERO        ::= [0-9]+
```

## Ejemplo

Un ejemplo en lenguaje fuente simple podria ser:

```java
int x; 
x = 5;
if ( x == 5 )
{ 
x = 8 ;
}
else
{
	x= 9;
}
System.out.println(x);
```

