#ifndef file_util_
#define file_util_
//ifndef are guards, help prevent errors

//our includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string.h>
// our prototype functions
int getfilename(int argc,char *argv[]);  
int checkfile(int true2);
int openfile(int true);
int copyfile();
int closefile();

// our global variables
extern FILE *input, *output, *list, *tempfile;  //extern extends visibility of variables and files from other parts of the assignment 
extern char inputfile[103], outputfile[103],temporary1[103],buffer[103],linebuffer[103],syntaxBuffer[103];
extern int expectedToken[100];

#endif
