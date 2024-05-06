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

O bien, utilizar el `Makefile` (recomendado), solo Linux o bash-compatible:

```shell
% make all
```

Tambien se pueden borrar los antiguos archivos de output de compilaciones anteriores con `make clean`, por ejemplo:

```shell
% make clean all
```

Una vez creado el compilador, podemos proceder a testera, los casos de prueba se encuentran en la carpeta [tests](./tests/), se pueden utilizar los siguientes comandos:

```shell
% ./compilador tests/<NOMBRE_DEL_TEST>
% java -jar ./jasmin-1.1/jasmin.jar output.j
% java test
```

`<NOMBRE_DEL_TEST>` vendria a ser el nombre del archivo a ejecutar, por ejemplo `op-matematicas`:

```shell
% make run test=op-matematicas

Ejecutando el analizador lexico
flex lex.l

Ejecutando el analizador Semantico
bison -y -d syntax.y
conflicts: 2 shift/reduce

Creando el compilador
g++ -w -std=c++11 lex.yy.c y.tab.c -o compilador

Ejecutando el test
./compilador tests/op-matematicas
                                                                        java -jar ./jasmin.jar output.j
Generated: test.class
java test
65536
11
```

## Utilizando Docker

Si por alguna razon no pudieramos ejecutar el compilador utilizando los comandos antes mencionados (ejemplo, se esta probando en Windows o MacOS) podemos utilizar [docker](https://docker.com).

Para el build:

```shell
% docker build -t compilador:latest .
STEP 1/6: FROM alpine:latest
STEP 2/6: WORKDIR /uc2
--> Using cache e5612697f26c7ebb5f6eddd939f8d38417c7744a1c4c0a612d63727aff2bbb4f
--> e5612697f26c
STEP 3/6: RUN apk update &&     apk upgrade --no-cache &&     apk add  --no-cache flex bison openjdk21-jdk gcc g++ make automake &&     rm /var/cache/apk/*
--> Using cache c138cd2054b0f4577a9606c1b3d448cb63dbbf58ff89897df2f35badd8826042
--> c138cd2054b0
STEP 4/6: COPY . .
--> c3fd6e52797a
STEP 5/6: RUN make clean all
rm -rf y.tab.c y.tab.h test.class output.j lex.yy.c compilador
\nEjecutando el analizador lexico
flex lex.l
\nEjecutando el analizador Semantico
bison -y -d syntax.y
syntax.y:64.1-5: warning: POSIX Yacc does not support %code [-Wyacc]
   64 | %code requires {
      | ^~~~~
syntax.y: warning: 2 shift/reduce conflicts [-Wconflicts-sr]
syntax.y: note: rerun with option '-Wcounterexamples' to generate conflict counterexamples
\nCreando el compilador
g++ -w -std=c++11 lex.yy.c y.tab.c -o compilador
--> 6e11b234d462
STEP 6/6: ENTRYPOINT ["./entrypoint.sh"]
COMMIT compilador:latest
--> 5e99ce98fe58
Successfully tagged localhost/compilador:latest
```

Luego ejecutamos los tests:

```shell
% docker run -ti compilador:latest <NOMBRE_DEL_TEST>
```

`<NOMBRE_DEL_TEST>` vendria a ser el nombre del archivo a ejecutar, por ejemplo `op-matematicas`:

```shell
% docker run -ti compilador:latest op-matematicas
\nEjecutando el test
./compilador tests/op-matematicas
                                                                        java -jar ./jasmin.jar output.j
Generated: test.class
java test
65536
11
```
