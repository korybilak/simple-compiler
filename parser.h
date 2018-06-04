#ifndef parser_
#define parser_

#include <stdio.h>  //libraries
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>

extern FILE *input, *output, *list, *tempfile;  //extern extends visibility of variables and files from other parts of the assignment 
extern char inputfile[103], temporary1[103], outputfile[103],buffer[103],linebuffer[103], errorbuffer[103], syntaxBuffer[103];

char symbol_table[100][100];                 //array for the symbol table 

static int current_symbol;                   //index for the symbol table

typedef char string[100];

enum expr{IDEXPR, LITERALEXPR, TEMPEXPR};

typedef struct operator        //structure for operators
{
string operator;
string data;
}op_rec;


typedef struct expression      //structure for expressions
{
enum expr kind;
string data;
}expr_rec;


char *_getcwd(char *buffer, int maxlen);

int systemGoal();   // prototype to start reading a program
int match(int token); //prototype to match enumerated tokens
int program();        // prototypes for each nonterminal in the parser's grammars
int stmtList();       //prototype for the statement list
int statement();      //prototype for the statement
int ifTail();         //prototype for the ifTail expression
int idList();         //protoype for the id list
int id();             //prototype for the id
int exprList();       //prototype for the expression list
expr_rec expr();      //the expression record expression
expr_rec expr1(); //used for the condition statement
expr_rec primary();   //the expression record primary
int mathOP();         //prototype for the math operator
int condition();      //protoype for the condition
int notCondition();   //prototype for the not condition
//int logicalCondition(); //prototype for logical condition
int relationalCondition();        //prototype for the relational condition
op_rec logicalOP();               //creates the operator record for the logical operator
op_rec relOP();                   //creates the operator record for the relational operator
op_rec addop(op_rec *result); //calls mathop and procees the op
void generate_to_temp1(expr_rec t, char character, expr_rec l, op_rec op, expr_rec r);    //generates to temp1 file the records and character
void assign1(expr_rec t);   
expr_rec gen_infix1(expr_rec e1, op_rec op, expr_rec e2); //generates an infix expression
expr_rec process_id();          //expression record process id
expr_rec ident();               //identfies a variable
char* get_temp();               //gets a temp value
op_rec process_op();            //process operator action routine that outputs an operator record
expr_rec process_literal();     //process literal action routine that outputs an expression record
expr_rec gen_infix(expr_rec e1, op_rec op, expr_rec e2);    //generates the infix from the expressions and operator
void generate_to_temp(expr_rec t, char character, expr_rec l, op_rec op, expr_rec r);  //generates to the temp file the records and character
void check_id(string s);       //checks the id of the string
void enter(string s);          //enters the string
void generate(string a, string s, string b, string c, string d);     //generates a string
int lookup(string s);          //prototype to look up the symbol in the symbol table
void start();                  //prototype for start action routine
void assign();                 //prototype for the assign action routine
void read_id(expr_rec t);      //prototype for the read id action routine
void write_expr();             //prototype for the write expression action routine
void gen_condition();          //prototype for the generate condition action routine
expr_rec primary1();
void finish();                 //prototype for the finish action routine
int nextToken();



#endif
