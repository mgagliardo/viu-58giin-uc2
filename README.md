# 58GIIN - Estrategias Algoritmicas - UC2

Unidad Competencial 2 de la asignatura 58GIIN - Estrategias Algoritmicas de la carrera de Ingenieria Informatica de la Universidad Internacional de Valencia (VIU)

## Descripcion

Desarrollar un compilador que traduzca instrucciones de un lenguaje fuente simple a uno de tres posibles lenguajes objetivo: C, Java o Python. Los lenguajes objetivo serán asignados aleatoriamente a los alumnos de la siguiente lista:

- Martín Alejandro Castro Álvarez  // Compilador lenguaje Python
- Miguel Ángel Gagliardo // Compilador lenguaje Java
- Amisadai Martel Suárez // Compilador lenguaje C
- José Vicente Martí Olmos // Compilador lenguaje C
- Tomás Martínez Guido // Compilador lenguaje Python
- Alejandro Navarro Arroyo // Compilador lenguaje Java 
- Miguel Solé González // Compilador lenguaje Python
- Jordi Vicens Farrus// Compilador lenguaje C 

1. Definición de la gramática del lenguaje fuente. Deberá incluir operaciones básicas y estructuras de control.
2. Creación de reglas léxicas utilizando Flex, seguidas por la definición de la gramática del lenguaje fuente con Bison, incorporando las acciones semánticas para la traducción al lenguaje objetivo.
3. Generación de código para el lenguaje objetivo asignado, manteniendo la fidelidad a la sintaxis y paradigmas de dicho lenguaje.
4. Redacción de casos de prueba y documentación del proceso de desarrollo, incluyendo las decisiones de diseño.
5. El proyecto debe ser compartido a través de GitHub, conteniendo todo el código fuente y la documentación correspondiente. Un archivo README.md deberá explicar cómo ejecutar el compilador y los casos de prueba.

**Criterios de evaluación**: Se evaluará la gramática y reglas léxicas, la implementación de la generación de código, la calidad de los casos de prueba y la documentación proporcionada.

## Prerequisitos

Todo el codigo ha sido testeado en Linux (Ubuntu 22.04). Se requiere:

- [GCC](https://gcc.gnu.org/) >= 11.4.0 // Dado que en este caso el compilador y el codigo deben ser testeados para Java
- [Flex](https://github.com/westes/flex) >= 2.6.4
- [Bison](https://www.gnu.org/software/bison/) >= 2.7
- [Java JDK 21](https://openjdk.org/projects/jdk/21/) 

## Documentos

- Para ver la definicion de la gramatica del lenguaje fuente, [ver aqui](./docs/DEFINICION.md)
- Para ver el outline del programa y decisiones de diseño [ir aqui](./docs/DISENO.md)
- Las gramaticas de reglas lexicas en Flex se encuentran en el archivo [lex.l](./lex.l). Las definiciones de la gramatica del lenguaje en Bison se encuentran en el archivo [syntax.y](./syntax.y)
- Para ver el codigo de los casos de prueba, ir a la carpeta [tests](./tests/)


## Como ejecutar el compilador

Para compilar, desde la linea de comandos, ejecutar:

```shell
% flex lex.l
% bison -y -d syntax.y
% g++ -std=c++11 lex.yy.c y.tab.c -o compilador
```

O bien, utilizar el `Makefile` (solo Linux o bash-compatible):

```shell
% make all
```

