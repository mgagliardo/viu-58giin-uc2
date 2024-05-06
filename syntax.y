%{
#include <fstream>
#include <iostream>
#include <map>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include "bytecode_inst.h"

#define GetCurrentDir getcwd

using namespace std;

extern  int yylex();
extern  FILE *yyin;
void yyerror(const char * s);
extern int lineCounter;

#define TRUE 1
#define FALSE 0
string outfileName ;

ofstream fout("output.j");    // Archivo donde se va a guardar el output

// Genera el encabezado para la clase para poder compilar el código
void generateHeader(void);

// Genera el pie de página para la clase para poder compilar el código
void generateFooter(void);

int labelsCount = 0;        // Para generar labels
int variablesNum = 1;       // Para generar nuevas variables, Java empieza con `1`, mientras que 0 es `this`

typedef enum {INT_T, FLOAT_T, BOOL_T, VOID_T, ERROR_T} type_enum;

map<string, pair<int,type_enum> > symbTab;

void cast (string x, int type_t1);
void arithCast(int from , int to, string op);
void relaCast(string op,char * nTrue, char * nFalse);

bool checkId(string id);
string getOp(string op);
void defineVar(string name, int type);

string genLabel();
string getLabel(int n);

void backpatch(vector<int> *list, int num);
vector<int> * merge (vector<int> *list1, vector<int>* list2);

vector<string> codeList;
void writeCode(string x);

void printCode(void);

void printLineNumber(int num)
{
    writeCode(".line "+ to_string(num));
}
%}

%code requires {
    #include <vector>
    using namespace std;
}

%start method_body

%union{
    int ival;
    float fval;
    int bval;
    char * idval;
    char * aopval;
    struct {
        int sType;
    } expr_type;
    struct {
        vector<int> *trueList, *falseList;
    } bexpr_type;
    struct {
        vector<int> *nextList;
    } stmt_type;
    int sType;
}

%token <ival> INT
%token <fval> FLOAT
%token <bval> BOOL
%token <idval> IDENTIFIER
%token <aopval> ARITH_OP
%token <aopval> RELA_OP
%token <aopval> BOOL_OP

%token IF_WORD
%token ELSE_WORD
%token WHILE_WORD
%token FOR_WORD

%token INT_WORD
%token FLOAT_WORD
%token BOOLEAN_WORD

%token SEMI_COLON
%token EQUALS

%token LEFT_BRACKET
%token RIGHT_BRACKET
%token LEFT_BRACKET_CURLY
%token RIGHT_BRACKET_CURLY

%token SYSTEM_OUT

%type <sType> primitive_type
%type <expr_type> expression
%type <bexpr_type> b_expression
%type <stmt_type> statement
%type <stmt_type> statement_list
%type <stmt_type> if
%type <stmt_type> while
%type <stmt_type> for

%type <ival> marker
%type <ival> goto

%% 

method_body: 
    {   generateHeader();   }
    statement_list
    marker
    {
        backpatch($2.nextList,$3);
        generateFooter();
    }
    ;

statement_list: 
     statement 
    | 
    statement
    marker
    statement_list 
    {
        backpatch($1.nextList,$2);
        $$.nextList = $3.nextList;
    }
    ;

marker:
{
    $$ = labelsCount;
    writeCode(genLabel() + ":");
}
;

statement: 
    declaration {vector<int> * v = new vector<int>(); $$.nextList =v;}
    |if {$$.nextList = $1.nextList;}
    |while   {$$.nextList = $1.nextList;}
    |for {$$.nextList = $1.nextList;}
    | assignment {vector<int> * v = new vector<int>(); $$.nextList =v;}
    | system_print {vector<int> * v = new vector<int>(); $$.nextList =v;}
    ;

declaration: 
    primitive_type IDENTIFIER SEMI_COLON /* implement multi-variable declaration */
    {
        string str($2);
        if($1 == INT_T)
        {
            defineVar(str,INT_T);
        }else if ($1 == FLOAT_T)
        {
            defineVar(str,FLOAT_T);
        }
    }
    ;

primitive_type: 
    INT_WORD {$$ = INT_T;}
    |FLOAT_WORD {$$ = FLOAT_T;}
    |BOOLEAN_WORD {$$ = BOOL_T;}
    ;

goto:
{
    $$ = codeList.size();
    writeCode("goto ");
}
;

if: 
    IF_WORD LEFT_BRACKET 
    b_expression 
    RIGHT_BRACKET LEFT_BRACKET_CURLY 
    marker
    statement_list
    goto 
    RIGHT_BRACKET_CURLY 
    ELSE_WORD LEFT_BRACKET_CURLY 
    marker
    statement_list 
    RIGHT_BRACKET_CURLY
    {
        backpatch($3.trueList,$6);
        backpatch($3.falseList,$12);
        $$.nextList = merge($7.nextList, $13.nextList);
        $$.nextList->push_back($8);
    }
    ;

while:
    marker 
    WHILE_WORD LEFT_BRACKET
    b_expression
    RIGHT_BRACKET LEFT_BRACKET_CURLY 
    marker
    statement_list
    RIGHT_BRACKET_CURLY
    {
        writeCode("goto " + getLabel($1));
        
        backpatch($8.nextList,$1);
        backpatch($4.trueList,$7);
        $$.nextList = $4.falseList;
    }
    ;

for:
    FOR_WORD 
    LEFT_BRACKET
    assignment
    marker
    b_expression
    SEMI_COLON
    marker
    assignment
    goto
    RIGHT_BRACKET
    LEFT_BRACKET_CURLY
    marker
    statement_list
    goto
    RIGHT_BRACKET_CURLY
    {
        backpatch($5.trueList,$12);
        vector<int> * v = new vector<int> ();
        v->push_back($9);
        backpatch(v,$4);
        v = new vector<int>();
        v->push_back($14);
        backpatch(v,$7);
        backpatch($13.nextList,$7);
        $$.nextList = $5.falseList;
    }
    ;

assignment: 
    IDENTIFIER EQUALS expression SEMI_COLON
    {
        string str($1);
        if(checkId(str))
        {
            if($3.sType == symbTab[str].second)
            {
                if($3.sType == INT_T)
                {
                    writeCode("istore " + to_string(symbTab[str].first));
                }else if ($3.sType == FLOAT_T)
                {
                    writeCode("fstore " + to_string(symbTab[str].first));
                }
            }
            else
            {
                cast(str,$3.sType);    /* do casting */
            }
        }else{
            string err = "El identificador: "+str+" no está declarado en este ámbito";
            yyerror(err.c_str());
        }
    }
    ;

expression: 
    FLOAT   {$$.sType = FLOAT_T; writeCode("ldc "+to_string($1));}
    | INT   {$$.sType = INT_T;  writeCode("ldc "+to_string($1));} 
    | expression ARITH_OP expression   {arithCast($1.sType, $3.sType, string($2));}
    | IDENTIFIER {
        string str($1);
        if(checkId(str))
        {
            $$.sType = symbTab[str].second;
            if(symbTab[str].second == INT_T)
            {
                writeCode("iload " + to_string(symbTab[str].first));
            }else if (symbTab[str].second == FLOAT_T)
            {
                writeCode("fload " + to_string(symbTab[str].first));
            }
        }
        else
        {
            string err = "El identificador: "+str+" no está declarado en este ámbito";
            yyerror(err.c_str());
            $$.sType = ERROR_T;
        }
    }
    | LEFT_BRACKET expression RIGHT_BRACKET {$$.sType = $2.sType;}
    ;

system_print:
    SYSTEM_OUT LEFT_BRACKET expression RIGHT_BRACKET SEMI_COLON
    {
        if($3.sType == INT_T)
        {
            writeCode("istore " + to_string(symbTab["1syso_int_var"].first));
            writeCode("getstatic      java/lang/System/out Ljava/io/PrintStream;");
            writeCode("iload " + to_string(symbTab["1syso_int_var"].first ));
            writeCode("invokevirtual java/io/PrintStream/println(I)V");

        }else if ($3.sType == FLOAT_T)
        {
            writeCode("fstore " + to_string(symbTab["1syso_float_var"].first));
            writeCode("getstatic      java/lang/System/out Ljava/io/PrintStream;");
            writeCode("fload " + to_string(symbTab["1syso_float_var"].first ));
            writeCode("invokevirtual java/io/PrintStream/println(F)V");
        }
    }
    ;

b_expression:
    BOOL
    {
        if($1)
        {
            $$.trueList = new vector<int> ();
            $$.trueList->push_back(codeList.size());
            $$.falseList = new vector<int>();
            writeCode("goto ");
        }else
        {
            $$.trueList = new vector<int> ();
            $$.falseList= new vector<int>();
            $$.falseList->push_back(codeList.size());
            writeCode("goto ");
        }
    }
    |b_expression
    BOOL_OP 
    marker
    b_expression
    {
        if(!strcmp($2, "&&"))
        {
            backpatch($1.trueList, $3);
            $$.trueList = $4.trueList;
            $$.falseList = merge($1.falseList,$4.falseList);
        }
        else if (!strcmp($2,"||"))
        {
            backpatch($1.falseList,$3);
            $$.trueList = merge($1.trueList, $4.trueList);
            $$.falseList = $4.falseList;
        }
    }   
    | expression RELA_OP expression     
    {
        string op ($2);
        $$.trueList = new vector<int>();
        $$.trueList ->push_back (codeList.size());
        $$.falseList = new vector<int>();
        $$.falseList->push_back(codeList.size()+1);
        writeCode(getOp(op)+ " ");
        writeCode("goto ");
    }
    /*|expression RELA_OP BOOL    // to be considered */ 
    ;
%%

int main(int argv, char * argc[])
{
    FILE *miArchivo;
    miArchivo = fopen(argc[1], "r");
    outfileName = string(argc[1]);
    if (!miArchivo) {
        string err = "Error: No se ha podido abrir el archivo indicado\n";
        yyerror(err.c_str());
        char cCurrentPath[200];
         if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
             {
             return -1;
             }
        printf("%s\n",cCurrentPath);  
                getchar();

        return -1;

    }
    yyin = miArchivo;
    yyparse();
    printCode();
    return 0;
}

void yyerror(const char * s)
{
    printf("Error@%d: %s\n",lineCounter, s);
}

void generateHeader()
{
    writeCode(".source " + outfileName);
    writeCode(".class public test\n.super java/lang/Object\n"); //código para definir la clase
    writeCode(".method public <init>()V");
    writeCode("aload_0");
    writeCode("invokenonvirtual java/lang/Object/<init>()V");
    writeCode("return");
    writeCode(".end method\n");
    writeCode(".method public static main([Ljava/lang/String;)V");
    writeCode(".limit locals 100\n.limit stack 100");

    defineVar("1syso_int_var",INT_T);
    defineVar("1syso_float_var",FLOAT_T);

    // Genera nueva linea
    writeCode(".line 1");
}

void generateFooter()
{
    writeCode("return");
    writeCode(".end method");
}

void cast (string str, int t1)
{
    yyerror("Error: Casting todavía no implementado :)");
}

void arithCast(int from , int to, string op)
{
    if(from == to)
    {
        if(from == INT_T)
        {
            writeCode("i" + getOp(op));
        }else if (from == FLOAT_T)
        {
            writeCode("f" + getOp(op));
        }
    }
    else
    {
        yyerror("Error: Casting todavía no implementado");
    }
}


string getOp(string op)
{
    if(inst_list.find(op) != inst_list.end())
    {
        return inst_list[op];
    }
    return "";
}

bool checkId(string op)
{
    return (symbTab.find(op) != symbTab.end());
}

void defineVar(string name, int type)
{
    if(checkId(name))
    {
        string err = "La variable: " + name + " ya ha sido declarada anteriormente.";
        yyerror(err.c_str());
    }else
    {
        if(type == INT_T)
        {
            writeCode("iconst_0\nistore " + to_string(variablesNum));
        }
        else if ( type == FLOAT_T)
        {
            writeCode("fconst_0\nfstore " + to_string(variablesNum));
        }
        symbTab[name] = make_pair(variablesNum++,(type_enum)type);
    }
}

string genLabel()
{
    return "L_"+to_string(labelsCount++);
}

string getLabel(int n)
{
    return "L_"+to_string(n);
}

vector<int> * merge(vector<int> *list1, vector<int> *list2)
{
    if(list1 && list2){
        vector<int> *list = new vector<int> (*list1);
        list->insert(list->end(), list2->begin(),list2->end());
        return list;
    }else if(list1)
    {
        return list1;
    }else if (list2)
    {
        return list2;
    }else
    {
        return new vector<int>();
    }
}

void backpatch(vector<int> *lists, int ind)
{
    if(lists)
    for(int i =0 ; i < lists->size() ; i++)
    {
        codeList[(*lists)[i]] = codeList[(*lists)[i]] + getLabel(ind);
    }
}

void writeCode(string x)
{
    codeList.push_back(x);
}

void printCode(void)
{
    for ( int i = 0 ; i < codeList.size() ; i++)
    {
        fout<<codeList[i]<<endl;
    }
}
