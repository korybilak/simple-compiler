#ifndef scanner_
#define scanner_
//ifndef are guards, help prevent errors

//our includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>

int scanner(int destruct);
int listing_placer(int token, int syntax_error, int destruct);
int output_placer(int token);
int file_append();
typedef enum token_types     //struct to define our list of tokens
{
	//todo: add divop and multop, if we decide to use them - tested and working - KB
    BEGIN, END, READ, WRITE, IF, THEN, ELSE, ENDIF, ANDOP, OROP, NOTOP, LESSEQOP, GREQOP, NOTEQOP, ID, INTLITERAL, LPAREN, RPAREN, SEMICOLON, COMMA, COMMENT,
	ASSIGNOP, PLUSOP, MINUSOP, DIVOP, MULTOP, LESSOP, GREATEROP, EQUALOP, WHILE, ENDWHILE, SCANEOF, ERROR, NEWLINE, SPACE, OTHER, MORE=-1
}
token;

// our global variables
extern FILE *input, *output, *list, *tempfile;  //extern extends visibility of variables and files from other parts of the assignment 
extern char inputfile[103], temporary1[103], outputfile[103],buffer[103],linebuffer[103], errorbuffer[103],syntaxBuffer[103];
extern int expectedToken[100];

#endif
